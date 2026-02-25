#include "Flash_Writing.h"
#include "Default_Values.h"
#include "LVD_Status.h"
FlashState_t FLASHSTATE = READ_ACTUAL_FLASH_VALUE;
uint32_t save_Parameter_Counter;



/**
*@breif This is used for Write the data to Flash Memorty
*@param Start_Address and Data
*@retrun None
*/
void Data_write_to_flash(uint32_t Start_Address,uint32_t Size,uint16_t * data)
{
	uint16_t temp_data, i;
	// Enable Flash Access and Write
	CFMC_FlashAccessCmd(ENABLE);
	CFMC_WriteCmd(ENABLE);

	// Erase Flash Page (required before write)
	CFMCErase(CFMC_CTRL_PERS, Start_Address);

	// Program 1 word (4 bytes)
	for(i = 0; i < Size; i++)
	{
		temp_data = data[i];
		CFMCProgramPage(Start_Address + i*4, 1, (unsigned char *)&temp_data);
	}

	// Disable Flash Access
	CFMC_WriteCmd(DISABLE);
	CFMC_FlashAccessCmd(DISABLE);
}


uint16_t g_Default_Write,g_Flash_Write,g_Flash_control_Flag;//Actual_Vaule[HOLDING_TOTAL_MEMBER],;
uint16_t g_Actal_value_status,g_Total_Size_Holding_Reg = 0,g_defaultValue;

/**
*@breif This Function Control the Flash Writing State Machine Run at every 1 Millisecond....
*@param void
*@retrun None
*/
void FlashWriting(void)
{
	static uint32_t Flash_value=0,Flah_valueDefault = 0;
  uint16_t Checkarr[200];
	uint16_t Actual_Vaule[128],Dummy_Arr[90];
	g_Flash_Write = MODBUS_HOLDING_REGISTERS[HOLDING_FLASHWRITING].actual_value;           //Set the value for write a values in Flash
	g_defaultValue = MODBUS_HOLDING_REGISTERS[HOLDING_SET_DEFAULT_FACTORY].actual_value;  //Set the default value form the Flash
	g_Total_Size_Holding_Reg = HOLDING_TOTAL_MEMBER;    //Total Number of Holding Parameter
	
	switch(FLASHSTATE)
	{
			case READ_ACTUAL_FLASH_VALUE:                                    //This State to read the value from the flash according to Flashwriting and Set_DefaultFactory value
		
     

			if(g_flash_value == 1)                                           //Value read from flash when the FlashWriting holding Parameter is set
			{
				for(int i = 0;i<= 127;i++)
				{
					Flash_value = Read_Flash_U32(HOLDING_REG_ACTUAL_START_ADDR+ (i * 4));
					MODBUS_HOLDING_REGISTERS[i].actual_value =(uint16_t)(Flash_value&0x0000FFFF);
				}
	
				for(int j = 0;j<70;j++)
				{
					Flash_value = Read_Flash_U32(HOLDING_REG_ACTUAL_START_ADDR_1+ (j * 4));
					MODBUS_HOLDING_REGISTERS[j+128].actual_value = (uint16_t)(Flash_value&0x0000FFFF);
				}
				
				g_flash_value = 0;
			}
			
			if((g_Default_Write == 1)||(g_defaultValue == 1)){                                       //g_Default_Write flag is used only for first time power off and g_defaultvalue flag is used set the factory default at any time
				FLASHSTATE = DEFAULT_FLASH_SETTING;
			}
			else if(g_Flash_Write == 1)                              //g_flash write flag is used whtne the Write the actual value in Flash Memory
			{
				FLASHSTATE = WRITE_ACTUAL_VALUE_SETTING;
			}
			break;
		
		
		case DEFAULT_FLASH_SETTING:                                        //This state Set the Default value from flash to actual value of Holding Register using Set default factory Register
			if ((g_Default_Write == 1) || (g_defaultValue == 1))
			{
					g_Default_Write = 0;

					for (int i = 0; i < 128; i++)
					{
							Checkarr[i] =*(uint16_t *)(HOLDING_REG_DEFAULT_START_ADDR + i * 4);
					}

					for (int j = 0; j < 70; j++)
					{
							Checkarr[j + 128] =*(uint16_t *)(HOLDING_REG_DEFAULT_START_ADDR_LOW + j * 4);
					}
					
					for (int k = 0; k < Holding_Register_Total ; k++)
					{
						MODBUS_HOLDING_REGISTERS[k].actual_value = Checkarr[k];
					}
					
					uint16_t zero = 0;
					Data_write_to_flash(HOLDING_REG_FLASH_CONTROL_START_ADDR, 1, &zero);

					FLASHSTATE = READ_ACTUAL_FLASH_VALUE;
			}
			break;
		
		case WRITE_ACTUAL_VALUE_SETTING:                              //This State write the actual value of Holding register to the flash Memory using Flashwriting holding Register.
     if (g_LVI_Detected == 1)
			{
					/* Voltage unstable ? DO NOT write flash */
					FLASHSTATE = READ_ACTUAL_FLASH_VALUE;
					break;
			}		

		if(g_Flash_Write == 1)
			{
				g_Flash_Write = 0;		
				for (int i = 0; i < 128 ; i++)
				{
					Actual_Vaule[i] = MODBUS_HOLDING_REGISTERS[i].actual_value;
				}
				
				Data_write_to_flash(HOLDING_REG_ACTUAL_START_ADDR, 128, (uint16_t *)Actual_Vaule);
				for (int j = 0; j < 70 ; j++)
				{
					Dummy_Arr[j] = MODBUS_HOLDING_REGISTERS[j+128].actual_value;
				}
				Data_write_to_flash(HOLDING_REG_ACTUAL_START_ADDR_1, 70, (uint16_t *)Dummy_Arr);
        
			}

//			if(user_delay(200,&save_Parameter_Counter))
//				{
					MODBUS_HOLDING_REGISTERS[HOLDING_FLASHWRITING].actual_value = g_Flash_Write;
					g_Actal_value_status = 1;
					Data_write_to_flash(HOLDING_REG_FLASH_CONTROL_START_ADDR,2,(uint16_t *)&g_Actal_value_status);
					g_Actal_value_status = 0;
					FLASHSTATE = READ_ACTUAL_FLASH_VALUE;
		//		}
			
			break;
			
			
	}	
}

/**
*@breif This Function used read the value from the flash
*@param Address
*@retrun temp_data
*/
uint32_t Read_Flash_U32(uint32_t Address)
{
    uint32_t temp_data = 0;       // local variable

    temp_data = *(uint32_t*)Address;   // read from flash

    return temp_data;             // return local variable
}



