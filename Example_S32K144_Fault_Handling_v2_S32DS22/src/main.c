/************************************************************************************************
* NXP Semiconductors
* (c) Copyright 2020 NXP Semiconductors
* ALL RIGHTS RESERVED.
*************************************************************************************************
*************************************************************************************************
Services performed by NXP in this matter are performed AS IS and without any
warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be held
liable by CUSTOMER for the success of this project.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
CUSTOMER agrees to hold NXP harmless against any and all claims demands
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result
of the advise or assistance supplied CUSTOMER in connection with product,
services or goods supplied under this Agreement.
*************************************************************************************************
* File:             main.c
* Owner:            Daniel Martynek
* Version:          2.0
* Date:             Aug-14-2020
* Classification:   General Business Information
* Brief             Fault handling on S32K14x
*************************************************************************************************
* Detailed Description:
* This example forces certain fault exceptions to shows the exception handling on S32K144 MCU.
* Core registers are read to determine the root cause of the exception.
* Stack frame is read to find the fault instruction.
* -----------------------------------------------------------------------------------------------
* Test HW:         S32144EVB-Q100
* MCU:             S32K144 0N57U
* Debugger:        S32DS 2.2, OpenSDA
* Target:          internal_FLASH
*************************************************************************************************
* Revision History:
* 1.0      May-30-2017   Daniel Martynek
* 2.0      Aug-15-2020   Daniel Martynek
************************************************************************************************/

/************************************************************************************************
* Includes
************************************************************************************************/
#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "fault_exceptions.h"

/************************************************************************************************
* Macros
************************************************************************************************/
#define DIV_BY_ZERO 0
#define UNALIGNED_MEMORY 0
#define NON_THUMB_INS 0
#define UNDEFINED_INS 0
#define UNIMPLEMENTED_MEM 1
#define IMPRECISE_BUS_FAULT 0
#define INS_FETCH_FROM_GPIO 0

/************************************************************************************************
* Function prototypes
************************************************************************************************/
typedef void (*function_pointer)(void);

/************************************************************************************************
* Main Function
************************************************************************************************/
int main(void)
{

    enable_fault_handlers();        // If not set, all fault are handled by HardFault_Handler
    set_fault_handlers_priority();  // priority: MemManage (1), BusFault (1), UsageFault(1)

    /********* USAGE FAULT *********************************************************************/

#if DIV_BY_ZERO
        /* Executed an SDIV or UDIV instruction with a divisor of 0
         * Result: S32_SCB->CFSR[DIVBYZERO]                                        */

            enable_div_by_zero_trap(); // Enables faulting on SDIV or UDIV instruction with a divisor of 0
             uint32_t div = (9/0);

#elif UNALIGNED_MEMORY
        /* An unaligned memory access
         * Result: S32_SCB->CFSR[UNALIGNED]                                                    */

             enable_unaligned_access_trap();
             uint32_t read = *((uint32_t*)0x0007FFFA);
             // or
             //uint32_t read_ = *((uint32_t*)0x20000021);

#elif NON_THUMB_INS
         /* Attempted to execute an instruction that makes illegal use of the EPSR.
         * all branch targets should have bit[0] set, indicating a Thumb opcode.
         * The code below attempt to execute a non-thumb instruction
         * Result: S32_SCB->CFSR[INVSTATE]                                                      */

             function_pointer func_p = (function_pointer) 0x00070000;
             func_p();

#elif UNDEFINED_INS
        /* Branch to an address where no code is located
         * Attempted to execute an undefined instruction
         * Result: S32_SCB->CFSR[UNDEFINSTR]                                                    */

             function_pointer func_p = (function_pointer) 0x00070001;
             func_p();


    /********* BUS FAULT ************************************************************************/

#elif UNIMPLEMENTED_MEM

         /* Access to an unimplemented memory area causes Precise Bus Fault
         * Result: S32_SCB->CFSR[PRECISERR], the illegal address will be stored in BFAR register */

              uint32_t read = *((uint32_t*)0x00080004);
         //   uint32_t read_ = *((uint32_t*)0x1FFF7FFE);


#elif IMPRECISE_BUS_FAULT
        /* Writing to PortD register while the port is not gated.
         * And an attempt to write to a read-only register
         * Both cause Imprecise Bus Fault, the illegal address won't be stored in BFAR register.
         * Result: S32_SCB->CFSR[IMPRECISERR]
         * Unless Write buffer is disabled which forces Imprecise bus faults to be Precise       */

             //disable_write_buffer();           // Forces an imprecise fault to be precise
             PDB0->MOD     = 0x11111111;

    /********* MEMORY MANAGE FAULT ***************************************************************/
#elif INS_FETCH_FROM_GPIO
         /*  Attempted instruction fetch from GPIO controller
         *  Result: S32_SCB->CFSR[IACCVIOL] MMFAR register doesn't hold a valid fault address    */

             function_pointer func_p = (function_pointer) 0x400FF000;
             func_p();
#endif

    while(1)
    {

    }

    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
#if defined (__ghs__)
#pragma ghs nowarning 111
#endif
#if defined (__ICCARM__)
#pragma diag_suppress=Pe111
#endif
    return 0;
}


