#include "Analog_Pwm_Output.h"

/**
	* @brief 	set both duty and Period.
	* @param  
	* @retval 
	*/
void Set_duty_period_Analog_PWM(void)
{
	
}

/**
	* @brief 	Initialize Analog PWM fuction 
	* @param  Set all necessary mode of seting for MPWM
	* @retval 
	*/
void ANALOG_PWM_INIT(void)
{
	struct mpwm_cfg cfg;
	union mpwm_irq_cfg cfg_u;
	cfg_u.irq_en = 0;
	cfg_u.irq_en_bit.bottom = 1;
	cfg.mode = MPWM_MODE_NORMAL;
	//cfg.chan_mode = 0;
	cfg.counter_mode = MPWM_COUNTER_MODE_UP;
	cfg.clk_div = 100;
	
	//HAL_MPWM_Init(MPWM_ID_0,&cfg,MPWM_IRQHandler,NULL);
  //HAL_MPWM_SetIRQConfig(MPWM_ID_0, &cfg_u);
	HAL_MPWM_SetPeriod(MPWM_ID_0,MPWM_PHASE_TYPE_W,60000);                        //Set Period value uisng this function
	HAL_MPWM_SetDuty(MPWM_ID_0,MPWM_PHASE_TYPE_W,MPWM_OUTPUT_TYPE_L,25000);       //Set Duty value uisng this function
	HAL_MPWM_ControlPWMOutput(MPWM_ID_0,MPWM_PHASE_TYPE_W,MPWM_OUTPUT_TYPE_L,1);  //Contorl PWM output uisng identity phase of PWM
	HAL_MPWM_Start(MPWM_ID_0,MPWM_PHASE_TYPE_W);																	//start MPWM
	HAL_MPWM_EnablePWMOutput(MPWM_ID_0);                                          //Enable PWM output
}
