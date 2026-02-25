#include "LVD_Status.h"
#include "Flash_Writing.h"


volatile uint8_t g_LVI_Detected = 0;
bool g_LVD_Reset;
void LVI_IRQHandler(void)
{
    /* Voltage is dropping */
    g_LVI_Detected = 1;

    /* Immediately stop flash write */
    g_Flash_Write = 0;

    /* Clear LVI interrupt flag */
    SCU->LVISR |= (1U << 1);   // LVDIFLAG (per manual)
}


void LVD_Enable(void)
{
    /* Enable LVR reset source */
    SCU->RSER |= (1U << 2);   // LVDRST enable

    /* Enable LVI (interrupt – early warning) */
    SCU->LVICR =
        LVI_ENABLE |
        LVI_INT_ENABLE |
        LVI_AON_ENABLE |
        LVI_LEVEL_2V9;

    /* Enable LVR (reset – brown-out protection) */
    SCU->LVRCR =
        LVD_RESET_ENABLE_KEY |
        LVD_AON_ENABLE |
        LVD_LEVEL_2V7;
}



void Check_LVD_Reset(void)
{
    if (SCU->LVRCR & (1U << 6))   // LVDRF
    {
        g_LVD_Reset = 1;
    }

    /* Clear reset flag */
    SCU->LVRCR |= (1U << 6);
}


