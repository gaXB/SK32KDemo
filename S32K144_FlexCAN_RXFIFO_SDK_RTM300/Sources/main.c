/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K1xx
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"
#include "clockMan1.h"

#include "dmaController1.h"

#include "pin_mux.h"

#include <stdint.h>
#include <stdbool.h>

volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */
/******************************************************************************
 * Definitions
 ******************************************************************************/

/* This example is setup to work by default with EVB. To use it with other boards
   please comment the following line
*/

#define EVB

#ifdef EVB
    #define LED_PORT        PORTD
    #define GPIO_PORT       PTD
    #define PCC_INDEX       PCC_PORTD_INDEX
    #define LED0            15U
    #define LED1            16U

    #define BTN_GPIO        PTC
    #define BTN1_PIN        13U
    #define BTN2_PIN        12U
    #define BTN_PORT        PORTC
    #define BTN_PORT_IRQn   PORTC_IRQn
#else
    #define LED_PORT        PORTC
    #define GPIO_PORT       PTC
    #define PCC_INDEX       PCC_PORTC_INDEX
    #define LED0            0U
    #define LED1            1U

    #define BTN_GPIO        PTC
    #define BTN1_PIN        13U
    #define BTN2_PIN        12U
    #define BTN_PORT        PORTC
    #define BTN_PORT_IRQn   PORTC_IRQn
#endif


/* Definition of the TX and RX message buffers depending on the bus role */
uint8_t TX_MAILBOX = (11UL);
uint8_t TX_MSG_ID  = (0x511UL);
#define RX_MAILBOX  (10UL)
#define RX_MSG_ID   (20UL)

/* Definition of power modes indexes, as configured in Power Manager Component
 *  Refer to the Reference Manual for details about the power modes.
 */
#define HSRUN (0u) /* High speed run      */
#define RUN   (1u) /* Run                 */
#define VLPR  (2u) /* Very low power run  */
#define STOP1 (3u) /* Stop option 1       */
#define STOP2 (4u) /* Stop option 2       */
#define VLPS  (5u) /* Very low power stop */


typedef enum
{
    LED0_CHANGE_REQUESTED = 0x00U,
    LED1_CHANGE_REQUESTED = 0x01U
} can_commands_list;

uint8_t ledRequested = (uint8_t)LED0_CHANGE_REQUESTED;
uint8_t rxMBdone=0;
uint8_t rxFIFOdone=0;
uint8_t rxFIFOcompldone=0;
/* ID Filter table */
flexcan_id_table_t filterTable[16]={};
uint16_t IDlist[16] = {0x402,0x403,0x404,0x408,0x410,0x420,0x430,0x440,0x448,0x449,0x44A,0x44B,0x44C,0x44F,0x450,0};
uint16_t IDmask[10] = {0x7FF,0x7FF,0x7FC,0x7F8,0x7F0,0x7F0,0x7F0,0x7F8,0x7FF,0x7FF};

/* Define user receive buffer */
flexcan_msgbuff_t recvBuff1, recvBuff2;

/******************************************************************************
 * Function prototypes
 ******************************************************************************/
void buttonISR(void);
void BoardInit(void);
void GPIOInit(void);
void SendCANData(uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len);
void flexcan0_Callback(uint8_t instance, flexcan_event_type_t eventType,
					   flexcan_state_t *flexcanState);

/******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * Button interrupt handler
 */
void buttonISR(void)
{
    /* Check if one of the buttons was pressed */
    uint32_t buttonsPressed = PINS_DRV_GetPortIntFlag(BTN_PORT) &
                                           ((1 << BTN1_PIN) | (1 << BTN2_PIN));
    bool sendFrame = false;

    if(buttonsPressed != 0)
    {

        /* Set FlexCAN TX value according to the button pressed */
        switch (buttonsPressed)
        {
            case (1 << BTN1_PIN):
                ledRequested = LED0_CHANGE_REQUESTED;
                sendFrame = true;
                /* Clear interrupt flag */
                PINS_DRV_ClearPinIntFlagCmd(BTN_PORT, BTN1_PIN);
                break;
            case (1 << BTN2_PIN):
                ledRequested = LED1_CHANGE_REQUESTED;
                sendFrame = true;
                /* Clear interrupt flag */
                PINS_DRV_ClearPinIntFlagCmd(BTN_PORT, BTN2_PIN);
                break;
            default:
                PINS_DRV_ClearPortIntFlagCmd(BTN_PORT);
                break;
        }

        if (sendFrame)
        {
        	/* Send the information via CAN */
        	SendCANData(TX_MAILBOX, TX_MSG_ID, &ledRequested, 1UL);
        }

    }
}

/*
 * @brief: Send data via CAN to the specified mailbox with the specified message id
 * @param mailbox   : Destination mailbox number
 * @param messageId : Message ID
 * @param data      : Pointer to the TX data
 * @param len       : Length of the TX data
 * @return          : None
 */
void SendCANData(uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len)
{
    /* Set information about the data to be sent
     *  - 1 byte in length
     *  - Standard message ID
     *  - Bit rate switch enabled to use a different bitrate for the data segment
     *  - Flexible data rate enabled
     *  - Use zeros for FD padding
     */
    flexcan_data_info_t dataInfo =
    {
            .data_length = len,
            .msg_id_type = FLEXCAN_MSG_ID_STD,
            .enable_brs  = false,
            .fd_enable   = false,
            .fd_padding  = 0U
    };

    /* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
    FLEXCAN_DRV_ConfigTxMb(INST_CANCOM1, mailbox, &dataInfo, messageId);

    /* Execute send non-blocking */
    FLEXCAN_DRV_Send(INST_CANCOM1, mailbox, &dataInfo, messageId, data);
}
/*
 * @brief : Initialize clocks, pins and power modes
 */
void BoardInit(void)
{

    /* Initialize and configure clocks
     *  -   Setup system clocks, dividers
     *  -   Configure FlexCAN clock, GPIO
     *  -   see clock manager component for more details
     */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                        g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);

    /* Initialize Power Manager
	 * -   See PowerSettings component for more info
	 */
    POWER_SYS_Init(&powerConfigsArr, POWER_MANAGER_CONFIG_CNT, &powerStaticCallbacksConfigsArr, POWER_MANAGER_CALLBACK_CNT);
    /* Set power mode to HSRUN */
    POWER_SYS_SetMode(HSRUN, POWER_MANAGER_POLICY_AGREEMENT);

    /* Initialize pins
     *  -   Init FlexCAN, and GPIO pins
     *  -   See PinSettings component for more info
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
}

/*
 * @brief Function which configures the LEDs and Buttons
 */
void GPIOInit(void)
{
    /* Output direction for LEDs */
    PINS_DRV_SetPinsDirection(GPIO_PORT, (1 << LED1) | (1 << LED0));

    /* Set Output value LEDs */
    PINS_DRV_ClearPins(GPIO_PORT, 1 << LED1);

    /* Setup button pin */
    PINS_DRV_SetPinsDirection(BTN_GPIO, ~((1 << BTN1_PIN)|(1 << BTN2_PIN)));

    /* Setup button pins interrupt */
    PINS_DRV_SetPinIntSel(BTN_PORT, BTN1_PIN, PORT_INT_RISING_EDGE);
    PINS_DRV_SetPinIntSel(BTN_PORT, BTN2_PIN, PORT_INT_RISING_EDGE);

    /* Install buttons ISR */
    INT_SYS_InstallHandler(BTN_PORT_IRQn, &buttonISR, NULL);

    /* Enable buttons interrupt */
    INT_SYS_EnableIRQ(BTN_PORT_IRQn);
}

void flexcan0_Callback(uint8_t instance, flexcan_event_type_t eventType,
					   flexcan_state_t *flexcanState)
{
	(void)flexcanState;
	(void)instance;

	switch(eventType)
	{
	case FLEXCAN_EVENT_RX_COMPLETE:
		{
			rxMBdone = 1;
		}
		break;
	case FLEXCAN_EVENT_RXFIFO_COMPLETE:
	{
		rxFIFOcompldone = 1;

	}
		break;
	case FLEXCAN_EVENT_DMA_COMPLETE:
		{
			rxFIFOdone = 1;
		}
		break;
	case FLEXCAN_EVENT_TX_COMPLETE:
		break;
	default:
		break;
	}
}

int u32TickCount;

void SysTick_Init(void)
{
    S32_SysTick->RVR = 48000ul;
    S32_SysTick->CVR = 0ul;
    S32_SysTick->CSR = 0u;

    S32_SysTick->CSR = S32_SysTick_CSR_TICKINT(1u) | S32_SysTick_CSR_ENABLE(1);
}

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	/* Write your local variable definition here */
	uint16_t id_counter;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
	PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Do the initializations required for this application */
	BoardInit();
	GPIOInit();
	SysTick_Init();
	/*Initialize eDMA driver */
	EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);

	/*Initialize FlexCAN driver */
	FLEXCAN_DRV_Init(INST_CANCOM1, &canCom1_State, &canCom1_InitConfig0);
	/* Install callback function */
	FLEXCAN_DRV_InstallEventCallback(INST_CANCOM1, flexcan0_Callback, NULL);

	/* Set information about the data to be received */
	flexcan_data_info_t dataInfo =
	{
		  .data_length = 1U,
		  .msg_id_type = FLEXCAN_MSG_ID_STD,
		  .enable_brs  = false,
		  .fd_enable   = false,
		  .fd_padding  = 0U
	};

	/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
	FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, RX_MAILBOX, &dataInfo, RX_MSG_ID);

	// Fill id filter table,
#if 0
	for(id_counter=0;id_counter<16;id_counter++)
	{
		filterTable[id_counter].isRemoteFrame = false;
		filterTable[id_counter].isExtendedFrame = (id_counter % 2);
		filterTable[id_counter].id = id_counter +1 ;
	}
	/* Configure RX FIFO ID filter table elements based on filter table defined above*/
		FLEXCAN_DRV_ConfigRxFifo(INST_CANCOM1, FLEXCAN_RX_FIFO_ID_FORMAT_A, filterTable);
		/* set individual masking type */
		FLEXCAN_DRV_SetRxMaskType(INST_CANCOM1, FLEXCAN_RX_MASK_INDIVIDUAL);
		/* first 10 filter items are masked with RXIMR0-RXIMR9 */
		for(id_counter=0;id_counter<10;id_counter++)
		FLEXCAN_DRV_SetRxIndividualMask(INST_CANCOM1, FLEXCAN_MSG_ID_EXT, id_counter, 0xFFFFFFFF);
		/* rest of filter items are masked with RXFGMASK */
		FLEXCAN_DRV_SetRxFifoGlobalMask(INST_CANCOM1, FLEXCAN_MSG_ID_EXT, 0xFFFFFFFF);
		/* set mask affecting MB10 */
		FLEXCAN_DRV_SetRxIndividualMask(INST_CANCOM1, FLEXCAN_MSG_ID_EXT, RX_MAILBOX, 0xFFFFFFFF);
#else
	for(id_counter=0;id_counter<16;id_counter++)
	{
		filterTable[id_counter].isRemoteFrame = false;
		filterTable[id_counter].isExtendedFrame = false;
		filterTable[id_counter].id = IDlist[id_counter] ;
	}
	/* Configure RX FIFO ID filter table elements based on filter table defined above*/
	FLEXCAN_DRV_ConfigRxFifo(INST_CANCOM1, FLEXCAN_RX_FIFO_ID_FORMAT_A, filterTable);
	/* set individual masking type */
	FLEXCAN_DRV_SetRxMaskType(INST_CANCOM1, FLEXCAN_RX_MASK_INDIVIDUAL);
	for(id_counter=0;id_counter<10;id_counter++)
		FLEXCAN_DRV_SetRxIndividualMask(INST_CANCOM1, FLEXCAN_MSG_ID_STD, id_counter, 0xC0000000|IDmask[id_counter]);
	/* rest of filter items are masked with RXFGMASK */
	FLEXCAN_DRV_SetRxFifoGlobalMask(INST_CANCOM1, FLEXCAN_MSG_ID_STD, 0xC0000000|0x7FF);

	/* set mask affecting MB10 */
	FLEXCAN_DRV_SetRxIndividualMask(INST_CANCOM1, FLEXCAN_MSG_ID_EXT, RX_MAILBOX, 0xFFFFFFFF);

#endif



	/* Start receiving data in RX_MAILBOX. */
	FLEXCAN_DRV_Receive(INST_CANCOM1, RX_MAILBOX, &recvBuff1);
	/* Start receiving data in RX_RXFIFO. */
	FLEXCAN_DRV_RxFifo(INST_CANCOM1,&recvBuff2);

	while(1)
	{
		if(FLEXCAN_DRV_GetTransferStatus(INST_CANCOM1, TX_MAILBOX) == STATUS_SUCCESS)
		{
			SendCANData(TX_MAILBOX, TX_MSG_ID, &ledRequested, 1);
		}

//		if(rxMBdone)		// if message was received into regular MB10
//		{
//			rxMBdone = 0;
//
//			if(recvBuff1.msgId == RX_MSG_ID)
//			{
//				/* Toggle output value LED1 */
//				PINS_DRV_TogglePins(GPIO_PORT, (1 << LED0));
//
//				/* enable receiving data in RX_MAILBOX again */
//				FLEXCAN_DRV_Receive(INST_CANCOM1, RX_MAILBOX, &recvBuff1);
//			}
//
//		}
//		if(rxFIFOdone)		// if message was received into RXFIFO
//		{
//			rxFIFOdone = 0;
//
//			/* process data from recvBuff2 */
//
//			/* Toggle output value LED0 */
//			PINS_DRV_TogglePins(GPIO_PORT, (1 << LED1));
//			/* enable receiving data in RX FIFO again */
//			FLEXCAN_DRV_RxFifo(INST_CANCOM1,&recvBuff2);
//
//
//		}

	}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/



/* SysTick IRQ handler */
void SysTick_Handler(void)
{
    /* Variable that stores the number of WDG PAL Refresh */
    u32TickCount++;
}

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP S32K series of microcontrollers.
**
** ###################################################################
*/
