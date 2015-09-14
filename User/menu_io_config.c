
#include "includes.h"

/*******************************************************************************
*******************************************************************************/
typedef struct paraiocgcitem               
{
	u8 *DisplayString;
  
	const DescripItem *gsDescripString; // 
  	
	u16 ParaAdr;       
  	
  u16 dmin;
  u16 dmax;			
  
} ParaIOCgcItem;
/*
typedef struct descripitem
{
	u8 ucID;
	
	u8 *UpperString[2];
	u8 *LowerString[2];
	
} DescripItem; 
*/
/*******************************************************************************
*******************************************************************************/
const ParaIOCgcItem ParaInputMBCgcItem[]=
{
	{
		"  X06  ",
		DescripInputItem,
		1160,
		0,
		160
	},	
	{
		"  X08  ",
		DescripInputItem,
		1161,
		0,
		160
	},			
	{
		"  X10  ",
		DescripInputItem,
		1162,
		0,
		160
	},			
	{
		"  X13  ",
		DescripInputItem,
		1163,
		0,
		160
	},			
	{
		"  X20  ",
		DescripInputItem,
		1164,
		0,
		160
	},			
	{
		"  X23  ",
		DescripInputItem,
		1165,
		0,
		160
	},			
	{
		"  X24  ",
		DescripInputItem,
		1166,
		0,
		160
	},			
	{
		"  X29  ",
		DescripInputItem,
		1167,
		0,
		160
	},			

	{
		"  X31  ",
		DescripInputItem,
		1170,
		0,
		139,
	},			
	{
		"  X32  ",
		DescripInputItem,
		1171,
		0,
		139,
	},			
	{
		"  X33  ",
		DescripInputItem,
		1172,
		0,
		139,
	},			
	{
		"  X34  ",
		DescripInputItem,
		1173,
		0,
		139,
	},			
	{
		"  X35  ",
		DescripInputItem,
		1174,
		0,
		139,
	},			
	{
		"  X36  ",
		DescripInputItem,
		1175,
		0,
		139,
	},			
	{
		"  X37  ",
		DescripInputItem,
		1176,
		0,
		139,
	},			
	{
		"  X38  ",
		DescripInputItem,
		1177,
		0,
		139,
	},			
	{
		"  X39  ",
		DescripInputItem,
		1178,
		0,
		139,
	},			
	{
		"  X40  ",
		DescripInputItem,
		1179,
		0,
		139,
	},			

	{
		"  X41  ",
		DescripInputItem,
		1180,
		0,
		139,
	},			
	{
		"  X42  ",
		DescripInputItem,
		1181,
		0,
		139,
	},			
	{
		"  X43  ",
		DescripInputItem,
		1182,
		0,
		139,
	},			
	{
		"  X44  ",
		DescripInputItem,
		1183,
		0,
		139,
	},			
	{
		"  X45  ",
		DescripInputItem,
		1184,
		0,
		139,
	},			
	{
		"  X46  ",
		DescripInputItem,
		1185,
		0,
		139,
	},			
	{
		"  X47  ",
		DescripInputItem,
		1186,
		0,
		139,
	},			
	{
		"  X48  ",
		DescripInputItem,
		1187,
		0,
		139,
	},			
	{
		"  X49  ",
		DescripInputItem,
		1188,
		0,
		139,
	},			
	{
		"  X50  ",
		DescripInputItem,
		1189,
		0,
		139,
	},			
};						

const ParaIOCgcItem ParaInputUpperCgcItem[]=
{
	{
		"  X16  ",
		DescripInputItem,
		1190,
		0,
		139
	},			
	{
		"  X17  ",
		DescripInputItem,
		1191,
		0,
		139
	},			
	{
		"  X18  ",
		DescripInputItem,
		1192,
		0,
		139
	},			
	{
		"  X19  ",
		DescripInputItem,
		1193,
		0,
		139
	},			
	{
		"  X20  ",
		DescripInputItem,
		1194,
		0,
		139
	},			
	{
		"  X21  ",
		DescripInputItem,
		1195,
		0,
		139
	},			
	{
		"  X22  ",
		DescripInputItem,
		1196,
		0,
		139
	},			
	{
		"  X23  ",
		DescripInputItem,
		1197,
		0,
		139
	},			
	{
		"  X24  ",
		DescripInputItem,
		1198,
		0,
		139
	},			
	{
		"  X25  ",
		DescripInputItem,
		1199,
		0,
		139
	},			
	{
		"  X26  ",
		DescripInputItem,
		1200,
		0,
		139
	},			
	{
		"  X27  ",
		DescripInputItem,
		1201,
		0,
		139
	},			
	{
		"  X28  ",
		DescripInputItem,
		1202,
		0,
		139
	},			
	{
		"  X29  ",
		DescripInputItem,
		1203,
		0,
		139
	},			
	{
		"  X30  ",
		DescripInputItem,
		1204,
		0,
		139
	},			
	{
		"  X31  ",
		DescripInputItem,
		1205,
		0,
		139
	},			
	{
		"  X32  ",
		DescripInputItem,
		1206,
		0,
		139
	},			
};

//
const ParaIOCgcItem ParaInputLowerCgcItem[]=
{
	{
		"  X16  ",
		DescripInputItem,
		1208,
		0,
		139
	},			
	{
		"  X17  ",
		DescripInputItem,
		1209,
		0,
		139
	},			
	{
		"  X18  ",
		DescripInputItem,
		1210,
		0,
		139
	},			
	{
		"  X19  ",
		DescripInputItem,
		1211,
		0,
		139
	},			
	{
		"  X20  ",
		DescripInputItem,
		1212,
		0,
		139
	},			
	{
		"  X21  ",
		DescripInputItem,
		1213,
		0,
		139
	},			
	{
		"  X22  ",
		DescripInputItem,
		1214,
		0,
		139
	},			
	{
		"  X23  ",
		DescripInputItem,
		1215,
		0,
		139
	},			
	{
		"  X24  ",
		DescripInputItem,
		1216,
		0,
		139
	},			
	{
		"  X25  ",
		DescripInputItem,
		1217,
		0,
		139
	},			
	{
		"  X26  ",
		DescripInputItem,
		1218,
		0,
		139
	},			
	{
		"  X27  ",
		DescripInputItem,
		1219,
		0,
		139
	},			
	{
		"  X28  ",
		DescripInputItem,
		1220,
		0,
		139
	},			
	{
		"  X29  ",
		DescripInputItem,
		1221,
		0,
		139
	},			
	{
		"  X30  ",
		DescripInputItem,
		1222,
		0,
		139
	},			
	{
		"  X31  ",
		DescripInputItem,
		1223,
		0,
		139
	},			
	{
		"  X32  ",
		DescripInputItem,
		1224,
		0,
		139
	},					
};

const ParaIOCgcItem ParaOutputMBCgcItem[]=
{
	{
		"  Q5.0 ",
		DescripOutputItem,
		1226,
		0,
		80
	},			
	{
		"  Q5.1 ",
		DescripOutputItem,
		1227,
		0,
		80
	},			
	{
		"  Q5.2 ",
		DescripOutputItem,
		1228,
		0,
		80
	},			

	{
		"   Q6  ",
		DescripOutputItem,
		1230,
		0,
		80
	},			
	{
		"   Q7  ",
		DescripOutputItem,
		1231,
		0,
		80
	},			
	{
		"   Q8  ",
		DescripOutputItem,
		1232,
		0,
		80
	},			
	{
		"   Q9  ",
		DescripOutputItem,
		1233,
		0,
		80
	},			
	{
		"  Q10  ",
		DescripOutputItem,
		1234,
		0,
		80
	},			
	{
		"  Q11  ",
		DescripOutputItem,
		1235,
		0,
		80
	},			
	{
		"  Q12  ",
		DescripOutputItem,
		1236,
		0,
		80
	},			
	{
		"  Q13  ",
		DescripOutputItem,
		1237,
		0,
		80
	},			
};

const ParaIOCgcItem ParaOutputUpperCgcItem[]=
{
	{
		"   Q1  ",
		DescripOutputItem,
		1238,
		0,
		80
	},			
	{
		"   Q2  ",
		DescripOutputItem,
		1239,
		0,
		80
	},			
	{
		"   Q3  ",
		DescripOutputItem,
		1240,
		0,
		80
	},			
	{
		"   Q4  ",
		DescripOutputItem,
		1241,
		0,
		80
	},			
	{
		"   Q5  ",
		DescripOutputItem,
		1242,
		0,
		80
	},			
	{
		"   Q6  ",
		DescripOutputItem,
		1243,
		0,
		80
	},			
	{
		"   Q7  ",
		DescripOutputItem,
		1244,
		0,
		80
	},			
	{
		"   Q8  ",
		DescripOutputItem,
		1245,
		0,
		80
	},			
};

ParaIOCgcItem ParaOutputLowerCgcItem[]=
{
	{
		"   Q1  ",
		DescripOutputItem,
		1246,
		0,
		80
	},			
	{
		"   Q2  ",
		DescripOutputItem,
		1247,
		0,
		80
	},			
	{
		"   Q3  ",
		DescripOutputItem,
		1248,
		0,
		80
	},			
	{
		"   Q4  ",
		DescripOutputItem,
		1249,
		0,
		80
	},			
	{
		"   Q5  ",
		DescripOutputItem,
		1250,
		0,
		80
	},			
	{
		"   Q6  ",
		DescripOutputItem,
		1251,
		0,
		80
	},			
	{
		"   Q7  ",
		DescripOutputItem,
		1252,
		0,
		80
	},			
	{
		"   Q8  ",
		DescripOutputItem,
		1253,
		0,
		80
	},			
};

/*******************************************************************************
*******************************************************************************/
const DescripItem DescripInputItem[]=
{
	{	0,
		{"",""},		 
		{"**  �޹���    **"," No Function !  "}, 
	},

	{	1,
		{"",""},
		{"���޿�������    ","Service UP key"}, 
	},
	{	2,
		{"",""},
		{"���޿�������    ","Service DOWN key"}, 
	},
	{	3,
		{"          ���ִ�","Handrail"},
		{"�������ɳڿ���1 ","driver switch 1"}, 
	},
	{	4,
		{"          ���ִ�","Handrail"},
		{"�������ɳڿ���2 ","driver switch 2"}, 
	},
	{	5,
		{"","Left handrail"},
		{"����ִ��ϴ�����","Breakage switch"}, 
	},
	{	6,
		{"","Right handrail"},
		{"�ҷ��ִ��ϴ�����","Breakage switch"}, 
	},
	{	7,
		{"","Middle switch"},
		{"�м����ֹͣ����","  Emergency stop"}, 
	},
	{	8,
		{"",""},
		{"ˮλ����        ","Water switch"}, 
	},

	{	9,
		{"�϶�            ","Upper"},
		{"ֱ��ȹ�忪����  ",""}, 
	},
	{	10,
		{"�϶�            ","Upper"},
		{"ֱ��ȹ�忪����  ",""}, 
	},
	{	11,
		{"�϶�            ","Upper combplate"},
		{"��ݰ崹ֱ������","Vertical left"}, 
	},
	{	12,
		{"�϶�            ","Upper combplate"},
		{"��ݰ崹ֱ������","Vertical right"}, 
	},
	{	13,
		{"","Upper/Left"},
		{"�϶��ݼ�������  ","Buggy protection"}, 
	},
	{	14,
		{"","Upper/Right"},
		{"�϶��ݼ�������  ","Buggy protection"}, 
	},
	{	15,
		{"            �¶�",""},
		{"ֱ��ȹ�忪����  ",""}, 
	},
	{	16,
		{"            �¶�",""},
		{"ֱ��ȹ�忪����  ",""}, 
	},

	{	17,
		{"            �¶�","Lower combplate"},
		{"��ݰ崹ֱ������","Vertical left"}, 
	},
	{	18,
		{"            �¶�","Lower combplate"},
		{"��ݰ崹ֱ������","Vertical right"}, 
	},
	{	19,
		{"","Lower/Left"},
		{"�¶��ݼ�������  ","Buggy protection"}, 
	},
	{	20,
		{"","Lower/Right"},
		{"�¶��ݼ�������  ","Buggy protection"}, 
	},
	{	21,
		{"",""},
		{"��е������բ�쳣","Aux brake error "}, 
	},
	{	22,
		{"",""},
		{"������SF����01  ","Config SF input1"}, 
	},
	{	23,
		{"",""},
		{"������SF����02  ","Config SF input2"}, 
	},
	{	24,
		{"",""},
		{"������SF����03  ","Config SF input3"}, 
	},

	{	25,
		{"",""},
		{"������SF����04  ","Config SF input4"}, 
	},
	{	26,
		{"",""},
		{"������SF����05  ","Config SF input5"}, 
	},
	{	27,
		{"",""},
		{"������SF����06  ","Config SF input6"}, 
	},
	{	28,
		{"",""},
		{"������SF����07  ","Config SF input7"}, 
	},
	{	29,
		{"",""},
		{"������SF����08  ","Config SF input8"}, 
	},
	{	30,
		{"",""},
		{"������SF����09  ","Config SF input9"}, 
	},
	{	31,
		{"",""},
		{"�϶���ݰ�      ","Upper combplate"}, 
	},
	{	32,
		{"","Upper"},
		{"�϶�ȹ��        ","Skirt switch"}, 
	},

	{	33,
		{"","Upper"},
		{"�϶��ݼ�����    ","Buggy protection"}, 
	},
	{	34,
		{"",""},
		{"�¶���ݰ�      ","Lower combplate"}, 
	},
	{	35,
		{"","Lower"},
		{"�¶�ȹ��        ","Skirt switch"}, 
	},
	{	36,
		{"","Lower"},
		{"�¶��ݼ�����    ","Buggy protection"}, 
	},
	{	37,
		{"","Upper Combplate"},
		{"�϶���ݰ�ˮƽ��","horizontal left"}, 
	},
	{	38,
		{"","Upper Combplate"},
		{"�϶���ݰ�ˮƽ��","horizontal right"}, 
	},
	{	39,
		{"","Upper/Left"},
		{"�϶˷��ִ������","Handrail inlet"}, 
	},
	{	40,
		{"","Upper/Right"},
		{"�϶˷��ִ������","Handrail inlet"}, 
	},

	{	41,
		{"",""},
		{"�϶����ȹ����  ",""}, 
	},
	{	42,
		{"",""},
		{"�϶����ȹ����  ",""}, 
	},
	{	43,
		{"","Upper"},
		{"�϶��ݼ����ݿ���","Broken step "}, 
	},
	{	44,
		{"","Upper PIT"},
		{"�϶˾���Ģ��ͷ  ","Emergency stop"}, 
	},
	{	45,
		{"","Upper"},
		{"�϶�ֹͣ��ť����","Emergency stop"}, 
	},
	{	46,
		{"","Lower Combplate"},
		{"�¶���ݰ�ˮƽ��","horizontal left"}, 
	},
	{	47,
		{"","Lower Combplate"},
		{"�¶���ݰ�ˮƽ��","horizontal right"}, 
	},
	{	48,
		{"","Lower/Left"},
		{"�¶˷��ִ������","Handrail inlet"}, 
	},

	{	49,
		{"            �¶�","     Lower/Right"},
		{"���ִ������    ","Handrail inlet  "}, 
	},
	{	50,
		{"                ","Lower"},
		{"�¶����ȹ����  ",""}, 
	},
	{	51,
		{"","Lower"},
		{"�¶����ȹ����  ",""}, 
	},
	{	52,
		{"","Step chain"},
		{"�¶������Ž���  ","Tension left"}, 
	},
	{	53,
		{"","Step chain"},
		{"�¶������Ž���  ","Tension right"}, 
	},
	{	54,
		{"","Lower"},
		{"�¶��ݼ����ݿ���","Broken step"}, 
	},
	{	55,
		{"","Lower PIT"},
		{"�¶˾���Ģ��ͷ  ","Emergency stop"}, 
	},
	{	56,
		{"","Lower"},
		{"�¶�ֹͣ��ť����","Emergency stop"}, 
	},

//�ǰ�ȫ��·
	{	57,
		{"            �϶�","Upper"},
		{"  ��դ�ź�����1 ","barrier input 1"}, 
	},
	{	58,
		{"            �϶�","Upper"},
		{"  ��դ�ź�����2 ","barrier input 2"}, 
	},
	{	59,
		{"            �϶�","Upper"},
		{"  �״��ź�����1 ","Radar input 1"}, 
	},
	{	60,
		{"            �϶�","Upper"},
		{"  �״��ź�����2 ","Radar input 2"}, 
	},
	{	61,
		{"            �¶�","Lower"},
		{"  ��դ�ź�����1 ","barrier input 1"}, 
	},
	{	62,
		{"            �¶�","Lower"},
		{"  ��դ�ź�����2 ","barrier input 2"}, 
	},
	{	63,
		{"            �¶�","Lower"},
		{"  �״��ź�����1 ","Radar input 1"}, 
	},
	{	64,
		{"            �¶�","Lower"},
		{"  �״��ź�����2 ","Radar input 2"}, 
	},

	{	65,
		{"",""},
		{"���ֲ��ٵ�����1 ","HDL cal input 1"}, 
	},
	{	66,
		{"",""},
		{"���ֲ��ٵ�����2 ","HDL cal input 2"}, 
	},
	{	67,
		{"",""},
		{"      ��բ���3 ","Brake input 3"}, 
	},
	{	68,
		{"",""},
		{"      ��բ���4 ","Brake input 4"}, 
	},
	{	69,
		{"",""},
		{"      ��բ���5 ","Brake input 5"}, 
	},
	{	70,
		{"",""},
		{"      ��բ���6 ","Brake input 6"}, 
	},
	{	71,
		{"",""},
		{"      ��բ���7 ","Brake input 7"}, 
	},
	{	72,
		{"",""},
		{"      ��բ���8 ","Brake input 8"}, 
	},
 
	{	73,
		{"","brake wear"},  
		{"      բ�߼��1 ","         input 1"}, 
	},
	{	74,
		{"","brake wear"},
		{"      բ�߼��2 ","         input 2"}, 
	},
	{	75,
		{"","brake wear"},
		{"      բ�߼��3 ","         input 3"}, 
	},
	{	76,
		{"","brake wear"},
		{"      բ�߼��4 ","         input 4"}, 
	},
	{	77,
		{"","brake wear"},
		{"      բ�߼��5 ","         input 5"}, 
	},
	{	78,
		{"","brake wear"},
		{"      բ�߼��6 ","         input 6"}, 
	},
	{	79,
		{"","brake wear"},
		{"      բ�߼��7 ","         input 7"}, 
	},
	{	80,
		{"","brake wear"},
		{"      բ�߼��8 ","         input 8"}, 
	},

	{	81,
		{"            �϶�","Upper"},
		{"        �ǰ忪��","Coverplat"}, 
	},
	{	82,
		{"            �϶�","Upper"},
		{"    �ǰ��������","Anti-theft"}, 
	},
	{	83,
		{"            �¶�","Lower"},
		{"        �ǰ忪��","Coverplat"}, 
	},
	{	84,
		{"            �¶�","Lower"},
		{"    �ǰ��������","Anti-theft"}, 
	},
	{	85,
		{"            �϶�","Upper"},
		{"�ֶ��Զ� -> �ֶ�","A/M -> Manual"}, 
	},
	{	86,
		{"            �϶�","Upper"},
		{"�ֶ��Զ� -> �Զ�","A/M -> Auto"}, 
	},
	{	87,
		{"            �¶�","Lower"},
		{"�ֶ��Զ� -> �ֶ�","A/M -> Manual"}, 
	},
	{	88,
		{"            �¶�","Lower"},
		{"�ֶ��Զ� -> �Զ�","A/M -> Auto"}, 
	},

	{	89,
		{"",""},
		{"�ͱù����ź�����","Oil alarm input"}, 
	},
	{	90,
		{"",""},
		{"    ���ź�����","Fire Alarm input"}, 
	},
	{	91,
		{"",""},
		{"  ���������ź�",""}, 
	},
	{	92,
		{"",""},
		{"  ����������ͣ��",""}, 
	},
	{	93,
		{"",""},
		{"    ����Զ��ͣ��","Remote stop"}, 
	},
	{	94,
		{"",""},
		{"���ȹ����ź�����","Fan alarm input"}, 
	},
	{	95,
		{"          ������","     Gearbox oil"},
		{"��λ��⿪���ź�","Low level alarm "}, 
	},
	{	96,
		{"",""},
		{"��Դ�����ź�����","Power fault"}, 
	},

  	{	97,
		{"",""},
		{"  ��ܲ����ſ���","Glass door"}, 
	},
	{	98,
		{"",""},
		{"  ��ܼ��ȴ�����",""}, 
	},
	{	99,
		{"          ���ִ�","Handrail"},
		{"��������������1 ","drive chain 1"}, 
	},
	{	100,
		{"          ���ִ�","Handrail"},
		{"��������������2 ","drive chain 2"}, 
	},
	{	101,
		{"",""},
		{"�ӵر���        ","ground connect"}, 
	},
	{	102,
		{"",""},
		{"���ȼ��        ","Heat error input"}, 
	},
	{	103,
		{"",""},
		{"���ַ����ִ�  ","Motor cover"}, 
	},
	{	104,
		{"",""},
		{"����ɽ��      ","Seismic sensor"}, 
	},

	{	105,
		{"",""},
		{"����ģʽѡ��    ","Fast run mode"}, 
	},
	{	106,
		{"",""},
		{"Զ��ʹ���ź�    ","Remote enable"}, 
	},
	{	107,
		{"",""},
		{"",""}, 
	},
	{	108,
		{"",""},
		{"",""}, 
	},
	{	109,
		{"",""},
		{"����λ�Ƽ��1   ","����λ�Ƽ��1"}, 
	},
	{	110,
		{"",""},
		{"����λ�Ƽ��2   ","����λ�Ƽ��2"}, 
	},
	{	111,
		{"",""},
		{"����λ�Ƽ��3   ","����λ�Ƽ��3"}, 
	},
	{	112,
		{"",""},
		{"����λ�Ƽ��4   ","����λ�Ƽ��4"}, 
	},

	{	113,
		{"",""},
		{"",""}, 
	},
	{	114,
		{"",""},
		{"",""}, 
	},
	{	115,
		{"",""},
		{"",""}, 
	},
	{	116,
		{"",""},
		{"",""}, 
	},
	{	117,
		{"",""},
		{"",""}, 
	},
	{	118,
		{"",""},
		{"",""}, 
	},
	{	119,
		{"",""},
		{"",""}, 
	},
	{	120,
		{"",""},
		{"",""}, 
	},

	{	121,
		{"",""},
		{"",""}, 
	},
	{	122,
		{"",""},
		{"",""}, 
	},
	{	123,
		{"",""},
		{"",""}, 
	},
	{	124,
		{"",""},
		{"",""}, 
	},
	{	125,
		{"",""},
		{"",""}, 
	},
	{	126,
		{"",""},
		{"",""}, 
	},
	{	127,
		{"",""},
		{"",""}, 
	},
	{	128,
		{"",""},
		{"",""}, 
	},

	{	129,
		{"�����ó�������01","Config NC input1"},
		{"",""}, 
	},
	{	130,
		{"�����ó�������02","Config NC input2"},
		{"",""}, 
	},
	{	131,
		{"�����ó�������03","Config NC input3"},
		{"",""}, 
	},
	{	132,
		{"�����ó�������04","Config NC input4"},
		{"",""}, 
	},
	{	133,
		{"�����ó�������05","Config NC input5"},
		{"",""}, 
	},
	{	134,
		{"�����ó�������06","Config NC input6"},
		{"",""}, 
	},
	{	135,
		{"�����ó�������07","Config NC input7"},
		{"",""}, 
	},
	{	136,
		{"�����ó�������08","Config NC input8"},
		{"",""}, 
	},

	{	137,
		{"�����ó�������01","Config NO input1"},
		{"",""}, 
	},
	{	138,
		{"�����ó�������02","Config NO input2"},
		{"",""}, 
	},
	{	139,
		{"�����ó�������03","Config NO input3"},
		{"",""}, 
	},
	{	140,
		{"      ���нӴ���","Down contactor"},
		{"�ջ��������    ","Check input"}, 
	},
	{	141,
		{"    �����ͽӴ���","Delta contactor"},
		{"�ջ��������    ","Check input"}, 
	},
	{	142,
		{"    �����ͽӴ���","Delta contactor"},
		{"�ջ��������2   ","Check input 2"}, 
	},
	{	143,
		{"",""},	  //{"",""},//
		{"����ת�ټ��    ","Main Shaft input"}, //{"",""},//
	},
	{	144,
		{"",""},	  //  {"",""},//
		{"",""},    // {"",""}, //
	},

	{	145,     
		{"",""},  //{"","Driver chain"},  
		{"",""},  //{"�������������2 ","     input 2"},   
	},
	{	146,
		{"",""},  //{"�ǣ����ǣ��Ӵ���",""},
		{"",""},  //{"  �ջ��������2 ","Check input 2"}, 
	},
	{	147,
		{"",""},  //{"","Dual motor"},
		{"",""},  //{"    F6.2��������","F6.2 input"}, 
	},
	{	148,
		{"",""},//
		{"",""},// 
	},
	{	149,
		{"",""},
		{"",""}, 
	},
	{	150,
		{"",""},
		{"",""}, 
	},
	{	151,
		{"",""},
		{"",""}, 
	},
	{	152,
		{"",""},
		{"",""}, 
	},

	{	153,
		{"",""},
		{"",""}, 
	},
	{	154,
		{"",""},
		{"",""}, 
	},
	{	155,
		{"",""},
		{"",""}, 
	},
	{	156,
		{"",""},
		{"",""}, 
	},
	{	157,
		{"",""},
		{"",""}, 
	},
	{	158,
		{"",""},
		{"",""}, 
	},
	{	159,
		{"",""},
		{"",""}, 
	},
	{	160,
		{"",""},
		{"",""}, 
	},
};

const DescripItem DescripOutputItem[]=
{
	{	0,
		{"",""},
		{"**  �޹���    **","* No Function! *"}, 
	},
	{	1,
		{"","VVVF multi speed"},
		{"��������--λ0 ","Output BIT     0"}, 
	},
	{	2,
		{"","VVVF multi speed"},
		{"��������--λ1 ","Output BIT     1"}, 
	},
	{	3,
		{"","VVVF multi speed"},
		{"��������--λ2 ","Output BIT     2"}, 
	},
	{	4,
		{"",""},
		{"��Ƶ�����ź����","VVVF run output"}, 
	},

	{	5,
		{"",""},
		{"    �ͱÿ������","Oil output"}, 
	},

	{	6,
		{"",""},
		{"",""}, 
	},

	{	7,
		{"",""},
		{"    ���ȿ������","Heat output"}, 
	},
	{	8,
		{"",""},
		{"",""}, 
	},
	{	9,
		{"","UP running"},
		{"��ͨ�����п���","Traffic light"}, 
	},
	{	10,
		{"","Down running"},
		{"��ͨ�����п���","Traffic light"}, 
	},
	{	11,
		{"",""},
		{"    ������--�϶�","Upper Buzzer"}, 
	},
	{	12,
		{"",""},
		{"    ������--�¶�","Lower Buzzer"}, 
	},
	{	13,
		{"",""},
		{"  ������--���ƹ�","Ctr. Box Buzzer"}, 
	},
	{	14,
		{"",""},
		{"  �ݼ�/ �������","Light output"}, 
	},
	{	15,
		{"",""},
		{"    �����������","ESC running"}, 
	},
	{	16,
		{"",""},
		{"    ��բ�������","Brake output"}, 
	},

	{	17,
		{"",""},
		{"    ���������ź�","ESC UP running"}, 
	},
	{	18,
		{"",""},
		{"    ���������ź�","ESC DOWN running"}, 
	},
	{	19,
		{"",""},
		{"    ����ͣ���ź�","ESC stop state"}, 
	},
	{	20,
		{"",""},
		{"        ��ͣ״̬","Emergency stop"}, 
	},
	{	21,
		{"",""},
		{"    ����״̬�ź�","ESC fault"}, 
	},
	{	22,
		{"",""},
		{"    ����״̬�ź�","Service state"}, 
	},
	{	23,
		{"",""},
		{"    �ǰ���ź�","Coverplat alarm"}, 
	},
	{	24,
		{"",""},
		{"    �ǰ�����ź�","Anti-Theft alarm"}, 
	},

	{	25,
		{"",""},
		{"��ؼ̵���1 ���","Relay output 1"}, 
	},
	{	26,
		{"",""},
		{"��ؼ̵���2 ���","Relay output 2"}, 
	},
	{	27,
		{"","Auto/Manual"},
		{"��/ �Զ����ֶ���","Output -> Manual"}, 
	},
	{	28,
		{"","Auto/Manual"},
		{"��/ �Զ����Զ���","Output -> Auto"}, 
	},
	{	29,
		{"","Fire Alarm"},
		{"    ���źŷ���","        feedback"}, 
	},
	{	30,
		{"","Fire Alarm"},
		{"��������ȷ������"," Action feedback"}, 
	},
	{	31,
		{"�������","Fault class"},
		{"        һ�����","Normal"}, 
	},
	{	32,
		{"�������","Fault class"},
		{"        ��������","Emergency"}, 
	},

	{	33,
		{"",""},
		{"    �ͱù������","Oil fault output"}, 
	},
	{	34,
		{"ͣ��״̬","Stop state"},
		{"        ����ͣ��","Fault"}, 
	},
	{	35,
		{"ͣ��״̬","Stop state"},
		{"    һ�����ͣ��","Normal"}, 
	},
	{	36,
		{"ͣ��״̬","Stop state"},
		{"    ��������ͣ��","Emergency"}, 
	},
	{	37,
		{"",""},
		{"",""}, 
	},
	{	38,
		{"",""},
		{"",""}, 
	},
	{	39,
		{"",""},
		{"",""}, 
	},
	{	40,
		{"",""},
		{"",""}, 
	},

	{	41,
		{"",""},
		{"",""}, 
	},
	{	42,
		{"",""},
		{"",""}, 
	},
	{	43,
		{"",""},
		{"",""}, 
	},
	{	44,
		{"",""},
		{"",""}, 
	},
	{	45,
		{"",""},
		{"",""}, 
	},
	{	46,
		{"",""},
		{"",""}, 
	},
	{	47,
		{"",""},
		{"",""}, 
	},
	{	48,
		{"",""},
		{"",""}, 
	},

	{	49,
		{"",""},
		{"",""}, 
	},
	{	50,
		{"",""},
		{"",""}, 
	},
	{	51,
		{"",""},
		{"",""}, 
	},
	{	52,
		{"",""},
		{"",""}, 
	},
	{	53,
		{"",""},
		{"",""}, 
	},
	{	54,
		{"",""},
		{"",""}, 
	},
	{	55,
		{"",""},
		{"",""}, 
	},
	{	56,
		{"",""},
		{"",""}, 
	},
		
	{	57,
		{"Modbus","Modbus"},
		{"  40001  H  bit0","  40001  H  bit0"}, 
	},

	{	58,
		{"Modbus","Modbus"},
		{"  40001  H  bit1","  40001  H  bit1"}, 
	},

	{	59,
		{"Modbus","Modbus"},
		{"  40001  H  bit2","  40001  H  bit2"}, 
	},

	{	60,
		{"Modbus","Modbus"},
		{"  40001  H  bit3","  40001  H  bit3"}, 
	},

	{	61,
		{"Modbus","Modbus"},
		{"  40001  H  bit4","  40001  H  bit4"}, 
	},

	{	62,
		{"Modbus","Modbus"},
		{"  40001  H  bit5","  40001  H  bit5"}, 
	},

	{	63,
		{"Modbus","Modbus"},
		{"  40001  H  bit6","  40001  H  bit6"}, 
	},

	{	64,
		{"Modbus","Modbus"},
		{"  40001  H  bit7","  40001  H  bit7"}, 
	},

	{	65,
		{"Modbus","Modbus"},
		{"  40001  L  bit0","  40001  L  bit0"}, 
	},

	{	66,
		{"Modbus","Modbus"},
		{"  40001  L  bit1","  40001  H  bit1"}, 
	},

	{	67,
		{"Modbus","Modbus"},
		{"  40001  L  bit2","  40001  L  bit2"}, 
	},

	{	68,
		{"Modbus","Modbus"},
		{"  40001  L  bit3","  40001  L  bit3"}, 
	},

	{	69,
		{"Modbus","Modbus"},
		{"  40001  L  bit4","  40001  L  bit4"}, 
	},

	{	70,
		{"Modbus","Modbus"},
		{"  40001  L  bit5","  40001  L  bit5"}, 
	},

	{	71,
		{"Modbus","Modbus"},
		{"  40001  L  bit6","  40001  L  bit6"}, 
	},

	{	72,
		{"Modbus","Modbus"},
		{"  40001  L  bit7","  40001  L  bit7"}, 
	},

	{	73,
		{"Modbus","Modbus"},
		{"  40002  H  bit0","  40002  H  bit0"}, 
	},

	{	74,
		{"Modbus","Modbus"},
		{"  40002  H  bit1","  40002  H  bit1"}, 
	},

	{	75,
		{"Modbus","Modbus"},
		{"  40002  H  bit2","  40002  H  bit2"}, 
	},

	{	76,
		{"Modbus","Modbus"},
		{"  40002  H  bit3","  40002  H  bit3"}, 
	},

	{	77,
		{"Modbus","Modbus"},
		{"  40002  H  bit4","  40002  H  bit4"}, 
	},

	{	78,
		{"Modbus","Modbus"},
		{"  40002  H  bit5","  40002  H  bit5"}, 
	},

	{	79,
		{"Modbus","Modbus"},
		{"  40002  H  bit6","  40002  H  bit6"},
	},

	{	80,
		{"Modbus","Modbus"},
		{"  40002  H  bit7","  40002  H  bit7"},
	},
}; 

const u8 IO_CfgItem_Descrip[6][2][16] =
{
  {"������������","   MB INPUT CFG"},
  {"�����������","  MB OUTPUT CFG"},
  {"�϶���������"," UPPER EB INPUT"},
  {"�϶��������","UPPER EB OUTPUT"},
  {"�¶���������","LOWER EB INPUT "},
  {"�¶��������","LOWER EB OUTPUT"},
};

/*******************************************************************************
*******************************************************************************/
const ParaIOCgcItem *ParaIoPoint;

static u8 Para_Number=0,Para_Number_Max=0,PS_Flag=0;
static u16 Para_Data=0,Para_Max=0,Para_Min=0;

/*******************************************************************************
typedef struct paraiocgcitem               
{
	u8 MenuCount; 
    
	u8 *DisplayString[2];

	const DescripItem *gsDescripString; // 
  	
	u16 ParaAdr;       
  	
  u16 dmin;
  u16 dmax;			
  
} ParaIOCgcItem;
*******************************************************************************/
void io_para_get(void)
{
  u16 i;
  
  i = ParaIoPoint[Para_Number].ParaAdr;
  
//  modbus_read(MB_COM_PORT, (i>>1), 1);
  
  Para_Data = ModBuff[i];
  
  Para_Max=ParaIoPoint[Para_Number].dmax;
  Para_Min=ParaIoPoint[Para_Number].dmin;
}

void io_para_set(void)
{ 
  u16 i;
  
  i = ParaIoPoint[Para_Number].ParaAdr;
  ModBuff[i] = Para_Data;
      
  modbus_write(MB_COM_PORT, (i>>1), 1);
}

void io_para_display(void)
{               
  u8 func_des[8]={"       "}; // port_des[8]={"< X00 >"},
  u16 fcolor_sn = NAVY,fcolor_fc = NAVY;
//  port_des[3] = 0x30+Para_Number/10;  
//  port_des[4] = 0x30+Para_Number%10;  

  func_des[2] = 0x30+Para_Data/100;  
  func_des[3] = 0x30+(Para_Data%100)/10;    
  func_des[4] = 0x30+Para_Data%10;    
  
  if(PS_Flag)
  {
    fcolor_fc = RED;
  }  
  else
  {
    fcolor_sn = RED;
  }  

  TXM_StringDisplay(0,120,50,32,1,fcolor_sn ,LGRAY, (void*)ParaIoPoint[Para_Number].DisplayString); 
  //TXM_FillTextWidget (362+PS_Flag, (void*)ParaIoPoint[Para_Number].DisplayString);
  TXM_StringDisplay(0,120,90,32,1,fcolor_fc ,LGRAY, (void*)func_des);  
  //TXM_FillTextWidget (365+PS_Flag, (void*)func_des);
  if(ParaIoPoint->gsDescripString[Para_Data].UpperString[LANGUAGE][0])
  {  
    TXM_StringDisplay(0,32,170,24,1,NAVY ,YELLOW, (void*)ParaIoPoint->gsDescripString[Para_Data].UpperString[LANGUAGE]); 
  }
  else
  {
    TXM_StringDisplay(0,32,170,24,1,NAVY ,YELLOW, "                "); 
  }  
  TXM_StringDisplay(0,32,200,24,1,NAVY ,YELLOW, (void*)ParaIoPoint->gsDescripString[Para_Data].LowerString[LANGUAGE]); 
//  TXM_FillTextWidget (368, (void*)ParaIoPoint->gsDescripString[Para_Data].UpperString[LANGUAGE]);
//  TXM_FillTextWidget (369, (void*)ParaIoPoint->gsDescripString[Para_Data].LowerString[LANGUAGE]);

/*  
  TXM_FillTextWidget (350, (void*)BaseParameter[Para_Number].DisplayString1[LANGUAGE]);
  TXM_FillTextWidget (351, (void*)BaseParameter[Para_Number].DisplayString2[LANGUAGE]);
  

  if(BaseParameter[Para_Number].ParaDisNum)
  {
    TXM_FillTextWidget (352+PS_Flag, (void*)BaseParameter[Para_Number].ParaDisString[LANGUAGE][Para_Data-Para_Min]);
  }
  //��ʾ����ֵ 
  else
  {
    TXM_FillTextWidget (352,"");
    TXM_DigitDisplay(354+PS_Flag,0,0,24,0,0,0,Para_Data,5,BaseParameter[Para_Number].dot,ALIGN_RIGHT);
    TXM_FillTextWidget (356, (void*)BaseParameter[Para_Number].UnitString);
  }
*/  
} 

/*******************************************************************************
*******************************************************************************/
void menu_para_io(u8 item)
{
  u8 *m_keydata,err=0;
 
  ZTM_FullScreenImageDisp(313);
  OSTimeDlyHMSM(0, 0,0,10);
  ZTM_RectangleFill (0,0,239,39,NAVY);
  OSTimeDlyHMSM(0, 0,0,10);
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)IO_CfgItem_Descrip[item][LANGUAGE]); 

  TXM_StringDisplay(0,8,50,32,0,NAVY ,0, "���Ӻ�: "); 
  TXM_StringDisplay(0,8,90,32,0,NAVY ,0, "���ܺ�: "); 
  TXM_StringDisplay(0,8,135,24,0,NAVY ,0, "���ù���˵��: "); 

  
  ZTM_RectangleFill (0,280,239,319,BLACK);
  TXM_StringDisplay(0,190,290,24,1,DGRAY ,LGRAY, "�޸�");
//  TXM_FillTextWidget (360, (void*)IO_CfgItem_Descrip[item][LANGUAGE]);
  
  switch(item) 
  {
    case 1:   ParaIoPoint = ParaOutputMBCgcItem;   
              Para_Number_Max = 11;
              break;                 
    case 2:   ParaIoPoint = ParaInputUpperCgcItem;  
              Para_Number_Max = 17;
              break;           
    case 3:   ParaIoPoint = ParaOutputUpperCgcItem; 
              Para_Number_Max = 8;
              break;           
    case 4:   ParaIoPoint = ParaInputLowerCgcItem;  
              Para_Number_Max = 17;
              break;            
    case 5:   ParaIoPoint = ParaOutputLowerCgcItem; 
              Para_Number_Max = 8;
              break;           
    default:  ParaIoPoint = ParaInputMBCgcItem;     
              Para_Number_Max = 28;
              break;           
  }  
  
/*  
  modbus_read(MB_COM_PORT, 550, 120);
  for(i=0;i<240;i++)
  {  
    Para_Buff[i] = ModBuff[1100+i];
  }
  
  Para_Number = 0;
  base_para_get();
*/  
  
  Para_Number = 0;
  io_para_get();
  io_para_display();  
   
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,10000,&err);
    if(err == OS_ERR_TIMEOUT)
    {
      break;
    } 
    else if((!PS_Flag) && (m_keydata[0] == KEY_ESC))
    {
      break;
    } 
    else 
    {      
      if(m_keydata[0] == KEY_F3)
      {
        PS_Flag ^= 0X01;
      }
      else if(PS_Flag && (m_keydata[0] == KEY_SET))
      {
        //���ò���
        io_para_set();
        
        PS_Flag = 0;   
      } 
      else if((PS_Flag) && (m_keydata[0] == KEY_ESC))
      {
        PS_Flag = 0;   
      }  
      else if(PS_Flag)
      {
        switch(m_keydata[0])
        {
          case KEY_UP:
            if(Para_Data < Para_Max) Para_Data++; else Para_Data = Para_Min;
            break;
          case KEY_DOWN:
            if(Para_Data > Para_Min) Para_Data--; else Para_Data = Para_Max;
            break;
          case KEY_F3:
          case KEY_SET:
            //���ò���
            io_para_set();     
            PS_Flag = 0;   
          break;
        }  
      } 
      else
      {
        switch(m_keydata[0])
        {
          case KEY_LEFT:
          case KEY_DOWN:
            if(Para_Number) Para_Number--; else Para_Number = Para_Number_Max-1;
            io_para_get();
            
            break;
          case KEY_RIGHT:
          case KEY_UP:
            Para_Number++;
            if(Para_Number>=Para_Number_Max) Para_Number = 0;
            io_para_get();
            
            break;
        }            
      }  
      
      io_para_display();     
    }   
  }  
}

/*******************************************************************************
*******************************************************************************/
