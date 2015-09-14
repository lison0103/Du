

typedef struct descripitem
{
	u8 ucID;
	
	u8 *UpperString[2];
	u8 *LowerString[2];
	
} DescripItem; 

extern const u8 MultiSpeedDisItem[8][2][21];
extern const DescripItem DescripInputItem[];
extern const DescripItem DescripOutputItem[];
extern const char EscAlarmDisItem[][2][21];
extern const char EscStateDisItem[][2][21];

