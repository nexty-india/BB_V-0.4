/**
 *******************************************************************************
 * @file        a31m22x_gpio.h
 * @author      ABOV R&D Division
 * @brief       
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#ifndef _A31M22X_GPIO_H_
#define _A31M22X_GPIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "a31m22x.h"
#include "a31m22x_driver_common.h"

	
/**
 * GPIO access must be enabled before chaning any register values.
 */
static __INLINE void GPIO_Access_Enable(void)
{
    PORTEN->EN = 0x15;
    PORTEN->EN = 0x51;
}

/**
 * GPIO access must be disabled to protect the settings.
 */
static __INLINE void GPIO_Access_Disable(void)
{
    PORTEN->EN = 0x00;
}


/* PAMR */
#define PA0_MUX_PA0                     (0)
#define PA0_MUX_T2IO                    (1)
#define PA0_MUX_AN0                     (7)

#define PA1_MUX_PA1                     (0)
#define PA1_MUX_T3IO                    (1)
#define PA1_MUX_CPOUT                (4)
#define PA1_MUX_AN1                     (7)

#define PA2_MUX_PA2                     (0)
#define PA2_MUX_SS                      (1)
#define PA2_MUX_WDTO                 (2)
#define PA2_MUX_CPA                     (7)
#define PA2_MUX_AN2                     (7)

#define PA3_MUX_PA3                     (0)
#define PA3_MUX_SCK                     (1)
#define PA3_MUX_STBO                    (2)
#define PA3_MUX_CPRE                   (7)
#define PA3_MUX_AN3                     (7)

#define PA4_MUX_PA4                     (0)
#define PA4_MUX_T0IO                    (3)
#define PA4_MUX_AIP0                    (7)
#define PA4_MUX_CPB                     (7)
#define PA4_MUX_AN4                     (7)

#define PA5_MUX_PA5                     (0)
#define PA5_MUX_T1IO                    (3)
#define PA5_MUX_AIN0                    (7)
#define PA5_MUX_CPC                     (7)
#define PA5_MUX_AN5                     (7)

#define PA6_MUX_PA6                     (0)
#define PA6_MUX_T0IO                    (1)
#define PA6_MUX_MOSI                    (2)
#define PA6_MUX_T2IO                    (3)
#define PA6_MUX_AO0                     (7)
#define PA6_MUX_AN6                     (7)

#define PA7_MUX_PA7                     (0)
#define PA7_MUX_T1IO                    (1)
#define PA7_MUX_MISO                    (2)
#define PA7_MUX_T3IO                    (3)
#define PA7_MUX_AIP1                    (7)
#define PA7_MUX_AN7                     (7)

#define PA8_MUX_PA8                     (0)
#define PA8_MUX_T2IO                    (1)
#define PA8_MUX_T0IO                    (2)
#define PA8_MUX_AN8                     (7)
#define PA8_MUX_AIN1                    (7)

#define PA9_MUX_PA9                     (0)
#define PA9_MUX_T3IO                    (1)
#define PA9_MUX_T1IO                    (2)
#define PA9_MUX_AO1                     (7)
#define PA9_MUX_AN9                     (7)

#define PA10_MUX_PA10                   (0)
#define PA10_MUX_AN10                   (7)

#define PA11_MUX_PA11                   (0)
#define PA11_MUX_AN11                   (7)

#define PA12_MUX_PA12                   (0)
#define PA12_MUX_T0IO                   (1)
#define PA12_MUX_AO2                    (7)

#define PA13_MUX_PA13                   (0)
#define PA13_MUX_T1IO                   (1)

#define PA14_MUX_PA14                   (0)
#define PA14_MUX_T2IO                   (1)

#define PA15_MUX_PA15                   (0)
#define PA15_MUX_T3IO                   (1)

/* PBMR */

#define PB0_MUX_PB0                     (0)
#define PB0_MUX_MPWMUH                  (1)
#define PB0_MUX_SS                      (2)

#define PB1_MUX_PB1                     (0)
#define PB1_MUX_MPWMUL                  (1)
#define PB1_MUX_SCK                   	(2)

#define PB2_MUX_PB2                     (0)
#define PB2_MUX_MPWMVH                  (1)
#define PB2_MUX_MOSI                  	(2)

#define PB3_MUX_PB3                     (0)
#define PB3_MUX_MPWMVL                  (1)
#define PB3_MUX_MISO                   	(2)

#define PB4_MUX_PB4                     (0)
#define PB4_MUX_MPWMWH                  (1)

#define PB5_MUX_PB5                     (0)
#define PB5_MUX_MPWMWL                  (1)

#define PB6_MUX_PB6                     (0)
#define PB6_MUX_PRTIN                   (1)
#define PB6_MUX_T0IO                    (3)

#define PB7_MUX_PB7                     (0)
#define PB7_MUX_OVIN                    (1)
#define PB7_MUX_CLKO                    (2)
#define PB7_MUX_T1IO                    (3)

/* PCMR */

#define PC0_MUX_PC0                     (0)
#define PC0_MUX_SWCLK                   (1)
#define PC0_MUX_RXD1                    (2)

#define PC1_MUX_PC1                     (0)
#define PC1_MUX_SWDIO                   (1)
#define PC1_MUX_TXD1                    (2)

#define PC2_MUX_PC2                     (0)

#define PC3_MUX_PC3                     (0)

#define PC4_MUX_PC4                     (0)
#define PC4_MUX_T0IO                    (2)

#define PC5_MUX_PC5                     (0)
#define PC5_MUX_RXD1                    (1)
#define PC5_MUX_T1IO                    (2)

#define PC6_MUX_PC6                     (0)
#define PC6_MUX_TXD1                    (1)
#define PC6_MUX_T2IO                    (2)

#define PC7_MUX_PC7                     (0)
#define PC7_MUX_SCL                     (1)
#define PC7_MUX_T3IO                    (2)
#define PC7_MUX_RXD1                    (3)
#define PC7_MUX_SS                      (4)
#define PC7_MUX_AIP2                    (7)

#define PC8_MUX_PC8                     (0)
#define PC8_MUX_SDA                     (1)
#define PC8_MUX_T1IO                    (2)
#define PC8_MUX_TXD1                    (3)
#define PC8_MUX_SCK                     (4)
#define PC8_MUX_AIN2                    (7)

#define PC9_MUX_PC9                     (0)
#define PC9_MUX_CLKO                    (1)

#define PC10_MUX_PC10                   (0)
#define PC10_MUX_nRESET                 (1)

#define PC11_MUX_PC11                   (0)
#define PC11_MUX_BOOT                   (1)
#define PC11_MUX_T0IO                   (2)

#define PC12_MUX_PC12                   (0)
#define PC12_MUX_T3IO                   (1)
#define PC12_MUX_XIN                    (7)

#define PC13_MUX_PC13                   (0)
#define PC13_MUX_T2IO                   (1)
#define PC13_MUX_XOUT                   (7)

#define PC14_MUX_PC14                   (0)
#define PC14_MUX_RXD0                   (1)
#define PC14_MUX_CLKO                   (2)
#define PC14_MUX_OVIN                   (3)
#define PC14_MUX_MOSI                   (4)

#define PC15_MUX_PC15                   (0)
#define PC15_MUX_TXD0                   (1)
#define PC15_MUX_PRTIN                  (3)
#define PC15_MUX_MISO                   (4)

#define PD0_MUX_PD0                     (0)
#define PD0_MUX_SS                      (1)

#define PD1_MUX_PD1                     (0)
#define PD1_MUX_SCK                     (1)

#define PD2_MUX_PD2                     (0)
#define PD2_MUX_MOSI                    (1)
#define PD2_MUX_SCL                     (2)
#define PD2_MUX_RXD0                    (4)
#define PD2_MUX_SXOUT                   (7)

#define PD3_MUX_PD3                     (0)
#define PD3_MUX_MISO                    (1)
#define PD3_MUX_SDA                   (2)
#define PD3_MUX_TXD0                   (4)
#define PD3_MUX_SXIN                   (7)

/**
 * GPIO port number
 */
enum gpio_port
{
    PORTA       = 0,
    PORTB       = 1,
    PORTC       = 2,
	  PORTD       = 3,
    PORT_MAX    = 4
};

/**
 * GPIO pin number
 */
enum gpio_pin
{
    PIN0    = 0,
    PIN1    = 1,
    PIN2    = 2,
    PIN3    = 3,
    PIN4    = 4,
    PIN5    = 5,
    PIN6    = 6,
    PIN7    = 7,
    PIN8    = 8,
    PIN9    = 9,
    PIN10   = 10,
    PIN11   = 11,
    PIN12   = 12,
    PIN13   = 13,
    PIN14   = 14,
    PIN15   = 15,
    PIN_MAX = 16,
};

/**
 * GPIO mode
 */
enum gpio_mode
{
    GPIO_MODE_INPUT     = 0,                /** intput */
    GPIO_MODE_OUTPUT    = 1,                /** output */
    GPIO_MODE_FUNC      = 2,                /** alternative function */
    GPIO_MODE_MAX       = 3,                /** Mode Max */
};

/**
 * GPIO output mode configuration
 */
enum gpio_output_type
{
    GPIO_OUTPUT_PUSH_PULL   = 0,            /**< push pull */
    GPIO_OUTPUT_OPEN_DRAIN  = 1,            /**< open drain */
};

/**
 * GPIO pull up down configuration
 */
enum gpio_pull
{
    GPIO_PULL_DISABLE   = 0,                /**< pull up pull down not used */
    GPIO_PULL_UP        = 2,                /**< pull up */
    GPIO_PULL_DOWN      = 3,                /**< pull down */
};

/**
 * GPIO interrupt triger control
 */
enum gpio_irq_trig
{
    GPIO_IRQ_TRIG_LEVEL = 0x01,             /**< level trigger */
    GPIO_IRQ_TRIG_EDGE  = 0x03,             /**< edge trigger */
};

/**
 * GPIO interrupt mode control
 */
enum gpio_irq_mode
{
    GPIO_IRQ_LOW_OR_FALLING     = 0x01,     /**< low level or falling edge */
    GPIO_IRQ_HIGH_OR_RISING     = 0x02,     /**< high level or rising edge */
    GPIO_IRQ_FALLING_AND_RISING = 0x03,     /**< falling/rising */
};

/**
 * GPIO strength
 */
enum gpio_strength
{
    GPIO_STRENGTH_LEVEL_1   = 0,            /**< strength level 1 */
    GPIO_STRENGTH_LEVEL_2   = 1,            /**< strength level 2 */
};

/**
 * GPIO debounce clock configuration
 */
enum gpio_dbc_clk_src
{
    GPIO_DBC_CLK_SRC_LSI,               /**< debounce clock from LSI */
    GPIO_DBC_CLK_SRC_LSE,               /**< debounce clock from LSE */
    GPIO_DBC_CLK_SRC_MCLK,              /**< debounce clock from MCLK */
    GPIO_DBC_CLK_SRC_HSI,               /**< debounce clock from HSI */
    GPIO_DBC_CLK_SRC_HSE,               /**< debounce clock from HSE */
    GPIO_DBC_CLK_SRC_PLL,               /**< debounce clock from PLL */
};


/**
 * number of irqs to support.
 * If an application requires more than this number of GPIO inputs
 * to be used as interrupt pins, then increase the number as much
 * as needed.
 */
#ifndef CONFIG_GPIO_NUM_IRQ
#define CONFIG_GPIO_NUM_IRQ    4
#endif

/**
 *******************************************************************************
 * @brief       GPIO interrupt callback function type
 * @param[in]   context context provided during initialization
 ******************************************************************************/
typedef void (*gpio_irq_handler_t)(void *context);

/**
 *******************************************************************************
 * @brief       Initialize GPIO.
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_Init(void);

/**
 *******************************************************************************
 * @brief       Set mode.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   mode mode to be used
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetMode(enum gpio_port port, enum gpio_pin pin, enum gpio_mode mode);

/**
 *******************************************************************************
 * @brief       Set function.
 *              GPIO must be configured as function first.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   func function to be used instead of input/output
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetFunction(enum gpio_port port, enum gpio_pin pin, uint32_t func);

/**
 *******************************************************************************
 * @brief       Set output type
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   type output type
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetOutput(enum gpio_port port, enum gpio_pin pin, enum gpio_output_type type);

/**
 *******************************************************************************
 * @brief       Set pull up or down
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   pull pull up/down/none
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetPull(enum gpio_port port, enum gpio_pin pin, enum gpio_pull pull);

/**
 *******************************************************************************
 * @brief       Set strength
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   strength strength level
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetStrength(enum gpio_port port, enum gpio_pin pin, enum gpio_strength strength);

/**
 *******************************************************************************
 * @brief       Set GPIO Debouncing.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   enable 1 to enable, 0 to disable
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetDebounce(enum gpio_port port, enum gpio_pin pin, uint8_t enable);

/**
 *******************************************************************************
 * @brief       Set GPIO Debouncing Clock
 * @param[in]   port port number
 * @param[in]   clk_src debounce clock source
 * @param[in]   clk_div debounce clock divider
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetDebounceClock(enum gpio_port port, enum gpio_dbc_clk_src clk_src,
                                  uint8_t clk_div);

/**
 *******************************************************************************
 * @brief       Enable interrupt.
 *              Interrupt are configured per port, interrupt priority can be
 *              set only once for each port.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   trig interrupt trigger
 * @param[in]   mode interrupt mode
 * @param[in]   irq_prio interrupt priority
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_EnableIRQ(enum gpio_port port, enum gpio_pin pin,
                           enum gpio_irq_trig trig,
                           enum gpio_irq_mode mode,
                           uint8_t irq_prio);

/**
 *******************************************************************************
 * @brief       Disable interrupt.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_DisableIRQ(enum gpio_port port, enum gpio_pin pin);

/**
 *******************************************************************************
 * @brief       Set GPIO callback function to receive event.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[in]   handler callback function to receive event
 * @param[in]   context caller's context
 * @return      driver error code
 * @return      ::DRIVER_ERROR_NO_RESOURCE no more gpio irq can be set.
 *              See ::CONFIG_GPIO_NUM_IRQ
 ******************************************************************************/
int32_t HAL_GPIO_SetIRQHandler(enum gpio_port port, enum gpio_pin pin, gpio_irq_handler_t handler, void *context);

/**
 *******************************************************************************
 * @brief       Set (high) the value of the specific port/pin.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_SetPin(enum gpio_port port, enum gpio_pin pin);

/**
 *******************************************************************************
 * @brief       Clear (low) the value of the specific port/pin.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_ClearPin(enum gpio_port port, enum gpio_pin pin);

/**
 *******************************************************************************
 * @brief       Read the value of the specific port/pin.
 * @param[in]   port port number
 * @param[in]   pin pin number
 * @param[out]  value value of the pin
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_ReadPin(enum gpio_port port, enum gpio_pin pin, uint32_t *value);

/**
 *******************************************************************************
 * @brief       Write the value for the whole GPIO port.
 *              It only sets the value for the pins configured as output.
 *              Other bits are not valid.
 * @param[in]   port port number
 * @param[in]   value port value
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_WritePort(enum gpio_port port, uint32_t value);

/**
 *******************************************************************************
 * @brief       Read the value for the whole GPIO port.
 *              It only returns the value for the pins configured as input.
 *              Other bits are not valid.
 * @param[in]   port port number
 * @param[out]  value port value
 * @return      driver error code
 ******************************************************************************/
int32_t HAL_GPIO_ReadPort(enum gpio_port port, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* _A31M22X_GPIO_H_ */

/** @} */
/** @} */

