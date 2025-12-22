#include "user_Switch.h"

/*************************************GLOBLE VAIRABLE***********************************/
uint8_t switch_1,switch_2,switch_3,switch_4;
/***************************************************************************************/

/**
	* @brief  Reads the status of input switches connected to GPIO ports PB and PC,
 *        and updates the corresponding switch variables (switch_1 to switch_4).
	* @param  
	* @retval 
	*/
	uint16_t pinstatus,pinstatus_1;
void SwitchControl(void)
{
	
	// Read the entire GPIO port PB input data register
	pinstatus = HAL_GPIO_ReadPin(PB);
	// Read the entire GPIO port PC input data register
	pinstatus_1 = HAL_GPIO_ReadPin(PC);
	if(pinstatus & (1 << 0))   // Check if bit 0 of PB is set (SWITCH 3 is ON)
	{
		switch_1 = 1;
	}
	else
	{
		switch_1 = 0;
	}
	
	if(pinstatus & (1 << 1))   //Check if bit 1 of PB is set (SWITCH 2 is ON)
	{
		switch_2 = 1;
	}
	else
	{
		switch_2 = 0;
	}
	
	if(pinstatus & (1 << 2))   //Check if bit 2 of PB is set (SWITCH 1 is ON)
	{
		switch_3 = 1;
	}
	else
	{
		switch_3 = 0;
	}
	
	if(pinstatus_1 & (1 << 14))   //Check if bit 14 of PC is set (SWITCH 4 is ON)
	{
		switch_4 = 1;
	}
	else
	{
		switch_4 = 0;
	}
}
