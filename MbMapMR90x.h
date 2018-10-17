/*
 * MbMapMR801.h
 *
 *  Created on: 15.05.2017
 *      Author: sagok
 */

#ifndef MBMAPMR90x_H_
#define MBMAPMR90x_H_

#include <bitmask.h>

#if defined (MR901)
#define _REVISION_DEVICE	206		//2.06		 ��������� ��� 13 �������

#define _swREV			"MR901"
#endif
#if defined (MR902)
#define _REVISION_DEVICE	206		//2.06		 ��������� ��� 13 �������

#define _swREV			"MR902"
#endif

#define _swREVverify	""
/*************************************************************************
 * MR901 MR902
 *************************************************************************/
#if defined (MR901) || defined (MR902)
#define MB_Speed					115200
#define MB_Slaveaddr   				1

#define		_delayAfterResponse		5//ms 						// ��� ������ 3.02 �� ���� 10��
//#define		_delayAfterResponse		1// ��� �������

// ���������.
#define range_maxIphs				40		// �������� ����� �� �����
#define range_minIphs				0
#define range_maxI0					40
#define range_minI0					0
#define range_maxIn					40
#define range_minIn					0

#define range_maxPris				40		// �������������

#define range_P						(3*40*256)

#define range_maxZ					256

#define range_maxU					256
#define range_minU					0

#define range_maxF					60
#define range_minF					40

#define range_maxCosF				1
#define range_minCosF				0

// --------------------------------------------------------
// �������
// ������ ������ �� 8
// --------------------------------------------------------
#define MB_WriteSysNoteaddr   		0x0600		//����� � ������� ����� ����� ��������� ��� ������
#define MB_StartSysNoteaddr   		0x0600
#define MB_EndSysNoteaddr   		0x0700

#define MB_NumbSysNote	   			9
#define MB_NumbSysNoteASCII			9
#define MB_SizeSysNote	   			256			// ����� ������� � �������

#define MB_OffsetSysNoteMessage	 	8			// ����� � ������� ��� ���������
// --------------------------------------------------------
#define MB_Code_SysNoteEndJurnal	0
// --------------------------------------------------------

#define MB_offset_Word				0
#define MB_offset_ASCII				8			// �� ������������, � ������� ������

#define MB_StartErrorNoteaddr  		0x0700
#define MB_EndErrorNoteaddr   		0x0800
#define MB_NumbErrorNote			52			// ����� ���� � ����� ������
#define MB_NumbErrorNoteASCII		52			//
#define MB_NextErrorNote			0			// ���������� �� �������

#define MB_OffsetErrorNoteMessage 	0			// ����� � ������� ��� ���������
// --------------------------------------------------------
#define MB_Code_ErrorNoteEndJurnal	0
// --------------------------------------------------------

#define MB_NumbErrorNoteTime		8			// ����� ���� ������� �������
#define MB_SizeErrorNote	   		69			// ����� ������� � �������

// ������ ������������ ---------
#define MB_StartOscNoteaddr			0x0800
#define MB_EndOscNoteaddr   		0x0D00
#define MB_NumbOscNote				20			// ������ ����� ������
#define MB_SizeOscNote	   			100			// ����� ������� � �������

#define MB_NumbOscNoteTime			8			// ����� ���� ������� �������

//#define MB_SizeOscNote	   			(0x9000 - 0x8000)/MB_NumbOscNote			// ����� ������� � �������
#define MB_OffsetOscNoteMessage	 	2			// ����� �� �������� ������ ��� ���� ������. ����� �����. �������� �� ������
// --------------------------------------------------------
#define MB_Code_OscNoteEndJurnal	0
#define MB_Code_OscNoteREADY		8
// ������������ -------------------------------------------
#define MB_StartOscaddr				0x0900
#define MB_SizeAllOsc				0x0D00

#define MB_SizeOscBlock				1024
#define MB_SizeOscFile		   		30000			// ������ �����

#define MB_Osc_POINT				10
#define MB_Osc_LEN					14
// --------------------------------------------------------

// ������ 28����
#define _LimitNoteSize				(MB_NumbErrorNote * 80)		// 64 ������� �� ������� ������	224 ������� �� ������� �������

// --------------------------------------------------------

#define MB_StartOtherUstavkiaddr	0x1000
#define MB_NumbOtherUstavki			(0x10A8 - MB_StartOtherUstavkiaddr)

#define MB_Prisx_Increment			6

#define MB_offset_Config_Pris1		0x1028 - MB_StartOtherUstavkiaddr
#define MB_offset_Config_Pris2		(MB_offset_Config_Pris1 + MB_Prisx_Increment)
#define MB_offset_Config_Pris3		(MB_offset_Config_Pris2 + MB_Prisx_Increment)
#define MB_offset_Config_Pris4		(MB_offset_Config_Pris3 + MB_Prisx_Increment)
#define MB_offset_Config_Pris5		(MB_offset_Config_Pris4 + MB_Prisx_Increment)
#define MB_offset_Config_Pris6		(MB_offset_Config_Pris5 + MB_Prisx_Increment)
#if defined (MR901)
#define MB_offset_Config_Pris7		(MB_offset_Config_Pris6 + MB_Prisx_Increment)
#define MB_offset_Config_Pris8		(MB_offset_Config_Pris7 + MB_Prisx_Increment)
#define MB_offset_Config_Pris9		(MB_offset_Config_Pris8 + MB_Prisx_Increment)
#define MB_offset_Config_Pris10		(MB_offset_Config_Pris9 + MB_Prisx_Increment)
#define MB_offset_Config_Pris11		(MB_offset_Config_Pris10 + MB_Prisx_Increment)
#define MB_offset_Config_Pris12		(MB_offset_Config_Pris11 + MB_Prisx_Increment)
#define MB_offset_Config_Pris13		(MB_offset_Config_Pris12 + MB_Prisx_Increment)
#define MB_offset_Config_Pris14		(MB_offset_Config_Pris13 + MB_Prisx_Increment)
#define MB_offset_Config_Pris15		(MB_offset_Config_Pris14 + MB_Prisx_Increment)
#define MB_offset_Config_Pris16		(MB_offset_Config_Pris15 + MB_Prisx_Increment)
#endif

//�����������z ���� ������
#define MB_offset_Config_Pris_Stat	0				// ������������ ���� ������ 1 ����� ���������
#define MB_offset_KTT				1

// ����
#define MB_bOffset_Config_Pris_Stat	0b011			// ���������

// ������������ �������������� ������ ------------------------------------------
#define MB_StartConfigTRMeas	   	0x109C								// ������������  �������������� ������
#define MB_NumbConfigTRMeas			(0x10A8 - MB_StartConfigTRMeas)		//
#define MB_offset_KTHL				(0x106E - MB_StartConfigTRMeas)
#define MB_offset_KTHX				(0x106F - MB_StartConfigTRMeas)

#define MB_offset_ConfigTT_SH1		(0x109C - MB_StartConfigTRMeas)
#define MB_offset_ConfigTT_SH2		(0x10A0 - MB_StartConfigTRMeas)
#define MB_offset_ConfigTT_PO		(0x10A4 - MB_StartConfigTRMeas)


// ������������ ������� ���������� �������� -------------------------------------
#define MB_StartConfigVLSIn			0x10A8
#define MB_NumbConfigVLSIn			(0x10E8 - MB_StartConfigVLSIn)

// ������������ �������� ���������� �������� -------------------------------------
#define MB_StartConfigVLSOut		0x10E8
#define MB_NumbConfigVLSOut			(0x1208 - MB_StartConfigVLSOut)

// ������ ������� ----------------------------------------------------------------
#define MB_StartUstavkiaddr0		0x1208			// �������� ������ �������
#define MB_StartUstavkiaddr1		0x13DC			// ��������� ������ �������
#define MB_NumbUstavki				(MB_StartUstavkiaddr1 - MB_StartUstavkiaddr0)			// ������ ����� �������			0x1D5

// ������������ ���� ������ ------------------------------------------------------
#define MB_offset_DIFFZ_1			(0x1208 - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������
#define MB_offset_DIFFZ_2			(0x1216 - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������
#define MB_offset_DIFFZ_3			(0x1224 - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������

#define MB_offset_DIFFZ_1m			(0x1232 - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������
#define MB_offset_DIFFZ_2m			(0x1240 - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������
#define MB_offset_DIFFZ_3m			(0x124E - MB_StartUstavkiaddr0)		// ����� ������������ ���� ������

//�����������z ���� ������
#define MB_offset_DIFFZ_Config_Stat		0				// ������������ ���� ������ 1 ����� ���������

// ����
#define MB_bOffset_DIFFZ_Config_Stat	0b11			// ���������

// ������������ ������� ��� ������ -------------------------------------------------
#define MB_StartConfigMTZ_SG0  		0x125c
#define MB_StartConfigMTZ_SG1  		0x1430
#define MB_NumbConfigMTZ			(0x135c - MB_StartConfigMTZ_SG0)

// ������������ ������� ��� ������ -------------------------------------------------
#define MB_offset_MTZ_I1			(0x125C - MB_StartUstavkiaddr0)		// ����� ������������ ������� ��� ������
#define MB_offset_MTZ_I2			(MB_offset_MTZ_I1+8)
#define MB_offset_MTZ_I3			(MB_offset_MTZ_I2+8)
#define MB_offset_MTZ_I4			(MB_offset_MTZ_I3+8)
#define MB_offset_MTZ_I5			(MB_offset_MTZ_I4+8)
#define MB_offset_MTZ_I6			(MB_offset_MTZ_I5+8)
#define MB_offset_MTZ_I7			(MB_offset_MTZ_I6+8)
#define MB_offset_MTZ_I8			(MB_offset_MTZ_I7+8)

#define MB_offset_MTZ_I9			(MB_offset_MTZ_I8+8)
#define MB_offset_MTZ_I10			(MB_offset_MTZ_I9+8)
#define MB_offset_MTZ_I11			(MB_offset_MTZ_I10+8)
#define MB_offset_MTZ_I12			(MB_offset_MTZ_I11+8)
#define MB_offset_MTZ_I13			(MB_offset_MTZ_I12+8)
#define MB_offset_MTZ_I14			(MB_offset_MTZ_I13+8)
#define MB_offset_MTZ_I15			(MB_offset_MTZ_I14+8)
#define MB_offset_MTZ_I16			(MB_offset_MTZ_I15+8)
#define MB_offset_MTZ_I17			(MB_offset_MTZ_I16+8)
#define MB_offset_MTZ_I18			(MB_offset_MTZ_I17+8)
#define MB_offset_MTZ_I19			(MB_offset_MTZ_I18+8)
#define MB_offset_MTZ_I20			(MB_offset_MTZ_I19+8)
#define MB_offset_MTZ_I21			(MB_offset_MTZ_I20+8)
#define MB_offset_MTZ_I22			(MB_offset_MTZ_I21+8)
#define MB_offset_MTZ_I23			(MB_offset_MTZ_I22+8)
#define MB_offset_MTZ_I24			(MB_offset_MTZ_I23+8)
#define MB_offset_MTZ_I25			(MB_offset_MTZ_I24+8)
#define MB_offset_MTZ_I26			(MB_offset_MTZ_I25+8)
#define MB_offset_MTZ_I27			(MB_offset_MTZ_I26+8)
#define MB_offset_MTZ_I28			(MB_offset_MTZ_I27+8)
#define MB_offset_MTZ_I29			(MB_offset_MTZ_I28+8)
#define MB_offset_MTZ_I30			(MB_offset_MTZ_I29+8)
#define MB_offset_MTZ_I31			(MB_offset_MTZ_I30+8)
#define MB_offset_MTZ_I32			(MB_offset_MTZ_I31+8)

//�����������z ������� ��� ������
#define MB_offset_MTZ_I_Config			0							// ������������

// ����
#define MB_bOffset_MTZ_I_Config_Stat	(0b11<<0)			// ���������

// ������������ ������� ����� -----------------------------------
#define MB_StartConfigExZ			(0x135C - MB_StartUstavkiaddr0)
//#define MB_NumbConfigExZ			0x13DC - MB_StartConfigExZ

#define MB_StartConfigExZ_SG0  		0x135c
#define MB_StartConfigExZ_SG1  		0x1530
#define MB_NumbConfigExZ			(0x13dc - MB_StartConfigExZ_SG0)

// ������������ ������� ������ -------------------------------------------------
#define MB_offset_Ext_1				(0x135C - MB_StartUstavkiaddr0)		// ����� ������������ ������� ��� ������
#define MB_offset_Ext_2				(MB_offset_Ext_1+8)
#define MB_offset_Ext_3				(MB_offset_Ext_2+8)
#define MB_offset_Ext_4				(MB_offset_Ext_3+8)
#define MB_offset_Ext_5				(MB_offset_Ext_4+8)
#define MB_offset_Ext_6				(MB_offset_Ext_5+8)
#define MB_offset_Ext_7				(MB_offset_Ext_6+8)
#define MB_offset_Ext_8				(MB_offset_Ext_7+8)
#define MB_offset_Ext_9				(MB_offset_Ext_8+8)
#define MB_offset_Ext_10			(MB_offset_Ext_9+8)
#define MB_offset_Ext_11			(MB_offset_Ext_10+8)
#define MB_offset_Ext_12			(MB_offset_Ext_11+8)
#define MB_offset_Ext_13			(MB_offset_Ext_12+8)
#define MB_offset_Ext_14			(MB_offset_Ext_13+8)
#define MB_offset_Ext_15			(MB_offset_Ext_14+8)
#define MB_offset_Ext_16			(MB_offset_Ext_15+8)

//������������
#define MB_offset_Ext_Config			0			// ������������
// ����
#define MB_bOffset_Ext_Config_Stat		(0b11<<0)		// ���������

// ----------------------------------------------------------------------------------------------
#define MB_StartDiscreetaddr   		0x0D00			// ����� � ������ ��� ������� ������ (3,4)
#define MB_NumbDiscreet   			0x24			// 0x22

#define MB_offset_Jurnals			0x10

//#define MB_offset_ErrorOFF		0x00		// ��������� ����������
//#define MB_bOffsetErrorOFF		(0)		// ��������� ����������

#define MB_offset_SysNote			0x10		// ����� ������ ������� �������
#define MB_bOffsetSysNote			BIT5	// ����� ������ ������� �������

#define MB_offset_ErrorNote			0x10		// ����� ������ ������� ������
#define MB_bOffsetErrorNote			BIT6	// ����� ������ ������� ������

#define MB_offset_OscNote			0x10		// ����� ������  ������� ������������
#define MB_bOffsetOscNote			BIT7	//

#define MB_offset_Jurnals			0x10		// ������� ������������� �� ������� �������
#define MB_bOffsetError				BIT8	// ������� ������������� �� ������� �������


// ---------------------------------
#define MB_offset_SG				0x0D			// ���� �� ������ �������
#define MB_bOffsetSG0				BIT14		// ������ ������� ��������
#define MB_bOffsetSG1				BIT15		// ������ ������� ���������

#define MB_Startaddr_SG_set_0		0x0D06
#define MB_Startaddr_SG_set_1		0x0D07

//#define MB_offset_ErrorOFF		0x0D		// ��������� ����������
//#define MB_bOffsetErrorOFF		1<<0		// ��������� ����������

// ---------------------------------

#define MB_CTRL_OFF					0xFF00
// ---------------------------------
#define MB_offset_errorM1			0x12
#define MB_offset_errorM2			0x12
#define MB_offset_errorM3			0x12
#define MB_offset_errorM4			0x12
#define MB_offset_errorM5			0x12
#define MB_offset_errorUstavki		0x12

#define MB_errorM1					BIT4			// 11R
#define MB_errorM2					BIT5			// 8D 8R
#define MB_errorM3					BIT6			// 16D
#define MB_errorM4					BIT7			// 16D 16R
#define MB_errorM5					BIT8			// 4I 5U

#define MB_offsetHardFaults			0x12			// ������������� ���������� ����������
#define MB_bOffsetModule1			BIT4			// ������� ������������� ������ 1
#define MB_bOffsetModule2			BIT5			// ������� ������������� ������ 2
#define MB_bOffsetModule3			BIT6			// ������� ������������� ������ 3
#define MB_bOffsetModule4			BIT7			// ������� ������������� ������ 4 ������ ������ ���
#define MB_bOffsetModule5			BIT8			// ������� ������������� ������ 5 ������ ��� � ����������
#define MB_bOffsetUstavki			BIT9			// ������� ������������� �������

#define MB_bOffsetALLFaults			(0b111111<<4)	// ������� ����� �������������

// ---------------------------------
#define MB_offsetHardFaults1	0x13			// �������������

#define MB_bOffsetErrorSWAll	0b111100

#define MB_bOffsetErrorTT1		BIT4
#define MB_bOffsetErrorTT2		BIT5
#define MB_bOffsetErrorTT3		BIT6
#define MB_bOffsetErrorUROV1	BIT7

//#define MB_bOffsetErrorCtrl1	1<<6
//#define MB_bOffsetErrorCtrl2	1<<7

// ---------------------------------
#define MB_offset_LogicError		0x12			// ������ �� ������
#define MB_bOffsetALLLogicError		BIT15		//
#define MB_offset_LogicError1		0x13			//
#define MB_bOffsetALLLogicError1	0b1111			//

// ---------------------------------
#define MB_offset_LogicMod			0x10			// ������
#define MB_bOffsetLogicMod_ON		BIT12		// ������ ���������/���������

// ---------------------------------
// --Discreet --
#define MB_offsetDiscreet_1		0x0
#define MB_offsetDiscreet_2		0x0
#define MB_offsetDiscreet_3		0x0
#define MB_offsetDiscreet_4		0x0
#define MB_offsetDiscreet_5		0x0
#define MB_offsetDiscreet_6		0x0
#define MB_offsetDiscreet_7		0x0
#define MB_offsetDiscreet_8		0x0
#define MB_offsetDiscreet_9		0x0
#define MB_offsetDiscreet_10	0x0
#define MB_offsetDiscreet_11	0x0
#define MB_offsetDiscreet_12	0x0
#define MB_offsetDiscreet_13	0x0
#define MB_offsetDiscreet_14	0x0
#define MB_offsetDiscreet_15	0x0
#define MB_offsetDiscreet_16	0x0
#define MB_offsetDiscreet_17	0x1
#define MB_offsetDiscreet_18	0x1
#define MB_offsetDiscreet_19	0x1
#define MB_offsetDiscreet_20	0x1
#define MB_offsetDiscreet_21	0x1
#define MB_offsetDiscreet_22	0x1
#define MB_offsetDiscreet_23	0x1
#define MB_offsetDiscreet_24	0x1

#define MB_bOffset_Discreet_1		BIT0
#define MB_bOffset_Discreet_2		BIT1
#define MB_bOffset_Discreet_3		BIT2
#define MB_bOffset_Discreet_4		BIT3
#define MB_bOffset_Discreet_5		BIT4
#define MB_bOffset_Discreet_6		BIT5
#define MB_bOffset_Discreet_7		BIT6
#define MB_bOffset_Discreet_8		BIT7
#define MB_bOffset_Discreet_9		BIT8
#define MB_bOffset_Discreet_10		BIT9
#define MB_bOffset_Discreet_11		BIT10
#define MB_bOffset_Discreet_12		BIT11
#define MB_bOffset_Discreet_13		BIT12
#define MB_bOffset_Discreet_14		BIT13
#define MB_bOffset_Discreet_15		BIT14
#define MB_bOffset_Discreet_16		BIT15
#define MB_bOffset_Discreet_17		BIT0
#define MB_bOffset_Discreet_18		BIT1
#define MB_bOffset_Discreet_19		BIT2
#define MB_bOffset_Discreet_20		BIT3
#define MB_bOffset_Discreet_21		BIT4
#define MB_bOffset_Discreet_22		BIT5
#define MB_bOffset_Discreet_23		BIT6
#define MB_bOffset_Discreet_24		BIT7

// ---------------------------------
#define MB_offsetRelay_1		0x0E
#define MB_offsetRelay_2		0x0E
#define MB_offsetRelay_3		0x0E
#define MB_offsetRelay_4		0x0E
#define MB_offsetRelay_5		0x0E
#define MB_offsetRelay_6		0x0E
#define MB_offsetRelay_7		0x0E
#define MB_offsetRelay_8		0x0E
#define MB_offsetRelay_9		0x0E
#define MB_offsetRelay_10		0x0E
#define MB_offsetRelay_11		0x0E
#define MB_offsetRelay_12		0x0F
#define MB_offsetRelay_13		0x0F
#define MB_offsetRelay_14		0x0F
#define MB_offsetRelay_15		0x0F
#define MB_offsetRelay_16		0x0F
#define MB_offsetRelay_17		0x0F
#define MB_offsetRelay_18		0x0F

#define MB_bOffset_Relay_1		BIT5
#define MB_bOffset_Relay_2		BIT6
#define MB_bOffset_Relay_3		BIT7
#define MB_bOffset_Relay_4		BIT8
#define MB_bOffset_Relay_5		BIT9
#define MB_bOffset_Relay_6		BIT10
#define MB_bOffset_Relay_7		BIT11
#define MB_bOffset_Relay_8		BIT12
#define MB_bOffset_Relay_9		BIT13
#define MB_bOffset_Relay_10		BIT14
#define MB_bOffset_Relay_11		BIT15
#define MB_bOffset_Relay_12		BIT0
#define MB_bOffset_Relay_13		BIT1
#define MB_bOffset_Relay_14		BIT2
#define MB_bOffset_Relay_15		BIT3
#define MB_bOffset_Relay_16		BIT4
#define MB_bOffset_Relay_17		BIT5
#define MB_bOffset_Relay_18		BIT6

// ---------------------------------
#define MB_offsetLED_1			0x0F
#define MB_offsetLED_2			0x0F
#define MB_offsetLED_3			0x0F
#define MB_offsetLED_4			0x0F
#define MB_offsetLED_5			0x0F
#define MB_offsetLED_6			0x0F
#define MB_offsetLED_7			0x0F
#define MB_offsetLED_8			0x0F
#define MB_offsetLED_9			0x0F
#define MB_offsetLED_10			0x10
#define MB_offsetLED_11			0x10
#define MB_offsetLED_12			0x10
#define MB_offsetLED_13			0x10
#define MB_offsetLED_14			0x10
#define MB_offsetLED_15			0x10
#define MB_offsetLED_16			0x10

#define MB_bOffset_LED_1		BIT7
#define MB_bOffset_LED_2		BIT8
#define MB_bOffset_LED_3		BIT9
#define MB_bOffset_LED_4		BIT10
#define MB_bOffset_LED_5		BIT11
#define MB_bOffset_LED_6		BIT12
#define MB_bOffset_LED_7		BIT13
#define MB_bOffset_LED_8		BIT14
#define MB_bOffset_LED_9		BIT15
#define MB_bOffset_LED_10		BIT0
#define MB_bOffset_LED_11		BIT1
#define MB_bOffset_LED_12		BIT2
#define MB_bOffset_LED_13		BIT3
#define MB_bOffset_LED_14		BIT4
#define MB_bOffset_LED_15		BIT10
#define MB_bOffset_LED_16		BIT11

// SSL -------------------------------
#define MB_offsetSSL_1			0x09
#define MB_offsetSSL_2			0x09
#define MB_offsetSSL_3			0x09
#define MB_offsetSSL_4			0x09
#define MB_offsetSSL_5			0x09
#define MB_offsetSSL_6			0x09
#define MB_offsetSSL_7			0x09
#define MB_offsetSSL_8			0x09
#define MB_offsetSSL_9			0x09
#define MB_offsetSSL_10			0x0A
#define MB_offsetSSL_11			0x0A
#define MB_offsetSSL_12			0x0A
#define MB_offsetSSL_13			0x0A
#define MB_offsetSSL_14			0x0A
#define MB_offsetSSL_15			0x0A
#define MB_offsetSSL_16			0x0A
#define MB_offsetSSL_17			0x0A
#define MB_offsetSSL_18			0x0A
#define MB_offsetSSL_19			0x0A
#define MB_offsetSSL_20			0x0A
#define MB_offsetSSL_21			0x0A
#define MB_offsetSSL_22			0x0A
#define MB_offsetSSL_23			0x0A
#define MB_offsetSSL_24			0x0A
#define MB_offsetSSL_25			0x0A
#define MB_offsetSSL_26			0x0B
#define MB_offsetSSL_27			0x0B
#define MB_offsetSSL_28			0x0B
#define MB_offsetSSL_29			0x0B
#define MB_offsetSSL_30			0x0B
#define MB_offsetSSL_31			0x0B
#define MB_offsetSSL_32			0x0B

#define MB_bOffset_SSL_1		BIT7
#define MB_bOffset_SSL_2		BIT8
#define MB_bOffset_SSL_3		BIT9
#define MB_bOffset_SSL_4		BIT10
#define MB_bOffset_SSL_5		BIT11
#define MB_bOffset_SSL_6		BIT12
#define MB_bOffset_SSL_7		BIT13
#define MB_bOffset_SSL_8		BIT14
#define MB_bOffset_SSL_9		BIT15
#define MB_bOffset_SSL_10		BIT0
#define MB_bOffset_SSL_11		BIT1
#define MB_bOffset_SSL_12		BIT2
#define MB_bOffset_SSL_13		BIT3
#define MB_bOffset_SSL_14		BIT4
#define MB_bOffset_SSL_15		BIT5
#define MB_bOffset_SSL_16		BIT6
#define MB_bOffset_SSL_17		BIT7
#define MB_bOffset_SSL_18		BIT8
#define MB_bOffset_SSL_19		BIT9
#define MB_bOffset_SSL_20		BIT10
#define MB_bOffset_SSL_21		BIT11
#define MB_bOffset_SSL_22		BIT12
#define MB_bOffset_SSL_23		BIT13
#define MB_bOffset_SSL_24		BIT14
#define MB_bOffset_SSL_25		BIT15
#define MB_bOffset_SSL_26		BIT0
#define MB_bOffset_SSL_27		BIT1
#define MB_bOffset_SSL_28		BIT2
#define MB_bOffset_SSL_29		BIT3
#define MB_bOffset_SSL_30		BIT4
#define MB_bOffset_SSL_31		BIT5
#define MB_bOffset_SSL_32		BIT6

// VLS -------------------------------
#define MB_offsetVLS_1			0x02
#define MB_offsetVLS_2			0x02
#define MB_offsetVLS_3			0x02
#define MB_offsetVLS_4			0x02
#define MB_offsetVLS_5			0x02
#define MB_offsetVLS_6			0x02
#define MB_offsetVLS_7			0x02
#define MB_offsetVLS_8			0x02
#define MB_offsetVLS_9			0x03
#define MB_offsetVLS_10			0x03
#define MB_offsetVLS_11			0x03
#define MB_offsetVLS_12			0x03
#define MB_offsetVLS_13			0x03
#define MB_offsetVLS_14			0x03
#define MB_offsetVLS_15			0x03
#define MB_offsetVLS_16			0x03

#define MB_bOffset_VLS_1		BIT8
#define MB_bOffset_VLS_2		BIT9
#define MB_bOffset_VLS_3		BIT10
#define MB_bOffset_VLS_4		BIT11
#define MB_bOffset_VLS_5		BIT12
#define MB_bOffset_VLS_6		BIT13
#define MB_bOffset_VLS_7		BIT14
#define MB_bOffset_VLS_8		BIT15
#define MB_bOffset_VLS_9		BIT0
#define MB_bOffset_VLS_10		BIT1
#define MB_bOffset_VLS_11		BIT2
#define MB_bOffset_VLS_12		BIT3
#define MB_bOffset_VLS_13		BIT4
#define MB_bOffset_VLS_14		BIT5
#define MB_bOffset_VLS_15		BIT6
#define MB_bOffset_VLS_16		BIT7

// LS -------------------------------
#define MB_offsetLS_1			0x01
#define MB_offsetLS_2			0x01
#define MB_offsetLS_3			0x01
#define MB_offsetLS_4			0x01
#define MB_offsetLS_5			0x01
#define MB_offsetLS_6			0x01
#define MB_offsetLS_7			0x01
#define MB_offsetLS_8			0x01
#define MB_offsetLS_9			0x02
#define MB_offsetLS_10			0x02
#define MB_offsetLS_11			0x02
#define MB_offsetLS_12			0x02
#define MB_offsetLS_13			0x02
#define MB_offsetLS_14			0x02
#define MB_offsetLS_15			0x02
#define MB_offsetLS_16			0x02

#define MB_bOffset_LS_1			BIT8
#define MB_bOffset_LS_2			BIT9
#define MB_bOffset_LS_3			BIT10
#define MB_bOffset_LS_4			BIT11
#define MB_bOffset_LS_5			BIT12
#define MB_bOffset_LS_6			BIT13
#define MB_bOffset_LS_7			BIT14
#define MB_bOffset_LS_8			BIT15
#define MB_bOffset_LS_9			BIT0
#define MB_bOffset_LS_10		BIT1
#define MB_bOffset_LS_11		BIT2
#define MB_bOffset_LS_12		BIT3
#define MB_bOffset_LS_13		BIT4
#define MB_bOffset_LS_14		BIT5
#define MB_bOffset_LS_15		BIT6
#define MB_bOffset_LS_16		BIT7

// ---------------------------------

//#define MB_offsetDiscreet13		0x13
//#define MB_offsetDiscreet14		0x14
//#define MB_OffsetLogic			0x00

// ---------------------------------
#define MB_offset_IO_I_1		0x04
#define MB_offset_IO_I_2		0x04
#define MB_offset_IO_I_3		0x04
#define MB_offset_IO_I_4		0x04
#define MB_offset_IO_I_5		0x04

#define MB_offset_IO_I_6		0x05
#define MB_offset_IO_I_7		0x05
#define MB_offset_IO_I_8		0x05
#define MB_offset_IO_I_9		0x05
#define MB_offset_IO_I_10		0x05
#define MB_offset_IO_I_11		0x05
#define MB_offset_IO_I_12		0x05
#define MB_offset_IO_I_13		0x05

#define MB_offset_IO_I_14		0x06
#define MB_offset_IO_I_15		0x06
#define MB_offset_IO_I_16		0x06
#define MB_offset_IO_I_17		0x06
#define MB_offset_IO_I_18		0x06
#define MB_offset_IO_I_19		0x06
#define MB_offset_IO_I_20		0x06
#define MB_offset_IO_I_21		0x06

#define MB_offset_IO_I_22		0x07
#define MB_offset_IO_I_23		0x07
#define MB_offset_IO_I_24		0x07
#define MB_offset_IO_I_25		0x07
#define MB_offset_IO_I_26		0x07
#define MB_offset_IO_I_27		0x07
#define MB_offset_IO_I_28		0x07
#define MB_offset_IO_I_29		0x07

#define MB_offset_IO_I_30		0x08
#define MB_offset_IO_I_31		0x08
#define MB_offset_IO_I_32		0x08

#define MB_b_IO_I1		BIT7		// �0 I>1
#define MB_b_IO_I2		BIT9		// �0 I>2
#define MB_b_IO_I3		BIT11		// �0 I>3
#define MB_b_IO_I4		BIT13		// �0 I>4
#define MB_b_IO_I5		BIT15		// �0 I>5
#define MB_b_IO_I6		BIT1		// �0 I>6
#define MB_b_IO_I7		BIT3		// �0 I>7
#define MB_b_IO_I8		BIT5		// �0 I>8

#define MB_b_IO_I9		BIT7		// �0 I>9
#define MB_b_IO_I10		BIT9		// �0 I>10
#define MB_b_IO_I11		BIT11		// �0 I>11
#define MB_b_IO_I12		BIT13		// �0 I>12
#define MB_b_IO_I13		BIT15		// �0 I>13
#define MB_b_IO_I14		BIT1		// �0 I>14
#define MB_b_IO_I15		BIT3		// �0 I>15
#define MB_b_IO_I16		BIT5		// �0 I>16

#define MB_b_IO_I17		BIT7		// �0 I>17
#define MB_b_IO_I18		BIT9		// �0 I>18
#define MB_b_IO_I19		BIT11		// �0 I>19
#define MB_b_IO_I20		BIT13		// �0 I>20
#define MB_b_IO_I21		BIT15		// �0 I>21
#define MB_b_IO_I22		BIT1		// �0 I>22
#define MB_b_IO_I23		BIT3		// �0 I>23
#define MB_b_IO_I24		BIT5		// �0 I>24

#define MB_b_IO_I25		BIT7		// �0 I>25
#define MB_b_IO_I26		BIT9		// �0 I>26
#define MB_b_IO_I27		BIT11		// �0 I>27
#define MB_b_IO_I28		BIT13		// �0 I>28
#define MB_b_IO_I29		BIT15		// �0 I>29
#define MB_b_IO_I30		BIT1		// �0 I>30
#define MB_b_IO_I31		BIT3		// �0 I>31
#define MB_b_IO_I32		BIT5		// �0 I>32


#define MB_offset_SRAB_I_1		0x04
#define MB_offset_SRAB_I_2		0x04
#define MB_offset_SRAB_I_3		0x04
#define MB_offset_SRAB_I_4		0x04

#define MB_offset_SRAB_I_5		0x05
#define MB_offset_SRAB_I_6		0x05
#define MB_offset_SRAB_I_7		0x05
#define MB_offset_SRAB_I_8		0x05
#define MB_offset_SRAB_I_9		0x05
#define MB_offset_SRAB_I_10		0x05
#define MB_offset_SRAB_I_11		0x05
#define MB_offset_SRAB_I_12		0x05

#define MB_offset_SRAB_I_13		0x06
#define MB_offset_SRAB_I_14		0x06
#define MB_offset_SRAB_I_15		0x06
#define MB_offset_SRAB_I_16		0x06
#define MB_offset_SRAB_I_17		0x06
#define MB_offset_SRAB_I_18		0x06
#define MB_offset_SRAB_I_19		0x06
#define MB_offset_SRAB_I_20		0x06

#define MB_offset_SRAB_I_21		0x07
#define MB_offset_SRAB_I_22		0x07
#define MB_offset_SRAB_I_23		0x07
#define MB_offset_SRAB_I_24		0x07
#define MB_offset_SRAB_I_25		0x07
#define MB_offset_SRAB_I_26		0x07
#define MB_offset_SRAB_I_27		0x07
#define MB_offset_SRAB_I_28		0x07

#define MB_offset_SRAB_I_29		0x08
#define MB_offset_SRAB_I_30		0x08
#define MB_offset_SRAB_I_31		0x08
#define MB_offset_SRAB_I_32		0x08

#define MB_b_SRAB_I1		BIT8		// ���� I>1
#define MB_b_SRAB_I2		BIT10		// ���� I>2
#define MB_b_SRAB_I3		BIT12		// ���� I>3
#define MB_b_SRAB_I4		BIT14		// ���� I>4
#define MB_b_SRAB_I5		BIT0		// ���� I>5
#define MB_b_SRAB_I6		BIT2		// ���� I>6
#define MB_b_SRAB_I7		BIT4		// ���� I>7
#define MB_b_SRAB_I8		BIT6		// ���� I>8

#define MB_b_SRAB_I9		BIT8		// ���� I>9
#define MB_b_SRAB_I10		BIT10		// ���� I>10
#define MB_b_SRAB_I11		BIT12		// ���� I>11
#define MB_b_SRAB_I12		BIT14		// ���� I>12
#define MB_b_SRAB_I13		BIT0		// ���� I>13
#define MB_b_SRAB_I14		BIT2		// ���� I>14
#define MB_b_SRAB_I15		BIT4		// ���� I>15
#define MB_b_SRAB_I16		BIT6		// ���� I>16

#define MB_b_SRAB_I17		BIT8		// ���� I>17
#define MB_b_SRAB_I18		BIT10		// ���� I>18
#define MB_b_SRAB_I19		BIT12		// ���� I>19
#define MB_b_SRAB_I20		BIT14		// ���� I>20
#define MB_b_SRAB_I21		BIT0		// ���� I>21
#define MB_b_SRAB_I22		BIT2		// ���� I>22
#define MB_b_SRAB_I23		BIT4		// ���� I>23
#define MB_b_SRAB_I24		BIT6		// ���� I>24

#define MB_b_SRAB_I25		BIT8		// ���� I>25
#define MB_b_SRAB_I26		BIT10		// ���� I>26
#define MB_b_SRAB_I27		BIT12		// ���� I>27
#define MB_b_SRAB_I28		BIT14		// ���� I>28
#define MB_b_SRAB_I29		BIT0		// ���� I>29
#define MB_b_SRAB_I30		BIT2		// ���� I>30
#define MB_b_SRAB_I31		BIT4		// ���� I>31
#define MB_b_SRAB_I32		BIT6		// ���� I>32

// ������� -----------------------------------------
#define MB_offset_SRAB_ext_1		0x08
#define MB_offset_SRAB_ext_2		0x08
#define MB_offset_SRAB_ext_3		0x08
#define MB_offset_SRAB_ext_4		0x08
#define MB_offset_SRAB_ext_5		0x08
#define MB_offset_SRAB_ext_6		0x08
#define MB_offset_SRAB_ext_7		0x08
#define MB_offset_SRAB_ext_8		0x08
#define MB_offset_SRAB_ext_9		0x08
#define MB_offset_SRAB_ext_10		0x09
#define MB_offset_SRAB_ext_11		0x09
#define MB_offset_SRAB_ext_12		0x09
#define MB_offset_SRAB_ext_13		0x09
#define MB_offset_SRAB_ext_14		0x09
#define MB_offset_SRAB_ext_15		0x09
#define MB_offset_SRAB_ext_16		0x09

#define MB_b_SRAB_ext_1			BIT7
#define MB_b_SRAB_ext_2			BIT8
#define MB_b_SRAB_ext_3			BIT9
#define MB_b_SRAB_ext_4			BIT10
#define MB_b_SRAB_ext_5			BIT11
#define MB_b_SRAB_ext_6			BIT12
#define MB_b_SRAB_ext_7			BIT13
#define MB_b_SRAB_ext_8			BIT14
#define MB_b_SRAB_ext_9			BIT15
#define MB_b_SRAB_ext_10		BIT0
#define MB_b_SRAB_ext_11		BIT1
#define MB_b_SRAB_ext_12		BIT2
#define MB_b_SRAB_ext_13		BIT3
#define MB_b_SRAB_ext_14		BIT4
#define MB_b_SRAB_ext_15		BIT5
#define MB_b_SRAB_ext_16		BIT6

// ���� -----------------------------------------
#define MB_offset_IO_I_d1		0x03
#define MB_offset_IO_I_d2		0x04
#define MB_offset_IO_I_d3		0x04
#define MB_offset_SRAB_I_d1		0x04
#define MB_offset_SRAB_I_d2		0x04
#define MB_offset_SRAB_I_d3		0x04

#define MB_offset_SRAB_I_d1m	0x03
#define MB_offset_SRAB_I_d2m	0x03
#define MB_offset_SRAB_I_d3m	0x03

#define MB_b_IO_I_d1			BIT14
#define MB_b_IO_I_d2			BIT1
#define MB_b_IO_I_d3			BIT4

#define MB_b_SRAB_I_d1			BIT0
#define MB_b_SRAB_I_d2			BIT3
#define MB_b_SRAB_I_d3			BIT6

#define MB_b_SRAB_I_d1m			BIT9
#define MB_b_SRAB_I_d2m			BIT11
#define MB_b_SRAB_I_d3m			BIT13

//���� -----------------------------------------
#define MB_offset_UROV_SH1		0x0B
#define MB_offset_UROV_SH2		0x0B
#define MB_offset_UROV_PO		0x0B
#define MB_offset_UROV_1		0x0B
#define MB_offset_UROV_2		0x0B
#define MB_offset_UROV_3		0x0B
#define MB_offset_UROV_4		0x0B
#define MB_offset_UROV_5		0x0B
#define MB_offset_UROV_6		0x0B
#define MB_offset_UROV_7		0x0C
#define MB_offset_UROV_8		0x0C
#define MB_offset_UROV_9		0x0C
#define MB_offset_UROV_10		0x0C
#define MB_offset_UROV_11		0x0C
#define MB_offset_UROV_12		0x0C
#define MB_offset_UROV_13		0x0C
#define MB_offset_UROV_14		0x0C
#define MB_offset_UROV_15		0x0C
#define MB_offset_UROV_16		0x0C

// 902
#define MB_offset_UROV_PRIn		MB_offset_UROV_6

#define MB_b_UROV_SH1		BIT7
#define MB_b_UROV_SH2		BIT8
#define MB_b_UROV_PO		BIT9
#define MB_b_UROV_1			BIT10
#define MB_b_UROV_2			BIT11
#define MB_b_UROV_3			BIT12
#define MB_b_UROV_4			BIT13
#define MB_b_UROV_5			BIT14
#define MB_b_UROV_6			BIT15
#define MB_b_UROV_7			BIT0
#define MB_b_UROV_8			BIT1
#define MB_b_UROV_9			BIT2
#define MB_b_UROV_10		BIT3
#define MB_b_UROV_11		BIT4
#define MB_b_UROV_12		BIT5
#define MB_b_UROV_13		BIT6
#define MB_b_UROV_14		BIT7
#define MB_b_UROV_15		BIT8
#define MB_b_UROV_16		BIT9

#define MB_b_UROV_PRIn		MB_b_UROV_6
// ----------------------------------------------------------------------------------------------
#define MB_StartAnalogINaddr   	0x0E00		// ���� ������ ��������
// ����� ������ 901 ��� 902
#if defined (MR901)
#define MB_NumbAnalog   		22			//

#define MB_offset_I1			0
#define MB_offset_I2			1
#define MB_offset_I3			2
#define MB_offset_I4			3
#define MB_offset_I5			4
#define MB_offset_I6			5
#define MB_offset_I7			6
#define MB_offset_I8			7
#define MB_offset_I9			8
#define MB_offset_I10			9
#define MB_offset_I11			10
#define MB_offset_I12			11
#define MB_offset_I13			12
#define MB_offset_I14			13
#define MB_offset_I15			14
#define MB_offset_I16			15

#define MB_offset_Id1			16
#define MB_offset_Id2			17
#define MB_offset_Id3			18

#define MB_offset_It1			19
#define MB_offset_It2			20
#define MB_offset_It3			21
#endif//(MR901)

#if defined (MR902)
#define MB_NumbAnalog   		34			// 51 ����


#define MB_offset_I1a			0
#define MB_offset_I1b			1
#define MB_offset_I1c			2

#define MB_offset_I2a			3
#define MB_offset_I2b			4
#define MB_offset_I2c			5

#define MB_offset_I3a			6
#define MB_offset_I3b			7
#define MB_offset_I3c			8

#define MB_offset_I4a			9
#define MB_offset_I4b			10
#define MB_offset_I4c			11

#define MB_offset_I5a			12
#define MB_offset_I5b			13
#define MB_offset_I5c			14

#define MB_offset_In			15

#define MB_offset_Id1a			16
#define MB_offset_Id2a			17
#define MB_offset_Id3a			18

#define MB_offset_It1a			19
#define MB_offset_It2a			20
#define MB_offset_It3a			21

#define MB_offset_Id1b			22
#define MB_offset_Id2b			23
#define MB_offset_Id3b			24

#define MB_offset_It1b			25
#define MB_offset_It2b			26
#define MB_offset_It3b			27

#define MB_offset_Id1c			28
#define MB_offset_Id2c			29
#define MB_offset_Id3c			30

#define MB_offset_It1c			31
#define MB_offset_It2c			32
#define MB_offset_It3c			33

#endif
// ----------------------------------------------------------------------------------------------
#define MB_StartDateNaddr   	0x0200
#define MB_NumbDate		   		7

// ----------------------------------------------------------------------------------------------
#define MB_Startaddr_SG			0x0400
#define MB_addr_SG				0x0400
#define MB_NumbSG		   		1

#define MB_selectGroupe0		0x0000
#define MB_selectGroupe1		0x0001

// ----------------------------------------------------------------------------------------------
#define MB_StartRevNaddr   		0x0500		// ������ 17 ����
#define MB_NumbWordRev	   		16			//

// ������ � ������
#define MB_offset_ModelDev		0x0			// ������ � ������� ����������
#define MB_Model_Size			10			// ������ ������

#define MB_offset_SerNumbDev	(MB_offset_ModelDev + MB_Model_Size)		// ������ � �������� �������
#define MB_SerNumb_Size			7			// ������ ������

#define MB_offset_VersionDev	(MB_offset_SerNumbDev + MB_SerNumb_Size)		// ������ � �������� �������
#define MB_Version_Size			15			// ������ ������
// ----------------------------------------------------------------------------------------------

#define MB_addr_SysNote_OFF		0x0D01
#define MB_addr_ErrorNote_OFF	0x0D02
#define MB_addr_OscNote_OFF		0x0D03
#define MB_addr_Error_OFF		0x0D04
#define MB_addr_LEDS_OFF		0x0D05

#define MB_addr_SGroupe0		0x0D06
#define MB_addr_SGroupe1		0x0D07

#define MB_addr_UstavkiModify	0x0D12		//����� ����� ��������� �������

#define MB_CTRL_OFF				0xFF00

// ��������� ���������� -------------------------------------------------------------------------
#define MB_StartAutomat			0x15B0
#define MB_NumbAutomat			(0x1612 - MB_StartAutomat + 1)

// ��������� ������� (��� �� IP �����) -----------------------------------------------------------
#define MB_StartSystemCfg		0x1612
#define MB_NumbSystemCfg		10
#define MB_offset_IP			4		// F

// ----------------------------------------------------------------------------------------------
// ���� ���� �� ������� ������ 0
#define MB_Startaddr_Goose		0x0D80
#define MB_NumbGoose	   		10

// ----------------------------------------------------------------------------------------------
// ��� ������� ����� ������
// ----------------------------------------------------------------------------------------------
#define MB_StartDUMP_Ustavki	0x01000
#define MB_NumbDUMP_Ustavki	   	(0x1615 - MB_StartDUMP_Ustavki)
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

// ������ ----------------------------------------------------------------------------------------------

#define MB_StartSWCrash   		0
#define MB_Size_SWCrash  		0

#define MB_Size_ConfSW			0

#define MB_addr_DRIVE_UP		0
#define MB_addr_DRIVE_DWN		0

#define MB_addr_SwON			0
#define MB_addr_SwOFF			0

#define MB_StartRPNaddr			0
#define MB_NumbRPN				0

#define MB_StartConfigF_SG0		0
#define MB_NumbConfigF			0

#define MB_StartConfigU_SG0		0
#define MB_NumbConfigU			0

#define MB_StartConfigI2I1I0_SG0	0
#define MB_NumbConfigI2I1I0			0

#define MB_StartConfigOut		0
#define MB_NumbConfigOut		0

#define MB_StartConfigSW		0
#define MB_NumbConfigSW			0

#define MB_StartConfigAPW		0
#define MB_NumbConfigAPW		0

#define MB_StartConfigAWR		0
#define MB_NumbConfigAWR		0

#define MB_StartConfigTRPWR		0
#define MB_NumbConfigTRPWR		0

#define MB_addr_Set_ExtMode		0
#define MB_addr_Clr_ExtMode		0

#define MB_addr_BLK_OFF			0

#endif


#endif /* MBMAPMR90x_H_ */
