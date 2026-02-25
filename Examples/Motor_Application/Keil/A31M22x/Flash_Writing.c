#include "Flash_Writing.h"
#include "Default_Values.h"



FlashState_t FLASHSTATE = READ_ACTUAL_FLASH_VALUE;
uint32_t save_Parameter_Counter;
uint16_t Array[5] = {1222,1222,1222,1222,1222};

/**
*@breif This is used for Write the data to Flash Memorty
*@param Start_Address and Data
*@retrun None
*/
void Data_write_to_flash(uint32_t Start_Address,uint32_t Size,uint32_t * data)
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

uint16_t g_Flash_Write,g_Flash_control_Flag,g_Default_Write = 1;
uint16_t Actual_Vaule[200];
uint16_t g_Actal_value_status,Total_Size_Holding_Reg = 0;
uint32_t g_Actal_value_read,g_Actal_read;
void FlashWriting(void)
{
    uint32_t *flash_data_control_value;  // Pointer for flash data (not currently used)
    uint16_t Start_address = 0, Quantity_register = 0;

    // Extract start address and quantity of registers from MODBUS received buffer
    Start_address = ((data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_HIGH_RX] << 8) |
                     data_logger.MODBUS_RECEIVED_BUFFER[START_ADDRESS_LOW_RX]);
    Quantity_register = ((data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_HIGH_RX] << 8) |
                         data_logger.MODBUS_RECEIVED_BUFFER[REGISTER_QUANTITY_LOW_RX]);

    // Read Flash Write flag from MODBUS holding register
    g_Flash_Write = MODBUS_HOLDING_REGISTERS[HOLDING_SENSOR_PRESSURE_UNIT].actual_value;

    // Total size of holding registers
    Total_Size_Holding_Reg = HOLDING_TOTAL_MEMBER;

    // Default write flag handling
    if (g_Default_Write == 1)
    {
        // If already set, do nothing
    }
    else
    {
        // Otherwise, read the flag from MODBUS holding register (HOLDING_BAUD_RATE used as placeholder)
        g_Default_Write = MODBUS_HOLDING_REGISTERS[HOLDING_BAUD_RATE].actual_value;
    }

    // Main flash state machine
    switch (FLASHSTATE)
    {
        case READ_ACTUAL_FLASH_VALUE:  // State to read actual flash values into RAM
            if (g_Actal_read == 1)    // Check if actual read requested
            {
                for (int i = 0; i < Total_Size_Holding_Reg; i++)
                {
                    uint32_t *flash_data_default_value = (uint32_t *)HOLDING_REG_ACTUAL_START_ADDR;
                    MODBUS_HOLDING_REGISTERS[i].actual_value = flash_data_default_value[i] & 0xFFFF; // Read lower 16 bits
                }
                g_Actal_read = 0;  // Clear the read flag
            }

            // Check if write or default operation is requested
            if (g_Flash_Write == 1)
            {
                FLASHSTATE = WRITE_ACTUAL_VALUE_SETTING;  // Move to write state
            }
            else if (g_Default_Write == 1)
            {
                FLASHSTATE = DEFAULT_FLASH_SETTING;  // Move to default write state
            }
            break;

        case DEFAULT_FLASH_SETTING:  // State to reset all registers to default values
            if (g_Default_Write == 1)
            {
                g_Default_Write = 0;  // Clear default write flag
                for (int i = 0; i < HOLDING_TOTAL_MEMBER; i++)
                {
                    uint32_t *flash_data_default_value = (uint32_t *)HOLDING_REG_DEFAULT_START_ADDR;
                    MODBUS_HOLDING_REGISTERS[i].actual_value = flash_data_default_value[i]; // Load default value
                }
                // Reset the MODBUS register flag to 0
                MODBUS_HOLDING_REGISTERS[HOLDING_BAUD_RATE].actual_value = g_Default_Write;
                FLASHSTATE = READ_ACTUAL_FLASH_VALUE;  // Return to read state
            }
            break;

        case WRITE_ACTUAL_VALUE_SETTING:  // State to write current RAM values into flash
            if (g_Flash_Write == 1)
            {
                g_Flash_Write = 0;  // Clear the write flag

                // Copy RAM holding registers into local flash array
                for (int i = 0; i < Total_Size_Holding_Reg; i++)
                {
                    Actual_Vaule[i] = (uint32_t)MODBUS_HOLDING_REGISTERS[i].actual_value;
                }

                // Write data to actual flash memory
                Data_write_to_flash(HOLDING_REG_ACTUAL_START_ADDR, Total_Size_Holding_Reg, (uint32_t *)&Actual_Vaule);

                // Wait for 100 ms before confirming the write
                if (user_delay(100, &save_Parameter_Counter))
                {
                    MODBUS_HOLDING_REGISTERS[HOLDING_SENSOR_PRESSURE_UNIT].actual_value = g_Flash_Write;  // Clear write flag in MODBUS
                    g_Actal_value_status = 1;  // Temporary status to indicate write complete
                    Data_write_to_flash(HOLDING_REG_FLASH_CONTROL_START_ADDR, 1, (uint32_t *)&g_Actal_value_status);  // Save status to flash
                    g_Actal_value_status = 0;  // Reset temporary status
                    FLASHSTATE = READ_ACTUAL_FLASH_VALUE;  // Return to read state
                }
            }
            break;
    }
}



uint32_t Read_Flash_U32(uint32_t Address)
{
    uint32_t temp_data = 0;                    // Temporary variable to store flash data

    temp_data = *(uint32_t*)Address;           // Read 32-bit value directly from the given flash memory address

    return temp_data;                          // Return the read value
}




