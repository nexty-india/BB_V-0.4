;/**
; *******************************************************************************
; * @file        a31m22x_startup_iar.s
; * @author      ABOV R&D Division
; * @brief       
; *
; * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
; *
; * This file is licensed under terms that are found in the LICENSE file
; * located at Document directory.
; * If this file is delivered or shared without applicable license terms,
; * the terms of the BSD-3-Clause license shall be applied.
; * Reference: https://opensource.org/licenses/BSD-3-Clause
; ******************************************************************************/


; <h> Stack Configuration
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size


       DATA
__vector_table
                DCD     sfe(CSTACK)     						; Top of Stack
                DCD     Reset_Handler             	; Reset Handler
                DCD     NMI_Handler              	; NMI Handler
                DCD     HardFault_Handler         	; Hard Fault Handler
                DCD     0              			; Reserved
                DCD     0         			; Reserved
                DCD     0              			; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     SVC_Handler               	; SVCall Handler
                DCD     0                		; Reserved
                DCD     0                         	; Reserved
                DCD     PendSV_Handler           		; PendSV Handler
                DCD     SysTick_Handler           	; SysTick Handler

                ; External Interrupts
				DCD		LVD_IRQHandler				;  0: LVD
				DCD		SYSCLKFAIL_IRQHandler		        ;  1: SYSCLKFAIL
				DCD		HSEFAIL_IRQHandler			;  2: HSEFAIL
				DCD		LSEFAIL_IRQHandler                      ;  3: LSEFAIL
				DCD		WDT_IRQHandler				;  4: WDT
				DCD		FRT_IRQHandler				;  5: FRT
				DCD		CFMC_IRQHandler				;  6: CFMC
				DCD		TIMER0_IRQHandler			;  7: TIMER0
				DCD		TIMER1_IRQHandler			;  8: TIMER1
				DCD		TIMER2_IRQHandler			;  9: TIMER2
				DCD		TIMER3_IRQHandler			; 10: TIMER3
				DCD		GPIOA_IRQHandler			; 11: GPIOA
				DCD		GPIOB_IRQHandler			; 12: GPIOB
				DCD		GPIOC_IRQHandler			; 13: GPIOC
				DCD		GPIOD_IRQHandler			; 14: GPIOD
				DCD		MPWMPRT_IRQHandler			; 15: MPWMPRT
				DCD		MPWMOV_IRQHandler			; 16: MPWMOV
				DCD		MPWM_IRQHandler				; 17: MPWM
				DCD		SPI_IRQHandler				; 18: SPI
				DCD		I2C_IRQHandler				; 19: I2C
				DCD		UART0_IRQHandler			; 20: UART0
				DCD		UART1_IRQHandler			; 21: UART1
				DCD		ADC_IRQHandler				; 22: ADC
				DCD		CRC_IRQHandler				; 23: CRC
				DCD		SRAM_IRQHandler				; 24: SRAM
				DCD		CMP_IRQHandler				; 25: CMP
__Vectors_End
__Vectors       EQU   __vector_table
__Vectors_Size  EQU     __Vectors_End - __Vectors

        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)		
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler     
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler     
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

       PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LVD_IRQHandler
        B LVD_IRQHandler
        
        PUBWEAK SYSCLKFAIL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SYSCLKFAIL_IRQHandler
        B SYSCLKFAIL_IRQHandler
    
        PUBWEAK HSEFAIL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
HSEFAIL_IRQHandler
        B HSEFAIL_IRQHandler

	PUBWEAK LSEFAIL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LSEFAIL_IRQHandler
        B LSEFAIL_IRQHandler
		
        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_IRQHandler
        B WDT_IRQHandler
        
        PUBWEAK FRT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FRT_IRQHandler
        B FRT_IRQHandler

        PUBWEAK CFMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CFMC_IRQHandler
        B CFMC_IRQHandler
 
         PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler
 
          PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler
        
          PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler
    
          PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

         PUBWEAK GPIOA_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA_IRQHandler
        B GPIOA_IRQHandler

         PUBWEAK GPIOB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB_IRQHandler
        B GPIOB_IRQHandler

         PUBWEAK GPIOC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC_IRQHandler
        B GPIOC_IRQHandler

         PUBWEAK GPIOD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD_IRQHandler
        B GPIOD_IRQHandler
        
         PUBWEAK MPWMPRT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MPWMPRT_IRQHandler
        B MPWMPRT_IRQHandler
        
         PUBWEAK MPWMOV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MPWMOV_IRQHandler
        B MPWMOV_IRQHandler
        
         PUBWEAK MPWM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MPWM_IRQHandler
        B MPWM_IRQHandler
        
         PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI_IRQHandler
        B SPI_IRQHandler
                
         PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C_IRQHandler
        B I2C_IRQHandler

         PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_IRQHandler
        B UART0_IRQHandler

         PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART1_IRQHandler
        B UART1_IRQHandler
        
         PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B ADC_IRQHandler

         PUBWEAK CRC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRC_IRQHandler
        B CRC_IRQHandler
        
         PUBWEAK SRAM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SRAM_IRQHandler
        B SRAM_IRQHandler
        
         PUBWEAK CMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CMP_IRQHandler
        B CMP_IRQHandler
        END