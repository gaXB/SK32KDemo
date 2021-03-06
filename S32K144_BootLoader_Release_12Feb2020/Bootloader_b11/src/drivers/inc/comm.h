/*
 * comm.h
 *
 *  Created on: Oct 31, 2016
 *      Author: B52932
 */

#ifndef SOURCES_DRIVERS_INC_COMM_H_
#define SOURCES_DRIVERS_INC_COMM_H_

/* Define communication interfaces to use, 0-> Disable 1-> Enable */
#define UART_COMM 		1
#define SPI_COMM		0

#include "pin_config.h"
#include "mem_man.h"
#include "common.h"

/* Error codes */
#define ERR_OK 	0x41
#define ERR_CRC	0x45

enum comms{
	NONE = 0,
	UART = 1,
	SPI = 2
};

/* Add routines needed by UART communication interface and configure it */
#if UART_COMM
	#include "uart.h"
	#define UART_PORT	LPUART1
	#define SYSCLK		(48000000/2)
	#define UART_BAUD	19200
#endif


/* Prototypes */
void init_comm(void);
void disable_comm(void);
uint8_t comm_status_rx(void);
void comm_download_app(void);
void comm_get_phrase(BootPhraseStruct *BP);

#endif /* SOURCES_DRIVERS_INC_COMM_H_ */
