#include "Application_Input_Register.h"
#include "Bharat_Bijlee.h"
#include "Flash_Writing.h"
uint64_t Remaing_hour;                   // 8
uint32_t g_Current_factor;               // 4
uint32_t g_PowerCal_Factor;
PowerCounter_t   counter;
FilterrunFlash_t Filterrunner;
FilterCounter_t  Filtercounter;
RunTimeFlash_t   runtime;
RemainingTimer_t remtimer;
RemTimer_t rementimer;

uint16_t g_currentFilt;
uint16_t g_PowerFilt;
uint16_t g_milliseconscounter;
uint16_t g_milliseconscounter_Remaing;
uint16_t g_powerrunhourcounterprv;
uint16_t g_FilStatus;
uint16_t g_HourFilter;
uint32_t g_tesecondcounter;                   // 10
uint8_t g_FilReset = 0;
bool flash_Hourflag;
bool modbus_set_initialized;
bool g_FilterFlash;
bool g_flash_check;
bool g_flash_rem;                        // 5
bool Remain_check;
uint32_t modbus_value;
/**
 * @brief   : 
 *   This function maintains the running time counters in seconds, minutes,
 *   and hours using a millisecond tick.
 * @execute :
 *   This function excute at every millisecond loop...
 */
void HourCounter(void)
{
		//g_milliseconscounter++;                    //inccrement at every millisecond
	  if(g_milliseconscounter > MILLI_TO_SEC){   //Calculate Second by the millisecond counter
			counter.Secondcounter++;
			g_milliseconscounter = 0;
		}
		
		if(counter.Secondcounter > SEC_TO_MIN)    //Calculate Minute by the Second Counter..
		{
			counter.Minutecounter++;
			counter.Secondcounter = 0;
		}
		
		if(counter.Minutecounter > MIN_TO_HOUR)     //Calculate Hour by the Minute Counter..
		{
			counter.Hourcounter++;
			counter.Minutecounter = 0;
		}

	  MODBUS_INPUT_REGISTERS[INPUT_RUN_HOURS].actual_value = counter.Hourcounter;
		
		
		
		if((Fault.Fault_bits.ACLineBreak_Fault == 1)||(Fault.Fault_bits.UnderVoltage_Fault))
		{
			if(g_tesecondcounter++ >= 600000)
			{
				g_tesecondcounter = 0; 
				g_flash_check = 1;
			}
		}
		
	if(g_flash_check == 1){
			g_flash_check = 0;
			Data_write_to_flash(RUNNING_SECOND_START_ADDR,sizeof(PowerCounter_t),(uint16_t*)&counter);	
		}
	
	
}

void RemainingHour(void)
{
	
	if(g_milliseconscounter_Remaing > MILLI_TO_SEC)
		{
		  remtimer.RemSecCounter++;
			g_milliseconscounter_Remaing = 0;
		}
		
		if(remtimer.RemSecCounter > SEC_TO_MIN)
		{
			remtimer.RemMinuteCounter++;
			remtimer.RemSecCounter=0;
		}
		
		if(remtimer.RemMinuteCounter > MIN_TO_HOUR)
		{
			remtimer.RemHourCounter++;
			remtimer.RemMinuteCounter = 0;
		}
		
		
		if(g_flash_rem == 1)
		{
			g_flash_rem = 0;
			Data_write_to_flash(INPUT_REMAININGLIFE_START_ADDR,4,(uint16_t*)&Remaing_hour);
		}
}

/**
 * @brief   Initializes the run-time hour, minute, and second counters
 *   by reading previously stored values from flash memory.
 *
  - Reads hours, minutes, and seconds from their respective
 *     flash memory addresses.
 *
 * If flash contains erased values (0xFFFF), counters are
 *     initialized to zero.
 */
uint64_t Flash_RemainingHour;
void HourCounterInit(void)
{	
	 
   runtime.hours = Read_Flash_U32(RUNNING_SECOND_START_ADDR);
	 runtime.minutes = Read_Flash_U32(RUNNING_MINUTE_START_ADDR);
	 runtime.seconds = Read_Flash_U32(RUNNING_HOUR_START_ADDR);
    if ((runtime.seconds == 0xFFFF)||(runtime.minutes == 0xFFFF)||(runtime.hours == 0xFFFF))
    {
        counter.Secondcounter = 0;
        counter.Minutecounter = 0;
        counter.Hourcounter   = 0;
    }
    else
    {
        counter.Secondcounter = runtime.seconds;
        counter.Minutecounter = runtime.minutes;
        counter.Hourcounter   = runtime.hours;
    }
		
		Filterrunner.hours = Read_Flash_U32(FILTER_SECOND_START_ADDR);
		Filterrunner.minutes = Read_Flash_U32(FILTER_MINUTE_START_ADDR);
		Filterrunner.seconds = Read_Flash_U32(FILTER_HOUR_START_ADDR);
		
		if ((Filterrunner.seconds == 0xFFFF)||(Filterrunner.minutes == 0xFFFF)||(Filterrunner.hours == 0xFFFF))
    {
        Filtercounter.FilterSecondCounter = 0;
        Filtercounter.FilterMinuteCounter = 0;
        Filtercounter.FilterHourCounter   = 0;
    }
		else
		{
				Filtercounter.FilterSecondCounter = Filterrunner.seconds;
        Filtercounter.FilterMinuteCounter = Filterrunner.minutes;
        Filtercounter.FilterHourCounter   = Filterrunner.hours;
		}
		
//		 rementimer.hours = Read_Flash_U32(REAMINING_SECOND_START_ADDR);
//		 rementimer.minutes = Read_Flash_U32(REAMINING_MINUTE_START_ADDR);
//		 rementimer.seconds = Read_Flash_U32(REAMINING_HOUR_START_ADDR);
		Flash_RemainingHour = Read_Flash_U32(INPUT_REMAININGLIFE_START_ADDR);
//		if((rementimer.seconds == 0xFFFF)||(rementimer.minutes == 0xFFFF)||(rementimer.hours == 0xFFFF))
//		{
//			remtimer.RemHourCounter = 0;
//			remtimer.RemMinuteCounter = 0;
//			remtimer.RemSecCounter = 0;
//		}
//		else
//		{
//			remtimer.RemHourCounter = rementimer.hours;
//			remtimer.RemMinuteCounter = rementimer.minutes;
//			remtimer.RemSecCounter = rementimer.seconds;
//		}
}

/**
 * @brief   *   Monitors the elapsed running hours and updates the remaining
 *   power-on life counter based on hour increments.
 *
 */

 uint32_t Prev_MinuteCounter = 0;  // for edge detection
 uint32_t Last_Modbus_Hour_Value = 0;

void HourCounterCheck(void)
{
    modbus_value = MODBUS_HOLDING_REGISTERS[HOLDING_SET_REMAINING_HOUR].actual_value;
    g_FilReset = MODBUS_HOLDING_REGISTERS[HOLDING_RESET_FILTER_RUN_HOURS].actual_value;
	  if(g_FilReset == 2)
		{
			Last_Modbus_Hour_Value = 0;
		}
		Remaing_hour = modbus_value - counter.Hourcounter;
    MODBUS_INPUT_REGISTERS[INPUT_POWER_ON_HOURS].actual_value = Remaing_hour;

	}

/**
 * @brief  System hour counter service function
 *
 * This function acts as a wrapper to handle all hour-related operations.
 * It should be called periodically from the main scheduler.
 */
void SystemHourStatus(void)
{
	HourCounterCheck();
	HourCounter();
	RemainingHour();
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

/**
*@brief : This Function Check the Filter is Clean or Dirty 
*         0:- Filter is Clean
* 				1:- Filter is Dirty
*         
*@return void
*/
uint16_t Minute_Filter = 0,SetFilerHour = 0,MinuteComplete= 0,Filter_milli= 0,Filterminutes = 0,filterhour = 0,millisecond;
uint16_t FilterMinuteshow = 0;
void FilterStatus(void)
{
	Filter_milli++;
	if(Filter_milli > 1000){
		Filtercounter.FilterSecondCounter++;
		Filter_milli = 0;
	}
	
	if(Filtercounter.FilterSecondCounter > 60)
	{
		Filtercounter.FilterSecondCounter=0;
		Filtercounter.FilterMinuteCounter++;
	}
	
	if(Filtercounter.FilterMinuteCounter > 60)
	{
		Filtercounter.FilterMinuteCounter = 0;
		Filtercounter.FilterHourCounter++;
	}
	
	FilterMinuteshow = Filtercounter.FilterMinuteCounter;
		
	SetFilerHour = MODBUS_HOLDING_REGISTERS[HOLDING_SET_FILTER_RUN_HOURS].actual_value;   //Set the Filter run hour for check dirty
	

 	MODBUS_INPUT_REGISTERS[INPUT_FILTER_RUN_HOURS].actual_value = FilterMinuteshow;    //show the hourfilte on input register
	if(Filtercounter.FilterMinuteCounter >= SetFilerHour)    //Check running filter hour is greater than set filter hour
	{ 
		g_FilStatus = 1;                //Filter is dirty
 	}else{
		g_FilStatus = 0;                //Filter is Clean
	}
	MODBUS_INPUT_REGISTERS[INPUT_FILTER_STATUS].actual_value = g_FilStatus;   //Show the filter status on Input register
  
  if(g_FilterFlash == 1)
	{
		Data_write_to_flash(FILTER_SECOND_START_ADDR,sizeof(FilterCounter_t),(uint16_t*)&Filtercounter);
	}		
}

/**
* @brief : This Function Reset the RUnning filter hour and Filter status Dirty to Clean
* 
* @return : Void
*
*/
void ResetFilterStatus(void)
{
	
	g_FilReset = MODBUS_HOLDING_REGISTERS[HOLDING_RESET_FILTER_RUN_HOURS].actual_value;
	if(g_FilReset == 1)           //Check ths Filterrest is 1 by Holding register
	{
		g_FilReset = 0;            //Reset the Filterrset
		Filtercounter.FilterHourCounter = 0;
		g_FilStatus = 0;
		Filtercounter.FilterMinuteCounter = 0;
		Filtercounter.FilterSecondCounter = 0;
		MODBUS_HOLDING_REGISTERS[HOLDING_RESET_FILTER_RUN_HOURS].actual_value = g_FilReset;      
	}
	else if(g_FilReset == 2)
	{
		g_FilReset = 0;
		remtimer.RemHourCounter = 0;
		remtimer.RemMinuteCounter = 0;
		remtimer.RemSecCounter = 0;
		MODBUS_HOLDING_REGISTERS[HOLDING_RESET_FILTER_RUN_HOURS].actual_value = g_FilReset;
	}
}


/**
* @brief : This Function run at every 1 millisecond for checking the Filter Status
* 
* @return : Void
*
*/
void FilterParameter(void)
{
	FilterStatus();          //check filter status
	ResetFilterStatus();     //Reset Filter Status
}


float powerCalculated = 0;
float Current_recv  = 0,Voltage_recv = 0;
float Curr_cal = 0,voltage_cal = 0;
int PowerCalculation(void)
{
	
	Current_recv = g_currentFilt;
	Voltage_recv = modbus_parameter.MODBUS_READ_AC_VOLTAGE;
	Curr_cal = (Current_recv/100);
	voltage_cal = (Voltage_recv / 10);
	powerCalculated = (Curr_cal*voltage_cal);
	powerCalculated = powerCalculated/10;
	return powerCalculated;
}

void PowerFilterCal(void)
{
	float PowerRaw = 0;
	PowerRaw = PowerCalculation();
	g_PowerCal_Factor = g_PowerCal_Factor +(PowerRaw - g_PowerFilt);
	g_PowerFilt = g_PowerCal_Factor >> POWERCAL_FACTOR;
	
	MODBUS_INPUT_REGISTERS[INPUT_KW].actual_value = g_PowerFilt;
}


/**
* @brief :- This Function calcuate the percentage of load of motor using the power receved by NXP controller
*	@note This function should be called from the main control loop
*       or an interrupt service routine that operates every 1 ms.
* @return none
*/
uint16_t g_Power;
uint16_t g_Total_Load=6000,g_Load_percentage;
float    g_Load_per = 0;
void LoadPercentage(void)
{
	g_Power =(float)g_PowerFilt;
	g_Load_per = (float)g_Power/g_Total_Load;
	g_Load_percentage = g_Load_per * 100;
	MODBUS_INPUT_REGISTERS[INPUT_LOAD].actual_value = g_Load_percentage;
}
