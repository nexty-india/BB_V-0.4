#include "user_timer.h"
#include "Define.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "NXP_Comm_uart.h"

uint64_t sys_counter = 0;
bool ms_elapsed = false;
extern UART_COMM_PARA_t uart_comm;
extern SYSTEM_DRIVE_EVENT_t SYSTEM_DRIVE_EVENT;
uint16_t counter_150_ms;
/**
 * @brief Timer interrupt handler for application-level timing events.
 *
 *        This function is triggered when a timer event occurs (e.g., count match).
 *        It sets a flag to indicate that 1 ms has elapsed and increments a system counter.
 */
void app_timer_irq_handler(uint32_t event, void *context)
{
	// Check if the timer event is a count match even
	if (event & TIMER_EVENT_COUNT_MATCH)
	{
		// Set the millisecond elapsed flag only once per tick
		if(ms_elapsed == false)
		{
			ms_elapsed = true;
		}
		// Increment system counter 
		sys_counter++;
		
//		g_One_millisecond++;
		SYSTEM_DRIVE_EVENT.DRIVE_STATUS.SYSTEM_EVENT_1_MS_PERIODIC = 1;		
	}
}

/**
 * @brief Initializes and starts Timer 0 with a periodic mode configuration.
 */
void USER_TIMER0_Init(void)
{												 
	struct timer_cfg cfg;
	 
	cfg.mode = TIMER_MODE_PERIODIC;         // Configure the timer for periodic mode
	cfg.clk_sel = TIMER_CLK_DIV_16_PCLK;      // Set clock source: PCLK divided by 16
	cfg.prescaler = 20;												// Set prescaler value to further divide the input clock
	cfg.adc_trig = TIMER_ADC_TRIG_ENABLE;   // Disable ADC trigger from this timer
	cfg.irq_prio = DRIVER_PRIORITY_LOWEST;   // Set lowest interrupt priority for the timer
	
	/* Initialize Timer */
	HAL_TIMER_Init(TIMER_ID_0, &cfg, app_timer_irq_handler, NULL);  /* Initialize Timer 0 with the above configuration */
	HAL_TIMER_Start(TIMER_ID_0, 0xF0);   // Start Timer 0 with a load value (reload count) of 0xF0
} 

/**
 * @brief Returns the current system time in milliseconds.
 *
	* @return uint64_t  The current system time in milliseconds.
 */
uint64_t get_system_time_ms(void)
{
	return sys_counter;
}


/**
 * @brief Implements a non-blocking delay using a system counter.
 */
bool user_delay(uint32_t delay_ms, uint32_t *last_call_ms)
{
	int current_time = get_system_time_ms();
	
	if (*last_call_ms == 0)
	{
		// Initialize the last call time to the current time if it has not been set yet
		*last_call_ms = current_time;
	}
	if (current_time - *last_call_ms >= delay_ms - 1)
	{
		// If the delay has elapsed, update the last call time and return true
		*last_call_ms = 0;
		return true;
	}
	else
	{
		// If the delay has not yet elapsed, return false
		return false;
	}
}


/**
*
*/
