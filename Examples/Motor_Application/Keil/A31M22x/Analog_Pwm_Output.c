#include "Analog_Pwm_Output.h"
#include "NXP_comm_uart.h"
#include "Application_Holding_Register.h"
uint16_t period_data = 1000;

/**
*@brief This function give the Rpm in duty Form
*
*
*/
uint16_t g_Duty_temp;
uint16_t ActualoRpm=0, TargetRpm=0;
void AnalogOutput(void)
{
//  HAL_MPWM_Start(MPWM_ID_0,MPWM_PHASE_TYPE_W);	
//	HAL_MPWM_SetPeriod(MPWM_ID_0,MPWM_PHASE_TYPE_W,period_data);                        //Set Period value uisng this function
//	HAL_MPWM_SetDuty(MPWM_ID_0,MPWM_PHASE_TYPE_W,MPWM_OUTPUT_TYPE_L,g_Duty_temp);       //Set Duty value uisng this function
   // ActualoRpm = modbus_parameter.MODBUS_ACTUAL_SPEED;
    TargetRpm = 1800;

    if (TargetRpm == 0) 
			return;   
		float duty_cycle = (ActualoRpm < TargetRpm) ? (float)ActualoRpm/TargetRpm : 1;
	
   // g_Duty_temp = (ActualoRpm * 100) / TargetRpm;
    g_Duty_temp = (float)duty_cycle * MPWM->PRD;
	
	 MPWM->DWL = (uint16_t)g_Duty_temp;
//    if (g_Duty_temp >= MPWM->PRD)
//    {
//        g_Duty_temp = MPWM->PRD - 1;
//    }

//    MPWM->DWL = g_Duty_temp;
}

void MPWM_IRQHandler(uint32_t event, void *context)
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
	cfg_u.irq_en_bit.bottom = 0;
	cfg.mode = MPWM_MODE_NORMAL;
	//cfg.chan_mode = 0;
	cfg.counter_mode = MPWM_COUNTER_MODE_UP;
	cfg.clk_div = 80;
	period_data = 1000;   		
	HAL_MPWM_Init(MPWM_ID_0,&cfg,MPWM_IRQHandler,NULL);
  HAL_MPWM_SetIRQConfig(MPWM_ID_0, &cfg_u);
	HAL_MPWM_SetPeriod(MPWM_ID_0,MPWM_PHASE_TYPE_W,period_data);                        //Set Period value uisng this function
	HAL_MPWM_SetDuty(MPWM_ID_0,MPWM_PHASE_TYPE_W,MPWM_OUTPUT_TYPE_L,g_Duty_temp);       //Set Duty value uisng this function
	HAL_MPWM_ControlPWMOutput(MPWM_ID_0,MPWM_PHASE_TYPE_W,MPWM_OUTPUT_TYPE_L,1);  //Contorl PWM output uisng identity phase of PWM
	HAL_MPWM_Start(MPWM_ID_0,MPWM_PHASE_TYPE_W);																	//start MPWM
	HAL_MPWM_EnablePWMOutput(MPWM_ID_0);                                          //Enable PWM output
}
