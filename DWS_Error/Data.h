/*Data.h*/


#ifndef DATA_H
#define DATA_H


#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define string1 6 //시계 첫째줄의 출력 위치
#define string2 3 //시계 둘째줄의 출력 위치
#define _CRT_SECURE_NO_WARNINGS


////////////////////////////////////////////////
/////////////////구조체 선언/////////////////////
////////////////////////////////////////////////

typedef struct CurrentTime	//Time Information
{
	int year;	//2012~2099
	int month;	//1~12
	int day;	//1~31
	int wday;	//0~6(SUN~SAT)
	int hour;	//0~23
	int minute;	//0~59
	int second;	//0~59
	int centisecond; //0~99
} TIME;

typedef struct Stopwatch	//Stopwatch Information
{
	int minute;	//0~99
	int second;	//0~59
	int C_second;	//centisecond(0~99)
	//stopwatch time being measured

	int Lap_min; //Lap 분 (0~99)
	int Lap_se; //Lap 초  (0~59)
	int Lap_Cse; //Lap centisecond  (0~99)
	//lap time
} STOPWATCH;

typedef struct ModeCondition	//Mode Information
{
	int M_TS, M_ALS;
	/*if setting(Timesetting,Alarmsetting) */
	//	true : 1, false : 0
	
	int TS_year, TS_month, TS_day, TS_hour, TS_minute, TS_second;
	//section indicated in Timesetting Mode.
	//	true : 1, false : 0
	int AL_month, AL_day, AL_hour, AL_minute;
	//section indicated in alarmsetting
	//true : 1 , false : 0
	//hour minute month day
	int LAP_ON;	//Whether lap time is recorded(LAP_ON)
	int LIGHT_STATE;	//Whether DWS should turn the backlight on.
	int ALARM_INDI_ON;	//this flag variation is information about alarm indication
	//	true : 1, false : 0

} MODE;

/*2012 11 23 추기 */
typedef struct AlarmInformation {
	int month;
	int day;
	int hour;
	int minute;
	int CHECK_ALARM; //1이면 삐

} ALARM;

////////////////////////////////////////////////
enum {DISABLE,ENABLE};

#endif
