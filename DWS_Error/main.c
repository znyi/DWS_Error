/*main.c*/

#include "Functions.h"


void WINAPI MMTimerCallback(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	static TIME t;			//Time Information
	static STOPWATCH st;	//Stopwatch Information
	static MODE md;			//Mode Information
	static ALARM r;
	char button_input[4];		//Button Input
	int button_info[2] = {0,0};	//Button Information(1,2)
	//int button;					//Button

	static int start=1;
	if(start==1)	//데이터 초기화. 한번만 수행
	{
		Initialize(&t, &st, &md, &r);
		start=0;
	}

	if(_kbhit())	//버튼 입력
	{
		//button_input[0] = 0;
		button_input[1] = 0;
		button_input[2] = 0;
		button_input[3] = 0;
		button_input[0] = _getch();

		//동시입력 처리
		if(_kbhit()) {
			button_input[1] = _getch();
		}
		if(_kbhit()) {
			button_input[2] = _getch();
		}
		if(_kbhit()) {
			button_input[3] = _getch();
		}
		ButtonIdentification(button_input, button_info);	//**Button Identification**
	}
	//Button Input없으면 Button_info[0]=0, Button_info[1]=0 (초기값)

	////////////////Display Control////////////////////////////////////////
	DisplayControl(&t, &st, &md, button_info[0], &r);//DisplayController	//////
	LightControl(button_info[1], &md, &r);		//LightController	////////////
	AlarmControl (&r,&md, &t,button_info[0],button_info[1]);
	/////////////////////////////////////////////////////////////////////
	return;
}

int main(void)
{
	MMRESULT hTimer;

	setcursortype(0);	//커서숨기기
	PrintWatchCase();	//시계틀 출력

	hTimer=timeSetEvent(10,0,MMTimerCallback,(DWORD)0,TIME_PERIODIC);
	//(10/1000)초의 Tick
	//0.01초마다 틱 발생하여 틱마다 MMTimerCallback 콜

	while(1) {}

	return 0;
}
