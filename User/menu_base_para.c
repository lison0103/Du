
#include "includes.h"

#define BASEMAX     43

/*******************************************************************************
*******************************************************************************/
typedef struct paraitem     
{
  u8 MenuCount;    
  
  u8 menu_id;  
  u8 user_right;

  const u8 *DisplayString[2];
  
  const u8 ParaDisNum;
  const u8 *ParaDisString[2][21];     

  u16 ParaAdr;       
  u8 len;   
  
  const u8 *UnitString;
  
  u16 dmin;
  u16 dmax;
  
  u8 dot;

}ParaItem;

/*******************************************************************************
*******************************************************************************/
const ParaItem BaseParameter[]= 
{
//1
  {
    BASEMAX,1,1,
    
		{" 01 扶梯额定速度    "," 01 Esc speed       "}, 

		3,
    {                                               
		{"     0.5米/ 秒      ","    0.65米/ 秒      ","     0.75米/ 秒     "},
		{"     0.5m/s         ","    0.65m/s         ","     0.75m/s        "}
    },
                  
    1102,1,                         
    "",
    0,2,0,	    
  },

//2
  {
    BASEMAX,2,1,
    
    {" 02 控制模式        "," 02 Control mode    "}, 

		5,
    {                                                                                             
		{"    星三角          ","    变频            ","    星三角+ 变频    ","    SMART VVVF      ","    SMART VVVF+D/S  "},
		{"    Delta/Star      ","    VVVF            ","  Delta/Star+ VVVF  ","    SMART VVVF      ","    SMART VVVF+D/S  "}
    },
                  
    1103,1,                         
    
    "",
    0,4,0,	    
  },

//3
  {
    BASEMAX,3,1,
    
		{" 03 主板组成        "," 03 Constitute     "}, 

		4,
    {                                                                      
		{" 主板+ 上下端扩展   "," 主板+ 下端扩展     "," 主板+ 上端扩展     "," 单主板             "},
		{" MB+UPPER+LOWER     "," MB+LOWER           "," MB+UPPER           "," Mainboard only     "}
    },
                  
    1104,1,                         
    
    "",
    0,3,0,	    
  },
  
//4
  {
    BASEMAX,4,1,
      
		{" 04 主机驱动        "," 04 Driver mode     "}, 

		2,
    {                        
      {" 双驱--双主机       "," 单驱--单主机       "},
      {" Double motor       "," Single motor       "}
    },
                  
    1105,1,                         
    
      "",
    0,1,0,	    
  },
  
//5
  {
    BASEMAX,5,1,
     
		{" 05 电机抱闸检测    "," 05 Motor brake     "}, 

    3,
    {                                              
		{" 是，正相信号       ","        无          "," 是，反相信号       "},
		{" Brake check        "," No brake check     "," No brake check     "}
		},
  
    1106,1,
  
      "",
    0,
    2,0,
  },
  
//6
  {
    BASEMAX,6,1,
    
    {" 06 辅助抱闸        "," 06 AUX. brake      "},
    
    2,
    {
		{"        有          ","        无          "},
		{"        YES         ","        NO          "}
    },
                  
    1107,1,  
    
      "",
    0,1,0,
  }, 
  
//7
  { 
    BASEMAX,7,1,
    
		{" 07 星型启动时间    "," 07 STAR start ts   "},	
  
		10,  
		{                                                                       
    { " 三角型直接启动     ","       1s           ","        2s          ","       3s           ",
      "       4s           ","       5s           ","        6s          ","       7s           ",
      "       8s           ","       9s           ","       10s          "
		},
    { "  Delta start  1    ","       1s           ","        2s          ","       3s           ",
      "       4s           ","       5s           ","        6s          ","       7s           ",
      "       8s           ","       9s           ","       10s          "
    }
		},
    
    1108,1,

      "",
    0,10,0,
  },

//8
  {    
    BASEMAX,8,1,
    
		{" 08 电机额定频率    "," 08 Driver freq     "},
    	    
		12,	     
    {                                                                      
      {"         66 Hz      ","        100 Hz      ","        166 Hz      ","        200 Hz      ",
       "        250 Hz      ","        290 Hz      ","        333 Hz      ","        400 Hz      ",
       "        500 Hz      ","                    ","                    ","                    "},
      {"         66 Hz      ","        100 Hz      ","        166 Hz      ","        200 Hz      ",
       "        250 Hz      ","        290 Hz      ","        333 Hz      ","        400 Hz      ",
       "        500 Hz      ","                    ","                    ","                    "},
    },
                  
    1109,1,  
        
    "",
    0,8,0 
  },  

//9      
  {     
    BASEMAX,9,1,
    
		{" 09 扶手额定比值    "," 09 HDL rated       "},
  
    0,
    {{0},{0}},
  
    1110,
    2,
  
      "",
    50,
    1500,0
  },

//10
  {
    BASEMAX,10,1,
    
    {" 10 梯级缺少检测    "," 10 Missing step    "},
    
    2,
		{                      
		{"        有          ","        无          "},
		{"        YES         ","        NO          "}
    },
              
    1112,1,  
    
      "",
    0,1,0
  },

//11  					     
  {
    BASEMAX,11,1,
    
		{" 11 扶手同步监测    "," 11 HDL monitor     "},
 
    3,
    {  
      {"    故障停梯        ","    仅报警          ","        无      "},
      {"    stop when fault ","    Alarm only      ","        NO      "}
    },                                                            
                        
    1113,1,      
    
      "",
    0,2,0       
  },  
		  
  {
    BASEMAX,12,0,
    
		{" 12 快慢速节能      "," 12 Fast/Slow       "},
    
    2,
    {                         
      {"      有            ","      无            "},
      {"      YES           ","      NO            "},
    },
  
    1114, 1,
  
      "",
    0, 1,0
  },

//  
  {
    BASEMAX,13,0,
    
		{" 13 快速运行时间    "," 13 Fast seconds    "},
                                
    0,
    {{0},{0}},
  
    1116,
    2,
  
      "s",
    15,
    10000,0
  },
  
  {
    BASEMAX,14,0,
    
		{" 14 间歇停梯节能    "," 14 Intermittence   "},
    

		2,
    	{                      
    	{"      有            ","      无            "},
      {"      Enable        ","      Disable       "},
    	},
  
    	1115, 1,
  
      "",
    	0, 1,0
  	},
  
  {
    BASEMAX,15,0,
    
		{" 15 间歇慢速时间    "," 15 Slow seconds    "},
                                
    0,
    {{0},{0}},
  
    1118, 2,
  
      "s",
    15, 10000,0
  },
  
  {
    BASEMAX,16,1,
    
		{" 16 盖板信号设置    "," 16 Coverplate      "},
    
    2,
    {                         
      {"    断开报警        ","    闭合报警        "},
      {"    Open->Fault     ","    Close->Fault    "}
		},
  
    1120,1,
  
      "",
    0,1,0
  },
  
  {
    BASEMAX,17,0,
    
		{" 17 防盗信号设置    "," 17 Anti-theft      "},
    
    2,
    {                         
      {"    断开报警        ","    闭合报警        "},
      {"    Open->Fault     ","    Close->Fault    "}
		},
  
    1121,1,
  
    "",
    0,1,0
  },

//
  {
    BASEMAX,18,0,
    
		{" 18 扶手档01->故障  "," 18 HDL 01->Error   "},
                                
    	0,
    	{{0},{0}},
  
	    1126, 1,
  
      "",
	    2, 20,0
  	},

//
  {
    BASEMAX,19,0,
    
		{" 19 扶手档01->报警  "," 19 HDL 01->Alarm   "},
                                
    	0,
    	{{0},{0}},
  
	    1127, 1,
  
      "",
	    2, 20,0
  	},

//
  {
    BASEMAX,20,0,
    
		{" 22 扶手档02->故障  "," 22 HDL 02->Error   "},
                                
    	0,
    	{{0},{0}},
  
	    1128, 1,
  
      "",
	    2, 20,0
  	},

//
  {
    BASEMAX,21,0,
    
		{" 21 扶手档02->报警  "," 21 HDL 02->Alarm   "},
                                
    	0,
    	{{0},{0}},
  
	    1129, 1,
  
      "",
	    2, 20,0
  	},

//
//
  {
    BASEMAX,22,0,
    
		{" 22 扶手档03->故障  "," 22 HDL 03->Error   "},
                                
    	0,
    	{{0},{0}},
  
	    1130, 1,
  
      "",
	    2, 20,0
  	},

//
  {
    BASEMAX,23,0,
    
		{" 23 扶手档03->报警  "," 23 HDL 03->Alarm   "},
                                
    	0,
    	{{0},{0}},
  
	    1131, 1,
  
      "",
	    2, 20,0
  	},

//    
  {
    BASEMAX,24,1,
    
		{" 24 钥匙复位        "," 24 Key reset       "}, 

    	2,
    	{                        
      	{"      允许          ","      禁止          "},
      	{"      Enable        ","      Disable       "}
    	},
  	   		
    	1133,
    	1,
  
      "",
    	0,1,0 
  	},

//                               
  {
    BASEMAX,25,1,
    
		{" 25 多段速运行      "," 25 Multi speed     "},
                          
    3,
    {  
      {" 禁止               "," 本地分时           ","    远程多段速      "},
      {" Disable            "," Local time multi   "," Remote Multi       "}
		},
  
    1134,   
    1,
  
      "",
    0,
    2,0
  },  	 

//    
  {
    BASEMAX,26,0,
    
		{" 26 交通灯控制      "," 26 Traffic right   "}, 

    2,
    {
      {"    停梯不亮    ","停梯指示禁止通行"},
      {"  OFF when stop ","  ON when stop  "}
    },
  
    1135,
    1,
  
      "",
    0,1,0 
  },

//	      
  {
    BASEMAX,27,0,
    
		{" 27 检修蜂鸣器      "," 27 Buzzer option   "},


    2,
    {                          
      {" 间隔5s响           "," 无输出             "},
      {" Maintenance--ON    "," Maintenance--OFF   "}
		},
  
    1136,1,
  
      "",
    0,1,0
  },         
  
  {
    BASEMAX,28,0,
    
		{" 28 逆向进入报警    "," 28 Reverse enter   "},  

    2,
    {                         
      {" 间歇前10s 响       "," 慢速即响           "},
      {" Before Int.  ON    "," Low speed  ON      "}
    },
					   	
    1137,1,
  
      "",
    0,1,0 
  },            
  		
  {
    BASEMAX,29,0,
      
		{" 29 加热控制        "," 29 Heat control    "},
    		 										
    2,
    {                         
      {"      无            ","      有            "},
      {"      NO            ","      YES           "},
    },
  
    1138,1,								
  
      "",
    0,1,0       
  },  
  
  {
    BASEMAX,30,0,
    
		{" 30 加热开始时间    "," 30 Heat start      "},
    
    0,
    {{0},{0}},
  
    1139,
    1,
  
      ":00",
    0,
    23,0
  },  
  
  {
    BASEMAX,31,0,
    
		{" 31 加热停止时间    "," 31 Heat stop       "},
    
    0,
    {{0},{0}},
  
    1140,
    1,
  
      ":00",
    0,
    23,0
  },  
  
  {
    BASEMAX,32,0,
    
		{" 32 加热延时分钟    "," 32 Heat delay min  "},
                                
    0,
    {{0},{0}},
  
    1141,
    1,
  
    "",
    0,
    60,0
  }, 

//
  {
    BASEMAX,33,0,
    
		{" 33 火警动作        "," 33 Fire alarm      "},
                             
    4,
    { //" 10 梯级缺少检测    " 
		{"      停梯      ","    上行疏散    ","    下行疏散    ","    仅报警      "},
    {"      STOP      ","   UP  running  ","  DOWN running  ","   Alarm only   "}
		},
  
    1143,
    1,
  
      "",
    0,
    3,0
  },    

  {
    BASEMAX,34,0,
    
		{" 34 故障记录方式    "," 34 Fault record    "},
                             
    2,
    {                          
      {"    停梯故障        ","    所有故障        "},
      {" ESC stop fault     "," All fault          "}
		},
  
    1144,
    1,
  
      "",
    0,
    1,0
  },      
 
  {    
    BASEMAX,35,1,		
    
		{" 35 梯路测速模式    "," 35 ESC. freq mode  "},
    	    
		4,	     
    {                                                                    
    {" X1&2飞轮探头测速   "," 主轴测速  2 探头   "," 主轴测速  3 探头   "," X1&2飞轮 X6&8主轴  "},
    {" Mode1 2 sensor     "," Mode2 2 sensor     "," Mode3 3 sensor     "," Mode4 4 sensor     "},
    },
                  
    1145,1,   
        
      "",
    0,3,0
  },  
 	      
  {     
    BASEMAX,36,1,
     
		{" 36 主轴比率设定    "," 36 Motor rated     "},
  
    0,
    {{0},{0}},	  
  
    1146, 2,
  
      "",
    30,	 
    200,0  
  },
    
  //37
  {    
    BASEMAX,37,0,		 

    {" 37 检修状态时      "," 37 ESC inspect     "},
    	    
		2,	     
    {
      {"  故障输出  是  ","  故障输出  否  "},
      {"Fault output EN.","Fault output DIS"},
    },
                  
    1148,1,   
        
      "",
    0,1,0
  },  
  
  //38
  {     
    BASEMAX,38,1,
    
		{" 38 开梯蜂鸣器      "," 38 Key Start Beep  "},
  
    6,	     
    {
    {"  开梯无延时    ","  开梯延时1s    ","  开梯延时2s    ","  开梯延时3s    ","  开梯延时4s    ","  开梯延时5s    "},
    {"  Start Delay 0s","  Start Delay 1s","  Start Delay 2s","  Start Delay 3s","  Start Delay 4s","  Start Delay 5s"},
    },
    
    1149,1,  
    
      "",
    0,	 
    5,0  
  },

  //39
  {     
    BASEMAX,39,0,
    
		{" 39 故障输出保持    "," 39 Fault keep time "},
  
    0,
    {{0},{0}},	  
          
    1124, 2,
  
      "",
    0,	 
    3600,0  
  },
  
  //40
  {     
    BASEMAX,40,1,
    
		{" 40 远程通信控制    "," 40 CMS control     "},
  
    2,	     
    {
    {"  禁止          ","  允许          "},              
    {"  Disable       ","  Enable        "},                 
    },
          
    1159, 1,
  
      "",
    0,	 
    1,0  
  },
 
  //41
  {     
    BASEMAX,41,1,

		{" 41 辅助抱闸延时    "," 41 Aux brake delay "},
  
    4,
    {
    {"        延时3s  ","        延时4s  ","        延时5s  ","        延时6s  "},
    {"      Delay 3s  ","      Delay 4s  ","      Delay 5s  ","      Delay 6s  "},
    },	  
          
    1142, 1,                                 
  
    "",
    3,	                                      
    6,0                                      
  },
    
  //42
  {     
    BASEMAX,42,1,
    
		{" 42 梯级缺少辅抱延时"," 42 AUX delay time  "},
                              
    0,
    {{0},{0}},	  
          
    1123, 1,
  
      "s",
    0,	 
    60,1  
  },

  //43
  {     
    BASEMAX,43,1,
    
		{" 43 火警动作延时    "," 43 Fire alarm delay"},
  
    0,
    {{0},{0}},	  
          
    1156, 2,
  
      "s",
    0,	 
    3600,0  
  },

  //44
  {     
    BASEMAX,44,1,
    
		{"  系统参数PARA04 ","  SYSTEM PARA 04 "},
  
    0,
    {{0},{0}},	  
          
    1154, 1,
  
      "",
    0,	 
    250,0  
  },

  //45
  {     
    BASEMAX,45,1,
    
		{"  系统参数PARA05 ","  SYSTEM PARA 05 "},
  
    0,
    {{0},{0}},	  
          
    1155, 1,
  
      "",
    0,	 
    250,0  
  },

  //46
  {     
    BASEMAX,46,1,
    
		{"  系统参数PARA06 ","  SYSTEM PARA 06 "},
  
    0,
    {{0},{0}},	  
          
    1156, 1,
  
      "",
    0,	 
    250,0 
  },

  //47
  {     
    BASEMAX,47,1,
    
		{"  系统参数PARA07 ","  SYSTEM PARA 07 "},
  
    0,
    {{0},{0}},	  
          
    1157, 1,
  
      "",
    0,	 
    250,0  
  },

  //48
  {     
    BASEMAX,48,1,
                            
		{" 48  系统参数PARA08 "," 48  SYSTEM PARA 08 "},
  
    0,
    {{0},{0}},	  
          
    1158, 1,
  
      "",
    0,	 
    250,0  
  },
};

const char EscBasepara_Title[2][20]={"基本参数设置","BASE PARA CFG"}; 

static u8 Para_Number=0,PS_Flag=0; //Para_Buff[240]
static u16 Para_Data=0,Para_Max=0,Para_Min=0;

/*******************************************************************************
 u8 MenuCount;    
  
  u8 menu_id;  
  u8 user_right;

  const u8 *DisplayString1[2];
  const u8 *DisplayString2[2]; 
  
  const u8 ParaDisNum;
  const u8 *ParaDisString[2][16];     

  u16 ParaAdr;       
  u8 len;   
  
  const u8 *UnitString;
  
  u16 dmin;
  u16 dmax;
*******************************************************************************/
/*******************************************************************************
*******************************************************************************/
void base_para_get(void)
{
  u16 i;
  
  i = BaseParameter[Para_Number].ParaAdr;
  
  if(BaseParameter[Para_Number].len==1)
  {
    Para_Data = ModBuff[i];
  }  
  else if(BaseParameter[Para_Number].len==2)
  {
    Para_Data = (ModBuff[i+1]<<8)|ModBuff[i];
  } 
  
  Para_Max=BaseParameter[Para_Number].dmax;
  Para_Min=BaseParameter[Para_Number].dmin;
  
  if(Para_Data<Para_Min) Para_Data = Para_Min;
  else if(Para_Data>Para_Max) Para_Data = Para_Max;
}

void base_para_set(void)
{ 
  u16 i;
  i = BaseParameter[Para_Number].ParaAdr;
  
  if(BaseParameter[Para_Number].len==1)
  {
    ModBuff[i] = Para_Data;
  }  
  else if(BaseParameter[Para_Number].len==2)
  {
    ModBuff[i] = Para_Data;
    ModBuff[i+1] = Para_Data>>8;
  } 
        
  modbus_write(MB_COM_PORT, (i>>1), 1);
}

void base_para_display(void)
{
  u16 fcolor= WHITE;
  TXM_StringDisplay(0,0,80,24,1,WHITE ,BLUE, (void*)BaseParameter[Para_Number].DisplayString[LANGUAGE]);
  
//  TXM_FillTextWidget (350, (void*)BaseParameter[Para_Number].DisplayString[LANGUAGE]);
//  TXM_FillTextWidget (351, (void*)BaseParameter[Para_Number].DisplayString[LANGUAGE]);

  if(BaseParameter[Para_Number].ParaDisNum)
  {
    if(PS_Flag) fcolor= RED;
    
    TXM_StringDisplay(0,0,115,24,1,fcolor ,BLUE, (void*)BaseParameter[Para_Number].ParaDisString[LANGUAGE][Para_Data-Para_Min]);
    //TXM_FillTextWidget (352+PS_Flag, (void*)BaseParameter[Para_Number].ParaDisString[LANGUAGE][Para_Data-Para_Min]);
  }
  //显示参数值 
  else
  {
    if(PS_Flag)  
    {  
      fcolor= RED;
    }
    else
    {  
      TXM_StringDisplay(0,0,115,24,1,WHITE ,BLUE, "                    ");
    }
    
    TXM_DigitDisplay(0,8,115,24,1,fcolor,BLUE,Para_Data,5,BaseParameter[Para_Number].dot,ALIGN_RIGHT);
      
    TXM_StringDisplay(0,80,115,24,1,fcolor ,BLUE, (void*)BaseParameter[Para_Number].UnitString);
  
/*    
    TXM_FillTextWidget (352,"");
    TXM_DigitDisplay(354+PS_Flag,0,0,24,0,0,0,Para_Data,5,BaseParameter[Para_Number].dot,ALIGN_RIGHT);
    TXM_FillTextWidget (356, (void*)BaseParameter[Para_Number].UnitString);
*/
  }  
} 

/*******************************************************************************
*******************************************************************************/
extern u8 USER_RIGHT_LEVEL;
void menu_para_base(void)
{
  u8 *m_keydata,err=0;
  
  ZTM_FullScreenImageDisp(312);
  OSTimeDlyHMSM(0, 0,0,100); 
  
  ZTM_RectangleFill (0,0,239,39,NAVY);
  OSTimeDlyHMSM(0, 0,0,10);
  TXM_StringDisplay(0,8,2,32,0,WHITE ,0, (void*)EscBasepara_Title[LANGUAGE]); 

  Para_Number = 0;
  base_para_get();
  
  base_para_display();   

  ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
  
  TXM_StringDisplay(0,192,290,24,1,WHITE ,DGRAY, "设置");

  TXM_StringDisplay(0,0,50,24,1,LGRAY ,BLUE, " 选择参数           "); 
  
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
      if(PS_Flag)
      {
        switch(m_keydata[0])
        {
          case KEY_SET:
          case KEY_F2:
            
            PS_Flag = 0;
            
            //设置参数
            base_para_set();

            break;
          case KEY_F3:
          case KEY_ESC:
            
            PS_Flag = 0;
            
            break;
          case KEY_UP:
            if(Para_Data < Para_Max) Para_Data++; else Para_Data = Para_Min;
            break;
          case KEY_DOWN:
            if(Para_Data > Para_Min) Para_Data--; else Para_Data = Para_Max;
            break;
        } 
        
        if(PS_Flag==0)
        {  
          
            TXM_StringDisplay(0,122,290,24,1,WHITE ,DGRAY, "    "); 
            TXM_StringDisplay(0,192,290,24,1,WHITE ,DGRAY, "设置"); 
            
            TXM_StringDisplay(0,0,50,24,1,LGRAY ,BLUE, " 选择参数           "); 
        }        
      } 
      else
      {
        switch(m_keydata[0])
        {
          case KEY_LEFT:
          case KEY_DOWN:
            if(Para_Number) Para_Number--; else Para_Number = BASEMAX-1;
            base_para_get();
            break;
          case KEY_RIGHT:
          case KEY_UP:
            Para_Number++;
            if(Para_Number>=BASEMAX) Para_Number = 0;
            base_para_get();
            break;
          case KEY_F3:
            //@用户权限需要大于0才能设置
            if(USER_RIGHT_LEVEL >= (BaseParameter[Para_Number].user_right + 1))
            {
              PS_Flag = 1;
              
              TXM_StringDisplay(0,122,290,24,1,WHITE ,DGRAY, "确定"); 
              TXM_StringDisplay(0,192,290,24,1,WHITE ,DGRAY, "返回"); 

              TXM_StringDisplay(0,0,50,24,1,LGRAY ,BLUE, " 参数设置           "); 
            }
            //@end
            break;
        }          
      }  
      
      base_para_display();
    }    
  }  
}

/*******************************************************************************
*******************************************************************************/
