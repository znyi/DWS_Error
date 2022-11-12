/*DisplayControl.c*/

#include "Functions.h"


enum d_state
{
	TK_N_STW_STOP,	//TimekeepingMode(Stopwatch����)
	TS_N_STW_STOP,	//TimesettingMode(Stopwatch����)
	STW_STOP,		//StopwatchMode(����)
	TK_N_STW_RUN,	//TimekeepingMode(Stopwatch������)
	TS_N_STW_RUN,	//TimesettingMode(Stopwatch������)
	STW_RUN,			//StopwatchMode(������)
	AL_N_STW_STOP,		//Alarm mode(Stopwatch stop)
	AL_SETTING_N_STW_STOP, 	//Alarm setting(stopwatch stop)
	AL_N_STW_RUN,			//Alarm mode(Stopwatch run)
	AL_SETTING_N_STW_RUN	//Alarm setting(stopwatch run)
};

void DisplayControl(TIME* t, STOPWATCH* st, MODE* md, int button_info, ALARM* r)
{
	static enum d_state state = TK_N_STW_STOP;
	IncreaseCurrentTime(t);		//Enable "Increase Current Time"

	static int D_TK = ENABLE;	//Timekeeping
	static int D_TS = DISABLE;	//Timesetting
	static int D_ST = DISABLE;	//Stopwatch
	static int R_ST = DISABLE;	//If Stopwatch is Running
	static int A_MD = DISABLE;  //normal alarm mode
	static int A_ST = DISABLE;	//setting alarm mode

	if (D_TK) DisplayCurrentTime(t, md);
	else if (D_TS) DisplaySetting(t, md);
	else if (D_ST) DisplayStopwatch(t, st, md);
	else if (A_MD) DisplayAlarm(r, md);
	else if (A_ST) DisplayAlarmSetting(r, md);

	if (R_ST) RunStopwatch(st);

	switch (state)
	{
	case TK_N_STW_STOP:
		if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			D_TK = DISABLE;
			D_TS = ENABLE;
			state = TS_N_STW_STOP;
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			D_TK = DISABLE;
			A_MD = ENABLE;
			state = AL_N_STW_STOP;
		}
		break;
	case TS_N_STW_STOP:
		if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			D_TS = DISABLE;
			D_TK = ENABLE;
			state = TK_N_STW_STOP;
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			SwitchSection(md);			//Trigger "Switch Section"
		}
		else if (button_info == 2 && r->CHECK_ALARM == 0)
		{
			IncreaseValue(md, t);		//Trigger "Increase Value"
		}
		break;
	case STW_STOP:
		if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			D_ST = DISABLE;
			D_TK = ENABLE;
			state = TK_N_STW_STOP;
		}
		else if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			StopwatchReset(st);			//Trigger "Stopwatch Reset"
		}
		else if (button_info == 2 && r->CHECK_ALARM == 0)
		{
			R_ST = ENABLE;
			state = STW_RUN;
		}
		break;
	case TK_N_STW_RUN:
		if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			D_TK = DISABLE;
			D_TS = ENABLE;
			state = TS_N_STW_RUN;
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			D_TK = DISABLE;
			A_MD = ENABLE;
			state = AL_N_STW_RUN;
		}
		break;
	case TS_N_STW_RUN:
		if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			D_TS = DISABLE;
			D_TK = ENABLE;
			state = TK_N_STW_RUN;
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			SwitchSection(md);			//Trigger "Switch Section"
		}
		else if (button_info == 2 && r->CHECK_ALARM == 0)
		{
			IncreaseValue(md, t);		//Trigger "Increase Value"
		}
		break;
	case STW_RUN:
		if (button_info == 2 && md->LAP_ON == 1 && r->CHECK_ALARM == 0)
		{
			LapTimeReset(st, md);		//Trigger "Lap Time Reset"
		}
		else if (button_info == 1 && r->CHECK_ALARM == 0)
		{
			RecordLapTime(st, md);		//Trigger "Record Lap Time"
		}
		else if (button_info == 2 && !(md->LAP_ON == 1) && r->CHECK_ALARM == 0)
		{
			R_ST = DISABLE;
			state = STW_STOP;
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0)
		{
			D_ST = DISABLE;
			D_TK = ENABLE;
			state = TK_N_STW_RUN;
		}
		break;
	case AL_N_STW_STOP:
		if (button_info == 1 && r->CHECK_ALARM == 0) {//�˶� ����
			A_MD = DISABLE;
			A_ST = ENABLE;
			state = AL_SETTING_N_STW_STOP;
		}
		else if (button_info == 2 && r->CHECK_ALARM == 0) {
			AlarmIndicator(md);
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0) {
			A_MD = DISABLE;
			D_ST = ENABLE;
			state = STW_STOP;
		}
		break;
	case AL_SETTING_N_STW_STOP:
		if (button_info == 1 && r->CHECK_ALARM == 0) {
			A_ST = DISABLE;
			A_MD = ENABLE;
			state = AL_N_STW_STOP;
		}
		if (button_info == 2 && r->CHECK_ALARM == 0) {
			IncreaseAlarmValue(r, md);   //trigger increase value
		}
		if (button_info == 3 && r->CHECK_ALARM == 0) {
			SwitchSectionAlarm(md);
		}
		break;
	case AL_N_STW_RUN:
		if (button_info == 1 && r->CHECK_ALARM == 0) {//�˶� ����
			A_MD = DISABLE;
			A_ST = ENABLE;
			state = AL_SETTING_N_STW_RUN;
		}
		else if (button_info == 2 && r->CHECK_ALARM == 0) {
			AlarmIndicator(md);
		}
		else if (button_info == 3 && r->CHECK_ALARM == 0) {
			A_MD = DISABLE;
			D_ST = ENABLE;
			state = STW_RUN;
		}
		break;
	case AL_SETTING_N_STW_RUN:
		if (button_info == 1 && r->CHECK_ALARM == 0) {
			A_ST = DISABLE;
			A_MD = ENABLE;
			state = AL_N_STW_RUN;
		}
		if (button_info == 2 && r->CHECK_ALARM == 0) {
			IncreaseAlarmValue(r, md);   //trigger increase value
		}
		if (button_info == 3 && r->CHECK_ALARM == 0) {
			SwitchSectionAlarm(md);
		}
		break;
	}
}


int leapYear(int i) {  //������ �˻��Ͽ� �����̸� 1
	if (i % 4 == 0 && i % 100 != 0) { //������ �ƴϸ� 0����
		return 1; 
	}
	else if (i % 400 == 0)
		return 1;
	return 0;
}



int calwday(int year, int month, int day) {//0~6 �Ͽ�ȭ�������


	int a[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int cnt = 0;
	int allday = 0;   //�� ��¥
	int yearday = 0;   //�� ���� ������ ��¥
	int date;  // 1�� 2ȭ 3�� 4�� 5�� 6�� 7��
	int i;

	for (i = 1; i < year; i++) {    //�Է��� �������� ����� ���
		cnt += leapYear(i);    //cnt�� �Էµ� �⵵ �������� ����
	}

	switch (month) {    //���� �Էµ� �⵵�� �ޱ��� �귯�� �ϼ� ����

	case 1:
		break;
	case 2:
		yearday = a[0];
		break;
	case 3:
		yearday = a[0] + a[1];
		break;
	case 4:
		yearday = a[0] + a[1] + a[2];
		break;
	case 5:
		for (i = 0; i < 4; i++) { yearday += a[i]; }
		break;
	case 6:
		for (i = 0; i < 5; i++) { yearday += a[i]; }
		break;
	case 7:
		for (i = 0; i < 6; i++) { yearday += a[i]; }
		break;
	case 8:
		for (i = 0; i < 7; i++) { yearday += a[i]; }
		break;
	case 9:
		for (i = 0; i < 8; i++) { yearday += a[i]; }
		break;
	case 10:
		for (i = 0; i < 9; i++) { yearday += a[i]; }
		break;
	case 11:
		for (i = 0; i < 10; i++) { yearday += a[i]; }
		break;
	case 12:
		for (i = 0; i < 11; i++) { yearday += a[i]; }
		break;
	}


	if (leapYear(year) == 1 && month > 2)   //���� �⵵�� �����̸� +1 ���ش�
		yearday = yearday + 1;

	allday = 365 * (year - 1) + cnt + yearday;    //�Է��� ������ �Է��� �� �� ������ �� �ϼ�

	date = (allday + day) % 7;  // ���� ��¥�� ����

	return date;   //���� ���� �������� ���
}

void IncreaseCurrentTime(TIME* a) {   //100ƽ���� 1�� ����
	int leap = leapYear((*a).year);


	(*a).centisecond++;

	if ((*a).centisecond == 100)	//100ƽ ������
	{
		(*a).second++;
		if ((*a).second >= 60) {	//�� �ִ� -> �� ����
			(*a).minute++;
			(*a).second = 0;
		}
		if ((*a).minute >= 60) {	//�� �ִ� -> �� ����
			(*a).hour++;
			(*a).minute = 0;
		}
		if ((*a).hour >= 24) {	//�� �ִ� -> �� ���� 
			(*a).day++;
			//(*a).wday++; //wday should be 0~6, can be out of range
			(*a).hour = 0;
		}

		//�� �ִ��� �޿� ���� -> �� ����
		if ((*a).month == 1 || (*a).month == 3 || (*a).month == 5 || (*a).month == 7 || (*a).month == 8
			|| (*a).month == 10 || (*a).month == 12) {
			if ((*a).day > 31) {
				(*a).month++;
				(*a).day = 1;    //31���� �� 31���� ������ �� �ϳ� �����ɷ�
			}
		}
		else if ((*a).month == 4 || (*a).month == 6 || (*a).month == 9 || (*a).month == 11) {
			if ((*a).day > 30) {
				(*a).month++;
				(*a).day = 1;   //30���δ� ������ �ϳ� �����ɷ�
			}
		}
		else if ((*a).month == 2) {    //2���� ��� 28 29 ���缭 �� ����
			if (leap == 0 && (*a).day > 28) {
				(*a).day = 1;
				(*a).month++;

			}
			else if (leap == 1 && (*a).day > 29) {
				(*a).day = 1;
				(*a).month++;
			}
		}

		if ((*a).month > 12) {	//�� �ִ� -> �� ����
			(*a).month = 1;
			(*a).year++;
		}
		if ((*a).year > 2099) {	//�� �ִ� -> �ʱ�⵵��
			(*a).year = 2012;
		}
		(*a).wday = calwday((*a).year, (*a).month, (*a).day); //get correct wday using calwday
		(*a).centisecond = 0;
	}
}


void DisplayCurrentTime(TIME* time, MODE* mode)
{
	/////////////////////////////////
	char s1[3];
	char s2[3];
	char s3[3];
	char s4[3];
	char s5[3];
	char s6[3];
	char s7[5];
	char s8[5];
	int indi = mode->ALARM_INDI_ON;
	///////Display Command//////////

	if (mode->M_TS == 1)		//Timesetting Mode���� ����Ű�� section�� Second�� �ʱ�ȭ
	{
		InitSwitchSection(mode);
		mode->M_TS = 0;
	}
	//Mode Information ����

	switch (time->wday)
	{
	case 0:
		strcpy_s(s1, 3, "SU");
		break;
	case 1:
		strcpy_s(s1, 3, "MO");
		break;
	case 2:
		strcpy_s(s1, 3, "TU");
		break;
	case 3:
		strcpy_s(s1, 3, "WE");
		break;
	case 4:
		strcpy_s(s1, 3, "TH");
		break;
	case 5:
		strcpy_s(s1, 3, "FR");
		break;
	case 6:
		strcpy_s(s1, 3, "SA");
		break;
	}

	_itoa_s(time->month, s2, 3, 10);
	_itoa_s(time->day, s3, 3, 10);

	if ((time->hour) < 12)
	{
		strcpy_s(s4, 3, "A");
		_itoa_s(time->hour, s5, 3, 10);
		_itoa_s(time->minute, s6, 3, 10);
	}
	else
	{
		strcpy_s(s4, 3, "P");
		if (time->hour == 12)
		{
			_itoa_s(time->hour, s5, 3, 10);
		}
		else
		{
			_itoa_s((time->hour) - 12, s5, 3, 10);
		}
		_itoa_s(time->minute, s6, 3, 10);
	}
	_itoa_s(time->second, s7, 5, 10);
	_itoa_s(time->year, s8, 5, 10);

	PrintWatchNum(s1, s2, s3, s4, s5, s6, s7, s8, indi); 
	//Display Command ���
}

void PrintWatchNum(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, int indi)
{

	RemoveLine();
	if (indi == 1) {
		gotoxy(string1 - 1, 3);
		printf("��");
	}
	gotoxy(string1, 2);
	printf("%s %2s\'-%2s", s1, s2, s3);

	gotoxy(string2, 6);
	printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
}

void DisplaySetting(TIME* time, MODE* mode)
{
	//////////////////////////////
	char s1[3];
	char s2[3];
	char s3[3];
	char s4[3];
	char s5[3];
	char s6[3];
	char s7[5];
	char s8[5];
	int indi = mode->ALARM_INDI_ON;
	///////Display Command//////////

	mode->M_TS = 1;
	//Mode Information ����

	switch (time->wday)
	{
	case 0:
		strcpy_s(s1, 3, "SU");
		break;
	case 1:
		strcpy_s(s1, 3, "MO");
		break;
	case 2:
		strcpy_s(s1, 3, "TU");
		break;
	case 3:
		strcpy_s(s1, 3, "WE");
		break;
	case 4:
		strcpy_s(s1, 3, "TH");
		break;
	case 5:
		strcpy_s(s1, 3, "FR");
		break;
	case 6:
		strcpy_s(s1, 3, "SA");
		break;
	}

	_itoa_s(time->month, s2, 3, 10);
	_itoa_s(time->day, s3, 3, 10);



	if ((time->hour) < 12)
	{
		strcpy_s(s4, 3, "A");
		_itoa_s(time->hour, s5, 3, 10);
		_itoa_s(time->minute, s6, 3, 10);
	}
	else
	{
		strcpy_s(s4, 3, "P");
		if (time->hour == 12)
		{
			_itoa_s(time->hour, s5, 3, 10);
		}
		else
		{
			_itoa_s((time->hour) - 12, s5, 3, 10);
		}
		_itoa_s(time->minute, s6, 3, 10);
	}
	_itoa_s(time->second, s7, 5, 10);
	_itoa_s(time->year, s8, 5, 10);

	PrintSettingNum(s1, s2, s3, s4, s5, s6, s7, s8, mode, indi); 
	//Display Command ���
}

void PrintSettingNum(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, MODE* mode, int indi)
{

	//Timesetting Mode���� ���õ� section ���� �Բ� ���
	if ((mode->TS_year) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 7, 7);
		printf("����");

		gotoxy(string2, 6);
		printf("       %4s      ", s8);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->TS_month) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string1 + 3, 3);
		printf("��");

		gotoxy(string2, 6);
		printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->TS_day) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string1 + 6, 3);
		printf("��");

		gotoxy(string2, 6);
		printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->TS_hour) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 3, 7);
		printf("��");

		gotoxy(string2, 6);
		printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->TS_minute) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 9, 7);
		printf("��");

		gotoxy(string2, 6);
		printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->TS_second) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 15, 7);
		printf("��");

		gotoxy(string2, 6);
		printf("%s  %2s  \': %2s \':  %2s", s4, s5, s6, s7);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
}

void SwitchSection(MODE* md) {
	(*md).M_TS = 1;

	//�� �ð� �� �� �� �� �� ������ �ð����ø�带 �Űܾ� �Ѵ�!
	//Second �� Hour �� Minute �� Year �� Month �� Day �� Second
	if ((*md).TS_second == 1) {
		(*md).TS_second = 0;
		(*md).TS_hour = 1;
	}
	else if ((*md).TS_hour == 1) {
		(*md).TS_hour = 0;
		(*md).TS_minute = 1;
	}
	else if ((*md).TS_minute == 1) {
		(*md).TS_minute = 0;
		(*md).TS_year = 1;
	}
	else if ((*md).TS_year == 1) {
		(*md).TS_year = 0;
		(*md).TS_month = 1;
	}
	else if ((*md).TS_month == 1) {
		(*md).TS_month = 0;
		(*md).TS_day = 1;
	}
	else if ((*md).TS_day == 1) { //solved missing day to second
		(*md).TS_day = 0;
		(*md).TS_second = 1;
	}
}

void IncreaseValue(MODE* m, TIME* t) {
	//Mode Information���� ���õ� section�˻��ؼ� �׿� �ش��ϴ� Time Information ������ ����.
	if ((*m).TS_year == 1)
	{
		(*t).year++;
		if ((*t).year > 2099)
		{
			(*t).year = 2012;
		}
	}
	else if ((*m).TS_month == 1)
	{
		(*t).month++;
		if ((*t).month > 12)
		{
			(*t).month = 1;
		}
	}
	else if ((*m).TS_day == 1)
	{
		(*t).day++;
		if ((*t).month == 1 || (*t).month == 3 || (*t).month == 5 || (*t).month == 7 || (*t).month == 8
			|| (*t).month == 10 || (*t).month == 12)
		{
			if ((*t).day > 31) {
				(*t).day = 1;    //31���� �� 31���� ������ �� �ϳ� �����ɷ�
			}
		}
		else if ((*t).month == 4 || (*t).month == 6 || (*t).month == 9 || (*t).month == 11) {
			if ((*t).day > 30) {
				(*t).day = 1;   //30���δ� ������ �ϳ� �����ɷ�
			}
		}
		else if ((*t).month == 2) {    //2���� ��� 28 29 ���缭 �� ����
			//if ((*t).day > 29) {
			//	(*t).day = 1;
			//}
			if (leapYear((*t).year)) {
				if ((*t).day > 29) {
					(*t).day = 1;
				}
			}
			else {
				if ((*t).day > 28) {
					(*t).day = 1;
				}
			}
		}
	}
	else if ((*m).TS_hour == 1) {
		(*t).hour++;
		if ((*t).hour >= 24) {
			(*t).hour = 0;
		}

	}
	else if ((*m).TS_minute == 1) {
		(*t).minute++;
		if ((*t).minute >= 60) {
			(*t).minute = 0;
		}
	}
	else if ((*m).TS_second == 1) {
		(*t).second++;
		if ((*t).second >= 60) {
			(*t).second = 0;
		}
	}
	(*t).wday = calwday((*t).year, (*t).month, (*t).day);
}


void DisplayStopwatch(TIME* time, STOPWATCH* stopwatch, MODE* mode)
{
	///////////////////////////
	char s1[3];
	char s2[3];
	char s3[3];
	char s4[3];
	char s5[3];
	char s6[3];
	char s7[5];
	char s8[5];
	int indi = mode->ALARM_INDI_ON;
	/////////////Display Command///////////

	if (mode->LAP_ON == 0)	//lap time ��� �ȵǾ� ������, stopwatch time ���
	{
		_itoa_s(time->hour, s2, 3, 10);
		_itoa_s(time->minute, s3, 3, 10);	//���� ��, �� �Բ�
		_itoa_s(stopwatch->minute, s5, 3, 10);
		_itoa_s(stopwatch->second, s6, 3, 10);
		_itoa_s(stopwatch->C_second, s7, 5, 10);	//stopwatch time
	}
	else	//lap time ��� �Ǿ� ������, lap time ���
	{
		_itoa_s(time->hour, s2, 3, 10);
		_itoa_s(time->minute, s3, 3, 10);	//���� ��, �� �Բ�
		_itoa_s(stopwatch->Lap_min, s5, 3, 10);
		_itoa_s(stopwatch->Lap_se, s6, 3, 10);
		_itoa_s(stopwatch->Lap_Cse, s7, 5, 10);	//lap time
	}


	strcpy_s(s1, 3, "ST");

	PrintStopWatch(s1, s2, s3, s4, s5, s6, s7, s8, mode, indi);
	//Display Command ���
}

void PrintStopWatch(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, MODE* mode, int indi)
{
	if (indi == 1) {
		gotoxy(string1 - 1, 3);
		printf("��");
	}
	gotoxy(string1, 2);
	printf("%s %2s-%2s", s1, s2, s3);
	gotoxy(string2, 6);
	printf("   ");
	gotoxy(string2 + 4, 6);
	printf("%s  \' %2s \"  %2s", s5, s6, s7);
}

void RunStopwatch(STOPWATCH* sw)
{
	sw->C_second++;		//tick�� �ѹ��� �ö����� 0.01�ʾ� ����

	if (sw->C_second >= 100) {	//100����1�ʰ� 100�� �Ѿ��,
		sw->C_second = 0;	//0���� �ʱ�ȭ �����ش�.
		sw->second++;	//�ʸ� 1�� ���� ���� �ش�.
	}
	if (sw->second >= 60) {	//60�ʰ� �Ǹ�,
		sw->second = 0;		//�ʸ� 0���� �ʱ�ȭ �����ְ�,
		sw->minute++;	//1�� ���� �����ش�.
	}
	if (sw->minute >= 100)	//100���� �Ǹ�
		sw->minute = 0;	//0������ �����Ѵ�.
}

void RecordLapTime(STOPWATCH* sw, MODE* md)
{
	md->LAP_ON = 1;
	//Mode Information ���� 
	//sw->Lap_min = sw->second; //= sw->minute; //should be minute, not second
	sw->Lap_min = sw->minute; //should be minute, not second
	sw->Lap_se = sw->second;
	sw->Lap_Cse = sw->C_second;
	//stopwatch time �� lap time�� ����
}

void StopwatchReset(STOPWATCH* sw)	//��ž��ġ ����
{
	sw->C_second = 0;
	sw->second = 0;
	//sw->minute = 1;	//= 0; //should be 0
	sw->minute = 0; //should be 0
}

void LapTimeReset(STOPWATCH* sw, MODE* md)	//��Ÿ�� ����
{
	//sw->Lap_min = 5; // = 0; //should be 0
	sw->Lap_min = 0; //should be 0
	sw->Lap_se = 0;
	sw->Lap_Cse = 0;
	//lap time ���� 0����
	md->LAP_ON = 0;
	//Mode Information ����
}


void PrintAlarm(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, int indi)
{

	RemoveLine();
	if (indi == 1) {
		gotoxy(string1 - 1, 3);
		printf("��");
	}
	gotoxy(string1, 2);
	printf("%s %2s\'-%2s", s1, s2, s3);
	gotoxy(string2, 6);
	printf("%s    %2s  \': %2s    ", s4, s5, s6);
}

void DisplayAlarm(ALARM* r, MODE* mode)
{
	//////////////////////////////
	char s1[3];  //AL
	char s2[3];  //
	char s3[3];
	char s4[3];
	char s5[3];
	char s6[3];
	int indi = mode->ALARM_INDI_ON;
	//	char s7[5];  //second
	//	char s8[5];  //year
		///////Display Command//////////

	if (mode->M_ALS == 1)
	{
		//InitALSwitchSection(mode);
		mode->M_ALS = 0;
	}
	//Mode Information ����


	strcpy_s(s1, 3, "AL");

	_itoa_s(r->month, s2, 3, 10);
	_itoa_s(r->day, s3, 3, 10);



	if ((r->hour) < 12)
	{
		strcpy_s(s4, 3, "A");
		_itoa_s(r->hour, s5, 3, 10);
		_itoa_s(r->minute, s6, 3, 10);
	}
	else
	{
		strcpy_s(s4, 3, "P");
		if (r->hour == 12)
		{
			_itoa_s(r->hour, s5, 3, 10);
		}
		else
		{
			_itoa_s((r->hour) - 12, s5, 3, 10);
		}
		_itoa_s(r->minute, s6, 3, 10);
	}
	//	_itoa_s(r->second,s7,10);
	//	_itoa_s(r->year,s8,10);

	PrintAlarm(s1, s2, s3, s4, s5, s6, indi);
	//Display Command ���

}


void PrintAlarmSet(char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, MODE* mode, int indi)
{
	//Timesetting Mode���� ���õ� section ���� �Բ� ���
	if ((mode->AL_month) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string1 + 3, 3);
		printf("��");

		gotoxy(string2, 6);
		printf("%s    %2s  \': %2s   ", s4, s5, s6);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->AL_day) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string1 + 6, 3);
		printf("��");

		gotoxy(string2, 6);
		printf("%s    %2s  \': %2s   ", s4, s5, s6);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
	if ((mode->AL_hour) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\'-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 5, 7);
		printf("��");

		gotoxy(string2, 6);
		printf("%s    %2s  \': %2s   ", s4, s5, s6);
		if (indi == 1) {
			//gotoxy(string1-1,3);
			printf("��");
		}
		return;
	}
	if ((mode->AL_minute) == 1)
	{
		gotoxy(string1, 2);
		printf("%s %2s\"-%2s", s1, s2, s3);

		RemoveLine();
		gotoxy(string2 + 11, 7);
		printf("��");

		gotoxy(string2, 6);
		printf("%s    %2s  \': %2s   ", s4, s5, s6);
		if (indi == 1) {
			gotoxy(string1 - 1, 3);
			printf("��");
		}
		return;
	}
}



void DisplayAlarmSetting(ALARM* r, MODE* mode)
{
	//////////////////////////////
	char s1[3];  //AL
	char s2[3];  //
	char s3[3];
	char s4[3];
	char s5[3];
	char s6[3];
	int indi = mode->ALARM_INDI_ON;
	//	char s7[5];  //second
	//	char s8[5];  //year
		///////Display Command//////////

	mode->M_ALS = 1;
	//Mode Information ����

	strcpy_s(s1, 3, "AL");

	_itoa_s(r->month, s2, 3, 10);
	_itoa_s(r->day, s3, 3, 10);



	if ((r->hour) < 12)
	{
		strcpy_s(s4, 3, "A");
		_itoa_s(r->hour, s5, 3, 10);
		_itoa_s(r->minute, s6, 3, 10);
	}
	else
	{
		strcpy_s(s4, 3, "P");
		if (r->hour == 12)
		{
			_itoa_s(r->hour, s5, 3, 10);
		}
		else
		{
			_itoa_s((r->hour) - 12, s5, 3, 10);
		}
		_itoa_s(r->minute, s6, 3, 10);
	}
	//	_itoa_s(r->second,s7,10);
	//	_itoa_s(r->year,s8,10);

	PrintAlarmSet(s1, s2, s3, s4, s5, s6, mode, indi);
	//Display Command ���

}

void SwitchSectionAlarm(MODE* m) {
	/* change mode information about alarm switch section
	 * hour minute month day hour
	 */
	m->M_ALS = 1;

	if (m->AL_hour == 1) {
		m->AL_hour = 0;
		m->AL_minute = 1;
	}
	else if (m->AL_minute == 1) {
		m->AL_minute = 0;
		m->AL_month = 1;
	}
	else if (m->AL_month == 1) { //solved missing month to day
		m->AL_month = 0;
		m->AL_day = 1;
	}
	else if (m->AL_day == 1) {
		m->AL_day = 0;
		m->AL_hour = 1;
	}
}

void IncreaseAlarmValue(ALARM* r, MODE* m) {
	if (m->AL_hour == 1) {
		r->hour++;
		if (r->hour >= 24) {
			r->hour = 0;
		}
	}
	else if (m->AL_minute == 1) {
		r->minute++;
		if (r->minute >= 60) {
			r->minute = 0;
		}
	}
	else if (m->AL_month == 1) {
		r->month++;
		if (r->month > 12) {
			r->month = 0;
		}

		if (r->month == 4 || r->month == 6 || r->month == 9 || r->month == 11) {
			if (r->day > 30) {
				r->day = 30;   //30���δ� ������ �ϳ� �����ɷ�
			}
		}
		else if (r->month == 2) {    //2���� ��� 28 29 ���缭 �� ����
			if (r->day > 29) {
				r->day = 29;
			}
		}
	}
	else if (m->AL_day == 1)
	{

		r->day++;

		if (r->month == 1 || r->month == 3 || r->month == 5 || r->month == 7 || r->month == 8
			|| r->month == 10 || r->month == 12 || r->month == 0)
		{
			if (r->day > 31) {
				r->day = 0;    //31���� �� 31���� ������ �� �ϳ� �����ɷ�
			}
		}
		else if (r->month == 4 || r->month == 6 || r->month == 9 || r->month == 11) {
			if (r->day > 30) {
				r->day = 0;   //30���δ� ������ �ϳ� �����ɷ�
			}
		}
		else if (r->month == 2) {    //2���� ��� 28 29 ���缭 �� ����
			if (r->day > 29) {
				r->day = 0;
			}
		}
	}

}


void AlarmIndicator(MODE* m) { // function not defined
	if (m->ALARM_INDI_ON == 0)
		m->ALARM_INDI_ON = 1;
	else if (m->ALARM_INDI_ON == 1)
		m->ALARM_INDI_ON = 0;
}



