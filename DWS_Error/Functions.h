/*Functions.h*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Data.h"

///////////버튼/////////////
void ButtonIdentification(char button[], int button_info[]);

////////////초기화 관련 함수/////////////////
void InitSwitchSection(MODE *md);
void Initialize(TIME *t, STOPWATCH *st, MODE *md, ALARM *r);
void InitALSwitchSection(MODE *md);   //in etc.c

///////////화면출력 관련함수/////////////////
void gotoxy(int x, int y);
void PrintWatchCase(void);
void RemoveLine(void);
void SetColor( int colFront, int colBack );
void setcursortype(int cur_t);
//////////////////////////////////////

////////////////////////////////////////////////////
/////////////디스플레이 컨트롤러 관련 함수////////////
///////////////////////////////////////////////////
void DisplayControl(TIME *t, STOPWATCH *st, MODE *md, int button_info, ALARM *r);

int leapYear(int i); //
int calwday(int year, int month, int day); //
void IncreaseCurrentTime(TIME *a); //test1

void DisplayCurrentTime(TIME *time,MODE *mode); //
void PrintWatchNum(char *s1,char *s2,char *s3,char *s4,char *s5,char *s6,char *s7,char *s8, int indi);

void DisplaySetting(TIME *time,MODE *mode); 
void PrintSettingNum(char *s1,char *s2,char *s3,char *s4,char *s5,char *s6,char *s7,char *s8,MODE *mode, int indi);

void SwitchSection(MODE *md); //test2

void IncreaseValue(MODE *m, TIME *t); //test 10

void DisplayStopwatch(TIME *time,STOPWATCH *stopwatch,MODE *mode);
void PrintStopWatch(char *s1,char *s2,char *s3,char *s4,char *s5,char *s6,char *s7,char *s8,MODE *mode, int indi);

void RunStopwatch(STOPWATCH *sw);//

void RecordLapTime(STOPWATCH *sw, MODE *md); //test3

void StopwatchReset(STOPWATCH *sw); //test4

void LapTimeReset(STOPWATCH *sw, MODE *md); //test5



void PrintAlarm(char *s1,char *s2,char *s3,char *s4,char *s5,char *s6,int indi);
void DisplayAlarm(ALARM *r, MODE *mode);

void PrintAlarmSet(char *s1,char *s2,char *s3,char *s4,char *s5,char *s6, MODE *mode, int indi);
void DisplayAlarmSetting(ALARM *r, MODE *mode);

void SwitchSectionAlarm(MODE *m); //test6
void IncreaseAlarmValue(ALARM *r, MODE *m); // correct bcs no need to check leap year
void AlarmIndicator(MODE *m); //test7
///////////////////////////////////////////////
////////////////////////////////////


////////////////////////////light 컨트롤러////////////////////////
//////////////////////////////////////////////////////
void TurnOnTheLight(MODE *md);
void TurnOffTheLight(MODE *md);
void LightControl(int Button, MODE * md, ALARM *r); //test8


//////////////alarm controller//////////////////////////////
void CheckAlarm(ALARM *r, MODE *m, TIME *t); //test9
void AlarmOff(ALARM *r);
void Bell();
void AlarmControl (ALARM *r,MODE *m, TIME *t, int buttoninfo1, int buttoninfo2);
/////////////////////////////////////////////////
#endif
