#include "Default_Values.h"
/* Place the constant into section FLASH_PARAMS (linker maps it to desired address).
 * Keep `used` attribute so the compiler/linker doesn't discard it even if unused.
 */
//#define FLASH_START_ADDR  (0x0000FE00U)   // Make sure this is valid in Flash

__attribute__((at(INPUT_REG_MIN_START_ADDR))) 
const uint32_t Input_Reg_Min_Start_Addr[] = {
    0,      /* INPUT_MOTOR_STATUS_MIN */
    0,      /* INPUT_FAULT_CODE_MIN */
    0,      /* INPUT_MOTOR_SPEED_MIN */
    0,      /* INPUT_MOTOR_CURRENT_MIN */
    0,      /* INPUT_DC_VOLTAGE_MIN */
    0,      /* INPUT_KW_MIN */
    200,    /* INPUT_WINDING_TEMPERATURE_MIN */
    1338,   /* INPUT_IGBT_TEMPERATURE_MIN */
    0,      /* INPUT_POWER_ON_HOURS_MIN */
    0,      /* INPUT_RUN_HOURS_MIN */
    0,      /* INPUT_DI1_STATUS_MIN */
    0,      /* INPUT_KWH_MIN */
    0,      /* INPUT_RESERVED_13_MIN */
    10000,  /* INPUT_TARGET_SPEED_MODBUS_MIN */
    0,      /* INPUT_FIRE_STATUS_MIN */
    0,      /* INPUT_FAIL_SAFE_STATUS_MIN */
    0,      /* INPUT_FILTER_STATUS_MIN */
    0,      /* INPUT_FILTER_RUN_HOURS_MIN */
    0,      /* INPUT_AI1_VALUE_MIN */
    0,      /* INPUT_AI1_CALCULATED_VALUE_MIN */
    0,      /* INPUT_AI_VALUE_MIN */
    0,      /* INPUT_AI_CALCULATED_VALUE_MIN */
    0,      /* INPUT_RESERVED_3_MIN */
    0,      /* INPUT_RESERVED_4_MIN */
    0,      /* INPUT_LAST_ERROR_CODE_1ST_MIN */
    0,      /* INPUT_LAST_ERROR_CODE_2ND_MIN */
    0,      /* INPUT_LAST_ERROR_CODE_3RD_MIN */
    0,      /* INPUT_LAST_ERROR_CODE_4TH_TIME_MIN */
    0,      /* INPUT_RESERVED_9_MIN */
    0,      /* INPUT_RESERVED_30_MIN */
    0,      /* INPUT_RESERVED_31_MIN */
    0,      /* INPUT_RESERVED_32_MIN */
    0,      /* INPUT_RESERVED_33_MIN */
    0,      /* INPUT_RESERVED_34_MIN */
    0,      /* INPUT_RESERVED_35_MIN */
    0,      /* INPUT_RESERVED_36_MIN */
    0,      /* INPUT_RESERVED_37_MIN */
    0,      /* INPUT_RESERVED_38_MIN */
    0,      /* INPUT_RESERVED_39_MIN */
    0,      /* INPUT_RESERVED_40_MIN */
    0,      /* INPUT_RESERVED_41_MIN */
    0,      /* INPUT_RESERVED_42_MIN */
    0,      /* INPUT_RESERVED_43_MIN */
    0,      /* INPUT_RESERVED_44_MIN */
    0,      /* INPUT_RESERVED_45_MIN */
    0,      /* INPUT_RESERVED_46_MIN */
    0,      /* INPUT_RESERVED_47_MIN */
    0,      /* INPUT_RESERVED_48_MIN */
    0,      /* INPUT_RESERVED_49_MIN */
    0,      /* INPUT_TORQUE_MIN */
    0,      /* INPUT_LOAD_MIN */
    50,     /* INPUT_OPERATING_FREQUENCY_MIN */
    0       /* INPUT_ACUTAL_MOTOR_SPEED_RATED_MIN */
};

	

__attribute__((at(INPUT_REG_MAX_START_ADDR))) 
const uint32_t Input_Reg_Max_Start_Addr[] = {
    4,       /* INPUT_MOTOR_STATUS_MAX */
    65535,   /* INPUT_FAULT_CODE_MAX */
    10000,   /* INPUT_MOTOR_SPEED_MAX */
    2493,    /* INPUT_MOTOR_CURRENT_MAX */
    778,     /* INPUT_DC_VOLTAGE_MAX */
    6000,    /* INPUT_KW_MAX */
    320,     /* INPUT_WINDING_TEMPERATURE_MAX */
    3553,    /* INPUT_IGBT_TEMPERATURE_MAX */
    65535,   /* INPUT_POWER_ON_HOURS_MAX */
    65535,   /* INPUT_RUN_HOURS_MAX */
    1,       /* INPUT_DI1_STATUS_MAX */
    65535,   /* INPUT_KWH_MAX */
    0,       /* INPUT_RESERVED_13_MAX */
    10000,   /* INPUT_TARGET_SPEED_MODBUS_MAX */
    1,       /* INPUT_FIRE_STATUS_MAX */
    1,       /* INPUT_FAIL_SAFE_STATUS_MAX */
    1,       /* INPUT_FILTER_STATUS_MAX */
    65535,   /* INPUT_FILTER_RUN_HOURS_MAX */
    1000,    /* INPUT_AI1_VALUE_MAX */
    10,      /* INPUT_AI1_CALCULATED_VALUE_MAX */
    1000,    /* INPUT_AI_VALUE_MAX */
    20,      /* INPUT_AI_CALCULATED_VALUE_MAX */
    0,       /* INPUT_RESERVED_3_MAX */
    0,       /* INPUT_RESERVED_4_MAX */
    65525,   /* INPUT_LAST_ERROR_CODE_1ST_MAX */
    65525,   /* INPUT_LAST_ERROR_CODE_2ND_MAX */
    65525,   /* INPUT_LAST_ERROR_CODE_3RD_MAX */
    65525,   /* INPUT_LAST_ERROR_CODE_4TH_TIME_MAX */
    0,       /* INPUT_RESERVED_9_MAX */
    0,       /* INPUT_RESERVED_30_MAX */
    0,       /* INPUT_RESERVED_31_MAX */
    0,       /* INPUT_RESERVED_32_MAX */
    0,       /* INPUT_RESERVED_33_MAX */
    0,       /* INPUT_RESERVED_34_MAX */
    0,       /* INPUT_RESERVED_35_MAX */
    0,       /* INPUT_RESERVED_36_MAX */
    0,       /* INPUT_RESERVED_37_MAX */
    0,       /* INPUT_RESERVED_38_MAX */
    0,       /* INPUT_RESERVED_39_MAX */
    0,       /* INPUT_RESERVED_40_MAX */
    0,       /* INPUT_RESERVED_41_MAX */
    0,       /* INPUT_RESERVED_42_MAX */
    0,       /* INPUT_RESERVED_43_MAX */
    0,       /* INPUT_RESERVED_44_MAX */
    0,       /* INPUT_RESERVED_45_MAX */
    0,       /* INPUT_RESERVED_46_MAX */
    0,       /* INPUT_RESERVED_47_MAX */
    0,       /* INPUT_RESERVED_48_MAX */
    0,       /* INPUT_RESERVED_49_MAX */
    750,     /* INPUT_TORQUE_MAX */
    100,     /* INPUT_LOAD_MAX */
    60,      /* INPUT_OPERATING_FREQUENCY_MAX */
    10000    /* INPUT_ACUTAL_MOTOR_SPEED_RATED_MAX */
};

	

__attribute__((at(HOLDING_REG_MAX_START_ADDR))) 
const uint32_t Holding_Reg_Max_Start_Addr[] = {
    247,    // Max Node address
    65535,  // Max Baud Rate
    3,      // Max Parity Bit
    6,      // Max Stop bit
    5,      // Max Control Bit
    3,      // Max Fan Rotation
    3000,   // Max Maximum Speed
    3000,   // Max Minimum Speed
    100,    // Max Ramp Up
    100,    // Max Ramp Down
    0,      // Max Reserved
    0,      // Max Reserved
    3000,   // Max Minimum Running Speed
    100,    // Max Ai0 Min Value
    100,    // Max Ai0 Max Value
    0,      // Max Reserved
    0,      // Max Reserved
    3000,   // Max Speed set from Modbus
    3000,   // Max Modbus Signal loss speed
    2,      // Max Control Bit
    5,      // Max Set Internal Speed
    3000,   // Max Internal speed 0
    3000,   // Max Internal speed 1
    3000,   // Max Internal speed 3
    5,      // Max Disable Temperature Management
    0,      // Max Reserved
    0,      // Max Reserved
    1000,   // Max Target Set point
    1000,   // Max Kp Constant
    1000,   // Max Ki Constant
    1000,   // Max Control signal max limit
    1000,   // Max Control Signal Min limit
    0,      // Max Pid Sensor Select
    0,      // Max Reserved
    0,      // Max Reserved
    2,      // Max Fire Alarm activate
    5,      // Max Fire Alarm Mode source
    5,      // Max Fire Alarm Control Source
    3000,   // Max Set speed in Fire alarm mode
    0,      // Max Reserved
    0,      // Max Reserved
    0,      // Max Reserved
    5000,   // Max Set Filter Run hour
    2,      // Max Reset Filter Run hour
    0,      // Max Reserved
    0,      // Max Reserved
    0,      // Max Reserved
    3,      // Max Di0 Enable Function
    3,      // Max Fail Function Active
    4,      // Max Fail Safe Source
    3000,   // Max Fail Safe Set Speed
    3,      // Max Fail Safe Running Direction
    12,     // Max Fail Safe Activate At set value
    0,      // Max Reserved
	65535,  // Max SUPPRESSION_RANGE_SETTING
    65535,  // Max Upper Voltage Min
    65535,  // Max Upper Voltage Max
    65535,  // Max Lower Voltage Min
    65535,  // Max Lower Voltage Max
    65535,  // Max Winding Temperature Min
    65535,  // Max Winding Temperature Max
    65535,  // Max IGBT Temperature Min
    65535,  // Max IGBT Temperature Max
    65535,  // Max Motor Current Min
    65535,  // Max Motor Current Max
    65535,  // Max Upper Ambient Temperature Min
    65535,  // Max Upper Ambient Temperature Max
    65535,  // Max Lower Ambient Temperature Min
    65535,  // Max Lower Ambient Temperature Max
    65535,      // Max Overpowered Min
    65535,      // Max Overpowered Max
    0,  		// Max Reserved
    0,  		// Max Reserved
    65535,  // Max DC Over Voltage Limit
    65535,  // Max Under Voltage Limit
    65535,  // Max Overload Limit
    65535,  // Max OverSpeed Limit
    65535,  // Max IPM Temperature Limit
    65535,  // Max Winding Temperature Limit
    65535,  // Max Over RMS Voltage Limit
    65535,  // Max Under RMS Voltage Limit
    0,      // Max Reserved
    0,      // Max Reserved
    0,      // Max Reserved
    0,      // Max Reserved
    65535,  // Max Recovery DC Over Voltage Limit
    65535,  // Max Recovery DC Under Voltage Limit
    65535,  // Max Recovery Overload Limit
    65535,  // Max Recovery Overspeed Limit
    65535,  // Max Anti-lock Retries Rotor Lock
    65535,  // Max Recovery IPM Temperature Limit
    65535,  // Max Recovery Winding Temperature Limit
    65535,  // Max Recovery Over AC Voltage Limit
    65535,  // Max Recovery Under AC Voltage Limit
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max LED Mode
    65535,  // Max K0 Function
    65535,  // Max VibFrq_1
    65535,  // Max VibFrq_2
    65535,  // Max VibFrq_3
    65535,  // Max VibFrq_4
    65535,  // Max VibFrq_5
    65535,  // Max VibFrq_6
    65535,  // Max VibFrq_7
    65535,  // Max VibFrq_8
    65535,  // Max VibFrq_9
    65535,  // Max VibFrq_10
    65535,  // Max VibFrq_11
    65535,  // Max VibFrq_12
    65535,  // Max VibFrq_13
    65535,  // Max VibFrq_14
    65535,  // Max VibFrq_15
    65535,  // Max MOTORMODEL1
    65535,  // Max MOTORMODEL2
    65535,  // Max MOTORMODEL3
    65535,  // Max MOTORMODEL4
    65535,  // Max MOTORMODEL5
    65535,  // Max MOTORMODEL6
    65535,  // Max MOTORMODEL7
	65535,  // Max MOTORMODEL8
    65535,  // Max MOTORMACHINE1
    65535,  // Max MOTORMACHINE2
    65535,  // Max MOTORMACHINE3
    65535,  // Max MOTORMACHINE4
    65535,  // Max MOTORMACHINE5
    65535,  // Max MOTORMACHINE6
    65535,  // Max MOTORPRODUCTION_YEAR
    65535,  // Max MOTORPRODUCTION_MONTH
    65535,  // Max MOTORPRODUCTION_DAY
    65535,  // Max DRIVEMODELNAME1
    65535,  // Max DRIVEMODELNAME2
    65535,  // Max DRIVEMODELNAME3
    65535,  // Max DRIVEMODELNAME4
    65535,  // Max DRIVEMODELNAME5
    65535,  // Max DRIVEMODELNAME6
    65535,  // Max DRIVEMODELNAME7
	65535,  // Max DRIVEMODELNAME8
    65535,  // Max DRIVEMACHINENUMBER1
    65535,  // Max DRIVEMACHINENUMBER2
    65535,  // Max DRIVEMACHINENUMBER3
    65535,  // Max DRIVEMACHINENUMBER4
    65535,  // Max DRIVEMACHINENUMBER5
    65535,  // Max DRIVEMACHINENUMBER6
    65535,  // Max DRIVEPRODUCTION_YEAR
    65535,  // Max DRIVEPRODUCTION_MONTH
    65535,  // Max DRIVEPRODUCTION_DAY
    65535,  // Max Rated Current
    65535,  // Max Drive input voltage min range
    65535,  // Max Drive input voltage max range
    65535,  // Max Maximum current rating
    65535,  // Max Output max power
    65535,  // Max Frequency max range
    65535,  // Max Frequency min range
	  65535,  // Max Drive Frequency max range
    65535,  // Max Drive Frequency min range
    65535,  // Max Power rating
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Line input frequency min range
    65535,  // Max Line input frequency max range
    65535,  // Max Number of poles
    65535,  // Max Torque Constant
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Flash Writing
    65535,  // Max Set Default factory
    65535,  // Max Reserved
    65535,  // Max Reserved
    65535,  // Max Switching Frequency
    65535,   // Max Block protection Change of Direction
		65535,
		65535,
		65535,
		65535,
//		180,  // Max Holding Register
};

__attribute__((at(HOLDING_REG_MIN_START_ADDR))) 
const uint32_t Holding_Reg_Min_Start_Addr[] = {
    0,   // Min Node address
    0,   // Min Baud Rate
    0,   // Min Parity Bit
    0,   // Min Stop bit
    0,   // Min Control Bit
    0,   // Min Fan Rotation
    0,   // Min Maximum Speed
    0,   // Min Minimum Speed
    0,   // Min Ramp Up
    0,   // Min Ramp Down
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Minimum Running Speed
    0,   // Min Ai0 Min Value
    0,   // Min Ai0 Max Value
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Speed set from Modbus
    0,   // Min Modbus Signal loss speed
    0,   // Min Control Bit
    0,   // Min Set Internal Speed
    0,   // Min Internal speed 0
    0,   // Min Internal speed 0
    0,   // Min Internal speed 3
    0,   // Min Disable Temperature Management
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Target Set point
    0,   // Min Kp Constant
    0,   // Min Ki Constant
    0,   // Min Control signal max limit
    0,   // Min Control Signal Min limit
    0,   // Min Pid Sensor Select
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Fire Alarm activate
    0,   // Min Fire Alarm Mode source
    0,   // Min Fire Alarm Control Source
    0,   // Min Set speed in Fire alarm mode
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Set Filter Run hour
    0,   // Min Reset Filter Run hour
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Di0 Enable Function
    0,   // Min Fail Function Active
    0,   // Min Fail Safe Source
    0,   // Min Fail Safe Set Speed
    0,   // Min Fail Safe Running Direction
    0,   // Min Fail Safe Activate At set value
    0,   // Min Reserved
    0,   // Min Set Suppression Range Setting
    0,   // Min Upper Voltage Min
    0,   // Min Upper Voltage Max
    0,   // Min Lower Voltage Min
    0,   // Min Lower Voltage Max
    0,   // Min Winding Temperature Min
    0,   // Min Winding Temperature Max
    0,   // Min IGBT Temperature Min
    0,   // Min IGBT Temperature Max
    0,   // Min Motor Current Min
    0,   // Min Motor Current Max
    0,   // Min Upper Ambient Temperature Min
    0,   // Min Upper Ambient Temperature Max
    0,   // Min Lower Ambient Temperature Min
    0,   // Min Lower Ambient Temperature Max
    0,   // Min Overpowered Min
    0,   // Min Overpowered Max
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min DC Over Voltage Limit
    0,   // Min Under Voltage Limit
    0,   // Min Overload Limit
    0,   // Min OverSpeed Limit
    0,   // Min IPM Temperature Limit
    0,   // Min Winding Temperature Limit
    0,   // Min Over RMS Voltage Limit
    0,   // Min Under RMS Voltage Limit
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Recovery DC Over Voltage Limit
    0,   // Min Recovery DC Under Voltage Limit
    0,   // Min Recovery Overload Limit
    0,   // Min Recovery Overspeed Limit
    0,   // Min Anti-lock Retries Rotor Lock
    0,   // Min Recovery IPM Temperature Limit
    0,   // Min Recovery Winding Temperature Limit
    0,   // Min Recovery Over AC Voltage Limit
    0,   // Min Recovery Under AC Voltage Limit
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min LED Mode
    0,   // Min K0 Function
    0,   // Min VibFrq_0
    0,   // Min VibFrq_1
    0,   // Min VibFrq_3
    0,   // Min VibFrq_4
    0,   // Min VibFrq_5
    0,   // Min VibFrq_6
    0,   // Min VibFrq_7
    0,   // Min VibFrq_8
    0,   // Min VibFrq_9
    0,   // Min VibFrq_10
    0,   // Min VibFrq_11
    0,   // Min VibFrq_12
    0,   // Min VibFrq_13
    0,   // Min VibFrq_14
    0,   // Min VibFrq_15
    0,   // Min MOTORMODEL0
    0,   // Min MOTORMODEL1
    0,   // Min MOTORMODEL3
    0,   // Min MOTORMODEL4
    0,   // Min MOTORMODEL5
    0,   // Min MOTORMODEL6
    0,   // Min MOTORMODEL7
    0,   // Min MOTORMODEL8
    0,   // Min MOTORMACHINE0
    0,   // Min MOTORMACHINE1
    0,   // Min MOTORMACHINE3
    0,   // Min MOTORMACHINE4
    0,   // Min MOTORMACHINE5
    0,   // Min MOTORMACHINE6
    0,   // Min MOTORPRODUCTION_YEAR
    0,   // Min MOTORPRODUCTION_MONTH
    0,   // Min MOTORPRODUCTION_DAY
    0,   // Min DRIVEMODELNAME0
    0,   // Min DRIVEMODELNAME1
    0,   // Min DRIVEMODELNAME3
    0,   // Min DRIVEMODELNAME4
    0,   // Min DRIVEMODELNAME5
    0,   // Min DRIVEMODELNAME6
    0,   // Min DRIVEMODELNAME7
    0,   // Min DRIVEMODELNAME8
    0,   // Min DRIVEMACHINENUMBER0
    0,   // Min DRIVEMACHINENUMBER1
    0,   // Min DRIVEMACHINENUMBER3
    0,   // Min DRIVEMACHINENUMBER4
    0,   // Min DRIVEMACHINENUMBER5
    0,   // Min DRIVEMACHINENUMBER6
    0,   // Min DRIVEPRODUCTION_YEAR
    0,   // Min DRIVEPRODUCTION_MONTH
    0,   // Min DRIVEPRODUCTION_DAY
    0,   // Min Rated Current
    0,   // Min Drive input voltage min range
    0,   // Min Drive input voltage max range
    0,   // Min Maximum current rating
    0,   // Min Output max power
    0,   // Min Frequency max range
    0,   // Min Frequency min range
    0,   // Min Frequency max range
    0,   // Min Frequency min range
    0,   // Min Power rating
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Line input frequency min range
    0,   // Min Line input frequency max range
    6,   // Min Number of poles
    0,   // Min Torque Constant
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Flash Writing
    0,   // Min Set Default factory
    0,   // Min Reserved
    0,   // Min Reserved
    0,   // Min Switching Frequency
    0,   // Min Block protection Change of Direction
		0,
		0,
		0,
		0,
		1,
//    180, // Min Holding Register
	};
		
	__attribute__((at(HOLDING_REG_DEFAULT_START_ADDR))) 
const uint32_t Holding_Reg_Default_Start_Addr[] = {
	1      , //Default Node address
	9600  , //Default Baud Rate
	0      , //Default Parity Bit
	3      , //Default Stop bit
	3      , //Default Control BIt
	0      , //Default Fan Rotation
	1800   , //Default Maximum Speed
	400    , //Default Minimum Speed
	0      , //Default Ramp Up
	0      , //Default Ramp Down
	0      , //Default Reserved 
	0      , //Default Reserved
	300    , //Default Minimum Running Speed
	20     , //Default Ai1 Min Value
	80     , //Default Ai1 Max Value
	0      , //Default Reserved
	0      , //Default Reserved
	500   , //Default Speed set from Modbus
	1800   , //Default Modbus Signal loss speed
	0      , //Default Control Bit
	1      , //Default Set Internal Speed
	1000   , //Default Internal speed 1
	1500   , //Default Internal speed 2
	1800   , //Default Internal speed 3
	0      , //Default Disable Temperature Management
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Target Set point
	0      , //Default Kp Constant
	0      , //Default Ki Constant
	0      , //Default Control signal max limit
	0      , //Default Control SIgnal Min limit
	0      , //Default Pid Sensor Select
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Fire Alarm activate
	0      , //Default Fire Alarm Mode source
	1      , //Default Fire Alarm Conrol Source
	1200   , //Default Set speed in Fire alarm mode
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	1200   , //Default Set Filter Run hour
	0      , //Default Reset Filter Run hour
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Di1 Enable Function
	0      , //Default Fail Function Active
	1      , //Default Fail Safe Soruce
	1200   , //Default Fail Safe Set Speed 
	1      , //Default Fail Safe Running Direction
	2      , //Default Fail Safe Activate At set value
	5     , //Default Reserved
	0      , //Default Set Suppression Range Setting
	500    , //Default Upper Voltage Min
	520    , //Default Upper Voltage Max
	360    , //Default Lower Voltage Min
	380    , //Default Lower Voltage Max
	90     , //Default Winding Temperature Min
	100    , //Default Winding Temperature Max
	35     , //Default IGBT Temperature Min
	50    , //Default IGBT Temperature Max
	15     , //Default Motor Current Min 
	15     , //Default Motor Current Max
	90     , //Default Upper Ambient Temperature Min
	100    , //Default Upper Ambient Temperature Max
	90     , //Default Lower Ambient Temperature Min
	100    , //Default Lower Ambient Temperature Max
	6000   , //Default Overpowered Min
	6200   , //Default Overpowered Max
	3      , //Default Reserved 
	0      , //Default Reserved
	1600    , //Default Current limit
	270    , //Default Under Voltage Limit
	6000   , //Default overload Limt
	2200   , //Default OverSpeed Limit
	120    , //Default Ipm Temperature Limit
	120    , //Default Winding Temperature Limit
	495    , //Default Over Rms Voltage Limit
	320    , //Default Under Rms Voltage Limit
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved 
	0      , //Default Reserved
	540    , //Default Recovery Dc Over voltage limit
	350    , //Default Recovery DC Under Voltage Limit
	5700   , //Default Recovery overload limit
	1900   , //Default Recovery overspeed limit 
	5      , //Default Anti lock Retries rotor lock
	100     , //Default Recovery ipm temperature limit
	110     , //Default Recovery Winding Temperature limit
	440    , //Default Recovery over ac voltage limit
	350    , //Default Recovery under ac voltage limit
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	1      , //Default Led Mode
	1      , //Default K1 Function
	0      , //Default VibFrq_1
	0      , //Default VibFrq_2
	0      , //Default VibFrq_3
	0      , //Default VibFrq_4
	0      , //Default VibFrq_5
	0      , //Default VibFrq_6
	0      , //Default VibFrq_7
	0      , //Default VibFrq_8
	0      , //Default VibFrq_9
	0      , //Default VibFrq_10
	0      , //Default VibFrq_11
	0      , //Default VibFrq_12
	0      , //Default VibFrq_13
	0      , //Default VibFrq_14
	0      , //Default VibFrq_15
	9      , //Default MOTORMODEL1
	9      , //Default MOTORMODEL2
	9      , //Default MOTORMODEL3
	9      , //Default MOTORMODEL4
	9      , //Default MOTORMODEL5
	9      , //Default MOTORMODEL6
	9      , //Default MOTORMODEL7
	9      , //Default MOTORMODEL8
	8      , //Default MOTORMACHINE1
	8      , //Default MOTORMACHINE2
};

__attribute__((at(HOLDING_REG_DEFAULT_START_ADDR_LOW))) 
const uint32_t Holding_Reg_Default_Start_Addr_lOW[] = {
	8      , //Default MOTORMACHINE3
	8      , //Default MOTORMACHINE4
	8      , //Default MOTORMACHINE5
	8      , //Default MOTORMACHINE6
	2026   , //Default MOTORPRODUCTION_YEAR
	1      , //Default MOTORPRODUCTION_MONTH
	1      , //Default MOTORPRODUCTION_DAY
	1      , //Default DRIVEMODELNAME1
	1      , //Default DRIVEMODELNAME2
	1      , //Default DRIVEMODELNAME3
	1      , //Default DRIVEMODELNAME4
	1      , //Default DRIVEMODELNAME5
	1      , //Default DRIVEMODELNAME6
	1      , //Default DRIVEMODELNAME7
	1      , //Default DRIVEMODELNAME8 
	2      , //Default DRIVEMACHINENUMBER1
	2      , //Default DRIVEMACHINENUMBER2
	2      , //Default DRIVEMACHINENUMBER3
	2      , //Default DRIVEMACHINENUMBER4
	2      , //Default DRIVEMACHINENUMBER5
	2      , //Default DRIVEMACHINENUMBER6
	2026   , //Default DRIVEPRODUCTION_YEAR
	1      , //Default DRIVEPRODUCITON_MONTH
	1      , //Default DRIVEPRODUCITON_DAY
	12     , //Default Rated Current
	380    , //Default Drive input voltage min range
	480    , //Default Drive input voltage max range
	15     , //Default maximum current rating
	6000   , //Default output max power
	60     , //Default frequency max range 
	50     , //Default Frequency min range
	60     , //Default frequency max range
	50     , //Default frequency min range
	5700   , //Default power rating
	0      , //Default Reserved
	0      , //Default Reserved
	50     , //Default line input frequency min range
	60     , //Default line input frequency max range
	6      , //Default no of poles
	15     , //Default Torque Constant
	0			 , //Default Rated Torque
	0      , //Default Reserved  
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Reserved
	0      , //Default Flash Writing
	0      , //Default Set Default factory
	0      , //Default Reserved  
	0      , //Default Reserved 
	4000   , //Default Switching Frequency
	0      , //Default Block protection Change of Direction
	0			 , //BMS Function 
	0			 , //Reset Events
	0			 , //Static Pressure Filter   
	500    , //Remaing Service Life 
	0      , //Drive is configured from the software
	111,
	};
