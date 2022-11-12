#include "pch.h"
#include "E:\DWS_Error/Data.h"
#include "E:\DWS_Error/DisplayControl.c"
#include "E:\DWS_Error/AlarmControl.c"
#include "E:\DWS_Error/LightControl.c"
#include "E:\DWS_Error/ETC.c"
//#include "..\..\DWS_Error/ETC.c" 

//201913552 황신이
//2.1.2
TEST(IncreaseCurrentTimeTestSuite, IncreaseCurrentTimeTest) {
	TIME t;
	t.centisecond = 99;
	t.second = 59;
	t.minute = 59;
	t.hour = 23;
	t.wday = 6;
	t.day = 31;
	t.month = 12;
	t.year = 2099;
	IncreaseCurrentTime(&t);
	EXPECT_EQ(t.centisecond, 0);
	EXPECT_EQ(t.second, 0);
	EXPECT_EQ(t.minute, 0);
	EXPECT_EQ(t.hour, 0);
	EXPECT_EQ(t.wday, 0);
	EXPECT_EQ(t.day, 1);
	EXPECT_EQ(t.month, 1);
	EXPECT_EQ(t.year, 2012);
}

//201913552 황신이
//2.1.5
TEST(SwitchSectionTestSuite, SecondToHourTest) {
	MODE md;
	md.TS_year = 0;
	md.TS_month = 0;
	md.TS_day = 0;
	md.TS_hour = 0;
	md.TS_minute = 0;
	md.TS_second = 1;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 0);
	EXPECT_EQ(md.TS_month, 0);
	EXPECT_EQ(md.TS_day, 0);
	EXPECT_EQ(md.TS_hour, 1);
	EXPECT_EQ(md.TS_minute, 0);
	EXPECT_EQ(md.TS_second, 0);
}
TEST(SwitchSectionTestSuite, HourToMinuteTest) {
	MODE md;
	md.TS_year = 0;
	md.TS_month = 0;
	md.TS_day = 0;
	md.TS_hour = 1;
	md.TS_minute = 0;
	md.TS_second = 0;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 0);
	EXPECT_EQ(md.TS_month, 0);
	EXPECT_EQ(md.TS_day, 0);
	EXPECT_EQ(md.TS_hour, 0);
	EXPECT_EQ(md.TS_minute, 1);
	EXPECT_EQ(md.TS_second, 0);
}
TEST(SwitchSectionTestSuite, MinuteToYearTest) {
	MODE md;
	md.TS_year = 0;
	md.TS_month = 0;
	md.TS_day = 0;
	md.TS_hour = 0;
	md.TS_minute = 1;
	md.TS_second = 0;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 1);
	EXPECT_EQ(md.TS_month, 0);
	EXPECT_EQ(md.TS_day, 0);
	EXPECT_EQ(md.TS_hour, 0);
	EXPECT_EQ(md.TS_minute, 0);
	EXPECT_EQ(md.TS_second, 0);
}
TEST(SwitchSectionTestSuite, YearToMonthTest) {
	MODE md;
	md.TS_year = 1;
	md.TS_month = 0;
	md.TS_day = 0;
	md.TS_hour = 0;
	md.TS_minute = 0;
	md.TS_second = 0;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 0);
	EXPECT_EQ(md.TS_month, 1);
	EXPECT_EQ(md.TS_day, 0);
	EXPECT_EQ(md.TS_hour, 0);
	EXPECT_EQ(md.TS_minute, 0);
	EXPECT_EQ(md.TS_second, 0);
}
TEST(SwitchSectionTestSuite, MonthToDayTest) {
	MODE md;
	md.TS_year = 0;
	md.TS_month = 1;
	md.TS_day = 0;
	md.TS_hour = 0;
	md.TS_minute = 0;
	md.TS_second = 0;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 0);
	EXPECT_EQ(md.TS_month, 0);
	EXPECT_EQ(md.TS_day, 1);
	EXPECT_EQ(md.TS_hour, 0);
	EXPECT_EQ(md.TS_minute, 0);
	EXPECT_EQ(md.TS_second, 0);
}
TEST(SwitchSectionTestSuite, DayToSecondTest) {
	MODE md;
	md.TS_year = 0;
	md.TS_month = 0;
	md.TS_day = 1;
	md.TS_hour = 0;
	md.TS_minute = 0;
	md.TS_second = 0;
	SwitchSection(&md);
	EXPECT_EQ(md.TS_year, 0);
	EXPECT_EQ(md.TS_month, 0);
	EXPECT_EQ(md.TS_day, 0);
	EXPECT_EQ(md.TS_hour, 0);
	EXPECT_EQ(md.TS_minute, 0);
	EXPECT_EQ(md.TS_second, 1);
}

//201913552 황신이
//2.1.9
TEST(RecordLapTimeTestSuite, RecordLapTimeTest) {
	STOPWATCH sw;
	MODE md;
	sw.minute = 33;
	sw.second = 22;
	sw.C_second = 11;
	md.LAP_ON = 0;
	RecordLapTime(&sw, &md);
	EXPECT_EQ(md.LAP_ON, 1);
	EXPECT_EQ(sw.Lap_min, 33);
	EXPECT_EQ(sw.Lap_se, 22);
	EXPECT_EQ(sw.Lap_Cse, 11);
}

//201913552 황신이
//2.1.10
TEST(StopwatchResetTestSuite, StopwatchResetTest) {
	STOPWATCH sw;
	sw.minute = 33;
	sw.second = 22;
	sw.C_second = 11;
	StopwatchReset(&sw);
	EXPECT_EQ(sw.minute, 0);
	EXPECT_EQ(sw.second, 0);
	EXPECT_EQ(sw.C_second, 0);
}

//201913552 황신이
//2.1.11
TEST(LapTimeResetTestSuite, LapTimeResetTest) {
	STOPWATCH sw;
	MODE md;
	sw.minute = 33;
	sw.second = 22;
	sw.C_second = 11;
	md.LAP_ON = 1;
	LapTimeReset(&sw, &md);
	EXPECT_EQ(md.LAP_ON, 0);
	EXPECT_EQ(sw.Lap_min, 0);
	EXPECT_EQ(sw.Lap_se, 0);
	EXPECT_EQ(sw.Lap_Cse, 0);
}

//201913552 황신이
//2.1.14
TEST(SwitchSectionAlarmTestSuite, HourToMinuteTest) {
	MODE md;
	md.AL_month = 0;
	md.AL_day = 0;
	md.AL_hour = 1;
	md.AL_minute = 0;
	SwitchSectionAlarm(&md);
	EXPECT_EQ(md.AL_month, 0);
	EXPECT_EQ(md.AL_day, 0);
	EXPECT_EQ(md.AL_hour, 0);
	EXPECT_EQ(md.AL_minute, 1);
}
TEST(SwitchSectionAlarmTestSuite, MinuteToMonthTest) {
	MODE md;
	md.AL_month = 0;
	md.AL_day = 0;
	md.AL_hour = 0;
	md.AL_minute = 1;
	SwitchSectionAlarm(&md);
	EXPECT_EQ(md.AL_month, 1);
	EXPECT_EQ(md.AL_day, 0);
	EXPECT_EQ(md.AL_hour, 0);
	EXPECT_EQ(md.AL_minute, 0);
}
TEST(SwitchSectionAlarmTestSuite, MonthToDayTest) {
	MODE md;
	md.AL_month = 1;
	md.AL_day = 0;
	md.AL_hour = 0;
	md.AL_minute = 0;
	SwitchSectionAlarm(&md);
	EXPECT_EQ(md.AL_month, 0);
	EXPECT_EQ(md.AL_day, 1);
	EXPECT_EQ(md.AL_hour, 0);
	EXPECT_EQ(md.AL_minute, 0);
}
TEST(SwitchSectionAlarmTestSuite, DayToHourTest) {
	MODE md;
	md.AL_month = 0;
	md.AL_day = 1;
	md.AL_hour = 0;
	md.AL_minute = 0;
	SwitchSectionAlarm(&md);
	EXPECT_EQ(md.AL_month, 0);
	EXPECT_EQ(md.AL_day, 0);
	EXPECT_EQ(md.AL_hour, 1);
	EXPECT_EQ(md.AL_minute, 0);
}

//201913552 황신이
//2.1.16
TEST(AlarmIndicatorTestSuite, AlarmIndicatorTest1) {
	MODE md;
	md.ALARM_INDI_ON = 0;
	AlarmIndicator(&md);
	EXPECT_EQ(md.ALARM_INDI_ON, 1);
}
TEST(AlarmIndicatorTestSuite, AlarmIndicatorTest2) {
	MODE md;
	md.ALARM_INDI_ON = 1;
	AlarmIndicator(&md);
	EXPECT_EQ(md.ALARM_INDI_ON, 0);
}

//201913552 황신이
//2.3.1
TEST(LightControlTestSuite, LightControlTest1) { //light off, button 4
	int button;
	MODE md; 
	ALARM r;
	button = 4;
	md.LIGHT_STATE = 0;
	r.CHECK_ALARM = 0;
	LightControl(button, &md, &r);
	EXPECT_EQ(md.LIGHT_STATE, 1);
}
TEST(LightControlTestSuite, LightControlTest2) { //light on, button 4
	int button;
	MODE md;
	ALARM r;
	button = 4;
	md.LIGHT_STATE = 1;
	r.CHECK_ALARM = 0;
	LightControl(button, &md, &r);
	EXPECT_EQ(md.LIGHT_STATE, 1);
}
TEST(LightControlTestSuite, LightControlTest3) { //light on, not button 4
	int button;
	MODE md;
	ALARM r;
	button = 0;
	md.LIGHT_STATE = 1;
	r.CHECK_ALARM = 0;
	for (int i = 0; i < 200; i++) {		//simulate 200 ticks
		LightControl(button, &md, &r);
		EXPECT_EQ(md.LIGHT_STATE, 1);	//when less than 200 ticks
	}
	LightControl(button, &md, &r);
	EXPECT_EQ(md.LIGHT_STATE, 0);		//when equal or more than 200 ticks
}

//201913552 황신이
//2.5.2
TEST(CheckAlarmTestSuite, CheckAlarmTest1) {
	ALARM r;
	MODE m;
	TIME t;
	r.CHECK_ALARM = 0;
	m.M_TS = 0;
	m.M_ALS = 0;
	t.second = 0;
	t.centisecond = 0;
	m.ALARM_INDI_ON = 1;

	r.month = 0;
	r.day = 11;
	r.hour = 22;
	r.minute = 33;

	t.month = 1;
	t.day = 11;
	t.hour = 22;
	t.minute = 33;

	CheckAlarm(&r, &m, &t);
	EXPECT_EQ(r.CHECK_ALARM, 1);
}
TEST(CheckAlarmTestSuite, CheckAlarmTest2) {
	ALARM r;
	MODE m;
	TIME t;
	r.CHECK_ALARM = 0;
	m.M_TS = 0;
	m.M_ALS = 0;
	t.second = 0;
	t.centisecond = 0;
	m.ALARM_INDI_ON = 1;

	r.month = 1;
	r.day = 0;
	r.hour = 22;
	r.minute = 33;

	t.month = 1;
	t.day = 11;
	t.hour = 22;
	t.minute = 33;

	CheckAlarm(&r, &m, &t);
	EXPECT_EQ(r.CHECK_ALARM, 1);
}
TEST(CheckAlarmTestSuite, CheckAlarmTest3) {
	ALARM r;
	MODE m;
	TIME t;
	r.CHECK_ALARM = 0;
	m.M_TS = 0;
	m.M_ALS = 0;
	t.second = 0;
	t.centisecond = 0;
	m.ALARM_INDI_ON = 1;

	r.month = 1;
	r.day = 11;
	r.hour = 22;
	r.minute = 33;

	t.month = 1;
	t.day = 11;
	t.hour = 22;
	t.minute = 33;

	CheckAlarm(&r, &m, &t);
	EXPECT_EQ(r.CHECK_ALARM, 1);
}
TEST(CheckAlarmTestSuite, CheckAlarmTest4) {
	ALARM r;
	MODE m;
	TIME t;
	r.CHECK_ALARM = 0;
	m.M_TS = 0;
	m.M_ALS = 0;
	t.second = 0;
	t.centisecond = 0;
	m.ALARM_INDI_ON = 1;

	r.month = 1;
	r.day = 12;
	r.hour = 22;
	r.minute = 33;

	t.month = 1;
	t.day = 12;
	t.hour = 22;
	t.minute = 33;

	CheckAlarm(&r, &m, &t);
	EXPECT_EQ(r.CHECK_ALARM, 1);
}

//201913552 황신이
//2.1.6
TEST(IncreaseValueTestSuite, IncreaseYearTest) {
	MODE m;
	TIME t;

	m.TS_year = 1;
	m.TS_month = 0;
	m.TS_day = 0;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2098;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.year, 2099);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.year, 2012);
}
TEST(IncreaseValueTestSuite, IncreaseMonthTest) {
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 1;
	m.TS_day = 0;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.month = 11;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.month, 12);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.month, 1);
}
TEST(IncreaseValueTestSuite, IncreaseWDayTest) { //요일
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 1;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2021;
	t.month = 12;
	t.day = 10;
	t.wday = 5;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.wday, 6);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.wday, 0);
}
TEST(IncreaseValueTestSuite, IncreaseDayTest1) { //평년1
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 1;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2021;
	t.month = 2;
	t.day = 27;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 28);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 1);
}
TEST(IncreaseValueTestSuite, IncreaseDayTest2) { //평년2
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 1;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2021;
	t.month = 3;
	t.day = 30;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 31);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 1);
}
TEST(IncreaseValueTestSuite, IncreaseDayTest3) { //평년3
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 1;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2021;
	t.month = 4;
	t.day = 29;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 30);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 1);
}
TEST(IncreaseValueTestSuite, IncreaseDayTest4) { //윤년
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 1;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.year = 2020;
	t.month = 2;
	t.day = 28;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 29);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.day, 1);
}
TEST(IncreaseValueTestSuite, IncreaseHourTest) {
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 0;
	m.TS_hour = 1;
	m.TS_minute = 0;
	m.TS_second = 0;

	t.hour = 22;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.hour, 23);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.hour, 0);
}
TEST(IncreaseValueTestSuite, IncreaseMinuteTest) {
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 0;
	m.TS_hour = 0;
	m.TS_minute = 1;
	m.TS_second = 0;

	t.minute = 58;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.minute, 59);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.minute, 0);
}
TEST(IncreaseValueTestSuite, IncreaseSecondTest) {
	MODE m;
	TIME t;

	m.TS_year = 0;
	m.TS_month = 0;
	m.TS_day = 0;
	m.TS_hour = 0;
	m.TS_minute = 0;
	m.TS_second = 1;

	t.second = 58;

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.second, 59);

	IncreaseValue(&m, &t);
	EXPECT_EQ(t.second, 0);
}

