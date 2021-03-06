
#include "includes.h"

u16 DisplayPictureNumber=0,DisplayPictureNumberPre=0xff55;

/*******************************************************************************
*******************************************************************************/
void display_digital(DIS_DIGITAL_TypeDef* dps,u32 dat)
{
       
}

/*******************************************************************************
*******************************************************************************/
const char EscAlarmDisItem[][2][21]=
{                          
   {" W01 烟/ 火报警1    "," W01                "},  //01   
   {" W02 烟/ 火报警2    "," W02                "},  //02   
   {" W03 烟/ 火报警     "," W03                "},  //03   
   {" W04 上端光栅阻断   "," W04                "},  //04   
   {" W05 下端光栅阻断   "," W05                "},  //05   
   {" W06 左扶手带异常   "," W06                "},  //06   
   {" W07 右扶手带异常   "," W07                "},  //07   
   {" W08 油泵报警       "," W08                "},  //08   
   
   {" W09                "," W09                "},  //09   
   {" W10                "," W10                "},  //10   
   {" W11                "," W11                "},  //11  
   {" W12                "," W12                "},  //12   
   {" W13                "," W13                "},  //13   
   {" W14                "," W14                "},  //14   
   {" W15                "," W15                "},  //15   
   {" W16     加热异常   "," W16                "},  //16 

   {" W17 上端光栅异常   "," W17                "},  //17   
   {" W18 上端雷达异常   "," W18                "},  //18   
   {" W19 下端光栅异常   "," W19                "},  //19   
   {" W20 下端雷达异常   "," W20                "},  //20 
   {" W21                "," W21                "},  //21  
   {" W22                "," W22                "},  //22   
   {" W23                "," W23                "},  //23   
   {" W24 油泵报警       "," W24                "},  //24   
   
   {" W25 测速设置异常   "," W25 Config error   "},  //25   
   {" W26     设置异常   "," W26 Config error   "},  //26   
   {" W27                "," W27                "},  //27  
   {" W28                "," W28                "},  //28   
   {" W29                "," W29                "},  //29   
   {" W30                "," W30                "},  //30   
   {" W31                "," W31                "},  //31   
   {" W32     加热异常   "," W32                "},  //32 
};

/*******************************************************************************
*******************************************************************************/
const ErrorDescripItem ErrorCodeDescripItem[]= 
{	
	{
		0,
   		{"",""},
   		{"",""}
	},

	{
		1,
   		{" F01"," F01"},
   		{"",""}
	},
	{
		2,
   		{" F02           "," F02"},
   		{" 相位继电器异常"," Power phase"}
	},
	{
		3,
   		{" F03           "," F03"},		 
   		{" PTC 热保护异常"," Motor PTC"}
	},
	{
		4,
   		{" F04"," F04"},
   		{"",""}
	},
	{
		5,
   		{" F05"," F05"},
   		{"",""}
	},
	{
		6,
   		{" F06           "," F06 Upper"},
   		{" 上端梳齿板开关"," Combplate switch"}
	},
	{
		7,
   		{" F07           "," F07 Upper/Left"},
   		{" 上端左扶手入口"," Handrail inlet"}
	},
	{
		8,
   		{" F08           "," F08 Upper/Right"},
   		{" 上端右扶手入口"," Handrail inlet"}
	},
	{
		9,
   		{" F09           "," F09 Upper PIT"},
   		{" 上端蘑菇头按钮"," Emergency stop"}
	},
	{
		10,
   		{" F10         "," F10 Upper"},
   		{" 上端急停按钮"," Emergency stop"}
	},

	{
		11,
   		{" F11             "," F11 Upper"},
   		{" 上端梯级下陷开关"," Broken step"}
	},
	{
		12,
   		{" F12         "," F12 Upper"},
   		{" 上端裙板开关"," Skirt switch"}
	},
	{
		13,
   		{" F13         "," F13 Upper"},
   		{" 上端梯级防跳"," Buggy switch"}
	},
	{
		14,
   		{" F14             "," F14 Left handrail"},
   		{" 左边扶手断带开关"," Breakage switch"}
	},
	{
		15,
   		{" F15             "," F15 Right handrail"},
   		{" 右边扶手断带开关"," Breakage switch"}
	},
	{
		16,
   		{" F16         "," F16 Lower"},
   		{" 下端裙板开关"," Skirt switch"}
	},
	{
		17,
   		{" F17         "," F17 Lower"},
   		{" 下端梳齿开关"," Combplate switch"}
	},
	{
		18,
   		{" F18           "," F18 Lower/Left"},
   		{" 下端左扶手入口"," Handrail inlet"}
	},
	{
		19,			 
   		{" F19           "," F19 Lower/Right"},
   		{" 下端右扶手入口"," Handrail inlet"}
	},
	{
		20,
   		{" F20           "," F20 Lower PIT"},
   		{" 下端蘑菇头按钮"," Emergency stop"}
	},

	{
		21,
   		{" F21         "," F21 Lower"},
   		{" 下端急停按钮"," Emergency stop"}
	},
	{
		22,
   		{" F22           "," F22 Lower"},
   		{" 梯级下陷开关下"," Broken step"}
	},
	{
		23,
   		{" F23           "," F23 Step chain"},
   		{" 左链条涨紧开关"," Tension left"}
	},
	{
		24,
   		{" F24           "," F24 Step chain"},
   		{" 右链条涨紧开关"," Tension right"}
	},
	{
		25,
   		{" F25         "," F25 Lower"},
   		{" 下端梯级防跳"," Buggy switch"}
	},
	{
		26,
   		{" F26"," F26"},
   		{"",""}
	},
	{
		27,
   		{" F27       "," F27"},
   		{" 请注意安全"," Service"}
	},
	{
		28,
   		{" F28"," F28"},
   		{"",""}
	},
	{
		29,
   		{" F29"," F29"},
   		{"",""}
	},
	{
		30,
   		{" F30"," F30"},
   		{"",""}
	},

	{
		31,
   		{"",""},
   		{"",""}
	},
	{
		32,
   		{"",""},
   		{"",""}
	},
	{
		33,
   		{"",""},
   		{"",""}
	},
	{
		34,
   		{"",""},
   		{"",""}
	},
	{
		35,
   		{"",""},
   		{"",""}
	},
	{
		36,
   		{"",""},
   		{"",""}
	},
	{
		37,
   		{"",""},
   		{"",""}
	},
	{
		38,
   		{"",""},
   		{"",""}
	},
	{
		39,
   		{"",""},
   		{"",""}
	},
	{
		40,
   		{"",""},
   		{"",""}
	},

	{
		41,
   		{"",""},
   		{"",""}
	},
	{
		42,
   		{"",""},
   		{"",""}
	},
	{
		43,
   		{"",""},
   		{"",""}
	},
	{
		44,
   		{"",""},
   		{"",""}
	},
	{
		45,
   		{"",""},
   		{"",""}
	},
	{
		46,
   		{"",""},
   		{"",""}
	},
	{
		47,
   		{"",""},
   		{"",""}
	},
	{
		48,
   		{"",""},
   		{"",""}
	},
	{
		49,
   		{"",""},
   		{"",""}
	},
	{
		50,
   		{" F50         "," F50 Motor driver"},
   		{" 主机驱动断链"," Open chain"}
	},

	{
		51,
   		{" F51           "," F51"},
   		{" 电机抱闸1 异常"," Motor brake 1"}
	},
	{
		52,
   		{" F52           "," F52"},
   		{" 电机抱闸2 异常"," Motor brake 2"}
	},
	{
		53,
   		{" F53         "," F53"},
   		{" 辅助抱闸异常"," AUX. brake fault"}
	},
	{
		54,
   		{" F54      "," F54"},
   		{" 闸瓦检测1"," Brake wear 1"}
	},
	{
		55,
   		{" F55      "," F55"},
   		{" 闸瓦检测2"," Brake wear 2"}
	},
	{
		56,
   		{" F56         "," F56 "},
   		{" 钥匙开关粘连"," Key switch fault"}
	},
	{
		57,
   		{" F57       "," F57"},
   		{" 变频器故障"," VVVF fault"}
	},
	{
		58,
   		{" F58"," F58"},
   		{"",""}
	},
	{
		59,
   		{" F59"," F59"},
   		{"",""}
	},
	{
		60,
   		{" F60"," F60"},
   		{"",""}
	},

	{
		61,
   		{" F61"," F61"},
   		{"",""}
	},
	{
		62,
   		{" F62"," F62"},
   		{"",""}
	},
	{
		63,
   		{" F63"," F63"},
   		{"",""}
	},
	{
		64,
   		{" F64"," F64"},
   		{"",""}
	},
	{
		65,
   		{" F65"," F65"},
   		{"",""}
	},
	{
		66,
   		{" F66           "," F66"},
   		{" 扶手驱动连异常"," Handrail driver"}
	},
	{
		67,
   		{" F67             "," F67       Left"},
   		{" 左扶手带速度异常"," Handrail speed"}
	},
	{
		68,
   		{" F68             "," F68      Right"},
   		{" 右扶手带速度异常"," Handrail speed"}
	},
	{
		69,
   		{"",""},
   		{"",""}
	},
	{
		70,
   		{" F70         "," F70"},
   		{" 上端梯级缺少"," Upper stepmissing"}
	},

	{
		71,
   		{" F71         "," F70"},
   		{" 下端梯级缺少"," Lower stepmissing"}
	},
	{
		72,
   		{" F72     "," F72  Lubricator"},
   		{" 油泵故障"," Oil level lower"}
	},
	{
		73,
   		{" F73     "," F73 "},
   		{" 低温报警"," Temperature alarm"}
	},
	{
		74,
   		{" F74         "," F74"},
   		{" 风扇故障报警"," Fan alarm"}
	},
	{
		75,
   		{" F75             "," F75 Oil lower"},
   		{" 减速箱低液位报警"," Gear box     "}
	},
	{
		76,
   		{" F76     "," F76"},
   		{" 火警信号"," Fire alarm"}
	},
	{
		77,
   		{" F77            "," F77"},
   		{"  地震干结点报警"," Seismic activitie"}
	},
	{
		78,
   		{" F78     "," F78"},
   		{" 远程停梯"," Remote stop"}
	},
	{
		79,
   		{" F79     "," F79"},
   		{" 钥匙停梯"," Stop by key"}
	},
	{
		80,
   		{" F80           "," F80 Stopped"},
   		{" 卷帘门联动停梯"," By linkage"}
	},

	{
		81,
   		{" F81         "," F81"},
   		{" 系统自检异常"," System error"}
	},
	{
		82,
   		{" F82         "," F82 "},
   		{" F5电机热保护"," F5 activitie"}
	},
	{
		83,
   		{" F83           "," F83"},
   		{" F6.1电机热保护"," F6.1 PTC"}
	},
	{
		84,
   		{" F84           "," F84"},
   		{" F6.2电机热保护"," F6.2 PTC"}
	},
	{
		85,
   		{" F85 ",""},
   		{"",""}
	},
	{
		86,
   		{" F86 ",""},
   		{"",""}
	},
	{
		87,
   		{" F87 ",""},
   		{"",""}
	},
	{
		88,
   		{" F88 ",""},
   		{"",""}
	},
	{
		89,
   		{" F89 安全回路断开"," F89 SF chain open "},
   		{" 或检修盒断开    ","or Service box open"}
	},
	{
		90,
   		{" F90             "," F90   Upper left"},
   		{" 上端梳齿板开关左"," Combplate switch"}
	},

	{
		91,
   		{" F91             "," F91  Upper right"},
   		{" 上端梳齿板开关右"," Combplate switch"}
	},
	{
		92,
   		{" F92       上端"," F92 Upper left"},
   		{" 弯段裙板开关左"," Skirt switch"}
	},
	{
		93,
   		{" F93       上端"," F93 Upper right"},
   		{" 弯段裙板开关右"," Skirt switch"}
	},
	{
		94,
   		{" F94         下端"," F94 Lower left"},
   		{" 梳齿板水平开关左"," Combplate switch"}
	},
	{
		95,
   		{" F95         下端"," F95 Lower right"},
   		{" 梳齿板水平开关右"," Combplate switch"}
	},
	{
		96,
   		{" F96       下端"," F96 Lower left"},
   		{" 弯段裙板开关左"," Skirt switch"}
	},
	{
		97,
   		{" F97       下端"," F97 Lower right"},
   		{" 弯段裙板开关右"," Skirt switch"}
	},
	{
		98,
   		{" F98 松驰开关1"," F98"},
   		{" 扶手带驱动带 ",""}
	},
	{
		99,
   		{" F99 松驰开关2"," F99"},
   		{" 扶手带驱动带 ",""}
	},
 	{
		100,
   		{" F100            "," F100  Left handrail"},
   		{" 左扶手带断带开关"," Breakage switch    "}
	},

 	{
		101,
   		{" F101            "," F101 Right handrail"},
   		{" 右扶手带断带开关"," Breakage switch "}
	},
 	{
		102,
   		{" F100        "," F100    Middle"},
   		{" 中间急停按钮"," Emergency stop"}
	},
 	{
		103,
   		{" F103    "," F103"},
   		{" 水位开关"," "}
	},
 	{
		104,
   		{" F104              "," F104"},
   		{" 上端直段裙板开关左",""}
	},
 	{
		105,
   		{" F105              "," F105"},
   		{" 上端直段裙板开关右",""}
	},
 	{
		106,
   		{" F106        上端"," F106 Vertical left"},
   		{" 梳齿板垂直开关左"," Upper combplate   "}
	},
 	{
		107,
   		{" F107        上端"," F107 Vertical right"},
   		{" 梳齿板垂直开关右"," Upper combplate    "}
	},
 	{
		108,
   		{" F108          "," F108 Upper left "},
   		{" 上端梯级防跳左"," Buggy protection"}
	},
 	{
		109,
   		{" F109          "," F109 Upper right"},
   		{" 上端梯级防跳右"," Buggy protection"}
	},
 	{
		110,
   		{" F110      下端"," F110"},
   		{" 直段裙板开关左",""}
	},
   
 	{
		111,
   		{" F111      下端"," F111"},
   		{" 直段裙板开关右",""}
	},
 	{
		112,
   		{" F112        下端"," F112 Vertical left"},
   		{" 梳齿板垂直开关左"," Lower combplate   "}
	},
 	{
		113,
   		{" F113        下端"," F113 Vertical right"},
   		{" 梳齿板垂直开关右"," Lower combplate    "}
	},
 	{
		114,
   		{" F114          "," F114"},
   		{" 下端梯级防跳左",""}
	},
 	{
		115,
   		{" F115          "," F115"},
   		{" 下端梯级防跳右",""}
	},
 	{
		116,
   		{" F116            "," F116"},
   		{" 机械辅助抱闸异常",""}
	},
 	{
		117,
   		{" F117"," F117"},
   		{"",""}
	},
 	{
		118,
   		{" F118"," F118"},
   		{"",""}
	},
 	{
		119,
   		{" F119"," F119"},
   		{"",""}
	},
 	{
		120,
   		{" F120"," F120"},
   		{"",""}
	},

 	{
		121,
   		{" F121"," F121"},
   		{"",""}
	},
 	{
		122,
   		{" F122"," F122"},
   		{"",""}
	},
 	{
		123,
   		{" F123"," F123"},
   		{"",""}
	},
 	{
		124,
   		{" F124"," F124"},
   		{"",""}
	},
 	{
		125,
   		{" F125"," F125"},
   		{"",""}
	},
 	{
		126,
   		{" F126"," F126"},
   		{"",""}
	},
 	{
		127,
   		{" F127"," F127"},
   		{"",""}
	},
 	{
		128,
   		{" F128"," F128"},
   		{"",""}
	},
 	{
		129,
   		{" F129"," F129"},
   		{"",""}
	},
 	{
		130,
   		{" F130          "," F130           "},
   		{" 主板EEPROM错误"," MB eeprom error"}
	},

 	{
		131,
   		{" F131            "," F131         "},
   		{" 主板参数校验错误"," MB para error"}
	},
 	{
		132,
   		{" F132      "," F132"},
   		{" 安全继电器"," Safety relay err"}
	},
 	{
		133,
   		{" F133          "," F133"},
   		{" 主板继电器粘连"," MB relay error"}
	},
 	{
		134,
   		{" F134          "," F134"},
   		{" 双MCU 通信异常"," Dual comm error"}
	},
 	{
		135,
   		{" F135            "," F135"},
   		{" 上端扩展通信中断"," Upper comm error"}
	},
 	{
		136,
   		{" F136            "," F136"},
   		{" 下端扩展通信中断"," Lower comm error"}
	},
 	{
		137,
   		{" F137          "," F137"},              
   		{" 上下端通信中断"," U/L comm error"}
	},
 	{
		138,
   		{" F138    "," F138"},
   		{" 电机超速"," ESC overspeed"}
	},
 	{
		139,
   		{" F139    "," F139"},
   		{" 电机欠速"," ESC underspeed"}
	},
 	{
		140,
   		{" F140        "," F140"},
   		{" 制动距离超出"," Brake distance"}
	},

 	{
		141,
   		{" F141       "," F141"},
   		{" 电机超速15%"," Over speed 15%"}
	},
 	{
		142,
   		{" F142 电机欠速"," F142 ESC underspeed"},
   		{"    --高速状态"," Fast state"}
	},
 	{
		143,
   		{" F143 操作错误"," F143 Operate error"},
   		{"    --检修状态"," Service state"}
	},
 	{
		144,
   		{" F144 有钥匙信号"," F144 Key error"},
   		{"    --检修状态  "," Service state"}
	},
 	{
		145,
   		{" F145 有检修信号"," F145 Service Key"},
   		{"    --非检修状态"," Normal state"}
	},
 	{
		146,
   		{" F146        "," F146 Upper"},
   		{" 上端盖板打开"," Coverplat switch"}
	},
 	{
		147,
   		{" F147        "," F147 Upper"},
   		{" 上端防盗打开"," AntiTheft switch"}
	},
 	{
		148,
   		{" F148        "," F148 Lower"},
   		{" 下端盖板打开"," Coverplat switch"}
	},
 	{
		149,
   		{" F149        "," F149 Lower"},
   		{" 下端防盗打开"," AntiTheft switch"}
	},
 	{
		150,
   		{" F150          "," F150 service state"},		
   		{" 检修盖板未打开"," no cover plate open"}
	},

 	{
		151,
   		{" F151"," F151"},
   		{"",""}
	},
 	{
		152,
   		{" F152          "," F152 Aux brake"},
   		{" 辅助抱闸不断开","        not open"}
	},
 	{
		153,
   		{" F153          "," F153 "},
   		{" 辅助抱闸不闭合"," Aux brake not close"}
	},
 	{
		154,
   		{" F154        "," F154 Config error"},
   		{" 系统配置错误"," System fault     "}		   
	},
 	{
		155,
   		{" F155  电机欠速"," F155   Low speed"},
   		{" 防逆转停梯    "," Anti-reversal   "}
	},
 	{
		156,
   		{" F156 传感器异常"," F156"},
   		{" 测速不一致     ",""}
	},
 	{
		157,
   		{" F157 "," F157"},
   		{"",""}
	},
 	{
		158,
   		{" F158 "," F158 "},
   		{"",""}
	},
 	{
		159,
   		{" F159    "," F159       "},
   		{" 远程停梯"," Remote Stop"}
	},
 	{
		160,
   		{" F160  不闭合"," F160    Not close"},
   		{" 上下行接触器"," UP/DOWN contactor"}
	},

 	{
		161,
   		{" F161  不断开"," F161     Not open"},
   		{" 上下行接触器"," UP/DOWN contactor"}
	},
 	{
		162,
   		{" F162   不闭合"," F162    Not close"},
   		{" 星三角接触器1"," D/S contactor    "}
	},
 	{
		163,
   		{" F163   不断开"," F163     Not open"},
   		{" 星三角接触器1"," D/S contactor    "}
	},
 	{
		164,
   		{" F164      不闭合"," F164   Not close"},
   		{" 星三角输入接触器"," Delta/Star input"}
	},
 	{
		165,
   		{" F165 不断开     "," F165    Not open"},
   		{" 星三角输入接触器"," Delta/Star input"}
	},
 	{
		166,
   		{" F166    不闭合"," F166     Not close"},
   		{" 变频输入接触器"," VF input contactor"}
	},
 	{
		167,
   		{" F167    不断开"," F167      Not open"},
   		{" 变频输入接触器"," VF input contactor"}
	},
 	{
		168,
   		{" F168    不闭合"," F168      Not close"},
   		{" 变频输出接触器"," VF output contactor"}
	},
 	{
		169,
   		{" F169    不断开"," F169       Not open"},
   		{" 变频输出接触器"," VF output contactor"}
	},
 	{
		170,
   		{" F170  不闭合 "," F170   Not close"},
   		{" 星三角接触器2"," D/S contactor 2 "}
	},

 	{
		171,
   		{" F171   不断开"," F171    Not open"},
   		{" 星三角接触器2"," D/S contactor 2 "}
	},
 	{
		172,
   		{" F172            "," F172   Not close"},
   		{" 运行接触器不闭合"," Run contactor   "}
	},
 	{
		173,
   		{" F173            "," F173    Not open"},
   		{" 运行接触器不断开"," Run contactor   "}
	},
 	{
		174,
   		{" F174        "," F174         "},
   		{"主机位移检测1"," 主机位移检测1"}
	},
 	{
		175,
   		{" F175         "," F175         "},
   		{" 主机位移检测2"," 主机位移检测2"}
	},
 	{
		176,
   		{" F176    "," F176      "},
   		{" 加热故障"," Heat fault"}
	},
 	{
		177,
   		{" F177    "," F177          "},
   		{" 接地故障"," Ground connect"}
	},
 	{
		178,
   		{" F178  左扶手带"," F178 Left handrail"},
   		{" 驱动链断链开关"," Drive chain shitch"}
	},
 	{
		179,
   		{" F179  右扶手带"," F179 Right handrail"},
   		{" 驱动链断链开关"," Drive chain shitch "}
	},
 	{
		180,
   		{" F180    不闭合"," F180 Not close"},
   		{" 上行接触器异常"," UP contactor  "}
	},

 	{
		181,
   		{" F181    不断开"," F181 not open"},
   		{" 上行接触器异常"," UP contactor "}
	},
 	{
		182,
   		{" F182    不闭合"," F182 Not close"},
   		{" 下行接触器异常"," DOWN contactor"}
	},
 	{
		183,
   		{" F183    不断开"," F183  Not open"},
   		{" 下行接触器异常"," DOWN contactor"}
	},
 	{
		184,
   		{" F184    不闭合"," F184 Not close"},
   		{" 星型接触器异常"," STAR contactor"}
	},
 	{
		185,
   		{" F185    不断开"," F185  Not open"},
   		{" 星型接触器异常"," STAR contactor"}
	},
 	{
		186,
   		{" F186  不闭合"," F186  Not close"},
   		{" 三角型接触器"," DELTA contactor"}
	},
 	{
		187,
   		{" F187  不断开"," F187   Not open"},
   		{" 三角型接触器"," DELTA contactor"}
	},
 	{
		188,
   		{" F188     不闭合"," F188   Not close"},
   		{" 星型接触器异常2"," STAR contactor 2"}
	},
 	{
		189,
   		{" F189     不断开"," F189    Not open"},
   		{" 星型接触器异常2"," STAR contactor 2"}
	},
 	{
		190,
   		{" F190   不闭合"," F190   Not close"},
   		{" 三角型接触器2"," DELTA contactor2"}
	},

 	{
		191,			    
   		{" F191   不断开"," F191    Not open"},
   		{" 三角型接触器2"," DELTA contactor2"}
	},
 	{
		192,				 
   		{" F192      不闭合"," F192  Not close"},
   		{" 运行接触器异常2 "," Run contactor 2"}
	},
 	{
		193,				
   		{" F193     不断开"," F193   Not open"},
   		{" 运行接触器异常2"," Run contactor 2"}
	},
 	{
		194,
   		{" F194      "," F194       "},
   		{" 烟火传感器"," Fire sensor"}
	},
 	{
		195,
   		{" F195          "," F195            "},
   		{" 飞轮防护罩打开"," Motor cover open"}
	},
 	{
		196,
   		{" F196    "," F196       "},
   		{" 电源故障"," Power fault"}
	},
 	{
		197,
   		{" F197          "," F197           "},
   		{" 扶梯桁架玻璃门"," Glass door open"}
	},
 	{
		198,
   		{" F198            "," F198             "},
   		{" 电压跌落故障停梯"," Power voltage dip"}
	},
 	{
		199,
   		{" F199        "," F199       Upper"},
   		{" 上端用户停梯"," Passenger E-stop"}
	},
 	{
		200,
   		{" F200        "," F200       Lower"},
   		{" 下端用户停梯"," Passenger E-stop"}
	},

 	{
		201,
   		{" F201        "," F201 Contactor"},
   		{" 主板驱动异常"," Drive fault   "}
	},
 	{
		202,
   		{" F202"," F202"},
   		{"",""}
	},
 	{
		203,
   		{" F203"," F203"},
   		{"",""}
	},
 	{
		204,
   		{" F204"," F204"},
   		{"",""}
	},
 	{
		205,
   		{" F205"," F205"},
   		{"",""}
	},
 	{
		206,
   		{" F206"," F206"},
   		{"",""}
	},
 	{
		207,
   		{" F207"," F207"},
   		{"",""}
	},
 	{
		208,
   		{" F208"," F208"},
   		{"",""}
	},
 	{
		209,
   		{" F209"," F209"},
   		{"",""}
	},
 	{
		210,
   		{" F210"," F210"},
   		{"",""}
	},

 	{
		211,
   		{" F211"," F211"},
   		{"",""}
	},
 	{
		212,
   		{" F212"," F212"},
   		{"",""}
	},
 	{
		213,
   		{" F213"," F213"},
   		{"",""}
	},
 	{
		214,
   		{" F214"," F214"},
   		{"",""}
	},
 	{
		215,
   		{" F215"," F215"},
   		{"",""}
	},
 	{
		216,
   		{" F216"," F216"},
   		{"",""}
	},
 	{
		217,
   		{" F217"," F217"},
   		{"",""}
	},
 	{
		218,
   		{" F218"," F218"},
   		{"",""}
	},
 	{
		219,
   		{" F219"," F219"},
   		{"",""}
	},
 	{
		220,
   		{" F220"," F220"},
   		{"",""}
	},

 	{
		221,
   		{" F221"," F221"},
   		{"",""}
	},
 	{
		222,
   		{" F222"," F222"},
   		{"",""}
	},
 	{
		223,
   		{" F223"," F223"},
   		{"",""}
	},
 	{
		224,
   		{" F224"," F224"},
   		{"",""}
	},
 	{
		225,
   		{" F225"," F225"},
   		{"",""}
	},
 	{
		226,
   		{" F226"," F226"},
   		{"",""}
	},
 	{
		227,
   		{" F227"," F227"},
   		{"",""}
	},
 	{
		228,
   		{" F228"," F228"},
   		{"",""}
	},
 	{
		229,
   		{" F229"," F229"},
   		{"",""}
	},
 	{
		230,
   		{" F230"," F230"},
   		{"",""}
	},

 	{
		231,
   		{" F231"," F231"},
   		{"",""}
	},
 	{
		232,
   		{" F232"," F232"},
   		{"",""}
	},
 	{
		233,
   		{" F233"," F233"},
   		{"",""}
	},
 	{
		234,
   		{" F234"," F234"},
   		{"",""}
	},
 	{
		235,
   		{" F235"," F235"},
   		{"",""}
	},
 	{
		236,
   		{" F236"," F236"},
   		{"",""}
	},
 	{
		237,
   		{" F237"," F237"},
   		{"",""}
	},
 	{
		238,
   		{" F238"," F238"},
   		{"",""}
	},
 	{
		239,
   		{" F239"," F239"},
   		{"",""}
	},
 	{
		240,
   		{" F240"," F240"},
   		{"",""}
	},

 	{
		241,
   		{" F241"," F241"},
   		{"",""}
	},
 	{
		242,
   		{" F242"," F242"},
   		{"",""}
	},
 	{
		243,
   		{" F243"," F243"},
   		{"",""}
	},
 	{
		244,
   		{" F244"," F244"},
   		{"",""}
	},
 	{
		245,
   		{" F245"," F245"},
   		{"",""}
	},
 	{
		246,
   		{" F246"," F246"},
   		{"",""}
	},
 	{
		247,
   		{" F247"," F247"},
   		{"",""}
	},
 	{
		248,
   		{" F248"," F248"},
   		{"",""}
	},
 	{
		249,
   		{" F249"," F249"},
   		{"",""}
	},
 	{
		250,
   		{" F250"," F250"},
   		{"",""} 
	},
 	{
		251,
   		{" F251"," F251"},
   		{"",""} 
	},
 	{
		252,
   		{" F252"," F252"},
   		{"",""} 
	},
 	{
		253,
   		{" F253"," F253"},
   		{"",""} 
	},
 	{
		254,
   		{" F254"," F254"},
   		{"",""} 
	},
 	{
		255,
   		{" F255"," F255"},
   		{"",""} 
	},
  
  //系统故障解码
  // 1
 	{
		256,
   		{"系统错误","System error"},
   		{"        WDT 异常","       WDT fault"} 
	},
  // 2
 	{
		257,
   		{"系统错误","System error"},
   		{"    MCU 自检异常","       MCU fault"} 
	},
  // 3
 	{
		258,
   		{"系统错误","System error"},
   		{"   VVVF 速度配置","VVVF speed cfg"} 
	},
  // 4
 	{
		259,
   		{"系统错误","System error"},
   		{"",""} 
	},
  // 5
 	{
		260,
   		{"系统错误","System error"},
   		{"",""} 
	},
  // 6
 	{
		261,
   		{"系统错误","System error"},
   		{"",""} 
	},
  // 7
 	{
		262,
   		{"系统错误","System error"},
   		{"Q5  配置错误","Q5  cfg error"} 
	},
  // 8
 	{
		263,
   		{"系统错误","System error"},
   		{"主轴配置错误","Main Shaft cfg"} 
	},
  // 9
 	{
		264,
   		{"",""},
   		{"",""} 
	},
  // 10
 	{
		265,
   		{"",""},
   		{"",""} 
	},
  // 11
 	{
		266,
   		{"",""},
   		{"",""} 
	},
  // 12
 	{
		267,
   		{"",""},
   		{"",""} 
	},
  // 13
 	{
		268,
   		{"",""},
   		{"",""} 
	},
  // 14
 	{
		269,
   		{"",""},
   		{"",""} 
	},
  // 15
 	{
		270,
   		{"",""},
   		{"",""} 
	},
  // 16
 	{
		271,
   		{"",""},
   		{"",""} 
	}
  
  
};

/*******************************************************************************
*******************************************************************************/
void lcd_dis_record_error(u8 errcode)
{
  TXM_StringDisplay(0, 10,110,24, 1,RED ,BLUE, (void*)ErrorCodeDescripItem[errcode].UpperString[0]);
  TXM_StringDisplay(0, 10,142,24, 1,RED ,BLUE, (void*)ErrorCodeDescripItem[errcode].LowerString[0]);    
} 
  
/*******************************************************************************
*******************************************************************************/



/*******************************************************************************
*******************************************************************************/
void display_picture_update(void)
{
  if(DisplayPictureNumber == DisplayPictureNumberPre) return;
    
  ZTM_FullScreenImageDisp(DisplayPictureNumber);
  
  
//  TXM_StringDisplay (0,64, 200,32,1,BLACK, WHITE,"图");
//  TXM_DigitDisplay (0,96, 200,32,1,BLACK, WHITE, DisplayPictureNumber,3,0,ALIGN_ZERO_RIGHT);
//  TXM_DigitDisplay (0,100, 50,32,1,BLACK, WHITE, DisplayPictureNumber,4,1,ALIGN_RIGHT);
//  TXM_DigitDisplay (0,100, 100,32,1,BLACK, WHITE, DisplayPictureNumber,4,1,ALIGN_LEFT);
//  TXM_DigitDisplay (0,100, 150,32,1,BLACK, WHITE, DisplayPictureNumber,4,0,ALIGN_RIGHT);
//  TXM_DigitDisplay (0,100, 200,32,1,BLACK, WHITE, DisplayPictureNumber,4,0,ALIGN_LEFT);
//  TXM_DigitDisplay (0,100, 250,32,1,BLACK, WHITE, DisplayPictureNumber,3,0,ALIGN_ZERO_RIGHT);
  
//  subs_base_para_dis(DisplayPictureNumber);
  
  DisplayPictureNumberPre = DisplayPictureNumber;
}

/*******************************************************************************
*******************************************************************************/
void Task_Display(void *p_arg)
{
  (void)p_arg; 
  
  OSTimeDlyHMSM(0, 0,1,0);
  
  if(DisplayPictureNumber==0) DisplayPictureNumber=20;
  
  while(1) //main_loop
  {
    if(DisplayPictureNumber != DisplayPictureNumberPre)
    {
//      display_picture_update();
    }  
    
    OSTimeDlyHMSM(0, 0,0,10);
  }    
}

/*******************************************************************************
*******************************************************************************/
