/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "system_S32K144.h"
#include "timeout.h"
#include "comm.h"
#include "clock.h"

#define bMETHOD 0

/* Bootloader definitions */
/* Start address for the application received by the bootloader
 * application vector table should start at this address
 * */
#define APP_START_ADDRESS	0x00002000

/* Global variables */
uint8_t boot_from_comm = 0;				/* Used to signal activity on the comm channel */

typedef void(*user_app_fnptr)(void);
user_app_fnptr      *p_jump_to_app;             // Function pointer to the user application.

/* Prototype */
#if (bMETHOD==0)
	static void JumpToUserApplication( unsigned int userSP,  unsigned int userStartup);
#else
	static void JumpToUserApplication(void);
	//static void reset_clock(void);
	static void MSR_MSP(uint32_t addr);
#endif


/* Main Application*/
int main(void)
{

	/* Initialize clock */
	clock_initi();

	/* Initialize communication interfaces */
	init_comm();

	/* Initialize timeout */
	init_timeout();

	/* Check if boot start has been received or timeout occurred */
	do{
		uint8_t word_received = comm_status_rx();
		if(word_received){
			boot_from_comm = 1;
#if (bMETHOD!=0)
			disable_timeout();
#endif
			comm_download_app();
#if (bMETHOD!=0)
			//Reset immediately after updated
			//	__asm__ ("NOP");
			SystemSoftwareReset();
#endif
		}
	} while((!timeout()) & (!boot_from_comm));

	/* Disable all systems and leave device as if coming out of reset */
#if (bMETHOD==0)
	disable_timeout();
#endif
	disable_comm();
	reset_clock();

	/* Check if a valid application is loaded and jump to it */
#if (bMETHOD==0)
	  JumpToUserApplication(*((uint32_t*)APP_START_ADDRESS), *((uint32_t*)(APP_START_ADDRESS + 4)));
#else
	  JumpToUserApplication();
#endif

    /* Should never return from application code */
    for (;;) {};
    /* Never leave main */
    return 0;
}

/**
 * Used to jump to the entry point of the user application
 * The Vector table of the user application must be located at 0x1000
 *
 * */
#if (bMETHOD==0)
	void JumpToUserApplication( unsigned int userSP,  unsigned int userStartup)
	{
		/* Check if Entry address is erased and return if erased */
		if(userSP == 0xFFFFFFFF){
			return;
		}

		/* Set up stack pointer */
		__asm("msr msp, r0");
		__asm("msr psp, r0");

		/* Relocate vector table */
		S32_SCB->VTOR = (uint32_t)APP_START_ADDRESS;

		/* Jump to application PC (r1) */
		__asm("mov pc, r1");
	}
#else
	void JumpToUserApplication(void)
	{
		/* Check if Entry address is erased and return if erased */
		if(*(uint32_t*)APP_START_ADDRESS == 0xFFFFFFFF){
			return;
		}
		//reset_clock();
		//p_jump_to_app = ((user_app_fnptr*)APP_START_ADDRESS) + 1U; // Point to the start reset vector for the  application.
		__asm("cpsid i");                                            // Disable interrupts
		p_jump_to_app = ((uint32_t)APP_START_ADDRESS+4);             // Point to the start reset vector for the  application.
		S32_SCB->VTOR = (uint32_t)APP_START_ADDRESS;                 // Update the vector table to the reset vector of the application.
		// __asm("dsb");                                             //Complete all explicit memory accesses.
		MSR_MSP(*(volatile uint32_t*)APP_START_ADDRESS); ;           //Set stack for the application
		(*p_jump_to_app)();                                          //Jump to application
	}
	static void MSR_MSP(uint32_t addr)
	{
	  __asm("msr msp, r0");
	}
#endif


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
