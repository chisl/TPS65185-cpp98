/*
 * name:        TPS65185
 * description: Single chip PMIC for E Ink (R) Vizplex (TM) Enabled Electronic Paper Display
 * manuf:       Texas Instruments
 * version:     0.1
 * url:         http://www.ti.com/lit/ds/symlink/tps65185.pdf
 * date:        2016-08-01
 * author       https://chisl.io/
 * file:        TPS65185.hpp
 */

#include <cinttypes>

/* Derive from class TPS65185_Base and implement the read and write functions! */

/* TPS65185: Single chip PMIC for E Ink (R) Vizplex (TM) Enabled Electronic Paper Display */
class TPS65185_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	virtual uint16_t read16(uint16_t address, uint16_t n=16) = 0;  // 16 bit read
	virtual void write(uint16_t address, uint16_t value, uint16_t n=16) = 0;  // 16 bit write
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG TMST_VALUE                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG TMST_VALUE:
	 * Thermistor value read by ADC signed int, in ˚C
	 * 1111 0110 – < -10°C
	 * 1111 0110 – -10°C
	 * 1111 0111 – -9°C
	 * ...
	 * 1111 1110 – -2°C
	 * 1111 1111 – -1°C
	 * 0000 0000 – 0°C
	 * 0000 0001 – 1°C
	 * 0000 0010 – 2°C
	 * ...
	 * 0001 1001 – 25°C
	 * ...
	 * 0101 0101 – 85°C
	 * 0101 0101 – > 85°C
	 */
	struct TMST_VALUE
	{
		static const uint16_t __address = 0;
		
		/* Bits TEMP: */
		struct TEMP
		{
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register TMST_VALUE */
	void setTMST_VALUE(uint8_t value)
	{
		write(TMST_VALUE::__address, value, 8);
	}
	
	/* Get register TMST_VALUE */
	uint8_t getTMST_VALUE()
	{
		return read8(TMST_VALUE::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG ENABLE                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG ENABLE:
	 * Enable/disable bits for regulators
	 */
	struct ENABLE
	{
		static const uint16_t __address = 1;
		
		/* Bits ACTIVE: */
		/*
		 * 1 = Transition from STANDBY to ACTIVE mode. Rails power up as defined by UPSEQx
		 * registers.
		 * 0 = No effect.
		 * NOTE: After transition bit is cleared automatically
		 */
		struct ACTIVE
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits STANDBY: */
		/*
		 * Transition from STANDBY to ACTIVE mode. Rails power up as defined by DWNSEQx
		 * registers.
		 * NOTE: After transition bit is cleared automatically.
		 * STANDBY bit has priority over AVTIVE.
		 */
		struct STANDBY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits V3P3_EN: */
		/* VIN3P3 to V3P3 switch enable (1=ON)  */
		struct V3P3_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits VCOM_EN: */
		/* VCOM buffer enable (1 = enabled)  */
		struct VCOM_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits VDDH_EN: */
		/* VDDH charge pump enable (1 = enabled)  */
		struct VDDH_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits VPOS_EN: */
		/*
		 * VPOS LDO regulator enable. (1 = enabled)
		 * NOTE: VPOS cannot be enabled before VNEG is enabled.
		 */
		struct VPOS_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits VEE_EN: */
		/* VEE charge pump enable (1 = enabled)  */
		struct VEE_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits VNEG_EN: */
		/*
		 * VNEG LDO regulator enable. (1 = enabled)
		 * NOTE: When VNEG is disabled VPOS will also be disabled.
		 */
		struct VNEG_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register ENABLE */
	void setENABLE(uint8_t value)
	{
		write(ENABLE::__address, value, 8);
	}
	
	/* Get register ENABLE */
	uint8_t getENABLE()
	{
		return read8(ENABLE::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG VADJ                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG VADJ:
	 * VPOS/VNEG voltage adjustment
	 */
	struct VADJ
	{
		static const uint16_t __address = 2;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b00100; // 5'b100
			static const uint8_t mask = 0b11111000; // [3,4,5,6,7]
		};
		/* Bits VSET: */
		/* VPOS and VNEG voltage setting  */
		struct VSET
		{
			static const uint8_t dflt = 0b011; // 3'b11
			static const uint8_t mask = 0b00000111; // [0,1,2]
			static const uint8_t unused_0 = 0b00; // not valid
			static const uint8_t unused_1 = 0b01; // not valid
			static const uint8_t unused_2 = 0b10; // not valid
			static const uint8_t V15 = 0b11; // 15V
			static const uint8_t V14_75 = 0b100; // 14.75V
			static const uint8_t V14_5 = 0b101; // 14.5V
			static const uint8_t V15_25 = 0b110; // 15.25V
			static const uint8_t unused_3 = 0b111; // reserved
		};
	};
	
	/* Set register VADJ */
	void setVADJ(uint8_t value)
	{
		write(VADJ::__address, value, 8);
	}
	
	/* Get register VADJ */
	uint8_t getVADJ()
	{
		return read8(VADJ::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG VCOM                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG VCOM:
	 * VCOM voltage setting, byteorder little
	 */
	struct VCOM
	{
		static const uint16_t __address = 3;
		
		/* Bits ACQ: */
		/*
		 * Kick-back voltage acquisition bit.
		 * 1 - starts kick-back voltage measurement routine.
		 * NOTE: After measurement is complete bit is cleared automatically and measurement
		 * result is reflected in VCOM[8:0] bits.
		 */
		struct ACQ
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b1000000000000000; // [15]
		};
		/* Bits PROG: */
		/*
		 * VCOM programming bit.
		 * 1 - VCOM[8:0] value is committed to nonvolatile memory and becomes new power-up
		 * default.
		 * NOTE: After programming bit is cleared automatically and TPS65185 will enter
		 * STANDBY mode.
		 */
		struct PROG
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b0100000000000000; // [14]
		};
		/* Bits HiZ: */
		/*
		 * VCOM HiZ bit.
		 * 1 - VCOM pin is placed into hi-impedance state to allow VCOM measurement
		 * 0 - VCOM amplifier is connected to VCOM pin
		 */
		struct HiZ
		{
			static const uint16_t dflt = 0b0; // 1'b0
			static const uint16_t mask = 0b0010000000000000; // [13]
		};
		/* Bits AVG: */
		/*
		 * Number of acquisitions that is averaged to a single kick-back voltage measurement
		 * NOTE: When the ACQ bit is set, the state machine repeat the A/D conversion of the
		 * kick-back voltage AVD[1:0] times and returns a single, averaged, value to VCOM[8:0]
		 */
		struct AVG
		{
			static const uint16_t dflt = 0b00; // 2'b0
			static const uint16_t mask = 0b0001100000000000; // [11,12]
			static const uint16_t AVG1x = 0b00; // 
			static const uint16_t AVG2x = 0b01; // 
			static const uint16_t AVG4x = 0b10; // 
			static const uint16_t AVG8x = 0b11; // 
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint16_t dflt = 0b10; // 2'b10
			static const uint16_t mask = 0b0000011000000000; // [9,10]
		};
		/* Bits VCOM: */
		/*
		 * VCOM voltage adjustment
		 * VCOM = -10 mV * VCOM[8:0] in the range from 0 mV to -5.110 V
		 * 0x000h – 0 0000 0000 – –0 mV
		 * 0x001h – 0 0000 0001 – –10 mV
		 * 0x002h – 0 0000 0010 – –20 mV
		 * ...
		 * 0x07Dh - 0 0111 1101 – –1250 mV
		 * ...
		 * 0x1FEh – 1 1111 1110 – –5100 mV
		 * 0x1FFh – 1 1111 1111 – –5110 mV
		 * 
		 */
		struct VCOM_
		{
			static const uint16_t dflt = 0b001111101; // 9'b1111101
			static const uint16_t mask = 0b0000000111111111; // [0,1,2,3,4,5,6,7,8]
		};
	};
	
	/* Set register VCOM */
	void setVCOM(uint16_t value)
	{
		write(VCOM::__address, value, 16);
	}
	
	/* Get register VCOM */
	uint16_t getVCOM()
	{
		return read16(VCOM::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG INT_EN1                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG INT_EN1:
	 * Interrupt enable group1
	 * 1 = enabled, 0 = disabled
	 */
	struct INT_EN1
	{
		static const uint16_t __address = 5;
		
		/* Bits DTX_EN: */
		/* Panel temperature-change interrupt enable */
		struct DTX_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits TSD_EN: */
		/* Thermal shutdown interrupt enable */
		struct TSD_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits HOT_EN: */
		/* Thermal shutdown early warning enable */
		struct HOT_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits TMST_HOT_EN: */
		/* Thermistor hot interrupt enable */
		struct TMST_HOT_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits TMST_COLD_EN: */
		/* Thermistor cold interrupt enable */
		struct TMST_COLD_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits UVLO_EN: */
		/* VIN under voltage detect interrupt enable */
		struct UVLO_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits ACQC_EN: */
		/* VCOM acquisition complete interrupt enable */
		struct ACQC_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits PRGC_EN: */
		/* VCOM programming complete interrupt enable */
		struct PRGC_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register INT_EN1 */
	void setINT_EN1(uint8_t value)
	{
		write(INT_EN1::__address, value, 8);
	}
	
	/* Get register INT_EN1 */
	uint8_t getINT_EN1()
	{
		return read8(INT_EN1::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG INT_EN2                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG INT_EN2:
	 * Interrupt enable group2
	 * 1 = enabled, 0 = disabled
	 */
	struct INT_EN2
	{
		static const uint16_t __address = 6;
		
		/* Bits VBUVEN: */
		/* Positive boost converter under voltage detect interrupt enable */
		struct VBUVEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits VDDHUVEN: */
		/* VDDH under voltage detect interrupt enable */
		struct VDDHUVEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits VNUV_EN: */
		/* Inverting buck-boost converter under voltage detect interrupt enable */
		struct VNUV_EN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits VPOSUVEN: */
		/* VPOS under voltage detect interrupt enable */
		struct VPOSUVEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits VEEUVEN: */
		/* VEE under Voltage detect interrupt enable */
		struct VEEUVEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits VCOMFEN: */
		/* VCOM FAULT interrupt enable */
		struct VCOMFEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits VNEGUVEN: */
		/* VNEG under Voltage detect interrupt enable */
		struct VNEGUVEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits EOCEN: */
		/* Temperature ADC end of conversion interrupt enable */
		struct EOCEN
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register INT_EN2 */
	void setINT_EN2(uint8_t value)
	{
		write(INT_EN2::__address, value, 8);
	}
	
	/* Get register INT_EN2 */
	uint8_t getINT_EN2()
	{
		return read8(INT_EN2::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG INT1                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG INT1:
	 * Interrupt group1 DEFAULT '0xxxxx00
	 */
	struct INT1
	{
		static const uint16_t __address = 7;
		
		/* Bits DTX: */
		/*
		 * Panel temperature-change interrupt, 1 - temperature has changed by 3 deg or more
		 * over previous reading
		 */
		struct DTX
		{
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits TSD: */
		/* Thermal shutdown interrupt */
		struct TSD
		{
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits HOT: */
		/* Thermal shutdown early warning */
		struct HOT
		{
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits TMST_HOT: */
		/*
		 * Thermistor hot interrupt. 1 - thermistor temperature is equal or greater than
		 * TMST_HOT threshold
		 */
		struct TMST_HOT
		{
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits TMST_COLD: */
		/*
		 * Thermistor cold interrupt. 1 - thermistor temperature is equal or less than
		 * TMST_COLD threshold
		 */
		struct TMST_COLD
		{
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits UVLO: */
		/* VIN under voltage detect interrupt. 1 - input voltage is below UVLO threshold  */
		struct UVLO
		{
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits ACQC: */
		/* VCOM acquisition complete */
		struct ACQC
		{
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits PRGC: */
		/* VCOM programming complete */
		struct PRGC
		{
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register INT1 */
	void setINT1(uint8_t value)
	{
		write(INT1::__address, value, 8);
	}
	
	/* Get register INT1 */
	uint8_t getINT1()
	{
		return read8(INT1::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG INT2                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG INT2:
	 * Interrupt group2
	 */
	struct INT2
	{
		static const uint16_t __address = 8;
		
		/* Bits VB_UV: */
		/*
		 * Positive boost converter undervoltage detect interrupt 1 - under-voltage on
		 * DCDC1 detected
		 */
		struct VB_UV
		{
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits VDDH_UV: */
		/* VDDH under voltage detect interrupt on VDDH charge pump  */
		struct VDDH_UV
		{
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits VN_UV: */
		/*
		 * Inverting buck-boost converter under voltage detect interrupt 1 -
		 * undervoltage on DCDC2 detected
		 */
		struct VN_UV
		{
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits VPOS_UV: */
		/* VPOS undervoltage detect interrupt 1 - undervoltage on LDO1(VPOS) detected  */
		struct VPOS_UV
		{
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits VEE_UV: */
		/* VEE undervoltage detect interrupt 1 - undervoltage on VEE charge pump detected  */
		struct VEE_UV
		{
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits VCOMF: */
		/*
		 * VCOM fault detection 1 - fault on VCOM detected
		 * (VCOM is outside normal operating range)
		 */
		struct VCOMF
		{
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits VNEG_UV: */
		/* VNEG undervoltage detect interrupt  1 - undervoltage on LDO2(VNEG) detected  */
		struct VNEG_UV
		{
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits EOC: */
		/*
		 * ADC end of conversion interrupt 1 - ADC conversion is complete
		 * (temperature acquisition is complete)
		 */
		struct EOC
		{
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register INT2 */
	void setINT2(uint8_t value)
	{
		write(INT2::__address, value, 8);
	}
	
	/* Get register INT2 */
	uint8_t getINT2()
	{
		return read8(INT2::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG UPSEQ0                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG UPSEQ0:
	 * Power-up strobe assignment
	 */
	struct UPSEQ0
	{
		static const uint16_t __address = 9;
		
		/* Bits VDDH_UP: */
		/* VDDH power-up order  */
		struct VDDH_UP
		{
			static const uint8_t dflt = 0b11; // 2'b11
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VPOS_UP: */
		/* VPOS power-up order  */
		struct VPOS_UP
		{
			static const uint8_t dflt = 0b10; // 2'b10
			static const uint8_t mask = 0b00110000; // [4,5]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VEE_UP: */
		/* VEE power-up order  */
		struct VEE_UP
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00001100; // [2,3]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VNEG_UP: */
		/* VNEG power-up order  */
		struct VNEG_UP
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
	};
	
	/* Set register UPSEQ0 */
	void setUPSEQ0(uint8_t value)
	{
		write(UPSEQ0::__address, value, 8);
	}
	
	/* Get register UPSEQ0 */
	uint8_t getUPSEQ0()
	{
		return read8(UPSEQ0::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG UPSEQ1                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG UPSEQ1:
	 * Power-up sequence delay times
	 */
	struct UPSEQ1
	{
		static const uint16_t __address = 10;
		
		/* Bits UDLY4: */
		/* DLY4 delay time set; defines the delay time from STROBE3 to STROBE4  */
		struct UDLY4
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t delay3ms = 0b00; // 
			static const uint8_t delay6ms = 0b01; // 
			static const uint8_t delay9ms = 0b10; // 
			static const uint8_t delay12ms = 0b11; // 
		};
		/* Bits UDLY3: */
		/* DLY3 delay time set; defines the delay time from STROBE2 to STROBE3  */
		struct UDLY3
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00110000; // [4,5]
			static const uint8_t delay3ms = 0b00; // 
			static const uint8_t delay6ms = 0b01; // 
			static const uint8_t delay9ms = 0b10; // 
			static const uint8_t delay12ms = 0b11; // 
		};
		/* Bits UDLY2: */
		/* DLY2 delay time set; defines the delay time from STROBE1 to STROBE2   */
		struct UDLY2
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00001100; // [2,3]
			static const uint8_t delay3ms = 0b00; // 
			static const uint8_t delay6ms = 0b01; // 
			static const uint8_t delay9ms = 0b10; // 
			static const uint8_t delay12ms = 0b11; // 
		};
		/* Bits UDLY: */
		/* DLY1 delay time set; defines the delay time from VN_PG high to STROBE1  */
		struct UDLY
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t delay3ms = 0b00; // 
			static const uint8_t delay6ms = 0b01; // 
			static const uint8_t delay9ms = 0b10; // 
			static const uint8_t delay12ms = 0b11; // 
		};
	};
	
	/* Set register UPSEQ1 */
	void setUPSEQ1(uint8_t value)
	{
		write(UPSEQ1::__address, value, 8);
	}
	
	/* Get register UPSEQ1 */
	uint8_t getUPSEQ1()
	{
		return read8(UPSEQ1::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG DWNSEQ0                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG DWNSEQ0:
	 * Power-down strobe assignment
	 */
	struct DWNSEQ0
	{
		static const uint16_t __address = 11;
		
		/* Bits VDDH_DWN: */
		/* VDDH power-down order  */
		struct VDDH_DWN
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VPOS_DWN: */
		/* VPOS power-down order  */
		struct VPOS_DWN
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00110000; // [4,5]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VEE_DWN: */
		/* VEE power-down order  */
		struct VEE_DWN
		{
			static const uint8_t dflt = 0b11; // 2'b11
			static const uint8_t mask = 0b00001100; // [2,3]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
		/* Bits VNEG_DWN: */
		/* VNEG power-down order  */
		struct VNEG_DWN
		{
			static const uint8_t dflt = 0b10; // 2'b10
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t STROBE1 = 0b00; // 
			static const uint8_t STROBE2 = 0b01; // 
			static const uint8_t STROBE3 = 0b10; // 
			static const uint8_t STROBE4 = 0b11; // 
		};
	};
	
	/* Set register DWNSEQ0 */
	void setDWNSEQ0(uint8_t value)
	{
		write(DWNSEQ0::__address, value, 8);
	}
	
	/* Get register DWNSEQ0 */
	uint8_t getDWNSEQ0()
	{
		return read8(DWNSEQ0::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG DWNSEQ1                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG DWNSEQ1:
	 * Power-down sequence delay times
	 */
	struct DWNSEQ1
	{
		static const uint16_t __address = 12;
		
		/* Bits DDLY4: */
		/* DLY4 delay time set; defines the delay time from STROBE3 to STROBE4  */
		struct DDLY4
		{
			static const uint8_t dflt = 0b11; // 2'b11
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t delay6ms = 0b00; // 
			static const uint8_t delay12ms = 0b01; // 
			static const uint8_t delay24ms = 0b10; // 
			static const uint8_t delay48ms = 0b11; // 
		};
		/* Bits DDLY3: */
		/* DLY3 delay time set; defines the delay time from STROBE2 to STROBE3  */
		struct DDLY3
		{
			static const uint8_t dflt = 0b10; // 2'b10
			static const uint8_t mask = 0b00110000; // [4,5]
			static const uint8_t delay6ms = 0b00; // 
			static const uint8_t delay12ms = 0b01; // 
			static const uint8_t delay24ms = 0b10; // 
			static const uint8_t delay48ms = 0b11; // 
		};
		/* Bits DDLY2: */
		/* DLY2 delay time set; defines the delay time from STROBE1 to STROBE2  */
		struct DDLY2
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00001100; // [2,3]
			static const uint8_t delay6ms = 0b00; // 
			static const uint8_t delay12ms = 0b01; // 
			static const uint8_t delay24ms = 0b10; // 
			static const uint8_t delay48ms = 0b11; // 
		};
		/* Bits DDLY1: */
		/* DLY2 delay time set; defines the delay time from WAKEUP low to STROBE1  */
		struct DDLY1
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
			static const uint8_t delay3ms = 0b0; // 
			static const uint8_t delay6ms = 0b1; // 
		};
		/* Bits DFCTR: */
		/* At power-down delay time DLY2[1:0], DLY3[1:0], DLY4[1:0] are multiplied with DFCTR[1:0]  */
		struct DFCTR
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
			static const uint8_t multiply1x = 0b0; // 
			static const uint8_t multiply16x = 0b1; // 
		};
	};
	
	/* Set register DWNSEQ1 */
	void setDWNSEQ1(uint8_t value)
	{
		write(DWNSEQ1::__address, value, 8);
	}
	
	/* Get register DWNSEQ1 */
	uint8_t getDWNSEQ1()
	{
		return read8(DWNSEQ1::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG TMST1                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG TMST1:
	 * Thermistor configuration
	 */
	struct TMST1
	{
		static const uint16_t __address = 13;
		
		/* Bits READ_THERM: */
		/*
		 * Read thermistor value. 1 - initiates temperature acquisition
		 * NOTE: Bit is self-cleared after acquisition is completed
		 */
		struct READ_THERM
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits CONV_END: */
		/* ADC conversion done flag */
		struct CONV_END
		{
			static const uint8_t dflt = 0b1; // 1'b1
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits unused_2: */
		struct unused_2
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits unused_3: */
		struct unused_3
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits DT: */
		/*
		 * Panel temperature-change interrupt threshold DTX interrupt is issued when
		 * difference between most recent temperature reading and baseline temperature
		 * is equal to or greater than threshold value. See Hot, Cold, and
		 * Temperature-Change Interrupts for details.
		 */
		struct DT
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t TEMP2C = 0b00; // 2°C
			static const uint8_t TEMP3C = 0b01; // 3°C
			static const uint8_t TEMP4C = 0b10; // 4°C
			static const uint8_t TEMP5C = 0b11; // 5°C
		};
	};
	
	/* Set register TMST1 */
	void setTMST1(uint8_t value)
	{
		write(TMST1::__address, value, 8);
	}
	
	/* Get register TMST1 */
	uint8_t getTMST1()
	{
		return read8(TMST1::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG TMST2                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG TMST2:
	 * Thermistor register 2: hot/cold temperature setting,
	 * default cold=0C, hot=50C
	 */
	struct TMST2
	{
		static const uint16_t __address = 14;
		
		/* Bits TMST_COLD: */
		/*
		 * Thermistor COLD threshold
		 * NOTE: An interrupt is issued when thermistor temperature is equal or less
		 * than COLD threshold
		 * temp = -7C + TMST_COLD
		 */
		struct TMST_COLD
		{
			static const uint8_t dflt = 0b0111; // 4'b111
			static const uint8_t mask = 0b11110000; // [4,5,6,7]
		};
		/* Bits TMST_HOT: */
		/*
		 * Thermistor HOT threshold
		 * NOTE: An interrupt is issued when thermistor temperature is equal or greater
		 * than HOT threshold
		 * temp = 42C + TMST_HOT
		 */
		struct TMST_HOT
		{
			static const uint8_t dflt = 0b1000; // 4'b1000
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register TMST2 */
	void setTMST2(uint8_t value)
	{
		write(TMST2::__address, value, 8);
	}
	
	/* Get register TMST2 */
	uint8_t getTMST2()
	{
		return read8(TMST2::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                              REG PG                                               *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG PG:
	 * Power good status each rails
	 */
	struct PG
	{
		static const uint16_t __address = 15;
		
		/* Bits VB_PG: */
		/* Positive boost converter power good. 1 - DCDC1 is in regulation */
		struct VB_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits VDDH_PG: */
		/* VDDH power good. 1 - VDDH charge pump is in regulation */
		struct VDDH_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits VN_PG: */
		/* Inverting buck-boost power good. 1 - DCDC2 is in regulation */
		struct VN_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits VPOS_PG: */
		/* VPOS power good. 1 - LDO1(VPOS) is in regulation */
		struct VPOS_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits VEE_PG: */
		/* VEE power good. 1 - VEE charge pump is in regulation */
		struct VEE_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits VNEG_PG: */
		/* VNEG power good. 1 - LDO2(VNEG) is in regulation */
		struct VNEG_PG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register PG */
	void setPG(uint8_t value)
	{
		write(PG::__address, value, 8);
	}
	
	/* Get register PG */
	uint8_t getPG()
	{
		return read8(PG::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG REVID                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG REVID:
	 * Device revision ID information
	 */
	struct REVID
	{
		static const uint16_t __address = 16;
		
		/* Bits MJREV: */
		struct MJREV
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t TPS65185_1p0 = 0b00; // 
			static const uint8_t TPS65185_1p1 = 0b01; // 
			static const uint8_t TPS65185_1p2 = 0b10; // 
		};
		/* Bits MNREV: */
		struct MNREV
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00110000; // [4,5]
		};
		/* Bits VERSION: */
		struct VERSION
		{
			static const uint8_t dflt = 0b0101; // 4'b101
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register REVID */
	void setREVID(uint8_t value)
	{
		write(REVID::__address, value, 8);
	}
	
	/* Get register REVID */
	uint8_t getREVID()
	{
		return read8(REVID::__address, 8);
	}
	
};
