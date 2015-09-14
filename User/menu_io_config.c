
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
		{"**  无功能    **"," No Function !  "}, 
	},

	{	1,
		{"",""},
		{"检修开梯上行    ","Service UP key"}, 
	},
	{	2,
		{"",""},
		{"检修开梯下行    ","Service DOWN key"}, 
	},
	{	3,
		{"          扶手带","Handrail"},
		{"驱动带松弛开关1 ","driver switch 1"}, 
	},
	{	4,
		{"          扶手带","Handrail"},
		{"驱动带松弛开关2 ","driver switch 2"}, 
	},
	{	5,
		{"","Left handrail"},
		{"左扶手带断带开关","Breakage switch"}, 
	},
	{	6,
		{"","Right handrail"},
		{"右扶手带断带开关","Breakage switch"}, 
	},
	{	7,
		{"","Middle switch"},
		{"中间紧急停止开关","  Emergency stop"}, 
	},
	{	8,
		{"",""},
		{"水位开关        ","Water switch"}, 
	},

	{	9,
		{"上端            ","Upper"},
		{"直段裙板开关左  ",""}, 
	},
	{	10,
		{"上端            ","Upper"},
		{"直段裙板开关右  ",""}, 
	},
	{	11,
		{"上端            ","Upper combplate"},
		{"梳齿板垂直开关左","Vertical left"}, 
	},
	{	12,
		{"上端            ","Upper combplate"},
		{"梳齿板垂直开关右","Vertical right"}, 
	},
	{	13,
		{"","Upper/Left"},
		{"上端梯级防跳左  ","Buggy protection"}, 
	},
	{	14,
		{"","Upper/Right"},
		{"上端梯级防跳右  ","Buggy protection"}, 
	},
	{	15,
		{"            下端",""},
		{"直段裙板开关左  ",""}, 
	},
	{	16,
		{"            下端",""},
		{"直段裙板开关右  ",""}, 
	},

	{	17,
		{"            下端","Lower combplate"},
		{"梳齿板垂直开关左","Vertical left"}, 
	},
	{	18,
		{"            下端","Lower combplate"},
		{"梳齿板垂直开关右","Vertical right"}, 
	},
	{	19,
		{"","Lower/Left"},
		{"下端梯级防跳左  ","Buggy protection"}, 
	},
	{	20,
		{"","Lower/Right"},
		{"下端梯级防跳右  ","Buggy protection"}, 
	},
	{	21,
		{"",""},
		{"机械辅助抱闸异常","Aux brake error "}, 
	},
	{	22,
		{"",""},
		{"可配置SF输入01  ","Config SF input1"}, 
	},
	{	23,
		{"",""},
		{"可配置SF输入02  ","Config SF input2"}, 
	},
	{	24,
		{"",""},
		{"可配置SF输入03  ","Config SF input3"}, 
	},

	{	25,
		{"",""},
		{"可配置SF输入04  ","Config SF input4"}, 
	},
	{	26,
		{"",""},
		{"可配置SF输入05  ","Config SF input5"}, 
	},
	{	27,
		{"",""},
		{"可配置SF输入06  ","Config SF input6"}, 
	},
	{	28,
		{"",""},
		{"可配置SF输入07  ","Config SF input7"}, 
	},
	{	29,
		{"",""},
		{"可配置SF输入08  ","Config SF input8"}, 
	},
	{	30,
		{"",""},
		{"可配置SF输入09  ","Config SF input9"}, 
	},
	{	31,
		{"",""},
		{"上端梳齿板      ","Upper combplate"}, 
	},
	{	32,
		{"","Upper"},
		{"上端裙板        ","Skirt switch"}, 
	},

	{	33,
		{"","Upper"},
		{"上端梯级防跳    ","Buggy protection"}, 
	},
	{	34,
		{"",""},
		{"下端梳齿板      ","Lower combplate"}, 
	},
	{	35,
		{"","Lower"},
		{"下端裙板        ","Skirt switch"}, 
	},
	{	36,
		{"","Lower"},
		{"下端梯级防跳    ","Buggy protection"}, 
	},
	{	37,
		{"","Upper Combplate"},
		{"上端梳齿板水平左","horizontal left"}, 
	},
	{	38,
		{"","Upper Combplate"},
		{"上端梳齿板水平右","horizontal right"}, 
	},
	{	39,
		{"","Upper/Left"},
		{"上端扶手带入口左","Handrail inlet"}, 
	},
	{	40,
		{"","Upper/Right"},
		{"上端扶手带入口右","Handrail inlet"}, 
	},

	{	41,
		{"",""},
		{"上端弯段裙板左  ",""}, 
	},
	{	42,
		{"",""},
		{"上端弯段裙板右  ",""}, 
	},
	{	43,
		{"","Upper"},
		{"上端梯级下陷开关","Broken step "}, 
	},
	{	44,
		{"","Upper PIT"},
		{"上端井道蘑菇头  ","Emergency stop"}, 
	},
	{	45,
		{"","Upper"},
		{"上端停止按钮开关","Emergency stop"}, 
	},
	{	46,
		{"","Lower Combplate"},
		{"下端梳齿板水平左","horizontal left"}, 
	},
	{	47,
		{"","Lower Combplate"},
		{"下端梳齿板水平右","horizontal right"}, 
	},
	{	48,
		{"","Lower/Left"},
		{"下端扶手带入口左","Handrail inlet"}, 
	},

	{	49,
		{"            下端","     Lower/Right"},
		{"扶手带入口右    ","Handrail inlet  "}, 
	},
	{	50,
		{"                ","Lower"},
		{"下端弯段裙板左  ",""}, 
	},
	{	51,
		{"","Lower"},
		{"下端弯段裙板右  ",""}, 
	},
	{	52,
		{"","Step chain"},
		{"下端链条张紧左  ","Tension left"}, 
	},
	{	53,
		{"","Step chain"},
		{"下端链条张紧右  ","Tension right"}, 
	},
	{	54,
		{"","Lower"},
		{"下端梯级下陷开关","Broken step"}, 
	},
	{	55,
		{"","Lower PIT"},
		{"下端井道蘑菇头  ","Emergency stop"}, 
	},
	{	56,
		{"","Lower"},
		{"下端停止按钮开关","Emergency stop"}, 
	},

//非安全回路
	{	57,
		{"            上端","Upper"},
		{"  光栅信号输入1 ","barrier input 1"}, 
	},
	{	58,
		{"            上端","Upper"},
		{"  光栅信号输入2 ","barrier input 2"}, 
	},
	{	59,
		{"            上端","Upper"},
		{"  雷达信号输入1 ","Radar input 1"}, 
	},
	{	60,
		{"            上端","Upper"},
		{"  雷达信号输入2 ","Radar input 2"}, 
	},
	{	61,
		{"            下端","Lower"},
		{"  光栅信号输入1 ","barrier input 1"}, 
	},
	{	62,
		{"            下端","Lower"},
		{"  光栅信号输入2 ","barrier input 2"}, 
	},
	{	63,
		{"            下端","Lower"},
		{"  雷达信号输入1 ","Radar input 1"}, 
	},
	{	64,
		{"            下端","Lower"},
		{"  雷达信号输入2 ","Radar input 2"}, 
	},

	{	65,
		{"",""},
		{"扶手测速档输入1 ","HDL cal input 1"}, 
	},
	{	66,
		{"",""},
		{"扶手测速档输入2 ","HDL cal input 2"}, 
	},
	{	67,
		{"",""},
		{"      抱闸检测3 ","Brake input 3"}, 
	},
	{	68,
		{"",""},
		{"      抱闸检测4 ","Brake input 4"}, 
	},
	{	69,
		{"",""},
		{"      抱闸检测5 ","Brake input 5"}, 
	},
	{	70,
		{"",""},
		{"      抱闸检测6 ","Brake input 6"}, 
	},
	{	71,
		{"",""},
		{"      抱闸检测7 ","Brake input 7"}, 
	},
	{	72,
		{"",""},
		{"      抱闸检测8 ","Brake input 8"}, 
	},
 
	{	73,
		{"","brake wear"},  
		{"      闸瓦检测1 ","         input 1"}, 
	},
	{	74,
		{"","brake wear"},
		{"      闸瓦检测2 ","         input 2"}, 
	},
	{	75,
		{"","brake wear"},
		{"      闸瓦检测3 ","         input 3"}, 
	},
	{	76,
		{"","brake wear"},
		{"      闸瓦检测4 ","         input 4"}, 
	},
	{	77,
		{"","brake wear"},
		{"      闸瓦检测5 ","         input 5"}, 
	},
	{	78,
		{"","brake wear"},
		{"      闸瓦检测6 ","         input 6"}, 
	},
	{	79,
		{"","brake wear"},
		{"      闸瓦检测7 ","         input 7"}, 
	},
	{	80,
		{"","brake wear"},
		{"      闸瓦检测8 ","         input 8"}, 
	},

	{	81,
		{"            上端","Upper"},
		{"        盖板开关","Coverplat"}, 
	},
	{	82,
		{"            上端","Upper"},
		{"    盖板防盗开关","Anti-theft"}, 
	},
	{	83,
		{"            下端","Lower"},
		{"        盖板开关","Coverplat"}, 
	},
	{	84,
		{"            下端","Lower"},
		{"    盖板防盗开关","Anti-theft"}, 
	},
	{	85,
		{"            上端","Upper"},
		{"手动自动 -> 手动","A/M -> Manual"}, 
	},
	{	86,
		{"            上端","Upper"},
		{"手动自动 -> 自动","A/M -> Auto"}, 
	},
	{	87,
		{"            下端","Lower"},
		{"手动自动 -> 手动","A/M -> Manual"}, 
	},
	{	88,
		{"            下端","Lower"},
		{"手动自动 -> 自动","A/M -> Auto"}, 
	},

	{	89,
		{"",""},
		{"油泵故障信号输入","Oil alarm input"}, 
	},
	{	90,
		{"",""},
		{"    火警信号输入","Fire Alarm input"}, 
	},
	{	91,
		{"",""},
		{"  烟雾传感器信号",""}, 
	},
	{	92,
		{"",""},
		{"  防火门联动停梯",""}, 
	},
	{	93,
		{"",""},
		{"    联动远程停梯","Remote stop"}, 
	},
	{	94,
		{"",""},
		{"风扇故障信号输入","Fan alarm input"}, 
	},
	{	95,
		{"          减速箱","     Gearbox oil"},
		{"油位检测开关信号","Low level alarm "}, 
	},
	{	96,
		{"",""},
		{"电源故障信号输入","Power fault"}, 
	},

  	{	97,
		{"",""},
		{"  桁架玻璃门开关","Glass door"}, 
	},
	{	98,
		{"",""},
		{"  桁架加热传感器",""}, 
	},
	{	99,
		{"          扶手带","Handrail"},
		{"驱动链断链开关1 ","drive chain 1"}, 
	},
	{	100,
		{"          扶手带","Handrail"},
		{"驱动链断链开关2 ","drive chain 2"}, 
	},
	{	101,
		{"",""},
		{"接地保护        ","ground connect"}, 
	},
	{	102,
		{"",""},
		{"加热检测        ","Heat error input"}, 
	},
	{	103,
		{"",""},
		{"飞轮防护罩打开  ","Motor cover"}, 
	},
	{	104,
		{"",""},
		{"地震干结点      ","Seismic sensor"}, 
	},

	{	105,
		{"",""},
		{"快速模式选择    ","Fast run mode"}, 
	},
	{	106,
		{"",""},
		{"远程使能信号    ","Remote enable"}, 
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
		{"主机位移检测1   ","主机位移检测1"}, 
	},
	{	110,
		{"",""},
		{"主机位移检测2   ","主机位移检测2"}, 
	},
	{	111,
		{"",""},
		{"主机位移检测3   ","主机位移检测3"}, 
	},
	{	112,
		{"",""},
		{"主机位移检测4   ","主机位移检测4"}, 
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
		{"可配置常闭输入01","Config NC input1"},
		{"",""}, 
	},
	{	130,
		{"可配置常闭输入02","Config NC input2"},
		{"",""}, 
	},
	{	131,
		{"可配置常闭输入03","Config NC input3"},
		{"",""}, 
	},
	{	132,
		{"可配置常闭输入04","Config NC input4"},
		{"",""}, 
	},
	{	133,
		{"可配置常闭输入05","Config NC input5"},
		{"",""}, 
	},
	{	134,
		{"可配置常闭输入06","Config NC input6"},
		{"",""}, 
	},
	{	135,
		{"可配置常闭输入07","Config NC input7"},
		{"",""}, 
	},
	{	136,
		{"可配置常闭输入08","Config NC input8"},
		{"",""}, 
	},

	{	137,
		{"可配置常开输入01","Config NO input1"},
		{"",""}, 
	},
	{	138,
		{"可配置常开输入02","Config NO input2"},
		{"",""}, 
	},
	{	139,
		{"可配置常开输入03","Config NO input3"},
		{"",""}, 
	},
	{	140,
		{"      下行接触器","Down contactor"},
		{"闭环检测输入    ","Check input"}, 
	},
	{	141,
		{"    三角型接触器","Delta contactor"},
		{"闭环检测输入    ","Check input"}, 
	},
	{	142,
		{"    三角型接触器","Delta contactor"},
		{"闭环检测输入2   ","Check input 2"}, 
	},
	{	143,
		{"",""},	  //{"",""},//
		{"主轴转速检测    ","Main Shaft input"}, //{"",""},//
	},
	{	144,
		{"",""},	  //  {"",""},//
		{"",""},    // {"",""}, //
	},

	{	145,     
		{"",""},  //{"","Driver chain"},  
		{"",""},  //{"主驱动断链检测2 ","     input 2"},   
	},
	{	146,
		{"",""},  //{"星（三角）接触器",""},
		{"",""},  //{"  闭环检测输入2 ","Check input 2"}, 
	},
	{	147,
		{"",""},  //{"","Dual motor"},
		{"",""},  //{"    F6.2故障输入","F6.2 input"}, 
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
		{"**  无功能    **","* No Function! *"}, 
	},
	{	1,
		{"","VVVF multi speed"},
		{"多段速输出--位0 ","Output BIT     0"}, 
	},
	{	2,
		{"","VVVF multi speed"},
		{"多段速输出--位1 ","Output BIT     1"}, 
	},
	{	3,
		{"","VVVF multi speed"},
		{"多段速输出--位2 ","Output BIT     2"}, 
	},
	{	4,
		{"",""},
		{"变频启动信号输出","VVVF run output"}, 
	},

	{	5,
		{"",""},
		{"    油泵控制输出","Oil output"}, 
	},

	{	6,
		{"",""},
		{"",""}, 
	},

	{	7,
		{"",""},
		{"    加热控制输出","Heat output"}, 
	},
	{	8,
		{"",""},
		{"",""}, 
	},
	{	9,
		{"","UP running"},
		{"交通灯上行控制","Traffic light"}, 
	},
	{	10,
		{"","Down running"},
		{"交通灯下行控制","Traffic light"}, 
	},
	{	11,
		{"",""},
		{"    蜂鸣器--上端","Upper Buzzer"}, 
	},
	{	12,
		{"",""},
		{"    蜂鸣器--下端","Lower Buzzer"}, 
	},
	{	13,
		{"",""},
		{"  蜂鸣器--控制柜","Ctr. Box Buzzer"}, 
	},
	{	14,
		{"",""},
		{"  梯级/ 梳齿照明","Light output"}, 
	},
	{	15,
		{"",""},
		{"    扶梯运行输出","ESC running"}, 
	},
	{	16,
		{"",""},
		{"    抱闸输出控制","Brake output"}, 
	},

	{	17,
		{"",""},
		{"    扶梯上行信号","ESC UP running"}, 
	},
	{	18,
		{"",""},
		{"    扶梯下行信号","ESC DOWN running"}, 
	},
	{	19,
		{"",""},
		{"    扶梯停梯信号","ESC stop state"}, 
	},
	{	20,
		{"",""},
		{"        急停状态","Emergency stop"}, 
	},
	{	21,
		{"",""},
		{"    故障状态信号","ESC fault"}, 
	},
	{	22,
		{"",""},
		{"    检修状态信号","Service state"}, 
	},
	{	23,
		{"",""},
		{"    盖板打开信号","Coverplat alarm"}, 
	},
	{	24,
		{"",""},
		{"    盖板防盗信号","Anti-Theft alarm"}, 
	},

	{	25,
		{"",""},
		{"外控继电器1 输出","Relay output 1"}, 
	},
	{	26,
		{"",""},
		{"外控继电器2 输出","Relay output 2"}, 
	},
	{	27,
		{"","Auto/Manual"},
		{"手/ 自动（手动）","Output -> Manual"}, 
	},
	{	28,
		{"","Auto/Manual"},
		{"手/ 自动（自动）","Output -> Auto"}, 
	},
	{	29,
		{"","Fire Alarm"},
		{"    火警信号返回","        feedback"}, 
	},
	{	30,
		{"","Fire Alarm"},
		{"消防功能确定返回"," Action feedback"}, 
	},
	{	31,
		{"故障输出","Fault class"},
		{"        一般故障","Normal"}, 
	},
	{	32,
		{"故障输出","Fault class"},
		{"        紧急故障","Emergency"}, 
	},

	{	33,
		{"",""},
		{"    油泵故障输出","Oil fault output"}, 
	},
	{	34,
		{"停梯状态","Stop state"},
		{"        故障停梯","Fault"}, 
	},
	{	35,
		{"停梯状态","Stop state"},
		{"    一般故障停梯","Normal"}, 
	},
	{	36,
		{"停梯状态","Stop state"},
		{"    紧急故障停梯","Emergency"}, 
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
  {"主板输入配置","   MB INPUT CFG"},
  {"主板输出配置","  MB OUTPUT CFG"},
  {"上端输入配置"," UPPER EB INPUT"},
  {"上端输出配置","UPPER EB OUTPUT"},
  {"下端输入配置","LOWER EB INPUT "},
  {"下端输出配置","LOWER EB OUTPUT"},
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
  //显示参数值 
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

  TXM_StringDisplay(0,8,50,32,0,NAVY ,0, "端子号: "); 
  TXM_StringDisplay(0,8,90,32,0,NAVY ,0, "功能号: "); 
  TXM_StringDisplay(0,8,135,24,0,NAVY ,0, "配置功能说明: "); 

  
  ZTM_RectangleFill (0,280,239,319,BLACK);
  TXM_StringDisplay(0,190,290,24,1,DGRAY ,LGRAY, "修改");
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
        //设置参数
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
            //设置参数
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
