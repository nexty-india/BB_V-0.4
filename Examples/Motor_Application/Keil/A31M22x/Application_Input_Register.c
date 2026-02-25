#include "Application_Input_Register.h"
#include "Bharat_Bijlee.h"
#include "Flash_Writing.h"
uint32_t g_Power_factor = 0,g_Current_factor = 0;
uint16_t g_Power_Filt = 0,g_currentFilt = 0;;

bool flash_Hourflag;
uint64_t g_milliseconscounter = 0,g_runhourcounter,g_powerrunhourcounter;
uint64_t g_secondcounter = 0;
uint64_t g_runhourcountercur,g_powerrunhourcountercurr;
uint64_t run_hours_flash;
uint64_t power_on_hours_flash;


/**
 * @brief  Initialize run-hour and remaining-life counters from flash memory
 *
 * This function is called once during system power-up.
 * It restores previously stored hour counters from non-volatile flash
 * so that run time and remaining life continue correctly after reset
 * or power failure.
 *
 * - INPUT_RUNHOUR_START_ADDR        : Flash address storing total run hours
 * - INPUT_REMAININGLIFE_START_ADDR  : Flash address storing remaining life hours
 *
 * The values read from flash are copied into RAM working variables
 * used by the hour counter logic during normal operation.
 */
void HourCounterInit(void)
{
	run_hours_flash = Read_Flash_U32(INPUT_RUNHOUR_START_ADDR);
	power_on_hours_flash = Read_Flash_U32(INPUT_REMAININGLIFE_START_ADDR);
	
	g_runhourcounter = run_hours_flash;
	g_powerrunhourcounter = power_on_hours_flash;
}

/**
 * @brief  Run hour and remaining life hour calculation
 *
 * This function is executed periodically every 1 millisecond.
 * It calculates motor run hours based on actual motor RPM.
 *
 * Logic:
 * - Millisecond counter increments continuously
 * - Seconds are derived from millisecond counter
 * - Run hour increments only when motor RPM > 0
 * - After 1 hour of motor run:
 *      • RUN_HOUR counter increments
 *      • REMAINING_LIFE counter decrements
 * - Flash write flag is set but actual flash write
 *   is handled elsewhere when motor is OFF
 */
void HourCounterCheck(void)            //Run at 1 millisecond;
{

	g_milliseconscounter++;
	g_secondcounter = g_milliseconscounter/1000;
		if(g_secondcounter >= SECONDTOHOURFACTOR) /* Check if 1 hour of run time is completed */
		{
			g_secondcounter = 0;
			g_milliseconscounter = 0;
			g_runhourcounter++;
			
			
			if(g_powerrunhourcounter > 0)
			{
				g_powerrunhourcounter--;
			}
			
			g_runhourcountercur = g_runhourcounter;
			g_powerrunhourcountercurr = g_powerrunhourcounter;
			
			flash_Hourflag = 1;
		}
}

/**
 * @brief  Store run hour and remaining life hour counters into flash memory
 *
 * This function is responsible for updating non-volatile flash storage
 * with the latest hour counter values.
 *
 * Conditions:
 * - Flash write is triggered only when flash_Hourflag is set
 * - Values are written only if they have changed (wear reduction)
 * - Function must be called when motor is OFF
 *
 * Flash addresses used:
 * - INPUT_RUNHOUR_START_ADDR        : Total run hours
 * - INPUT_REMAININGLIFE_START_ADDR  : Remaining life hours
 */
void FlashHourSetting(void)
{
	uint16_t Actual_rpm = 0;
	Actual_rpm = modbus_parameter.MODBUS_ACTUAL_SPEED;
	
		if(flash_Hourflag == 1)
		{
			/* Write run hour counter if value has changed */
			if(run_hours_flash != g_runhourcountercur)
			{
				run_hours_flash = g_runhourcountercur;
				Data_write_to_flash(INPUT_RUNHOUR_START_ADDR,1,(uint32_t*)&run_hours_flash);
			}
			 /* Write remaining life counter if value has changed */
			if(power_on_hours_flash!=g_powerrunhourcountercurr)
			{
				power_on_hours_flash = g_powerrunhourcountercurr;
				Data_write_to_flash(INPUT_REMAININGLIFE_START_ADDR,1,(uint32_t*)&power_on_hours_flash);
			}
			
			flash_Hourflag = 0;
		}
}
/**
 * @brief  System hour counter service function
 *
 * This function acts as a wrapper to handle all hour-related operations.
 * It should be called periodically from the main scheduler.
 *
 * Responsibilities:
 * - Update run hour and remaining life hour counters based on motor status
 * - Trigger flash write operation when hour values are updated
 *
 * Execution flow:
 * 1. HourCounterCheck()
 *    - Calculates run hours when motor is running
 *    - Decrements remaining life hours accordingly
 *    - Sets flash write flag after each completed run hour
 *
 * 2. FlashHourSetting()
 *    - Writes updated hour counters into flash memory
 *    - Flash write occurs only when permitted by system logic
 */
void SystemHourStatus(void)
{
	HourCounterCheck();
	FlashHourSetting();
}


/**
 * @brief Simple low-pass filter for motor power (KW)
 *
 * This function applies a basic filtering algorithm to the
 * received power value to smooth out fluctuations.
 */
void Power_Filter(void)
{
	uint16_t Rec_Power = 0;
	Rec_Power = modbus_parameter.KW/10;															 // Read received power value and scale (assuming KW is multiplied by 10 in Modbus)
	g_Power_factor = g_Power_factor + (Rec_Power-g_Power_Filt);       // Update the filtered power using a simple IIR-like approach
	g_Power_Filt = g_Power_factor >> Power_Filter_FACTOR;            // Apply the filter factor (right shift by Power_Filter_FACTOR)
}


/**
 * @brief Simple low-pass filter for motor current
 *
 * This function applies a basic filtering algorithm to the
 * received motor current to smooth out measurement fluctuations.
 */
void Current_Filt(void)
{
	uint16_t Rec_Current = 0;
	Rec_Current = modbus_parameter.MODBUS_READ_MOTOR_CURRENT;          // Read motor current from Modbus parameter
	g_Current_factor = g_Current_factor + (Rec_Current - g_currentFilt);        //  Update the filtered current using a simple IIR-like approach
	g_currentFilt = g_Current_factor >> Current_Filter_Factor;          // Apply the filter factor (right shift by Current_Filter_Factor)
} 