
#include "includes.h"

#define  SF_ERROR_XPIN 			ModBuff[409]

const char EscModeDescripBuff[][2][21]={           	                           
	{{" 星三角             "}, {" D/S                "}},
	{{" 星三角  手动       "}, {" D/S       Manual   "}},
	{{" 星三角  自动       "}, {" D/S         Auto   "}},	 
	{{" 变频               "}, {" VVVF               "}},	 
	{{" 变频    手动       "}, {" VVVF      Manual   "}},	 
	{{" 变频    自动       "}, {" VVVF        Auto   "}},	 	 
	{{"                    "}, {"                    "}},	 	 
};

const char EscStateDescripBuff[][2][21]={ 
							
	{{"      扶梯停止 "}, {"ESCALATOR  STOP"}},
	{{"      钥匙停梯 "}, {"ESC Stop by key"}},
	{{"      远程停梯 "}, {"Stop by remote "}},
	{{" 急停 扶梯停止 "}, {"Emergency  STOP"}},

	{{"      扶梯上行 "}, {"ESCALATOR    UP"}},
	{{" 快速 扶梯上行 "}, {"FAST UP RUNNING"}},
	{{" 慢速 扶梯上行 "}, {"SLOW UP RUNNING"}},
	{{" 间歇 扶梯上行 "}, {"Intermittent UP"}},
	{{" 星形 扶梯上行 "}, {"SLOW UP RUNNING"}},
	{{"               "}, {"               "}},

	{{"      扶梯下行 "}, {"ESCALATOR  DOWN"}},
	{{" 快速 扶梯下行 "}, {"FAST   DOWN    "}},
	{{" 慢速 扶梯下行 "}, {"SLOW   DOWN    "}},
	{{" 间歇 扶梯下行 "}, {"Intermit.  DOWN"}},
	{{" 星形 扶梯下行 "}, {"SLOW   DOWN    "}},
	{{"               "}, {"               "}},

	{{"** 检修模式  **"}, {"INSPECTION MODE"}},
};

extern u8 ResetKeyPin;
extern u16 ResetTms;

u8 MainDisFlag=0;

u16 rt_para[8];

/*******************************************************************************
*******************************************************************************/
u8 get_display_state_code(u8 *state_buff)
{
	u16 state=0;
	u8 temp1=0;	
	  
  if(state_buff[0]&0x02) state |= 0x0002; //上行
    else if(state_buff[0]&0x04) state |= 0x0004; //下行  
      else state |= 0x0001; //停梯
	
	if(state & 0x0006) 
	{
		if((state_buff[1]&0x30) && (!(state_buff[0]&0xc0)))	
		{
			state |= 0x0010;//快速
		}
		else if(state_buff[0]&0x40)
		{
      //星三角控制
      if((state_buff[2]&0x01) || (ModBuff[1103]==0))
      {  
        state |= 0x0080;//星型运行
      }        
      else
      {  
        state |= 0x0020;//慢速	
      }  
		}
		else if(state_buff[0]&0x80)
		{
			state |= 0x0040;//间歇
		}
	}				
	else
	{
		if(state_buff[0]&0x20)	//急停
		{
			state |= 0x0100; //
		}
		else if(state_buff[3]&0x02)	//钥匙停梯
		{
			state |= 0x0200; //		
		}
		else if(state_buff[3]&0x01)	//远程停梯
		{
			state |= 0x0400; //			
		}
	}  	

  switch(state)   
  {
    case 0x0001: temp1 = 0;break;
    case 0x0201: temp1 = 1;break;
    case 0x0401: temp1 = 2;break;
    case 0x0101: temp1 = 3;break;

    case 0x0002: temp1 = 4;break;
    case 0x0012: temp1 = 5;break;
    case 0x0022: temp1 = 6;break;
    case 0x0042: temp1 = 7;break;
    case 0x0082: temp1 = 8;break;

    case 0x0004: temp1 = 10;break;
    case 0x0014: temp1 = 11;break;  
    case 0x0024: temp1 = 12;break;
    case 0x0044: temp1 = 13;break;
    case 0x0084: temp1 = 14;break;

    //default: 	 temp1 = 16;
  }
  
  if(ModBuff[460]&0x10) temp1 = 16;
  
  return(temp1);
}

u8 get_display_mode_code(u8 *state_buff)
{  
	u16 state=0;
	u8 temp1=0;	

  //星三角控制
  if((state_buff[2]&0x01) || (ModBuff[1103]==0))  
  {
    state |= 0x0001;
  }  
  else
  {  
    state |= 0x0002;
  }

  //手自动
  if(state_buff[1]&0x04)  
  {
    state |= 0x0010;
  }  
  else if(state_buff[1]&0x08)
  {  
    state |= 0x0020;
  }

  switch(state)   
  {
    case 0x0001: temp1 = 0;break;
    case 0x0011: temp1 = 1;break;
    case 0x0021: temp1 = 2;break;
    case 0x0002: temp1 = 3;break;
    case 0x0012: temp1 = 4;break;
    case 0x0022: temp1 = 5;break;
    
    default: 	 temp1 = 6;
  }
    
  return(temp1);
}

/*******************************************************************************
*******************************************************************************/
void *get_error_coed_str(u8 dat, char *pstr)
{
  char *s = pstr;
  
  *pstr = 'F';
  pstr++;
  //显示3位数
  if(dat>99)
  {
    *pstr = 0x30+(dat/100);
    pstr++;
  }
  *pstr = 0x30+((dat%100)/10);
  pstr++;
  *pstr = 0x30+(dat%10);
  pstr++;
  if(dat<100)
  {  
    *pstr = ' ';
    pstr++;
  }
  *pstr = 0;

  return(s);
}

void get_error_descrip(u8 errcode, char *pstr)
{
  u16 i;
  
  pstr[0] = 0;
  strcpy(pstr, ErrorCodeDescripItem[errcode].UpperString[LANGUAGE]);
  i=strlen(pstr);
  for(;i<20;i++)
  {
    pstr[i] = ' ';
  }  
  pstr[20] = 0;
  strcat(pstr, ErrorCodeDescripItem[errcode].LowerString[LANGUAGE]);
  i=strlen(pstr);
  for(;i<40;i++)
  {
    pstr[i] = ' ';
  }  
  pstr[40] = 0;
  if(!errcode) pstr[0] = 0; 
}

void display_error_descrip(u16 wid_num,u8 errcode)
{
  char a[50];
  
  get_error_descrip(errcode, a);
  
  TXM_FillTextWidget(wid_num,a);  
}

void display_rt_speed(void)
{
  
  if(ECT_A_VERSION == 1)
  {
    rt_para[0] = pt_ModBuff[35];
    rt_para[1] = pt_ModBuff[36];
    rt_para[2] = pt_ModBuff[37];
    rt_para[3] = pt_ModBuff[38];
    rt_para[4] = pt_ModBuff[39];
    rt_para[5] = pt_ModBuff[40];
  }  
  else if((ECT_A_VERSION == 2) || (ECT_A_VERSION == 3))
  {
    rt_para[0] = pt_ModBuff[320];
    rt_para[1] = pt_ModBuff[371];
    rt_para[2] = pt_ModBuff[322];
    rt_para[3] = pt_ModBuff[373];
    rt_para[4] = pt_ModBuff[433];
    rt_para[5] = pt_ModBuff[484];
    rt_para[6] = pt_ModBuff[324];
    rt_para[7] = pt_ModBuff[375];
  }  
/*  
  else if(ECT_A_VERSION == 3)
  {
    rt_para[0] = pt_ModBuff[320];
    rt_para[1] = pt_ModBuff[321];
    rt_para[2] = pt_ModBuff[322];
    rt_para[3] = pt_ModBuff[323];
    rt_para[4] = pt_ModBuff[324];
    rt_para[5] = pt_ModBuff[325];
    rt_para[6] = pt_ModBuff[326];
    rt_para[7] = pt_ModBuff[327];
  }
*/  
  else
  {
    return;
  }
  
  //控制模式
  if((ModBuff[1145]==0) || (ModBuff[1145]==3) || (ECT_A_VERSION == 1))
  {
    TXM_StringDisplay(0,12,148,24,0,BLACK ,0, "电机频率"); 
    TXM_DigitDisplay(0,120,148,24,1,BLACK ,LGRAY, rt_para[0],4,0,ALIGN_RIGHT);
    TXM_DigitDisplay(0,180,148,24,1,BLACK ,LGRAY, rt_para[1],4,0,ALIGN_RIGHT);    
  } 
  //仅主轴
  else
  {
    TXM_StringDisplay(0,12,148,24,0,BLACK ,0, "主轴比值"); 
    TXM_DigitDisplay(0,120,148,24,1,BLACK ,LGRAY, rt_para[6],4,0,ALIGN_RIGHT);
    TXM_DigitDisplay(0,180,148,24,1,BLACK ,LGRAY, rt_para[7],4,0,ALIGN_RIGHT);    
  }  
       
  TXM_StringDisplay(0,12,180,24,0,BLACK ,0, "扶手比值");      
  TXM_DigitDisplay(0,120,180,24,1,BLACK ,LGRAY, rt_para[2],4,0,ALIGN_RIGHT);
  TXM_DigitDisplay(0,180,180,24,1,BLACK ,LGRAY, rt_para[3],4,0,ALIGN_RIGHT);
  
  if((ModBuff[1145]==3))
  {
    TXM_StringDisplay(0,12,212,24,0,BLACK ,0, "主轴比值"); 
    TXM_DigitDisplay(0,120,212,24,1,BLACK ,LGRAY, rt_para[6],4,0,ALIGN_RIGHT);
    TXM_DigitDisplay(0,180,212,24,1,BLACK ,LGRAY, rt_para[7],4,0,ALIGN_RIGHT);    
  }  
  
  TXM_StringDisplay(0,12,244,24,0,BLACK ,0, "制动距离");      
  TXM_DigitDisplay(0,120,244,24,1,BLACK ,LGRAY, rt_para[4],4,0,ALIGN_RIGHT);
  TXM_DigitDisplay(0,180,244,24,1,BLACK ,LGRAY, rt_para[5],4,0,ALIGN_RIGHT);
  
}

/*******************************************************************************
*******************************************************************************/
void main_display(void)
{  
  u8 i;
  char *errdescrip[2] = {"故障  ","ERROR "};
  char strbuff[30],a[10];
  
// RTCC_GetTime( &ModBuff[50]) ;
//  if()
//  time_display(307, 308, &ModBuff[50]);
  time_display(307, 308, TimeBuff);
  
  //Display_RTCC(0,290,0,0,&ModBuff[50]);

//  if(Esc_PreState)
// ModBuff[460] = 0x22;
  
  if(ModBuff[460]&0x01)
  {
    if(MainDisFlag != 2)
    {
      TXM_FillTextWidget (301, "");
      TXM_FillTextWidget (302, "");
      TXM_FillTextWidget (303, "");
      TXM_FillTextWidget (304, "");
      TXM_FillTextWidget (305, "");
      OSTimeDlyHMSM(0, 0,0,10);
      
      ZTM_RectangleFill (0, 280,239, 319,BLACK); 
      TXM_StringDisplay(0,60,290,24,0,RED ,WHITE, "复位 菜单 帮助"); 
    } 
    MainDisFlag = 2;
   
    if(SF_ERROR_XPIN)
    {
      strcpy(strbuff, errdescrip[LANGUAGE]);
      if(SF_ERROR_XPIN<=50)
      {
        strbuff[6] = 'M';
        i = SF_ERROR_XPIN;		
      }
      else if(SF_ERROR_XPIN<=82)
      {
        strbuff[6] = 'U';
        i = SF_ERROR_XPIN-50;			
      }
      else
      {
        strbuff[6] = 'D';
        i = SF_ERROR_XPIN-82;
      }
      strbuff[7] = 'X';
      strbuff[8] = i/10+0x30;
      strbuff[9] = i%10+0x30;
      strbuff[10] = ' '; 
      strbuff[11] = 0; 
      strcat(strbuff, get_error_coed_str(ModBuff[454], a)); 
    }
    else
    {
      strbuff[0] = ' ';
      strbuff[1] = ' ';
      strbuff[2] = 0;
      strcat(strbuff, errdescrip[LANGUAGE]);
      strcat(strbuff, get_error_coed_str(ModBuff[454], a));
      strbuff[12] = ' ';
      strbuff[13] = ' ';
      strbuff[14] = ' ';
      strbuff[15] = 0;
    }  
    
    TXM_FillTextWidget (310, strbuff);  //"扶梯故障"
    
    OSTimeDlyHMSM(0, 0,0,10); 
    display_error_descrip(311,ModBuff[454]);
    OSTimeDlyHMSM(0, 0,0,10); 
    display_error_descrip(312,ModBuff[455]);
    OSTimeDlyHMSM(0, 0,0,10); 
    display_error_descrip(313,ModBuff[456]);
    OSTimeDlyHMSM(0, 0,0,10); 
    display_error_descrip(314,ModBuff[457]);
    
    if(!ResetKeyPin)
    {
      if((ResetTms>200) && (ResetTms<1000))
      {
        ModBuff[5602] = 0xfa;
        ModBuff[5603] = 0x01;
        modbus_write(MB_COM_PORT, 2801, 1);
      }  
      ResetTms = 0;
    }  
  }
  else
  {       
    if(MainDisFlag != 1)
    {
      TXM_FillTextWidget (311, "");
      TXM_FillTextWidget (312, "");
      TXM_FillTextWidget (313, "");
      TXM_FillTextWidget (314, "");
      
      ZTM_RectangleFill (0, 280,239, 319,BLACK); 
      TXM_StringDisplay(0,60,290,24,0,RED ,WHITE, "     菜单 帮助"); 
    } 
    MainDisFlag = 1;

    //检修
    i = get_display_state_code(&ModBuff[460]);
    TXM_FillTextWidget (300, (void*)EscStateDescripBuff[i][LANGUAGE]);
    i = get_display_mode_code(&ModBuff[460]);
    TXM_FillTextWidget (301, (void*)EscModeDescripBuff[i][LANGUAGE]);
    OSTimeDlyHMSM(0, 0,0,100);
    
    if(1)//(ModBuff[460]&0x06)
    {  
      display_rt_speed(); 
    } 
  }
}

/*******************************************************************************
*******************************************************************************/