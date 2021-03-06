/*
 * datatoRREC.c
 *
 *  Created on: 20.04.2017
 *      Author: sagok
 */





#include "main.h"

#include "iec850.h"
#include "iec61850_server.h"

#include "datatoMMXU.h"
#include "dataDbzeroDB.h"
/*******************************************************
 * MR5_600
 *******************************************************/
#if defined (MR5_600)
#include "static_model_MR5_600.h"

/*******************************************************
 * ��������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime ){return false;}

#endif
/*******************************************************
 * MR851
 *******************************************************/
#if defined (MR851)
#include "static_model_MR851.h"

/*******************************************************
 * ��������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime ){return false;}

#endif

/*******************************************************
 * MR801 T12N5D58R51
 *******************************************************/
#if defined	(MR801) && defined (T12N5D58R51)
#include "static_model_MR801_T12N5D58R51.h"

#if defined (AN_PERV)
extern float   ucMAnalogInBuf[];
#else
	#if defined (AN_DUBLEDATA)
	extern	uint32_t   ucMAnalogInBuf[MB_Size_Analog/2];
	#else
	extern	uint16_t   ucMAnalogInBuf[MB_Size_Analog];
	#endif
#endif
extern uint16_t   ucMDiscInBuf[MB_Size_Discreet];
extern uint16_t   ucMUstavkiInBuf[MB_Size_Ustavki];
extern uint16_t   ucConfigUROVBuf[MB_Size_ConfigUROV];

/*******************************************************
 * ��������
 *******************************************************/
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}


/*******************************************************
 * Set_RSYN ��������� ������������ �������
 *******************************************************/
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){
int			ret;
float		Zt;

float		diapazon;

float		mag,premag;
float		level,dbLevel=0,zeroDbLevel=0;
float		K,K_dbLevel;

//Health
		uint32_t	Health = STVALINT32_OK;
		if ((ucMDiscInBuf[MB_offset_errorM6] & MB_bOffset_errorM6)>0) 			{Health = STVALINT32_Warning;}
		if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)>0) {Health = STVALINT32_Warning;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Health_stVal, Health)){
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Health_t, currentTime);
		}

//Mod
		uint32_t	Mod = STVALINT32_OFF;
		if (ucMUstavkiInBuf[MB_Addr_ConfigKS_UPPN + MB_offset_KS_Man_Config] & MB_bOffset_KS_Config_Stat) 	{Mod = STVALINT32_ON;}
		if (ucMUstavkiInBuf[MB_Addr_ConfigKS_UPPN + MB_offset_KS_Auto_Config] & MB_bOffset_KS_Config_Stat) 	{Mod = STVALINT32_ON;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Mod_stVal, Mod)){
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Mod_t, currentTime);
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Beh_stVal, Mod))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Beh_t, currentTime);
		}

//  Quality (Mod Beh)
		int	Qual = QUALITY_VALIDITY_GOOD;
		if (Health == STVALINT32_Warning) 		{Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Mod_q,Qual)){
			IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Beh_q,Qual);

			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Mod_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Beh_t, currentTime);
		}

// Rel
		if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RSYN1_Rel_stVal,(ucMDiscInBuf[MB_offset_UslOsUS] & MB_b_offset_UslOsUS)>0)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_Rel_t, currentTime);
			ret = true;
		}
		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Rel_q,Qual)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_Rel_t, currentTime);
		}

// DifVCIc (��������)
		diapazon = (float)range_maxU * 2;
		int32_t	*DifVCIc = (int32_t*)&ucMAnalogInBuf[MB_offset_dU];
		mag = (float)*DifVCIc;
		mag /= (float)256;
		ret |=  Set_Db_zeroDB_Znak_float(mag, diapazon,
				&iedModel_PROT_RSYN1_DifVCIc_db,
				&iedModel_PROT_RSYN1_DifVCIc_zeroDb,
				&iedModel_PROT_RSYN1_DifVCIc_instMag_f,
				&iedModel_PROT_RSYN1_DifVCIc_mag_f,
				&iedModel_PROT_RSYN1_DifVCIc_t,
				currentTime);
/*
		//����� ������ 256, � ���������� ��� ������� �������� �� ��������� �������, �� Ktnf �� ����� ��������.
		//K_dbLevel = (float)range_maxU * GetRealU(256,ucMUstavkiInBuf[MB_StartConfigTRMeas + MB_offset_Ktnf])  / (float)DbPercent;
		K_dbLevel = (float)(range_maxU) / (float)DbPercent;
		dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_db)* K_dbLevel;
		zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_zeroDb)* K_dbLevel;

		if (ucMAnalogInBuf[MB_offset_dU] > 32767)
				Zt = (float)ucMAnalogInBuf[MB_offset_dU] - (float)0xFFFF;
		else  	Zt = (float)ucMAnalogInBuf[MB_offset_dU];
		mag = (float)Zt/256;

		if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_instMag_f,mag)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifVCIc_t, currentTime);
			ret = true;
		}

		premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f);
		if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
		if (level > dbLevel) {
			if (mag<zeroDbLevel) mag = 0;
			IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,mag);
		}else{
			if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,0);
		}
		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifVCIc_q,Qual)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifVCIc_t, currentTime);
			ret = true;
		}
*/
// DifHzCIc (��������)
		diapazon = (float)DifHz_max * 2;
		int32_t	*DifHzCIc = (int32_t*)&ucMAnalogInBuf[MB_offset_dF];
		mag = (float)*DifHzCIc;
		mag /= (float)256;
		ret |=  Set_Db_zeroDB_Znak_float(mag, diapazon,
				&iedModel_PROT_RSYN1_DifHzCIc_db,
				&iedModel_PROT_RSYN1_DifHzCIc_zeroDb,
				&iedModel_PROT_RSYN1_DifHzCIc_instMag_f,
				&iedModel_PROT_RSYN1_DifHzCIc_mag_f,
				&iedModel_PROT_RSYN1_DifHzCIc_t,
				currentTime);
/*
		K_dbLevel = (float)(DifHz_max)  / (float)DbPercent;
		dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_db)* K_dbLevel;
		zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_zeroDb)* K_dbLevel;

		if (ucMAnalogInBuf[MB_offset_dF] > 32767) Zt = (float)ucMAnalogInBuf[MB_offset_dF] - (float)0xFFFF;
		else  Zt = (float)ucMAnalogInBuf[MB_offset_dF];
		mag = (float)Zt/256;

		if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_instMag_f,mag)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifHzCIc_t, currentTime);
			ret = true;
		}
		premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f);
		if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
		if (level > dbLevel) {
			if (mag<zeroDbLevel) mag = 0;
			IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,mag);
		}else{
			if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,0);
		}
		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_q,Qual)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifHzCIc_t, currentTime);
			ret = true;
		}
*/
// DifAngCIc
		diapazon = (float)DifAng_max;
		int32_t	*DifAngCIc = (int32_t*)&ucMAnalogInBuf[MB_offset_dfi];
		mag = (float)*DifAngCIc;
		mag = mag  * (float)360 / (float)65535;
		ret |=  Set_Db_zeroDB_Znak_float(mag, diapazon,
				&iedModel_PROT_RSYN1_DifAngCIc_db,
				&iedModel_PROT_RSYN1_DifAngCIc_zeroDb,
				&iedModel_PROT_RSYN1_DifAngCIc_instMag_f,
				&iedModel_PROT_RSYN1_DifAngCIc_mag_f,
				&iedModel_PROT_RSYN1_DifAngCIc_t,
				currentTime);
/*
		K_dbLevel = (float)(DifAng_max)  / (float)DbPercent;
		dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_db)* K_dbLevel;
		zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_zeroDb)* K_dbLevel;

		mag = (float)ucMAnalogInBuf[MB_offset_dfi]*360/65535;

		if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_instMag_f,mag)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifAngCIc_t, currentTime);
			ret = true;
		}
		premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f);
		if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
		if (level > dbLevel) {
			if (mag<zeroDbLevel) mag = 0;
			IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,mag);
		}else{
			if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,0);
		}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_q,Qual)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifAngCIc_t, currentTime);
			ret = true;
		}
*/
return ret;
}
/*******************************************************
 * Set_RPSB ��������� ������������ �������
 *******************************************************/
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime )
{
//Health
		uint32_t	Health = STVALINT32_OK;
		if ((ucMDiscInBuf[MB_offset_errorM6] & MB_bOffset_errorM6)>0) 			{Health = STVALINT32_Warning;}
		if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)>0) {Health = STVALINT32_Warning;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RPSB1_Health_stVal, Health))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_Health_t, currentTime);

// Str_general
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_Str_general,  ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_Str_t, currentTime);

//  Quality (Mod Beh)
		int	Qual = QUALITY_VALIDITY_GOOD;
		if (Health == STVALINT32_Warning) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_Str_q,Qual)){
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn1_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn2_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn3_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn4_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn5_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn6_q,Qual);

			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_Str_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn1_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn2_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn3_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn4_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn5_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn6_t, currentTime);

		}

// BlkZnxx_general
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn1_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z1_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn1_t, currentTime);
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn2_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z2_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn2_t, currentTime);
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn3_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z3_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn3_t, currentTime);
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn4_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z4_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn4_t, currentTime);
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn5_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z5_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn5_t, currentTime);
		if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn6_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_Addr_Config_Z + MB_offset_Z6_Conf] & MB_bOffset_Z_Config_KachBlk) ))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn6_t, currentTime);
return true;
}
/*******************************************************
 * Set_RREC ��������� ������������ �������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime ){
Quality quality;

//Health
		uint32_t	Health = STVALINT32_OK;
		if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)>0) {Health = STVALINT32_Warning;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Health_stVal, Health))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Health_t, currentTime);

//  Mod Beh
		uint32_t	Mod;
		if (ucMUstavkiInBuf[MB_Addr_ConfigAPW] & MB_bOffset_APW_Config_Stat) {Mod = STVALINT32_ON;} else {Mod = STVALINT32_OFF;}
		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Mod_stVal, Mod)){
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Mod_t, currentTime);
		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Beh_stVal, Mod))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Beh_t, currentTime);
		}

//  Quality (Mod Beh)
		quality = QUALITY_VALIDITY_GOOD;
		if (Health == STVALINT32_Warning) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Mod_q,quality)){
			IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Beh_q,quality);

			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC1_Mod_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC1_Beh_t, currentTime);
		}

// Op_general
		if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RREC1_Op_general,  ucMDiscInBuf[MB_offset_SW_ON_APW] & MB_b_SW_ON_APW)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC1_Op_t, currentTime);
		}

		quality = QUALITY_VALIDITY_GOOD;
		if (Health == STVALINT32_Warning) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Op_q,quality)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC1_Op_t, currentTime);
		}
return true;
}
/*******************************************************
 * Set_RBRF ��������� ������������ �������
 *******************************************************/
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime ){
int	ret = false;
uint32_t	Mod = STVALINT32_OFF;
//  Mod Beh

		if (ucConfigUROVBuf[MB_offset_UROV] & MB_bOffset_UROV_ModeI) 		{Mod = STVALINT32_ON;}
		if (ucConfigUROVBuf[MB_offset_UROV] & MB_bOffset_UROV_ModeSWctrl) 	{Mod = STVALINT32_ON;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Mod_stVal, Mod)){
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Mod_t, currentTime);
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Beh_stVal, Mod))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Beh_t, currentTime);
		}


//Health
		uint32_t	Health = STVALINT32_OK;
		if ((ucMDiscInBuf[MB_offset_errorM6] & MB_bOffset_errorM6)>0) 			{Health = STVALINT32_Warning;}
		if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)>0) {Health = STVALINT32_Warning;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Health_stVal, Health))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Health_t, currentTime);

//  Quality (Mod Beh)
		int	Qual = QUALITY_VALIDITY_GOOD;
		if (Health != STVALINT32_OK)		 {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if (IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx_q,Qual)){
			IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpIn_q,Qual);

			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpIn_t, currentTime);
		}

// OpEx_general
		if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx_general,  (ucMDiscInBuf[MB_offset_UROV2] & MB_b_Rab_UROV2)>0))
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx_t, currentTime);

// OpIn_general
		if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpIn_general,  (ucMDiscInBuf[MB_offset_UROV1] & MB_b_Rab_UROV1)>0))
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpIn_t, currentTime);

return	ret;
}
#endif

/*******************************************************
 * MR801 OLD
 *******************************************************/
#if defined	(MR801) && defined (OLD)
#include "static_model_MR801.h"

extern uint16_t   ucMDiscInBuf[MB_Size_Discreet];
extern uint16_t   ucConfigAPWBuf[MB_Size_ConfigAPW];


/*******************************************************
 * ��������
 *******************************************************/
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime ){return false;}

/*******************************************************
 * Set_RREC ��������� ������������ �������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime )
{

Quality quality;
//Health
			uint32_t	Health = STVALINT32_OK;
			if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Health_stVal, Health))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Health_t, currentTime);

//  Mod Beh
			uint32_t	Mod;
			if (ucConfigAPWBuf[MB_offset_ConfAPW] & MB_bOffset_APW_Config_Stat) {Mod = STVALINT32_ON;} else {Mod = STVALINT32_OFF;}
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Mod_stVal, Mod)){
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Mod_t, currentTime);
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Beh_stVal, Mod))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Beh_t, currentTime);
			}

//  Quality (Mod Beh)
			quality = QUALITY_VALIDITY_GOOD;
			if (ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

			if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Mod_q,quality)){
				IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Beh_q,quality);

				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Mod_t, currentTime);
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Beh_t, currentTime);
			}

// Op_general
			if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RREC_Op_general,  ucMDiscInBuf[MB_offset_SW_ON_APW] & MB_b_SW_ON_APW)){
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Op_t, currentTime);
			}

			quality = QUALITY_VALIDITY_GOOD;
			if (Health == STVALINT32_Warning) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

			if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Op_q,quality)){
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Op_t, currentTime);
			}


}
/*******************************************************
 * Set_RBRF ��������� ������������ �������
 *******************************************************/
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime )
{
Quality quality;

//Health
		uint32_t	Health = STVALINT32_OK;
		if ((ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorM4) || (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorM5)) {Health = STVALINT32_Warning;}
		if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

		if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF_Health_stVal, Health))
			IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF_Health_t, currentTime);

//  Quality (Mod Beh)
		quality = QUALITY_VALIDITY_GOOD;
		if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if(IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_Mod_q,quality)){
			IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_Beh_q,quality);

			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF_Mod_t, currentTime);
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF_Beh_t, currentTime);
		}


// OpEx_general
		if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF_OpEx_general,  ucMDiscInBuf[MB_offset_UROV] & MB_b_Rab_UROV))
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF_OpEx_t, currentTime);

		quality = QUALITY_VALIDITY_GOOD;
		if (Health == STVALINT32_Warning) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

		if(IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_OpEx_q,quality)){
			IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF_OpEx_t, currentTime);
		}

}
#endif
/*******************************************************
 * MR761OBR
 *******************************************************/
#if defined (MR761OBR)

/*******************************************************
 * ��������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime ){return false;}

#endif
/*******************************************************
 * MR771 MR761 MR762 MR763
 *******************************************************/
#if defined	(MR771) || defined	(MR761) || defined	(MR762) || defined	(MR763)

#if defined	(MR771)
#include "static_model_MR771.h"
#endif

#if defined	(MR761) || defined	(MR762) || defined	(MR763)
#include "static_model_MR76x.h"
#endif


extern uint16_t   ucMDiscInBuf[MB_Size_Discreet];
#if defined (AN_PERV)
extern float   ucMAnalogInBuf[];
#else
	#if defined (AN_DUBLEDATA)
	extern	uint32_t   ucMAnalogInBuf[MB_Size_Analog/2];
	#else
	extern	uint16_t   ucMAnalogInBuf[MB_Size_Analog];
	#endif
#endif
extern uint16_t   ucMUstavkiInBuf[MB_Size_Ustavki];
extern uint16_t   ucOtherUstavkiInBuf[MB_Size_OtherUstavki];

/*******************************************************
 * ��������
 *******************************************************/
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}

/*******************************************************
 * Set_RREC ��������� ������������ �������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime )
{
	int	ret = false;
	//Health
				uint32_t	Health = STVALINT32_OK;
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) {Health = STVALINT32_Warning;}

				if (IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Health_stVal, Health)){
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Health_t, currentTime);
				}


	//  Mod Beh
				uint32_t	Mod;
				if (ucMUstavkiInBuf[MB_Addr_ConfigAPW + MB_offset_ConfAPW] & MB_bOffset_APW_Config_Stat) {Mod = STVALINT32_ON;} else {Mod = STVALINT32_OFF;}
				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Mod_stVal, Mod)){
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Mod_t, currentTime);
					if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC1_Beh_stVal, Mod))
						IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC1_Beh_t, currentTime);
				}

	//  Quality (Mod Beh)
				int	Qual = QUALITY_VALIDITY_GOOD;
				if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Mod_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Beh_q,Qual);


	// Op_general
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RREC1_Op_general,  ucMDiscInBuf[MB_offset_SW_ON_APW] & MB_b_SW_ON_APW)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC1_Op_t, currentTime);
					ret = true;
				}

				IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_Op_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RREC1_AutoRecSt_q,Qual);
return ret;
}
/*******************************************************
 * Set_RBRF ��������� ������������ �������
 *******************************************************/
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime )
{
	int	ret = false;
	uint32_t	Mod = STVALINT32_OFF;
//  Mod Beh

			if (ucOtherUstavkiInBuf[MB_offset_UROV] & MB_bOffset_UROV_ModeI) 		{Mod = STVALINT32_ON;}
			if (ucOtherUstavkiInBuf[MB_offset_UROV] & MB_bOffset_UROV_ModeSWctrl) 	{Mod = STVALINT32_ON;}

			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Mod_stVal, Mod)){
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Mod_t, currentTime);
				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Beh_stVal, Mod))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Beh_t, currentTime);
			}


//Health
			uint32_t	Health = STVALINT32_OK;
			if ((ucMDiscInBuf[MB_offset_errorM5] & MB_bOffset_errorM5)) {Health = STVALINT32_Warning;}
			if (ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Health_stVal, Health))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Health_t, currentTime);

//  Quality (Mod Beh)
			int	Qual = QUALITY_VALIDITY_GOOD;
			//if (ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)
			if (Health != STVALINT32_OK)
			 {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

//				IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_Mod_q,Qual);
//				IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_Beh_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx_q,Qual);
			IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpIn_q,Qual);

// OpEx_general
			if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx_general,  ucMDiscInBuf[MB_offset_UROV2] & MB_b_Rab_UROV2))
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx_t, currentTime);

// OpIn_general
			if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpIn_general,  ucMDiscInBuf[MB_offset_UROV1] & MB_b_Rab_UROV1))
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpIn_t, currentTime);

	return	ret;
}
/*******************************************************
 * Set_RSYN ��������� ������������ �������
 *******************************************************/
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime )
{
	int			ret;
	float		Zt;

	float	mag,premag;
	float	level,dbLevel=0,zeroDbLevel=0;
	float	K,K_dbLevel;

	//Health
				uint32_t	Health = STVALINT32_OK;
				if ((ucMDiscInBuf[MB_offset_errorM5] & MB_bOffset_errorM5)) 		{Health = STVALINT32_Warning;}
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) {Health = STVALINT32_Warning;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Health_stVal, Health)){
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Health_t, currentTime);

				}

	//Mod
				uint32_t	Mod = STVALINT32_OFF;
				if (ucMUstavkiInBuf[MB_StartConfigKS_UPPN + MB_offset_KS_Man_Config] & MB_bOffset_KS_Config_Stat) {Mod = STVALINT32_ON;}
				if (ucMUstavkiInBuf[MB_StartConfigKS_UPPN + MB_offset_KS_Auto_Config] & MB_bOffset_KS_Config_Stat) {Mod = STVALINT32_ON;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Mod_stVal, Mod)){
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Mod_t, currentTime);
					if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RSYN1_Beh_stVal, Mod))
						IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RSYN1_Beh_t, currentTime);
				}

	//  Quality (Mod Beh)
				int	Qual = QUALITY_VALIDITY_GOOD;
				if (ucMDiscInBuf[MB_offset_errorM5] & MB_bOffset_errorM5) 		{Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Mod_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Beh_q,Qual);

	// Rel
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RSYN1_Rel_stVal,(ucMDiscInBuf[MB_offset_UslOsUS] & MB_b_offset_UslOsUS)>0)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_Rel_t, currentTime);
					ret = true;
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_Rel_q,Qual);

	// DifVCIc (��������)
				//����� ������ 256, � ���������� ��� ������� �������� �� ��������� �������, �� Ktnf �� ����� ��������.
				//K_dbLevel = (float)range_maxU * GetRealU(256,ucMUstavkiInBuf[MB_StartConfigTRMeas + MB_offset_Ktnf])  / (float)DbPercent;
				K_dbLevel = (float)(range_maxU) / (float)DbPercent;
				dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_db)* K_dbLevel;
				zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_zeroDb)* K_dbLevel;

				if (ucMAnalogInBuf[MB_offset_dU] > 32767)
						Zt = (float)ucMAnalogInBuf[MB_offset_dU] - (float)0xFFFF;
				else  	Zt = (float)ucMAnalogInBuf[MB_offset_dU];
				mag = (float)Zt/256;

				if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_instMag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifVCIc_t, currentTime);
					ret = true;
				}
				premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f);
				if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
				if (level > dbLevel) {
					if ((mag<zeroDbLevel)&&(mag>0)) mag = 0;
					if (((-mag)<zeroDbLevel)&&(mag<0)) mag = 0;
					IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,mag);
				}else{
					if ((mag<zeroDbLevel)&&(mag>0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,0);
					if (((-mag)<zeroDbLevel)&&(mag<0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,0);
//					if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifVCIc_mag_f,0);
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifVCIc_q,Qual);
/*
				if (ucMAnalogInBuf[MB_offset_dU] > 32767) Zt = (float)ucMAnalogInBuf[MB_offset_dU] - (float)0xFFFF;
				else  Zt = (float)ucMAnalogInBuf[MB_offset_dU];
				mag = (float)Zt/256;
				if ( IedServer_updateFloatAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifVCIc_mag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifVCIc_t, currentTime);
					ret = true;
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifVCIc_q,Qual);
*/
	// DifHzCIc (��������)
				K_dbLevel = (float)(DifHz_max)  / (float)DbPercent;
				dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_db)* K_dbLevel;
				zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_zeroDb)* K_dbLevel;

				if (ucMAnalogInBuf[MB_offset_dF] > 32767) Zt = (float)ucMAnalogInBuf[MB_offset_dF] - (float)0xFFFF;
				else  Zt = (float)ucMAnalogInBuf[MB_offset_dF];
				mag = (float)Zt/256;

				if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_instMag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifHzCIc_t, currentTime);
					ret = true;
				}
				premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f);
				if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
				if (level > dbLevel) {
//					if (mag<zeroDbLevel) mag = 0;
					if ((mag<zeroDbLevel)&&(mag>0)) mag = 0;
					if (((-mag)<zeroDbLevel)&&(mag<0)) mag = 0;
					IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,mag);
				}else{
					if ((mag<zeroDbLevel)&&(mag>0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,0);
					if (((-mag)<zeroDbLevel)&&(mag<0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,0);
//					if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_mag_f,0);
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_q,Qual);

/*
				if (ucMAnalogInBuf[MB_offset_dF] > 32767) Zt = (float)ucMAnalogInBuf[MB_offset_dF] - (float)0xFFFF;
				else  Zt = (float)ucMAnalogInBuf[MB_offset_dF];
				mag = (float)Zt/256;

				if ( IedServer_updateFloatAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifHzCIc_mag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifHzCIc_t, currentTime);
					ret = true;
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifHzCIc_q,Qual);
*/
	// DifAngCIc
				K_dbLevel = (float)(DifAng_max)  / (float)DbPercent;
				dbLevel 	= (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_db)* K_dbLevel;
				zeroDbLevel = (float)IedServer_getUInt32AttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_zeroDb)* K_dbLevel;

				mag = (float)ucMAnalogInBuf[MB_offset_dfi]*360/65535;

				if ( IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_instMag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifAngCIc_t, currentTime);
					ret = true;
				}
				premag = IedServer_getFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f);
				if (premag > mag) 	{level = premag - mag;} else {level = mag - premag;}
				if (level > dbLevel) {
//					if (mag<zeroDbLevel) mag = 0;
					if ((mag<zeroDbLevel)&&(mag>0)) mag = 0;
					if (((-mag)<zeroDbLevel)&&(mag<0)) mag = 0;
					IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,mag);
				}else{
					if ((mag<zeroDbLevel)&&(mag>0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,0);
					if (((-mag)<zeroDbLevel)&&(mag<0)) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,0);
//					if (mag<zeroDbLevel) IedServer_updateFloatAttributeValue(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_mag_f,0);
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_q,Qual);

/*
				mag = (float)ucMAnalogInBuf[MB_offset_dfi]*360/65535;
				if ( IedServer_updateFloatAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifAngCIc_mag_f,mag)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RSYN1_DifAngCIc_t, currentTime);
					ret = true;
				}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RSYN1_DifAngCIc_q,Qual);
*/
return ret;
}
/*******************************************************
 * Set_RPSB ��������� ������������ �������
 *******************************************************/
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime )
{
	//Health
				uint32_t	Health = STVALINT32_OK;
				if ((ucMDiscInBuf[MB_offset_errorM5] & MB_bOffset_errorM5)) {Health = STVALINT32_Warning;}
				if (ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RPSB1_Health_stVal, Health))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_Health_t, currentTime);

	// Str_general
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_Str_general,  ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_Str_t, currentTime);

	//  Quality (Mod Beh)
				int	Qual = QUALITY_VALIDITY_GOOD;
				if (Health == STVALINT32_Warning) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_Str_q,Qual);

				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn1_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn2_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn3_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn4_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn5_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn6_q,Qual);
#if defined	(MR771)
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn7_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn8_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn9_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RPSB1_BlkZn10_q,Qual);
#endif

	// BlkZnxx_general
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn1_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z1_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn1_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn2_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z2_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn2_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn3_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z3_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn3_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn4_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z4_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn4_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn5_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z5_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn5_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn6_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z6_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn6_t, currentTime);
#if defined	(MR771)
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn7_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z7_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn7_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn8_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z8_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn8_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn9_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z9_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn9_t, currentTime);
				if (IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RPSB1_BlkZn10_general, (ucMDiscInBuf[MB_offset_Kach] & MB_b_offset_Kach) && (ucMUstavkiInBuf[MB_StartConfig_Z + MB_offset_Z10_Conf] & MB_bOffset_Z_Config_KachBlk) ))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RPSB1_BlkZn10_t, currentTime);
#endif

}
#endif



/*******************************************************
 * MR901 MR902
 *******************************************************/
#if defined	(MR901) || defined	(MR902)

#include "static_model_MR901_902.h"

extern uint16_t   ucMDiscInBuf[MB_Size_Discreet];
#if defined (AN_PERV)
extern float   ucMAnalogInBuf[];
#else
	#if defined (AN_DUBLEDATA)
	extern	uint32_t   ucMAnalogInBuf[MB_Size_Analog/2];
	#else
	extern	uint16_t   ucMAnalogInBuf[MB_Size_Analog];
	#endif
#endif
extern uint16_t   ucMUstavkiInBuf[MB_Size_Ustavki];

/*******************************************************
 * ��������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RSYN	(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB	(uint16_t QTnum, uint64_t currentTime ){return false;}

/*******************************************************
 * Set_RBRF ��������� ������������ �������
 *******************************************************/
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime )
{
	//Health
				uint32_t	Health = STVALINT32_OK;
				if ((ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorM4)>0) 		{Health = STVALINT32_Warning;}
				if ((ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorM5)>0) 		{Health = STVALINT32_Warning;}

#if  defined (T24N0D24R51) || defined (T24N0D32R43) || defined (T24N0D40R35) || defined (T20N4D40R35)
				if ((ucMDiscInBuf[MB_offset_errorM6] & MB_bOffset_errorM6)>0) 		{Health = STVALINT32_Warning;}
#endif
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) 	{Health = STVALINT32_Warning;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF1_Health_stVal, Health))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF1_Health_t, currentTime);

	//  Quality (Mod Beh)
				int	quality = QUALITY_VALIDITY_GOOD;
				if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) 		{quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				if (IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_Mod_q,quality)){
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_Beh_q,quality);
				}


	// OpEx_general
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx1_general,  ucMDiscInBuf[MB_offset_UROV_1] & MB_b_UROV_1))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx1_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx2_general,  ucMDiscInBuf[MB_offset_UROV_2] & MB_b_UROV_2))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx2_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx3_general,  ucMDiscInBuf[MB_offset_UROV_3] & MB_b_UROV_3))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx3_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx4_general,  ucMDiscInBuf[MB_offset_UROV_4] & MB_b_UROV_4))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx4_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx5_general,  ucMDiscInBuf[MB_offset_UROV_5] & MB_b_UROV_5))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx5_t, currentTime);

#if defined	(MR902) && defined	(OLD)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_general,  ucMDiscInBuf[MB_offset_UROV_PRIn] & MB_b_UROV_PRIn))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_general,  ucMDiscInBuf[MB_offset_UROV_SH1] & MB_b_UROV_SH1))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_general,  ucMDiscInBuf[MB_offset_UROV_SH2] & MB_b_UROV_SH2))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_general,  ucMDiscInBuf[MB_offset_UROV_PO] & MB_b_UROV_PO))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_t, currentTime);

#endif

#if defined	(MR902) && defined (T16N0D24R19)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_general,  ucMDiscInBuf[MB_offset_UROV_6] & MB_b_UROV_6))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_general,  ucMDiscInBuf[MB_offset_UROV_7] & MB_b_UROV_7))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_general,  ucMDiscInBuf[MB_offset_UROV_8] & MB_b_UROV_8))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_general,  ucMDiscInBuf[MB_offset_UROV_SH1] & MB_b_UROV_SH1))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx10_general,  ucMDiscInBuf[MB_offset_UROV_SH2] & MB_b_UROV_SH2))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx10_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx11_general,  ucMDiscInBuf[MB_offset_UROV_PO] & MB_b_UROV_PO))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx11_t, currentTime);
#endif
#if defined	(MR901)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_general,  ucMDiscInBuf[MB_offset_UROV_6] & MB_b_UROV_6))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_general,  ucMDiscInBuf[MB_offset_UROV_7] & MB_b_UROV_7))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_general,  ucMDiscInBuf[MB_offset_UROV_8] & MB_b_UROV_8))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_general,  ucMDiscInBuf[MB_offset_UROV_9] & MB_b_UROV_9))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx10_general,  ucMDiscInBuf[MB_offset_UROV_10] & MB_b_UROV_10))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx10_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx11_general,  ucMDiscInBuf[MB_offset_UROV_11] & MB_b_UROV_11))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx11_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx12_general,  ucMDiscInBuf[MB_offset_UROV_12] & MB_b_UROV_12))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx12_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx13_general,  ucMDiscInBuf[MB_offset_UROV_13] & MB_b_UROV_13))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx13_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx14_general,  ucMDiscInBuf[MB_offset_UROV_14] & MB_b_UROV_14))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx14_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx15_general,  ucMDiscInBuf[MB_offset_UROV_15] & MB_b_UROV_15))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx15_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx16_general,  ucMDiscInBuf[MB_offset_UROV_16] & MB_b_UROV_16))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx16_t, currentTime);
#if defined (OLD)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_general,  ucMDiscInBuf[MB_offset_UROV_SH1] & MB_b_UROV_SH1))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_general,  ucMDiscInBuf[MB_offset_UROV_SH2] & MB_b_UROV_SH2))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_general,  ucMDiscInBuf[MB_offset_UROV_PO] & MB_b_UROV_PO))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_t, currentTime);
#endif
#if defined (T20N4D40R35)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_general,  ucMDiscInBuf[MB_offset_UROV_17] & MB_b_UROV_17))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_general,  ucMDiscInBuf[MB_offset_UROV_18] & MB_b_UROV_18))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_general,  ucMDiscInBuf[MB_offset_UROV_19] & MB_b_UROV_19))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_general,  ucMDiscInBuf[MB_offset_UROV_20] & MB_b_UROV_20))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_general,  ucMDiscInBuf[MB_offset_UROV_SH1] & MB_b_UROV_SH1))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_general,  ucMDiscInBuf[MB_offset_UROV_SH2] & MB_b_UROV_SH2))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_general,  ucMDiscInBuf[MB_offset_UROV_PO] & MB_b_UROV_PO))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_t, currentTime);

#endif
#if defined (T24N0D24R51) || defined (T24N0D32R43) || defined (T24N0D40R35)
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_general,  ucMDiscInBuf[MB_offset_UROV_17] & MB_b_UROV_17))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_general,  ucMDiscInBuf[MB_offset_UROV_18] & MB_b_UROV_18))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_general,  ucMDiscInBuf[MB_offset_UROV_19] & MB_b_UROV_19))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_general,  ucMDiscInBuf[MB_offset_UROV_20] & MB_b_UROV_20))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_general,  ucMDiscInBuf[MB_offset_UROV_21] & MB_b_UROV_21))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_general,  ucMDiscInBuf[MB_offset_UROV_22] & MB_b_UROV_22))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_general,  ucMDiscInBuf[MB_offset_UROV_23] & MB_b_UROV_23))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx24_general,  ucMDiscInBuf[MB_offset_UROV_24] & MB_b_UROV_24))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx24_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx25_general,  ucMDiscInBuf[MB_offset_UROV_SH1] & MB_b_UROV_SH1))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx25_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx26_general,  ucMDiscInBuf[MB_offset_UROV_SH2] & MB_b_UROV_SH2))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx26_t, currentTime);

				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx27_general,  ucMDiscInBuf[MB_offset_UROV_PO] & MB_b_UROV_PO))
					 IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx27_t, currentTime);
#endif

#endif

//  Quality (Mod Beh)
				quality = QUALITY_VALIDITY_GOOD;
				if (ucMDiscInBuf[MB_offset_errorM4] & MB_bOffset_errorM4) 		{quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
				if (ucMDiscInBuf[MB_offset_errorM5] & MB_bOffset_errorM5) 		{quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
#if  defined (T24N0D24R51) || defined (T24N0D32R43) || defined (T24N0D40R35) || defined (T20N4D40R35)
				if ((ucMDiscInBuf[MB_offset_errorM6] & MB_bOffset_errorM6)>0) 	{quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
#endif
				if ((ucMDiscInBuf[MB_offset_errorUstavki] & MB_bOffset_errorUstavki)) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				if (IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx1_q,quality)){
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx2_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx3_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx4_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx5_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx6_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx7_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx8_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx9_q,quality);
#if defined	(MR901)
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx10_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx11_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx12_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx13_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx14_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx15_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx16_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx17_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx18_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx19_q,quality);
#if  defined (T20N4D40R35)
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx20_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx21_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx22_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx23_q,quality);

#endif
#if  defined (T24N0D24R51) || defined (T24N0D32R43) || defined (T24N0D40R35)
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx20_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx21_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx22_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx23_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx24_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx25_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx26_q,quality);
					IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF1_OpEx27_q,quality);
#endif

#endif

					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx1_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx2_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx3_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx4_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx5_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx6_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx7_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx8_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx9_t, currentTime);
#if defined	(MR901)
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx10_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx11_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx12_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx13_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx14_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx15_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx16_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx17_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx18_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx19_t, currentTime);
#if  defined (T20N4D40R35)
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_t, currentTime);
#endif
#if  defined (T24N0D24R51) || defined (T24N0D32R43) || defined (T24N0D40R35)
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx20_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx21_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx22_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx23_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx24_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx25_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx26_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF1_OpEx27_t, currentTime);
#endif

#endif
				}
}

#endif
/*******************************************************
 * MR5_700, MR5_500
 *******************************************************/
#if defined (MR5_700) || defined (MR5_500) || defined (MR741)
#if defined (MR5_700)
#include "static_model_MR5_700.h"
#endif
#if defined (MR5_500)
#include "static_model_MR5_500.h"
#endif
#if defined (MR741)
#include "static_model_MR741.h"
#endif
extern uint16_t   ucMDiscInBuf[MB_Size_Discreet];
extern uint16_t   ucMAutomatBuf[MB_Size_Automat];

/*******************************************************
 * ��������
 *******************************************************/
#if defined (MR5_700) || defined (MR741)
int		Set_FRREC		(uint16_t QTnum, uint64_t currentTime ){return false;}
#endif
int		Set_RSYN		(uint16_t QTnum, uint64_t currentTime ){return false;}
int		Set_RPSB		(uint16_t QTnum, uint64_t currentTime ){return false;}

/*******************************************************
 * Set_RREC ��������� ������������ �������
 *******************************************************/
int		Set_RREC	(uint16_t QTnum, uint64_t currentTime )
{
	//  Mod Beh
				uint32_t	Mod;
				if ((ucMAutomatBuf[MB_offset_ConfAPW] & MB_bOffset_APW_Config_Stat)>0) {Mod = STVALINT32_ON;} else {Mod = STVALINT32_OFF;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Mod_stVal, Mod)){
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Mod_t, currentTime);
				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Beh_stVal, Mod))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Beh_t, currentTime);
				}

	//Health
				uint32_t	Health = STVALINT32_OK;
				if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RREC_Health_stVal, Health))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RREC_Health_t, currentTime);

	//  Quality (Mod Beh)
				int	Qual = QUALITY_VALIDITY_GOOD;
				if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Mod_q,Qual)){
					IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Beh_q,Qual);

					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Mod_t, currentTime);
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Beh_t, currentTime);
				}


	// Op_general
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RREC_Op_general,  ucMDiscInBuf[MB_offset_SW_ON_APW] & MB_b_SW_ON_APW)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Op_t, currentTime);
				}
				Qual = QUALITY_VALIDITY_GOOD;
				if (Health == STVALINT32_Warning) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

				if (IedServer_updateQuality(iedServer,&iedModel_PROT_RREC_Op_q,Qual)){
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RREC_Op_t, currentTime);
				}

}
#if defined (MR5_500)
/*******************************************************
 * Set_FRREC1 ��������� ������������ �������
 *******************************************************/
int		Set_FRREC	(uint16_t QTnum, uint64_t currentTime )
{
	Quality quality;
/*
//Health
			uint32_t	Health = STVALINT32_OK;
			if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {Health = STVALINT32_Warning;}

			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_FRREC_Health_stVal, Health))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_FRREC_Health_t, currentTime);


//  Mod Beh
			uint32_t	Mod;
			if (ucAutomatBuf[MB_offset_ConfAPW] & MB_bOffset_APW_Config_Stat) {Mod = STVALINT32_ON;} else {Mod = STVALINT32_OFF;}
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_FRREC_Mod_stVal, Mod)){
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_FRREC_Mod_t, currentTime);
			if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_FRREC_Beh_stVal, Mod))
				IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_FRREC_Beh_t, currentTime);
			}

//  Quality (Mod Beh)
			quality = QUALITY_VALIDITY_GOOD;
			if (ucMDiscInBuf[MB_offsetHardFaults] & MB_bOffset_errorUstavki) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

			if(IedServer_updateQuality(iedServer,&iedModel_PROT_FRREC_Mod_q,quality)){
				IedServer_updateQuality(iedServer,&iedModel_PROT_FRREC_Beh_q,quality);
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_FRREC_Mod_t, currentTime);
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_FRREC_Beh_t, currentTime);
			}

// Op_general
			if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_FRREC_Op_general,  ucMDiscInBuf[MB_offset_SW_ON_APW] & MB_b_SW_ON_APW)){
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_FRREC_Op_t, currentTime);
			}

			quality = QUALITY_VALIDITY_GOOD;
			if (Health == STVALINT32_Warning) {quality = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}

			if (IedServer_updateQuality(iedServer,&iedModel_PROT_FRREC_Op_q,quality)){
				IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_FRREC_Op_t, currentTime);
			}
*/
}
#endif
/*******************************************************
 * Set_RBRF ��������� ������������ �������
 *******************************************************/
int		Set_RBRF	(uint16_t QTnum, uint64_t currentTime )
{
	//Health
				uint32_t	Health = STVALINT32_OK;
				if (ucMDiscInBuf[MB_offsetError_M1] & MB_bOffsetErrModule1b) 			{Health = STVALINT32_Warning;}
				if 	(ucMDiscInBuf[MB_offsetError_Ustavki] & MB_bOffsetErrUstavki)	 	{Health = STVALINT32_Warning;}

				if ( IedServer_updateInt32AttributeValue(iedServer, &iedModel_PROT_RBRF_Health_stVal, Health))
					IedServer_updateUTCTimeAttributeValue(iedServer,&iedModel_PROT_RBRF_Health_t, currentTime);

	//  Quality (Mod Beh)
				int	Qual = QUALITY_VALIDITY_GOOD;
				IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_Mod_q,Qual);
				IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_Beh_q,Qual);


	// OpEx_general
				if ( IedServer_updateBooleanAttributeValue(iedServer, &iedModel_PROT_RBRF_OpEx_general,  ucMDiscInBuf[MB_offset_UROV] & MB_b_Rab_UROV))
					IedServer_updateUTCTimeAttributeValue(iedServer, &iedModel_PROT_RBRF_OpEx_t, currentTime);

				Qual = QUALITY_VALIDITY_GOOD;
				if (Health == STVALINT32_Warning) {Qual = QUALITY_VALIDITY_INVALID | QUALITY_DETAIL_FAILURE;}
				IedServer_updateQuality(iedServer,&iedModel_PROT_RBRF_OpEx_q,Qual);

}
#endif
