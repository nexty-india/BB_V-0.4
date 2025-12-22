/**
 *******************************************************************************
 * @file        a31m22x_pcu.c
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


/* Includes ------------------------------------------------------------------- */
#include "A31M22x_pcu.h"

/**********************************************************************//**
 * @brief 		Configure pin function
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	pin_no		Pin number, should be: 0..15
 * @param[in]	func 	Function mode, should be:
 * 					- FUNC0		:Function 0
 * 					- FUNC1		:Function 1
 * 					- FUNC2		:Function 2
 * 					- FUNC3		:Function 3
 * 					- FUNC4		:Function 4
 * 					- FUNC5		:Function 5
 * @return		None
 **********************************************************************/
void HAL_GPIO_ConfigFunction(PCU_Type *PCx, uint8_t pin_no, uint32_t func)
{
	uint8_t pin_offset; 
	uint32_t reg_val; 

	
	if (pin_no > 7)
	{
		pin_no = pin_no - 8;
		
		pin_offset = (pin_no << 2);
		
		//------------------------------------------------------------------------------
		// MR
		//------------------------------------------------------------------------------

		reg_val = PCx->MR2;
		reg_val &= ~(PCU_MR_FUNC_Msk << pin_offset); 
		reg_val |= (func << pin_offset); 

		PCx->MR2=reg_val;	
	}
	else
	{
		pin_offset = (pin_no << 2);
		
		//------------------------------------------------------------------------------
		// MR
		//------------------------------------------------------------------------------
		reg_val = PCx->MR1;
		reg_val &= ~(PCU_MR_FUNC_Msk << pin_offset); 
		reg_val |= (func << pin_offset); 
	
		PCx->MR1=reg_val;
	}
	
}


/**********************************************************************//**
 * @brief 		Configure pin mode
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	pin_no		Pin number, should be: 0..15
 * @param[in]	dir_type	Pin mode, should be:
 * 					- PUSH_PULL_OUTPUT   	:0
 * 					- OPEN_DRAIN_OUTPUT 	:1
 * 					- INPUT                 :2
 * 					- INPUT                 :2
 * @return		None
 **********************************************************************/
void HAL_GPIO_ConfigOutput(PCU_Type *PCx, uint8_t pin_no, PCU_PORT_MODE dir_type)
{
	uint8_t pin_offset; 
	uint32_t reg_val; 

	//------------------------------------------------------------------------------
	// pin_offset = pin_no * 2
	//------------------------------------------------------------------------------
	pin_offset = (pin_no << 1); 

	//------------------------------------------------------------------------------
	// CR
	//------------------------------------------------------------------------------
	reg_val = PCx->CR; 
	reg_val &= ~(PCU_CR_MODE_Msk << pin_offset); 
	reg_val |= (dir_type << pin_offset); 
	PCx->CR=reg_val; 	
}


/**********************************************************************//**
 * @brief 		Configure pin pullup
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	pin_no		Pin number, should be: 0..15
 * @param[in]	pullup pullup state, should be:
 * 					- PULL_UP_DOWN_DISABLE	:0
 * 					- PULL_UP_ENABLE 		:2
 * 					- PULL_DOWN_ENABLE 		:3
 * @return		None
 **********************************************************************/
void HAL_GPIO_ConfigPullup (PCU_Type *PCx, uint8_t pin_no, PCU_PULLUP_MODE pullup)
{
	uint8_t pin_offset; 
	uint32_t reg_val; 

	//------------------------------------------------------------------------------
	// pin_offset = pin_no * 2
	//------------------------------------------------------------------------------
	pin_offset = (pin_no << 1); 

	//------------------------------------------------------------------------------
	// PRCR
	//------------------------------------------------------------------------------

	reg_val = PCx->PRCR; 
	reg_val &= ~(PCU_PRCR_Msk << pin_offset); 
	reg_val |= (pullup << pin_offset); 
	PCx->PRCR=reg_val; 
		
}



/**********************************************************************//**
 * @brief 		Configure pin debounce
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	pin_no		Pin number, should be: 0..15
 * @param[in]	debounce debounce state, should be:
 * 					- DISABLE		:0
 * 					- ENABLE 		:1
 * @return		None
 **********************************************************************/
void HAL_GPIO_SetDebouncePin (PCU_Type *PCx, uint8_t pin_no, FunctionalState debounce)
{
	uint32_t	reg_val; 
	
	reg_val = PCx->DER; 
	reg_val &= ~(1<<pin_no); 
	if(debounce==ENABLE){
		reg_val |= (debounce<<pin_no); 
	}
	PCx->DER=reg_val; 
}


/**********************************************************************//**
 * @brief		Enable GPIO interrupt
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	pin_no		Pin number, should be: 0..15
 * @param[in]	pin_en 	Value that contains all bits on GPIO to enable,
 * 					    - IER_DISABLE = 0
 *						- IER_LEVEL_NON_PENDING = 1
 * 						- IER_LEVEL_PENDING = 2
 *						- IER_EDGE = 3
 * @param[in]	int_mode		interrupt mode, should be:
 * 					- ICR_PROHIBIT_INT = 0
 *                     if level
 * 					- ICR_LOW_LEVEL_INT = 1
 * 					- ICR_HIGH_LEVEL_INT = 2
 *                     if level
 * 					- ICR_FALLING_EDGE_INT = 1
 * 					- ICR_RISING_EDGE_INT = 2
 * 					- ICR_BOTH_EDGE_INT = 3
 * @return		None
 **********************************************************************/
void HAL_GPIO_EXTI_Config(PCU_Type *PCx, uint8_t pin_no, uint8_t pin_en, uint8_t int_mode)
{
	uint32_t temp_reg;
	
	// port n interrupt enable: disable or level or edge
	temp_reg = PCx->IER & (uint32_t)(~(3 << (pin_no<<1)));
	temp_reg |= (uint32_t)(pin_en << (pin_no<<1));
	PCx->IER = temp_reg;

	switch (pin_en){
		case 0: // disable
			PCx->ICR &= (uint32_t)(~(3 <<  (pin_no<<1)));
			break;
		case 1: // level non-pending
		case 2: // level pending
		case 3: // edge
			temp_reg = PCx->ICR & (uint32_t)(~(3 << (pin_no<<1)));
			temp_reg |= (uint32_t)(int_mode << (pin_no<<1));
			PCx->ICR = temp_reg;
			break;
		default:
			break;
	}
}


/**********************************************************************//**
 * @brief		Get GPIO Interrupt Status
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @return		ISR register value 
 **********************************************************************/
uint32_t HAL_GPIO_EXTI_GetStatus(PCU_Type *PCx)
{
	return (PCx->ISR);
}

/**********************************************************************//**
 * @brief		Clear GPIO interrupt status
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	Value Value that contains all bits on PCU to set, should
 * 				be in range from 0 to 0xFFFFFFFF.
 * @return		None
 **********************************************************************/
void HAL_GPIO_EXTI_ClearPin(PCU_Type *PCx, uint32_t value)
{
	PCx->ISR = value;
}



/**********************************************************************//**
 * @brief		Set Value for bits that have output direction on GPIO port.
 * @param[in]	Px selected port, should be in range from PA to PD
 * @param[in]	bitValue Value that contains all bits on GPIO to set, should
 * 				be in range from 0 to 0xFFFF.
 * 				example: value 0x5 to set bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void HAL_GPIO_SetPin(PCU_Type *Px, uint16_t bitValue)
{
	Px->BSR = bitValue;
}


/**********************************************************************//**
 * @brief		Clear Value for bits that have output direction on GPIO port.
 * @param[in]	Px selected port, should be in range from PA to PD
 * @param[in]	bitValue Value that contains all bits on GPIO to clear, should
 * 				be in range from 0 to 0xFFFF.
 * 				example: value 0x5 to clear bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void HAL_GPIO_ClearPin(PCU_Type *Px, uint16_t bitValue)
{
	Px->BCR = bitValue;
}


/**********************************************************************//**
 * @brief		Read Current state on port pin that have input direction of GPIO
 * @param[in]	Px selected port, should be in range from PA to PD
 * @return		Current value of GPIO port.
 *
 * Note: Return value contain state of each port pin (bit) on that GPIO regardless
 * its direction is input or output.
 **********************************************************************/
uint16_t HAL_GPIO_ReadPin(PCU_Type *Px)
{
	return Px->IDR;
}

/**********************************************************************//**
 * @brief		Write Value on port that have output direction of GPIO
 * @param[in]	PCx	Pointer to selected PCU peripheral, should be: A,B,C,D
 * @param[in]	Value Value that contains all bits on GPIO to write, should
 * 				be in range from 0 to 0xFFFF.
 * @return		None
 **********************************************************************/
void HAL_GPIO_WritePin(PCU_Type *Px, uint16_t Value)
{
	Px->ODR = Value;
}




/* --------------------------------- End Of File ------------------------------ */
