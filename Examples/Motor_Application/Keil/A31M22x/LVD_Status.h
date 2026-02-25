#ifndef _LVD_Status_H_
#define _LVD_Status_H_



#include "a31m22x_scu.h"
#include "a31m22x_system.h"

/* SCU_LVICR */
#define LVI_ENABLE        (1U << 7)
#define LVI_INT_ENABLE    (1U << 6)
#define LVI_AON_ENABLE    (1U << 5)
#define LVI_LEVEL_2V9     (4U << 0)

/* SCU_LVRCR */
#define LVD_RESET_ENABLE_KEY   (0x55U << 8)
#define LVD_AON_ENABLE         (1U << 4)
#define LVD_LEVEL_2V7          (3U << 0)



extern volatile uint8_t g_LVI_Detected;
void Check_LVD_Reset(void);

void LVD_Enable(void);
#endif