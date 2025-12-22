;/**
; *******************************************************************************
; * @file        a31m22x_startup.s
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
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp                    ; Top of Stack
                DCD     Reset_Handler                   ; Reset Handler
                DCD     NMI_Handler                     ; NMI Handler
                DCD     HardFault_Handler               ; Hard Fault Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     SVC_Handler                     ; SVCall Handler
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     PendSV_Handler                  ; PendSV Handler
                DCD     SysTick_Handler                 ; SysTick Handler

; External Interrupts
                DCD     LVI_IRQHandler                  ; IRQ0
                DCD     SYSCLKFAIL_IRQHandler           ; IRQ1
                DCD     HSEFAIL_IRQHandler              ; IRQ2
                DCD     LSEFAIL_IRQHandler              ; IRQ3
                DCD     WDT_IRQHandler                  ; IRQ4
                DCD     FRT_IRQHandler                  ; IRQ5
                DCD     CFMC_IRQHandler                 ; IRQ6
                DCD     TIMER0_IRQHandler               ; IRQ7
                DCD     TIMER1_IRQHandler               ; IRQ8
                DCD     TIMER2_IRQHandler               ; IRQ9
                DCD     TIMER3_IRQHandler               ; IRQ10
                DCD     GPIOA_IRQHandler                ; IRQ11
                DCD     GPIOB_IRQHandler                ; IRQ12
                DCD     GPIOC_IRQHandler                ; IRQ13
                DCD     GPIOD_IRQHandler                ; IRQ14
                DCD     MPWMPROT_IRQHandler             ; IRQ15
                DCD     MPWMOV_IRQHandler               ; IRQ16
                DCD     MPWM_IRQHandler                 ; IRQ17
                DCD     SPI_IRQHandler                  ; IRQ18
                DCD     I2C_IRQHandler                  ; IRQ19
                DCD     UART0_IRQHandler                ; IRQ20
                DCD     UART1_IRQHandler                ; IRQ21
                DCD     ADC_IRQHandler                  ; IRQ22
                DCD     CRC_IRQHandler                  ; IRQ23
                DCD     SRAM_IRQHandler                 ; IRQ24
                DCD     CMP_IRQHandler                  ; IRQ25
                AREA    |.text|, CODE, READONLY

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler                   [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP
; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler     PROC
                EXPORT  NMI_Handler                     [WEAK]
                B       .
                ENDP
HardFault_Handler PROC
                EXPORT  HardFault_Handler               [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                     [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                  [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                 [WEAK]
                B       .
                ENDP

; External Interrupt Handlers
NULL_IRQHandler PROC
                EXPORT  LVI_IRQHandler                  [WEAK]
                EXPORT  SYSCLKFAIL_IRQHandler           [WEAK]
                EXPORT  HSEFAIL_IRQHandler              [WEAK]
                EXPORT  LSEFAIL_IRQHandler                  [WEAK]
                EXPORT  WDT_IRQHandler                  [WEAK]
                EXPORT  FRT_IRQHandler                  [WEAK]
                EXPORT  CFMC_IRQHandler                 [WEAK]
                EXPORT  TIMER0_IRQHandler               [WEAK]
                EXPORT  TIMER1_IRQHandler               [WEAK]
                EXPORT  TIMER2_IRQHandler               [WEAK]
                EXPORT  TIMER3_IRQHandler               [WEAK]
                EXPORT  GPIOA_IRQHandler                [WEAK]
                EXPORT  GPIOB_IRQHandler                [WEAK]
                EXPORT  GPIOC_IRQHandler                [WEAK]
                EXPORT  GPIOD_IRQHandler                [WEAK]
                EXPORT  MPWMPROT_IRQHandler              [WEAK]
                EXPORT  MPWMOV_IRQHandler               [WEAK]
                EXPORT  MPWM_IRQHandler                 [WEAK]
                EXPORT  SPI_IRQHandler                  [WEAK]
                EXPORT  I2C_IRQHandler                  [WEAK]
                EXPORT  UART0_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  CRC_IRQHandler                  [WEAK]
                EXPORT  SRAM_IRQHandler                 [WEAK]
                EXPORT  CMP_IRQHandler                  [WEAK]
LVI_IRQHandler                                          ; IRQ0
SYSCLKFAIL_IRQHandler                                   ; IRQ1
HSEFAIL_IRQHandler                                      ; IRQ2
LSEFAIL_IRQHandler                                      ; IRQ3
WDT_IRQHandler                                          ; IRQ4
FRT_IRQHandler                                          ; IRQ5
CFMC_IRQHandler                                         ; IRQ6
TIMER0_IRQHandler                                       ; IRQ7
TIMER1_IRQHandler                                       ; IRQ8
TIMER2_IRQHandler                                       ; IRQ9
TIMER3_IRQHandler                                       ; IRQ10
GPIOA_IRQHandler                                        ; IRQ11
GPIOB_IRQHandler                                        ; IRQ12
GPIOC_IRQHandler                                        ; IRQ13
GPIOD_IRQHandler                                        ; IRQ14
MPWMPROT_IRQHandler                                     ; IRQ15
MPWMOV_IRQHandler                                       ; IRQ16
MPWM_IRQHandler                                         ; IRQ17
SPI_IRQHandler                                          ; IRQ18
I2C_IRQHandler                                          ; IRQ19
UART0_IRQHandler                                        ; IRQ20
UART1_IRQHandler                                        ; IRQ21
ADC_IRQHandler                                          ; IRQ22
CRC_IRQHandler                                          ; IRQ23
SRAM_IRQHandler                                         ; IRQ24
CMP_IRQHandler                                          ; IRQ25
                B       .
                ENDP

                ALIGN
; User Initial Stack & Heap
                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
