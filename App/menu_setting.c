
#include "includes.h"

#define BASEMAX   36
 
typedef struct paraiocgcitem
{
	u8 MenuCount; 
	u8 *DisplayString[2];

	const DescripItem *gsDescripString; // 
  	
	u16 ParaAdr;       
  	
  	u16 dmin;
  	u16 dmax;			
} ParaIOCgcItem;

typedef struct multispeeditem
{
	u8 *DisplayItemString;
	u16 ParaAdr;       			
} MULTISPEEDITEM;
	
					  
const MULTISPEEDITEM MultiSpeedItem[]= 
{
	{
    " 00:00-00:30",
		1600,
  	},
	{
  	" 00:30-01:00",
		1601,
  	},
	{
  	" 01:00-01:30",
		1602,
  	},
	{
  	" 01:30-02:00",
		1603,
  	},
	{
  	" 02:00-02:30",
		1604,
  	},
	{
  	" 02:30-03:00",
		1605,
  	},
	{
  		" 03:00-03:30",
		1606,
  	},
	{
  		" 03:30-04:00",
		1607,
  	},
	{
  		" 04:00-04:30",
		1608,
  	},
	{
  		" 04:30-05:00", 
		1609,
  	},
	{
 		" 05:00-05:30", 
		1610,
  	},
	{
  		" 05:30-06:00", 
		1611,
  	},
	{
  		" 06:00-06:30",  
		1612,
  	},
	{
  		" 06:30-07:00", 
		1613,
  	},
	{
  		" 07:00-07:30", 
		1614,
  	},
	{
  		" 07:30-08:00", 
		1615,
  	},
	{
  		" 08:00-08:30", 
		1616,
  	},
	{
  		" 08:30-09:00",
		1617,
  	},
	{
  		" 09:00-09:30", 
		1618,
  	},
	{
  		" 09:30-10:00", 
		1619,
  	},
	{
  		" 10:00-10:30",  
		1620,
  	},
	{
  		" 10:30-11:00",  
		1621,
  	},
	{
  		" 11:00-11:30", 
		1622,
  	},
	{
  		" 11:30-12:00", 
		1623,
  	},
	{
  		" 12:00-12:30", 
		1624,
  	},
	{
  		" 12:30-13:00", 
		1625,
  	},
	{
  		" 13:00-13:30", 
		1626,
  	},
	{
  		" 13:30-14:00", 
		1627,
  	},
	{
  		" 14:00-14:30", 
		1628,
  	},
	{
  		" 14:30-15:00", 
		1629,
  	},
	{
  		" 15:00-15:30", 
 		1630,
  	},
	{
 		" 15:30-16:00", 
		1631,
  	},
	{
  		" 16:00-16:30", 
		1632,
  	},
	{
  		" 16:30-17:00", 
		1633,
  	},
	{
  		" 17:00-17:30", 
		1634,
  	},
	{
  		" 17:30-18:00", 
		1635,
  	},
	{
  		" 18:00-18:30", 
		1636,
  	},
	{
  		" 18:30-19:00",  
		1637,
  	},
	{
  		" 19:00-19:30", 
		1638,
  	},
	{
  		" 19:30-20:00", 
		1639,
  	},
	{
  		" 20:00-20:30", 
		1640,
  	},
	{
  		" 20:30-21:00", 
		1641,
  	},
	{
  		" 21:00-21:30", 
		1642,
  	},
	{
  		" 21:30-22:00",   
		1643,
  	},
	{
  		" 22:00-22:30", 
		1644,
  	},
	{
  		" 22:30-23:00", 
		1645,
  	},
	{
  		" 23:00-23:30", 
		1646,
  	},
	{
  		" 23:30-00:00",
		1647,
  	}
};

const ParaIOCgcItem ParaInputMBCgcItem[]=
{
	{
		28,					  
		{"主板输入配置 X06","MB input cgc X06"},
		DescripInputItem,
		1160,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X08","MB input cgc X08"},
		DescripInputItem,
		1161,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X10","MB input cgc X10"},
		DescripInputItem,
		1162,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X13","MB input cgc X13"},
		DescripInputItem,
		1163,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X20","MB input cgc X20"},
		DescripInputItem,
		1164,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X23","MB input cgc X23"},
		DescripInputItem,
		1165,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X24","MB input cgc X24"},
		DescripInputItem,
		1166,
		0,
		160
	},			
	{
		28,					  
		{"主板输入配置 X29","MB input cgc X29"},
		DescripInputItem,
		1167,
		0,
		160
	},			

	{
		28,					  
		{"主板输入配置 X31","MB input cgc X31"},
		DescripInputItem,
		1170,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X32","MB input cgc X32"},
		DescripInputItem,
		1171,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X33","MB input cgc X33"},
		DescripInputItem,
		1172,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X34","MB input cgc X34"},
		DescripInputItem,
		1173,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X35","MB input cgc X35"},
		DescripInputItem,
		1174,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X36","MB input cgc X36"},
		DescripInputItem,
		1175,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X37","MB input cgc X37"},
		DescripInputItem,
		1176,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X38","MB input cgc X38"},
		DescripInputItem,
		1177,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X39","MB input cgc X39"},
		DescripInputItem,
		1178,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X40","MB input cgc X40"},
		DescripInputItem,
		1179,
		0,
		139,
	},			

	{
		28,					  
		{"主板输入配置 X41","MB input cgc X41"},
		DescripInputItem,
		1180,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X42","MB input cgc X42"},
		DescripInputItem,
		1181,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X43","MB input cgc X43"},
		DescripInputItem,
		1182,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X44","MB input cgc X44"},
		DescripInputItem,
		1183,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X45","MB input cgc X45"},
		DescripInputItem,
		1184,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X46","MB input cgc X46"},
		DescripInputItem,
		1185,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X47","MB input cgc X47"},
		DescripInputItem,
		1186,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X48","MB input cgc X48"},
		DescripInputItem,
		1187,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X49","MB input cgc X49"},
		DescripInputItem,
		1188,
		0,
		139,
	},			
	{
		28,					  
		{"主板输入配置 X50","MB input cgc X50"},
		DescripInputItem,
		1189,
		0,
		139,
	},			
};						

const ParaIOCgcItem ParaInputUpperCgcItem[]=
{
	{
		17,					  
		{"上端输入配置 X16","Upper input  X16"},
		DescripInputItem,
		1190,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X17","Upper input  X17"},
		DescripInputItem,
		1191,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X18","Upper input  X18"},
		DescripInputItem,
		1192,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X19","Upper input  X19"},
		DescripInputItem,
		1193,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X20","Upper input  X20"},
		DescripInputItem,
		1194,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X21","Upper input  X21"},
		DescripInputItem,
		1195,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X22","Upper input  X22"},
		DescripInputItem,
		1196,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X23","Upper input  X23"},
		DescripInputItem,
		1197,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X24","Upper input  X24"},
		DescripInputItem,
		1198,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X25","Upper input  X25"},
		DescripInputItem,
		1199,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X26","Upper input  X26"},
		DescripInputItem,
		1200,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X27","Upper input  X27"},
		DescripInputItem,
		1201,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X28","Upper input  X28"},
		DescripInputItem,
		1202,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X29","Upper input  X29"},
		DescripInputItem,
		1203,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X30","Upper input  X30"},
		DescripInputItem,
		1204,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X31","Upper input  X31"},
		DescripInputItem,
		1205,
		0,
		139
	},			
	{
		17,					  
		{"上端输入配置 X32","Upper input  X32"},
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
		17,					  
		{"下端输入配置 X16","Lower input  X16"},
		DescripInputItem,
		1208,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X17","Lower input  X17"},
		DescripInputItem,
		1209,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X18","Lower input  X18"},
		DescripInputItem,
		1210,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X19","Lower input  X19"},
		DescripInputItem,
		1211,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X20","Lower input  X20"},
		DescripInputItem,
		1212,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X21","Lower input  X21"},
		DescripInputItem,
		1213,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X22","Lower input  X22"},
		DescripInputItem,
		1214,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X23","Lower input  X23"},
		DescripInputItem,
		1215,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X24","Lower input  X24"},
		DescripInputItem,
		1216,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X25","Lower input  X25"},
		DescripInputItem,
		1217,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X26","Lower input  X26"},
		DescripInputItem,
		1218,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X27","Lower input  X27"},
		DescripInputItem,
		1219,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X28","Lower input  X28"},
		DescripInputItem,
		1220,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X29","Lower input  X29"},
		DescripInputItem,
		1221,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X30","Lower input  X30"},
		DescripInputItem,
		1222,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X31","Lower input  X31"},
		DescripInputItem,
		1223,
		0,
		139
	},			
	{
		17,					  
		{"下端输入配置 X32","Lower input   X32"},
		DescripInputItem,
		1224,
		0,
		139
	},					
};

const ParaIOCgcItem ParaOutputMBCgcItem[]=
{
	{
		11,				 
		{"主板输出配置Q5.0","MB output   Q5.0"},
		DescripOutputItem,
		1226,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置Q5.1","MB output   Q5.1"},
		DescripOutputItem,
		1227,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置Q5.2","MB output   Q5.2"},
		DescripOutputItem,
		1228,
		0,
		80
	},			

	{
		11,				 
		{"主板输出配置  Q6","MB output     Q6"},
		DescripOutputItem,
		1230,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置  Q7","MB output     Q7"},
		DescripOutputItem,
		1231,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置  Q8","MB output     Q8"},
		DescripOutputItem,
		1232,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置  Q9","MB output     Q9"},
		DescripOutputItem,
		1233,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置 Q10","MB output     Q10"},
		DescripOutputItem,
		1234,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置 Q11","MB output    Q11"},
		DescripOutputItem,
		1235,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置 Q12","MB output    Q12"},
		DescripOutputItem,
		1236,
		0,
		80
	},			
	{
		11,				 
		{"主板输出配置 Q13","MB output    Q13"},
		DescripOutputItem,
		1237,
		0,
		80
	},			
};

const ParaIOCgcItem ParaOutputUpperCgcItem[]=
{
	{
		8,				 
		{"上端输出配置  Q1","Upper output  Q1"},
		DescripOutputItem,
		1238,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q2","Upper output  Q2"},
		DescripOutputItem,
		1239,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q3","Upper output  Q3"},
		DescripOutputItem,
		1240,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q4","Upper output  Q4"},
		DescripOutputItem,
		1241,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q5","Upper output  Q5"},
		DescripOutputItem,
		1242,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q6","Upper output  Q6"},
		DescripOutputItem,
		1243,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q7","Upper output  Q7"},
		DescripOutputItem,
		1244,
		0,
		80
	},			
	{
		8,					  
		{"上端输出配置  Q8","Upper output  Q8"},
		DescripOutputItem,
		1245,
		0,
		80
	},			
};

ParaIOCgcItem ParaOutputLowerCgcItem[]=
{
	{
		8,					  
		{"下端输出配置  Q1","Lower output  Q1"},
		DescripOutputItem,
		1246,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q2","Lower output  Q2"},
		DescripOutputItem,
		1247,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q3","Lower output  Q3"},
		DescripOutputItem,
		1248,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q4","Lower output  Q4"},
		DescripOutputItem,
		1249,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q5","Lower output  Q5"},
		DescripOutputItem,
		1250,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q6","Lower output  Q6"},
		DescripOutputItem,
		1251,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q7","Lower output  Q7"},
		DescripOutputItem,
		1252,
		0,
		80
	},			
	{
		8,					  
		{"下端输出配置  Q8","Lower output  Q8"},
		DescripOutputItem,
		1253,
		0,
		80
	},			
};

			
/******************************************************************************* 
*******************************************************************************/
//const ParaItem *ParaItemPoint;
const ParaIOCgcItem *ParaIoCgcPoint;

u8 ParaChangeEN=0;
u8 ParaSetupDisFlag = 0; 
static u16 UserChoose=0,ParaNumber=0,ParaNumber_MAX=0,ParaData=0,ParaData_MAX=0,ParaData_MIN=0; 

static u8 *m_keydata,err=0;
//------------------------------------------------------ // 08 
/******************************************************************************* 
*******************************************************************************/

/******************************************************************************* 
*******************************************************************************/
void para_check(void)
{
	u16 i,j;

	if(UserChoose==0)
	{
		i = ParaItemPoint[ParaNumber].ParaAdr;
		if(ParaItemPoint[ParaNumber].len==2)
		{
			ParaData = (ModBuff[i+1]<<8) | ModBuff[i];	
		}
		else if(ParaItemPoint[ParaNumber].len==1)
		{
			ParaData = ModBuff[i];	
		}	

		ParaData_MAX = ParaItemPoint[ParaNumber].dmax;
		ParaData_MIN = ParaItemPoint[ParaNumber].dmin;
	}
	else if(UserChoose < 7)
	{
		i = ParaIoCgcPoint[ParaNumber].ParaAdr;
		ParaData = ModBuff[i];	
		
		ParaData_MAX = ParaIoCgcPoint[ParaNumber].dmax;
		ParaData_MIN = ParaIoCgcPoint[ParaNumber].dmin;
	}
	else if(UserChoose == 7)
	{
		i = MultiSpeedItem[ParaNumber].ParaAdr;
		ParaData = ModBuff[i];	
		
		ParaData_MAX = 7;
		ParaData_MIN = 0;
	}
	else if(UserChoose == 8)
	{
		i = ParaNumber/8;
		j =	ParaNumber%8;
		if(ModBuff[1260+i] & (1<<j))
		{
			ParaData = 1;	
		}
		else
		{
			ParaData = 0;	
		}
		
		ParaData_MAX = 1;												
		ParaData_MIN = 0;									
	}
										
	if(ParaData<ParaData_MIN) ParaData = ParaData_MIN;
	if(ParaData>ParaData_MAX) ParaData = ParaData_MAX;	
}
   		
void para_write(void)      	
{
	u16 i,j;
 
	if(UserChoose==0)
	{
		i = ParaItemPoint[ParaNumber].ParaAdr;
		if(ParaItemPoint[ParaNumber].len==2)
		{  	
      ModBuff[i] = ParaData;
			ModBuff[i+1] = ParaData>>8;
		}
		else if(ParaItemPoint[ParaNumber].len==1)
		{
	  		ModBuff[i] = ParaData;
		}
 	}
	else if(UserChoose<7)
	{
		i = ParaIoCgcPoint[ParaNumber].ParaAdr;
		ModBuff[i] = ParaData;
	}
	else if(UserChoose == 7)
	{
		i = MultiSpeedItem[ParaNumber].ParaAdr;
		ModBuff[i] = ParaData;	
		
	}
	else if(UserChoose == 8)
	{
		i = ParaNumber/8;
		i = 1260+i;
		j =	ParaNumber%8;
		if(ParaData)
		{
			ModBuff[i] |= (1<<j);
		}
		else
		{
			ModBuff[i] &= ~(1<<j);
		}								
	}
		
	//MbCommCMD(MODBUS_CMD_WRITE,(i>>1),1);  
}

void set_para_init(void)
{
	if(UserChoose==0)
	{
//		ParaItemPoint = BaseParameter;
		ParaNumber_MAX = ParaItemPoint[0].MenuCount;
	}
	else if(UserChoose<7)
	{
		switch(UserChoose)						
		{
			case 2:  ParaIoCgcPoint = ParaOutputMBCgcItem; break;
			case 3:  ParaIoCgcPoint = ParaInputUpperCgcItem; break;
			case 4:  ParaIoCgcPoint = ParaOutputUpperCgcItem; break;
			case 5:  ParaIoCgcPoint = ParaInputLowerCgcItem; break;
			case 6:  ParaIoCgcPoint = ParaOutputLowerCgcItem; break;
			default: ParaIoCgcPoint = ParaInputMBCgcItem; break;
		}

		ParaNumber_MAX = ParaIoCgcPoint[0].MenuCount;
	}
	else if(UserChoose==7)
	{
		ParaNumber_MAX = 48;	
	}	
	else if(UserChoose==8)
	{
		ParaNumber_MAX = 250;		
	}	

	ParaNumber = 0;
	ParaChangeEN = 0;
	ParaSetupDisFlag = 1;
	para_check();
/*      
	menu_dis_disable=1; 
	MemuLevelCnt++; //  

	if(MemuLevelCnt==2) 
	{
		if(UserChoose==0)
		{
			subs_base_para_dis();
		}
		else if(UserChoose<7) 
		{
			subs_iocgc_para_dis();
		}
		else if(UserChoose==7) 
		{
			subs_multispeed_para_dis();
		}
		else if(UserChoose==8)
		{
			subs_errortype_para_dis();	
		}
	}
*/  
}

/******************************************************************************* 
*******************************************************************************/


/******************************************************************************* 
*******************************************************************************/
void subs_base_para_dis(void)
{	
/*  
	const ParaItem* psPara;	               
	u16 uint1;
  
  ParaItemPoint = BaseParameter;  
	psPara = &BaseParameter[ParaNumber];	  				
        
  TXM_StringDisplay (4002,16, 200,24,1,BLACK, WHITE, (void*)psPara->DisplayString1[LANGUAGE]);
  TXM_StringDisplay (4003,16, 240,24,1,BLACK, WHITE, (void*)psPara->DisplayString2[LANGUAGE]);
  
  if(psPara->ParaDisNum)
  {  
    uint1 = ParaData - ParaData_MIN; 
        
    TXM_StringDisplay (4005,16, 200,24,1,BLACK, WHITE, "");
    TXM_StringDisplay (4006,16, 200,24,1,BLACK, WHITE, "");
    TXM_StringDisplay (4004,16, 200,24,1,BLACK, WHITE, (void*)psPara->ParaDisString[LANGUAGE][uint1]);
  }
  else
  {
    TXM_StringDisplay (4004,16, 200,24,1,BLACK, WHITE, "");
    
    TXM_DigitDisplay (4005,100, 250,32,1,BLACK, WHITE, ParaData,6,0,ALIGN_RIGHT);
    
    //显示单位
    if(psPara->unitstr)
    {
    TXM_StringDisplay (4006,16, 280,24,0,BLACK, WHITE, (void*)psPara->unitstr);
    } 
  }  
*/  
}

void subs_iocgc_para_dis(void)
{
	const ParaIOCgcItem *psPara;	               

	switch(UserChoose)		    
	{		
		case 2:  psPara = &ParaOutputMBCgcItem[ParaNumber]; break;
		case 3:  psPara = &ParaInputUpperCgcItem[ParaNumber]; break;
		case 4:  psPara = &ParaOutputUpperCgcItem[ParaNumber]; break;
		case 5:  psPara = &ParaInputLowerCgcItem[ParaNumber]; break;
		case 6:  psPara = &ParaOutputLowerCgcItem[ParaNumber]; break;
		
		default: psPara = &ParaInputMBCgcItem[ParaNumber];  				
	}
	     
  TXM_StringDisplay (4002,16, 200,24,1,BLACK, WHITE, (void*)psPara->DisplayString[LANGUAGE]);
  TXM_StringDisplay (4003,16, 240,24,1,BLACK, WHITE, (void*)psPara->gsDescripString[ParaData].UpperString[LANGUAGE]);
  TXM_StringDisplay (4004,16, 200,24,1,BLACK, WHITE, (void*)psPara->gsDescripString[ParaData].LowerString[LANGUAGE]);

	//lcd_dis_uchar(2, 7, ParaData); 

}

void subs_multispeed_para_dis(void)
{
  
	if(LANGUAGE)
	{
    TXM_StringDisplay (4102,16, 200,24,1,BLACK, WHITE, "MultiSpeed set");
  }
	else
	{
    TXM_StringDisplay (4102,16, 200,24,1,BLACK, WHITE, "分时段速度设置");
	}
 
	if(LANGUAGE)
	{
    TXM_StringDisplay (4103,16, 200,24,1,BLACK, WHITE, "Time");
  }
	else
	{
    TXM_StringDisplay (4103,16, 200,24,1,BLACK, WHITE, "时间");
	}
  
  TXM_StringDisplay (4104,16, 200,24,1,BLACK, WHITE, (void*)MultiSpeedItem[ParaNumber].DisplayItemString);

  TXM_StringDisplay (4105,16, 200,24,1,BLACK, WHITE, (void*)MultiSpeedDisItem[ParaData][LANGUAGE]);
	
}

void subs_errortype_para_dis(void)
{
  /*
	if(LANGUAGE)
	{
		lcd_dis_str(1,1,"09Error type set");	
   	}
	else
	{
		lcd_dis_str(1,1,"09  故障分类    ");	
	}

	lcd_clear(3); 
	lcd_dis_str(3,1," F");
	lcd_dis_uint_3bit(3,2,ParaNumber+1);
	
	if(ParaData)
	{
		if(LANGUAGE)
		{
			lcd_dis_str(4,1,"    Normal error");	
   		}
		else
		{
			lcd_dis_str(4,1,"        一般故障");	
		}		
	}
	else
	{
		if(LANGUAGE)
		{
			lcd_dis_str(4,1," Emergency error");	
	   	}
		else
		{
			lcd_dis_str(4,1,"        紧急故障");	
		}
	}
  */
}
		
/******************************************************************************* 
*******************************************************************************/
void para_display(void)
{
  if(UserChoose==0)
  {
    subs_base_para_dis();
  } 
  else if(UserChoose<7)
  {
    subs_iocgc_para_dis();
  }  
  else if(UserChoose==7)
  {
    subs_multispeed_para_dis();
  }  
}

/******************************************************************************* 
*******************************************************************************/
void para_setup(u8 paraitem)
{
  u8 return_flag=0; //current_para_number=0,
  
  UserChoose = paraitem;
  ParaNumber = 0;
  
  if(UserChoose<7)
  {  
    ZTM_FullScreenImageDisp(40);    
  }
  else
  {
    ZTM_FullScreenImageDisp(41);    
  }  
  modbus_read(MB_COM_PORT, 550, 120);    

  set_para_init();

  para_check();
  
  para_display();
    
  while(1)
  {
    m_keydata = OSMboxPend(KeyMbox,0,&err);
                                        
    switch(m_keydata[0])
    {
      case KEY_UP:
        if(ParaChangeEN)	//修改参数
        {
          ParaData++;
          if(ParaData>ParaData_MAX)	
          {
            ParaData = ParaData_MIN;
          }									
        }
        else //参数选择
        {
          ParaNumber++;
          if(ParaNumber >= ParaNumber_MAX) ParaNumber = 0;
          para_check();						  	
        }	
        break;

      case KEY_DOWN:
        if(ParaChangeEN)	//修改参数
        {
          if(ParaData<=ParaData_MIN)	
          {
            ParaData = ParaData_MAX;
          }			
          else
          {
            ParaData--;
          }						
        }
        else //参数选择
        {
          if(ParaNumber < 1) 
          {
				  	ParaNumber = ParaNumber_MAX-1;
          }
          else	
          {
            ParaNumber--;
          }
          
          para_check();						  	
        }	
        break;
        
      case KEY_ESC:
        return_flag = 1;
/*
		  	if(ParaChangeEN)
        {
		   		get_para_data();
        }
        else
        {
		   		MemuLevelCnt--;  		
        }
        ParaChangeEN = 0x00;
        menu_dis_disable = 0;
*/        
        break;
		
      case KEY_SET:
/*			
        if(MemuLevelChoose[0]==7)
        {
          if(ParaChangeEN)	
          {
            para_write();
            ParaChangeEN = 0x00;
          }
          else
          {
            ParaChangeEN = 0x01;
          }		
        }
*/        
        break;	  
    }
  
    para_display();
    
    if(return_flag) break;
  }      
/*		

        if(MemuLevelCnt==2) 
    {
      if(UserChoose==0)
      {
        subs_base_para_dis();
      }
      else if(UserChoose<7) 
      {
        subs_iocgc_para_dis();
      }
		else if(UserChoose==7)
		{
			subs_multispeed_para_dis();
		}
		else if(UserChoose==8)
		{
			subs_errortype_para_dis();
		}
	}
	else
	{
		ParaSetupDisFlag = 0;
	}

    if(m_keydata[0] == KEY_DOWN)
    {
//      MenuArrayNumber++;
//      if(MenuArrayNumber>15) MenuArrayNumber = 0;
//      DisplayPictureNumber = MenuArrayPictureIndex[MenuArrayNumber];
    }  
    else if(m_keydata[0] == KEY_UP)
    {
//      if(MenuArrayNumber>0) MenuArrayNumber--;else MenuArrayNumber=15;
//      DisplayPictureNumber = MenuArrayPictureIndex[MenuArrayNumber];
    }                            
    else if(m_keydata[0] == KEY_ESC)
    {
//      DisplayPictureNumber = 0;
//      menu_flag = 0;
    }  
    else if(m_keydata[0] == KEY_SET)  
    {
      
    }
  }      
*/		
}


/******************************************************************************* 
*******************************************************************************/




#ifdef dddd

/******************************************************************************* 
*******************************************************************************/ 
void dis_set_password(void)
{
	u8 a[6]={'*','*','*','*','*',0};
	
	lcd_dis_str(1, 1, "**修改操作密码**");
	lcd_dis_str(2, 1, "Set new Password");

	if(ParaNumber>0)  a[0] = PASSWORD_BUFF[0]+0x30;
	if(ParaNumber>1)  a[1] = PASSWORD_BUFF[1]+0x30;
	if(ParaNumber>2)  a[2] = PASSWORD_BUFF[2]+0x30;
	if(ParaNumber>3)  a[3] = PASSWORD_BUFF[3]+0x30;
	if(ParaNumber>4)  a[4] = PASSWORD_BUFF[4]+0x30;
				
	lcd_dis_str(4, 1, "  --->  ");
	lcd_dis_str(4, 6, a);
	
	if(ParaNumber<6)
	{
		lcd_clear(3);
	}	
	else
	{													
		if(ParaData)
		{
			lcd_dis_str(3, 1, "  确定修改？  是  "); 
		}
		else
		{
			lcd_dis_str(3, 1, "  确定修改？  否  ");	
		}
	}
}
	
void set_password(void)
{
	u8 ucStatus=0;

	switch(key)
	{
		case KEY_UP:
			if(ParaNumber)
			{
			  	if(ParaNumber<6)
			  	{
					if(PASSWORD_BUFF[ParaNumber-1]<4) PASSWORD_BUFF[ParaNumber-1]++;
				}
				else
				{
					ParaData++;
					if(ParaData>1) ParaData=0;	
				}
			}
						
			break;
		case KEY_DOWN:
			if(ParaNumber)
			{
			  	if(ParaNumber<6)
			  	{
					if(PASSWORD_BUFF[ParaNumber-1]>1) PASSWORD_BUFF[ParaNumber-1]--;
				}
				else
				{
					ParaData++;
					if(ParaData>1) ParaData=0;	
				}
			}
						
			break;
		case KEY_ESC:
			   	
			 ucStatus = 1;
								
			break;
		case KEY_SET:
			
			if(ParaNumber<6)
			{
				ParaNumber++;
			}
			else 
			{  	
				if(ParaData)
				{
					MB_PASSWORD_BUFF[0] = PASSWORD_BUFF[0];
					MB_PASSWORD_BUFF[1] = PASSWORD_BUFF[1];
					MB_PASSWORD_BUFF[2] = PASSWORD_BUFF[2];
					MB_PASSWORD_BUFF[3] = PASSWORD_BUFF[3];
					MB_PASSWORD_BUFF[4] = PASSWORD_BUFF[4];
					MbCommCMD(MODBUS_CMD_WRITE,503,3);  		
				}	
			   		
				ucStatus = 1;
			}
				
			break;
  	}
	
	if(ucStatus)
	{
		CurrentMenuSubs = NullSubs;	
		MemuLevelCnt--;	
		menu_dis_disable=0; 
		ShowMenu();		
	}
	else
	{
		dis_set_password();
	}			
}



/******************************************************************************* 
*******************************************************************************/
void subs_dis_base_parameter(void)
{
	static u8 discnt=0;							 
	const u8 changeIndicateStr[2][16]={{"**  修改参数  **"},{"**  Setting   **"}}; 

   	discnt++;
	if(discnt>3) discnt=0;

	if(ParaChangeEN)
	{
		if(discnt==0)
		{							   
			lcd_dis_const_str(2,1,changeIndicateStr[LANGUAGE]); 
		}
		else if(discnt==2)	 
		{
		  	lcd_dis_str(2,1,"                ");   
		}
	}	
	else
	{
		lcd_dis_str(2,1,"                ");   
	}
}

void subs_dis_iocgc_parameter(void)
{
	static u8 discnt=0;	 

   	discnt++;
	if(discnt>3) discnt=0;

	if(ParaChangeEN)
	{
		if(discnt==0)
		{		
			if(LANGUAGE)
			{
				lcd_dis_str(2,1,"Set FUNC -> "); 
			}
			else				  
			{
				lcd_dis_str(2,1,"修改功能号->");
			}		 
		}
		else if(discnt==2)	 
		{
		  	lcd_dis_str(2,1,"            ");   
		}
	}
	else
	{
		if(LANGUAGE)
		{
			lcd_dis_str(2,1,"FUNC NO. -> "); 
		}
		else
		{
	  		lcd_dis_str(2,1,"当前功能号->"); 
		}
	}	
}

void dis_menu08_para(void)
{
	if(ParaSetupDisFlag==1)
	{
		if((UserChoose==0) || (UserChoose==7) || (UserChoose==8))
		{
			subs_dis_base_parameter();	
		}
		else if(UserChoose<7)
		{
			subs_dis_iocgc_parameter();	
		}
	}
}

/******************************************************************************* 
*******************************************************************************/
#endif
