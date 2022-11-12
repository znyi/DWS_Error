#include "Functions.h"
enum AL_state { AL_OFF = 0, AL_ON};

void CheckAlarm(ALARM *r, MODE *m, TIME *t) {
	if(m->M_TS == 0 && m->M_ALS == 0 && t->second == 0 && t->centisecond == 0 && m->ALARM_INDI_ON == 1){  //time setting or alarm setting is not ¿ï¸®´Ù
		if(r->month == 0 && r->day != 0) {
			if(t->day == r->day && t->hour == r->hour && t->minute == r->minute){
				r->CHECK_ALARM = 1;
			}
		}
		else if(r->month != 0 && r->day == 0) {
			if(t->month == r->month && t->hour == r->hour && t->minute == r->minute) {
				r->CHECK_ALARM = 1;
			}
		}
		else if(t->month == r->month && t->day == r->day) {
			if(t->hour == r->hour && t->minute == r->minute){
				r->CHECK_ALARM = 1; 
			}
		}
		else if (r->month != 0 && r->day != 0) {// solved missing condition
			if (t->month == r->month && t->day == r->day && t->hour == r->hour && t->minute == r->minute) {
				r->CHECK_ALARM = 1;
			}
		}//
	}
}

void AlarmOff(ALARM *r){
	r->CHECK_ALARM = 0;
}

void Bell()
{
	static int cnt = 0;
	if(cnt == 40) {
		printf("\a");
		cnt = 0;
	}
	cnt++;
}

void AlarmControl (ALARM *r,MODE *m, TIME *t, int buttoninfo1, int buttoninfo2) {

	static enum AL_state al_state = AL_OFF;
	static int BEEP = DISABLE;

	CheckAlarm(r,m,t);

	if(BEEP) Bell();

	switch(al_state) {
	case  AL_OFF :
		if(r->CHECK_ALARM == 1) {
			BEEP = ENABLE;
			al_state = AL_ON;
		}
		break;
	case AL_ON:
		if((t->second >= 5) || (buttoninfo1 != 0 || buttoninfo2 != 0)){
				AlarmOff(r);
				BEEP = DISABLE;
				al_state = AL_OFF;
		}
		break;
	}
}
