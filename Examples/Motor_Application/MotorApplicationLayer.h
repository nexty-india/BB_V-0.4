/**
 *******************************************************************************
 * @file        MotorApplicationLayer.h
 * @author      ABOV R&D Division
 * @brief       
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#ifndef _MOTOR_APPLICATION_LAYER_H_
#define _MOTOR_APPLICATION_LAYER_H_




/*******************************************************************************
* Included File
*******************************************************************************/


/*******************************************************************************
* Public Macro
*******************************************************************************/
#if defined(__DEF_A31M22x__)
/** SPI data size select */
#define SPI_DS_8BITS						((uint32_t)(0))
#define SPI_DS_9BITS						((uint32_t)(1))
#define SPI_DS_16BITS						((uint32_t)(2))
#define SPI_DS_17BITS						((uint32_t)(3))
#define SPI_DS_BITMASK						((uint32_t)(0x3))
/** Clock phase control bit */
#define SPI_CPHA_LO							0
#define SPI_CPHA_HI							1
#define SPI_CPOL_LO							0
#define SPI_CPOL_HI							1
/** SPI MSB/LSB Transmit select bit */
#define SPI_LSB_FIRST						((uint32_t)(0))
#define SPI_MSB_FIRST						((uint32_t)(1))
/** SPI master mode enable */
#define SPI_SLAVE_MODE						((uint32_t)(0))
#define SPI_MASTER_MODE						((uint32_t)(1))
/** SPI interrupt enable */
#define SPI_INTCFG_TXDIE					((uint32_t)SPI_CR_DTXIE_Msk) /** DMA TX done interrupt enable */
#define SPI_INTCFG_RXDIE					((uint32_t)SPI_CR_DRXIE_Msk) /** DMA RX done interrupt enable */
#define SPI_INTCFG_SSCIE					((uint32_t)SPI_CR_SSCIE_Msk) /** SS edge change interrupt enable */
#define SPI_INTCFG_TXIE						((uint32_t)SPI_CR_TXIE_Msk) /** TX interrupt enable */
#define SPI_INTCFG_RXIE						((uint32_t)SPI_CR_RXIE_Msk) /** RX interrupt enable */

/**********************************************************************
 * Macro defines for Macro defines for UART interrupt enable register
 **********************************************************************/
#define UART_IER_DRINT_EN               (0x01UL << UART_IER_DRIE_Pos)   /*!< RBR Interrupt enable*/
#define UART_IER_THREINT_EN             (0x01UL << UART_IER_THREIE_Pos) /*!< THR Interrupt enable*/
#define UART_IER_RLSINT_EN              (0x01UL << UART_IER_RLSIE_Pos)  /*!< RX line status interrupt enable*/
#define UART_IER_TXEINT_EN              (0x01UL << UART_IER_TXEIE_Pos)  /*!< TX exit interrupt enable */
#define UART_IER_DRXINT_EN              (0x01UL << UART_IER_DRXIEN_Pos) /*!< DMA receive done interrupt enable */
#define UART_IER_DTXINT_EN              (0x01UL << UART_IER_DTXIEN_Pos) /*!< DMA transmit done interrupt enable */
#define UART_IER_BITMASK                (0x3F)                          /*!< UART interrupt enable register bit mask */

/**********************************************************************
 * Macro defines for Macro defines for UART interrupt identification register
 **********************************************************************/
#define UART_IIR_INTSTAT_PEND           ((uint8_t)(0x01UL << UART_IIR_IPEN_Pos)) /*!<Interrupt Status - Active low */
#define UART_IIR_INTID_MASK             ((uint8_t)(0x07UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: Interrupt ID mask */
#define UART_IIR_INTID_RDD              ((uint8_t)(0x06UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: Rx DMA status*/
#define UART_IIR_INTID_TDD              ((uint8_t)(0x05UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: Tx DMA status*/
#define UART_IIR_INTID_RLS              ((uint8_t)(0x03UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: Receive line status*/
#define UART_IIR_INTID_RDA              ((uint8_t)(0x02UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: Receive data available*/
#define UART_IIR_INTID_THRE             ((uint8_t)(0x01UL << UART_IIR_IID_Pos))  /*!<Interrupt identification: THRE interrupt*/
#define UART_IIR_BITMASK                ((uint8_t)(0x1F))                        /*!< UART interrupt identification register bit mask */
// Macro defines for Macro defines for UART line control register
#define UART_LCR_WLEN5                  ((uint8_t)(0x00UL << UART_LCR_DLEN_Pos))    /*!< UART 5 bit data mode */
#define UART_LCR_WLEN6                  ((uint8_t)(0x01UL << UART_LCR_DLEN_Pos))    /*!< UART 6 bit data mode */
#define UART_LCR_WLEN7                  ((uint8_t)(0x02UL << UART_LCR_DLEN_Pos))    /*!< UART 7 bit data mode */
#define UART_LCR_WLEN8                  ((uint8_t)(0x03UL << UART_LCR_DLEN_Pos))    /*!< UART 8 bit data mode */
#define UART_LCR_STOPBIT_SEL            ((uint8_t)(0x01UL << UART_LCR_STOPBIT_Pos)) /*!< UART Two Stop Bits Select */
#define UART_LCR_PARITY_EN              ((uint8_t)(0x01UL << UART_LCR_PEN_Pos))     /*!< UART Parity Enable */
#define UART_LCR_PARITY_ODD             ((uint8_t)(0x00UL << UART_LCR_PARITY_Pos))  /*!< UART Odd Parity Select */
#define UART_LCR_PARITY_EVEN            ((uint8_t)(0x01UL << UART_LCR_PARITY_Pos))  /*!< UART Even Parity Select */
#define UART_LCR_STICKP_F1              ((uint8_t)(0x01UL << UART_LCR_STICKP_Pos))  /*!< UART force 1 stick parity */
#define UART_LCR_STICKP_F0              ((uint8_t)(0x00UL << UART_LCR_STICKP_Pos))  /*!< UART force 0 stick parity */
#define UART_LCR_BREAK_EN               ((uint8_t)(0x01UL << UART_LCR_BREAK_Pos))   /*!< UART Transmission Break enable */
#define UART_LCR_BITMASK                ((uint8_t)(0x7F)) /*!< UART line control bit mask */
// Macro defines for Macro defines for UART data control register
#define UART_DCR_TXINV                  ((uint8_t)(0x01UL << UART_DCR_TXINV_Pos)) /*!<data control register: Tx Data Inversion*/
#define UART_DCR_RXINV                  ((uint8_t)(0x01UL << UART_DCR_RXINV_Pos)) /*!<data control register: Rx Data Inversion*/
#define UART_DCR_LBON                   ((uint8_t)(0x01UL << UART_DCR_LBON_Pos))  /*!<data control register: Local loopback test mode*/
#define UART_DCR_BITMASK                ((uint8_t)(0x07UL << 2)) /*!<UART data control bit mask */
// Macro defines for Macro defines for UART line status register
#define UART_LSR_DR                     ((uint8_t)(0x01UL << UART_LSR_DR_Pos))   /*!<Line status register: Receive data ready*/
#define UART_LSR_OE                     ((uint8_t)(0x01UL << UART_LSR_OE_Pos))   /*!<Line status register: Overrun error*/
#define UART_LSR_PE                     ((uint8_t)(0x01UL << UART_LSR_PE_Pos))   /*!<Line status register: Parity error*/
#define UART_LSR_FE                     ((uint8_t)(0x01UL << UART_LSR_FE_Pos))   /*!<Line status register: Framing error*/
#define UART_LSR_BI                     ((uint8_t)(0x01UL << UART_LSR_BI_Pos))   /*!<Line status register: Break interrupt*/
#define UART_LSR_THRE                   ((uint8_t)(0x01UL << UART_LSR_THRE_Pos)) /*!<Line status register: Transmit holding register empty*/
#define UART_LSR_TEMT                   ((uint8_t)(0x01UL << UART_LSR_TEMT_Pos)) /*!<Line status register: Transmitter empty*/
#define UART_LSR_BITMASK                ((uint8_t)(0x7F)) /*!<UART Line status bit mask */


#endif
/*******************************************************************************
* Public Typedef
*******************************************************************************/
typedef enum {
	// Stop the motor
	MAL_FAULT_NONE			= 0x0000,
	MAL_FAULT_IPM			= 0x0001,
	MAL_FAULT_TEMPERATURE	= 0x0002,
	MAL_FAULT_SW_OC			= 0x0004,
	MAL_FAULT_SHUNT_OFFSET	= 0x0008,
	MAL_FAULT_OV_L1			= 0x0010,
	MAL_FAULT_UV_L1			= 0x0020,
	MAL_FAULT_OL_L1			= 0x0040,
	MAL_FAULT_COMMUNICATOIN = 0x0080,
	MAL_FAULT_OV_L0			= 0x0100, // Stop by stop sequence
	MAL_FAULT_STOP			= 0x0FFF,

	// Warning and slow down
	MAL_FAULT_UV_L0			= 0x1000,
	MAL_FAULT_OL_L0			= 0x2000,
} MAL_FAULT_Type;
#if defined(__DEF_A31M22x__)
typedef enum {
	UART_DATABIT_5 = 0, /*!< UART 5 bit data mode */
	UART_DATABIT_6, /*!< UART 6 bit data mode */
	UART_DATABIT_7, /*!< UART 7 bit data mode */
	UART_DATABIT_8  /*!< UART 8 bit data mode */
} UART_DATABIT_Type;

typedef enum {
	UART_PARITY_NONE = 0, /*!< No parity */
	UART_PARITY_ODD,  /*!< Odd parity */
	UART_PARITY_EVEN, /*!< Even parity */
	UART_PARITY_SP1, /*!< Forced "1" stick parity */
	UART_PARITY_SP0  /*!< Forced "0" stick parity */
} UART_PARITY_Type;

typedef enum {
	UART_STOPBIT_1 = 0, /*!< UART 1 Stop Bits Select */
	UART_STOPBIT_2  /*!< UART 2 Stop Bits Select */
} UART_STOPBIT_Type;

typedef struct {
	uint32_t Baud_rate;         /*!< UART baud rate */
	UART_DATABIT_Type Databits; /*!< Number of data bits */
	UART_PARITY_Type Parity;    /*!< Parity selection */
	UART_STOPBIT_Type Stopbits; /*!< Number of stop bits */
} UART_CFG_Type;

typedef enum {
	SCU_SCCR_HCLKDIV_1   = 0x00,
	SCU_SCCR_HCLKDIV_2   = 0x01,
	SCU_SCCR_HCLKDIV_4   = 0x02,
	SCU_SCCR_HCLKDIV_8   = 0x03,
	SCU_SCCR_HCLKDIV_16  = 0x04,
	SCU_SCCR_HCLKDIV_32  = 0x05,
	SCU_SCCR_HCLKDIV_64  = 0x06,
	SCU_SCCR_HCLKDIV_128 = 0x07,
	SCU_SCCR_HCLKDIV_256 = 0x08,
	SCU_SCCR_HCLKDIV_512 = 0x09
} SCU_SCCR_HCLKDIV_Type;

typedef enum {
	SCU_SCCR_PCLKDIV_1  = 0x00,
	SCU_SCCR_PCLKDIV_2  = 0x01,
	SCU_SCCR_PCLKDIV_4  = 0x02,
	SCU_SCCR_PCLKDIV_8  = 0x03,
	SCU_SCCR_PCLKDIV_16 = 0x04
} SCU_SCCR_PCLKDIV_Type;

typedef enum {
	SCU_SCCR_PLLCLKSEL_HSI = 0x00,
	SCU_SCCR_PLLCLKSEL_HSE = 0x01
} SCU_SCCR_PLLCLKSEL_Type;

typedef enum {
	SCU_SCCR_PLLPREDIV_1 = 0x00,
	SCU_SCCR_PLLPREDIV_2 = 0x01,
	SCU_SCCR_PLLPREDIV_4 = 0x02,
	SCU_SCCR_PLLPREDIV_8 = 0x03
} SCU_SCCR_PLLPREDIV_Type;

typedef enum {
	SCU_SCCR_MCLKSEL_LSI = 0x00,
	SCU_SCCR_MCLKSEL_LSE = 0x01,
	SCU_SCCR_MCLKSEL_HSI = 0x02,
	SCU_SCCR_MCLKSEL_HSE = 0x06,
	SCU_SCCR_MCLKSEL_PLL = 0x07,
} SCU_SCCR_MCLKSEL_Type;

typedef enum {
	SCU_COR_CLKOINSEL_LSI  = 0x00,
	SCU_COR_CLKOINSEL_LSE = 0x02,
	SCU_COR_CLKOINSEL_MCLK = 0x04,
	SCU_COR_CLKOINSEL_HSI  = 0x05,
	SCU_COR_CLKOINSEL_HSE  = 0x06,
	SCU_COR_CLKOINSEL_PLL  = 0x07,
} SCU_COR_CLKOINSEL_Type;

typedef enum {
	SCU_MCCR_NUMBER_1 = 0x01,
	SCU_MCCR_NUMBER_3 = 0x03,
	SCU_MCCR_NUMBER_4 = 0x04,
	SCU_MCCR_NUMBER_5 = 0x05,
	SCU_MCCR_NUMBER_6 = 0x06,
	SCU_MCCR_NUMBER_7 = 0x07
} SCU_MCCR_NUMBER_Type;

typedef enum {
	WDT_TYPE,
	SYSTICK_TYPE,
	TIMER03_TYPE,
	PGA_TYPE,
	PGB_TYPE,
	PGC_TYPE,
	PGD_TYPE,
	FRT_TYPE,
	UART_TYPE
} SCU_MCCR_PERIPHERAL_Type;

typedef enum {
	SCU_MCCR_CSEL_LSI  = 0x00,
	SCU_MCCR_CSEL_LSE = 0x01,
	SCU_MCCR_CSEL_MCLK = 0x04,
	SCU_MCCR_CSEL_HSI  = 0x05,
	SCU_MCCR_CSEL_HSE  = 0x06,
	SCU_MCCR_CSEL_PLL  = 0x07
} SCU_MCCR_CSEL_Type;

typedef struct {
	uint32_t Databit; 		/** Databit number, should be 
										- SPI_DS_8BITS :0
										- SPI_DS_9BITS :1
										- SPI_DS_16BITS :2
										- SPI_DS_17BITS :3 */
	uint32_t CPHA;			/** Clock phase, should be:
										- SSP_CPHA_FIRST: first clock edge
										- SSP_CPHA_SECOND: second clock edge */
	uint32_t CPOL;			/** Clock polarity, should be:
										- SSP_CPOL_HI: high level
										- SSP_CPOL_LO: low level */
	uint8_t DataDir;			/** SPI mode, should be:
										- SPI_LSB_FIRST
										- SPI_MSB_FIRST */
	uint32_t Mode;			/** SPI mode, should be:
										- SPI_MASTER_MODE: Master mode
										- SPI_SLAVE_MODE: Slave mode */
	uint32_t BaudRate;		/** PCLK / (BaudRate+1)  BaudRate>=2 (0x0002~0xFFFF */
} SPI_CFG_Type;

typedef enum {
	PH_U,
	PH_V,
	PH_W
} MPWM_PH_VAL;

typedef struct {
	uint32_t ForceMatchEvent_Top;    /*!< Enable force match event at period match update*/
	uint32_t ForceMatchEvent_Bottom; /*!< Enable force match event at bottom update */
	uint32_t ClockDivider;           /*!< Clock Divider, MPWM Clock = HCLK / (ClockDivider + 1), CLKDIV Bit */
	uint32_t Mode;                   /*!< Mode, MOTORB Bit */
	uint32_t OLR_Update;             /*!< Update timing of OLR, UOL Bit */
	uint32_t OLR_Top;                /*!< Update OLR at period match, TUOL Bit */
	uint32_t OLR_Bottom;             /*!< Update OLR at bottom, BUOL Bit */
	uint32_t Duty_Update;            /*!< Update timing of duty and period, UAO Bit */
	uint32_t Duty_Top;               /*!< Update duty and period at period match, TUP Bit */
	uint32_t Duty_Bottom;            /*!< Update duty and period at bottom, BUP Bit */
	uint32_t MPWM_Mode;              /*!< MPWM mode, MCHMOD Bit */
} MPWM_MODE_Type;

typedef struct {
	uint32_t Enable_DT;     /*!< Enable dead-time, DTEN Bit */
	uint32_t Enable_SP;     /*!< Enable short-protection, PSHRT Bit */
	uint32_t Ouput_HDT;     /*!< Output level at high side during dead-time, HDTOL Bit */
	uint32_t Ouput_LDT;     /*!< Output level at low side during dead-time, LDTOL Bit */
	uint32_t Prescale;      /*!< Prescale of dead-time, DTCLK Bit */
	uint32_t DeadTime_High; /*!< Dead-time of high side, HDT Bit */
	uint32_t DeadTime_LOw;  /*!< Dead-time of low side, LDT Bit */
} MPWM_DEAD_TIME_Type;

typedef struct {
	uint32_t Update;    /*!< Update timing of ATR, ATUDT Bit */
	uint32_t Mode;    /*!< ADC trigger mode, ATMOD Bit */
	uint32_t Count;    /*!< ADC trigger count, ATCNT Bit */
} MPWM_ADC_TRIGGER_Type;

#endif

/*******************************************************************************
* Exported Public Variable
*******************************************************************************/



/*******************************************************************************
* Exported Public Function
*******************************************************************************/


void MAL_MainLoop(void);
void turn_off_compressor(void);

#endif // _MOTOR_APPLICATION_LAYER_H_

/* --------------------------------- End Of File ------------------------------ */
