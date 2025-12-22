#include "Digital_pwm_Output.h"


/*****************************GLOBLE VARIABLE********************************/
uint16_t duty,period;
/****************************************************************************/

/**
	* @brief 	Change PWM duty uisng GRA and GRB
	* @param  set Pwm Duty
	* @retval 
	*/

void DIGITAL_PWM(void)                   
{
		duty++;																					//increment duty of pwm
		if(duty >= TIMER1->GRB)													//check duty is greater than GRB register
		{
			duty = 0;																			//duty - 0
		}
		TIMER1->GRA = duty;                             //duty assign to GRA register 
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
	duty = 30;                                                //set initial duty.
	period = 100;   																					//set initial Periods
	cfg.mode=TIMER_MODE_PWM;																	//set Timer Mode PWM
	cfg.clk_sel = TIMER_CLK_DIV_16_PCLK;                      //set clock div .
	cfg.prescaler = 100;                                      //set prescalar
	cfg.adc_trig = TIMER_ADC_TRIG_DISABLE;                    //disable adc tigger
	cfg.irq_prio = DRIVER_PRIORITY_LOWEST;                    //set intrrupt priority 
	

	/* Initiialize PWM Timer */
	HAL_TIMER_Init(TIMER_ID_1,&cfg,MY_HANDLER,NULL);           //uisng Timer id 1 for init
	HAL_TIMER_StartPWM(TIMER_ID_1,TIMER_PWM_START_LOW,duty,period,TIMER_PWM_EVENT_DUTY);  //intialization of start pwm
}

