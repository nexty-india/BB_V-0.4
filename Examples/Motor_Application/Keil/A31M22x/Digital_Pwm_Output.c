#include "Digital_pwm_Output.h"
#include "NXP_comm_uart.h"

/*****************************GLOBLE VARIABLE********************************/
uint16_t duty,Per;//,period;
/****************************************************************************/




uint16_t g_TachometerTimer = 0;

/**
	* @brief 	Change PWM duty uisng GRA and GRB
	* @param  set Pwm Duty
	* @retval 
	*/

void DIGITAL_PWM(void)                   
{
		//duty++;																					//increment duty of pwm
		if(duty >= TIMER1->GRB)													//check duty is greater than GRB register
		{
			duty = 0;																			//duty - 0
		}
		TIMER1->GRA = duty;                             //duty assign to GRA register 
}
uint16_t ActualtSpeed=500,PPR_temp=0,Total_Pulse = 0;
float Per_Pulse = 0;
uint16_t Digital_timer_pwm=100;
float Tachoutput;
void TachometerOutput(void)
{
	ActualtSpeed =  modbus_parameter.MODBUS_ACTUAL_SPEED;
	float Digital_tim =  0.0000016f;
	PPR_temp =  12;
  Total_Pulse = (PPR_temp*ActualtSpeed)/60;
	if(Total_Pulse == 0)
		return;
	else
	Per_Pulse = (float)1/Total_Pulse;
  Tachoutput = Per_Pulse/Digital_tim;

    	TIMER1->GRA = (uint16_t)Tachoutput>>1; 
		TIMER1->GRB = Tachoutput; 
}


void DigitalOutput(void)
{
	if(g_TachometerTimer++ > Digital_timer_pwm)
	{
		g_TachometerTimer = 0;
		TachometerOutput();
		AnalogOutput();
	}
}



/**
	* @brief 	Time PWM intrrupt handler
	* @param  
	* @retval 
	*/
void MY_HANDLER(uint32_t event, void *context)
{
		
}


/**
	* @brief 	Init function of Digital PMW uisng Timer mode PWM
	* @param  set required parameter for pwm using timer
	* @retval 
	*/
void DIGITAL_PWM_INIT(void)
{
	struct timer_cfg cfg;   
	//duty = 50;                                                //set initial duty.
	Per = 100;   																					//set initial Periods
	cfg.mode=TIMER_MODE_PWM;																	//set Timer Mode PWM
	cfg.clk_sel = TIMER_CLK_DIV_64_PCLK;                      //set clock div .
	cfg.prescaler = 2;                                      //set prescalar
	cfg.adc_trig = TIMER_ADC_TRIG_DISABLE;                    //disable adc tigger
	cfg.irq_prio = 0;//DRIVER_PRIORITY_LOWEST;                    //set intrrupt priority 
	
	/* Initiialize PWM Timer */
	HAL_TIMER_Init(TIMER_ID_1,&cfg,MY_HANDLER,NULL);           //uisng Timer id 1 for init
	HAL_TIMER_StartPWM(TIMER_ID_1,TIMER_PWM_START_LOW,duty,Per,TIMER_PWM_EVENT_NONE);  //intialization of start pwm
}

