/*ETC.c*/

#include "Functions.h"


///////////버튼/////////////
void ButtonIdentification(char button[], int button_info[])
{
	int BUTTON = 0;
	int i = 0;
	for(i=0;i<4;i++) {
		if(button[i] == 'a' || button[i] == 'A')		//A Button Input
			button[i] = 1;
		else if(button[i] == 'b' || button[i] == 'B')	//B Button Input
			button[i] = 2;
		else if(button[i] == 'c' || button[i] == 'C')	//C Button Input
			button[i] = 3;
		else if(button[i] == 'd' || button[i] == 'D')	//D Button Input
			button[i] = 4;
		else
			button[i] = 0;
	}
	for(i = 0; i<4;i++) {		// the highest priority 검사
		if(button[i] > BUTTON) {
			BUTTON = button[i];
		}
	}

	if(BUTTON == 1 || BUTTON == 2 || BUTTON == 3) {		//A(1), B(2), C(3) 이면
		button_info[0] = BUTTON;	//**Button Information 1**
	}
	else if(BUTTON == 4) {		//D(4) 이면
		button_info[1] = BUTTON;	//**Button Information 2**
	}
}

////////////초기화 관련 함수/////////////////

void InitSwitchSection(MODE *md) {	//Timesetting에서 second 가리키게.
 (*md).TS_month = 0;
 (*md).TS_day = 0;
 (*md).TS_hour = 0;
 (*md).TS_minute = 0;
 (*md).TS_second = 1;
 (*md).TS_year = 0;
}
void InitALSwitchSection(MODE *md) {
	md->AL_day = 0;
	md->AL_hour = 1;
	md->AL_minute = 0;
	md->AL_month = 0;
}

void Initialize(TIME *t, STOPWATCH *st, MODE *md, ALARM *r)	//데이터 초기값 설정. 최초 1회 수행
{
	t->year = 2012;
	t->month = 1;
	t->day = 1;
	t->wday = 0;
	t->hour = 0;
	t->minute = 0;
	t->second = 0;
	t->centisecond = 0;
	//Time Information 초기화

	st->minute = 0;
	st->second = 0;
	st->C_second = 0;
	st->Lap_min = 0;
	st->Lap_se = 0;
	st->Lap_Cse = 0;
	//Stopwatch Information 초기화


	md->M_TS = 0;
	md->M_ALS = 0;
	md->LAP_ON = 0;
	md->LIGHT_STATE = 0;
	md->ALARM_INDI_ON = 0;
	md->TS_year = 0;
	md->TS_month = 0;
	md->TS_day = 0;
	md->TS_hour = 0; 
	md->TS_minute = 0;
	md->TS_second = 1; 
	md->AL_day = 0;
	md->AL_hour = 1;
	md->AL_minute = 0;
	md->AL_month = 0;
	//Mode Information 초기화

	r->CHECK_ALARM = 0;
	r->day = 0;
	r->hour = 0;
	r->minute = 0;
	r->month = 0;
	//Alarm Information 초기화
}

///////////화면출력 관련함수/////////////////
void gotoxy(int x, int y){		// 커서를 x,y좌표로 이동
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void PrintWatchCase(void)	//시계 틀 출력
{
	printf("┌─────────┐\n│                  │\n│                  │\n│                  │\n├─────────┤\n│                  │\n│                  │\n│                  │\n└─────────┘");
}

void RemoveLine(void)
{
	gotoxy(string1,3);
	printf("%14s","");
	gotoxy(string2,7);
	printf("%16s","");
}



void SetColor( int colFront, int colBack )		//Light Interface인 셈.
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((colBack << 4) | colFront));
}

void setcursortype(int cur_t)	// 커서 숨기기
{
    CONSOLE_CURSOR_INFO ccInfo;

    if (cur_t==0)		// NOCURSOR
    {
        ccInfo.dwSize = 20;
        ccInfo.bVisible = FALSE;
    }
    else if (cur_t==1)	// SOLIDCURSOR
    {
        ccInfo.dwSize = 100;
        ccInfo.bVisible = TRUE;
    }
    else				// NORMALCURSOR
    {
        ccInfo.dwSize = 20;
        ccInfo.bVisible = TRUE;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ccInfo);
}
