/*LightControl.c*/

#include "Functions.h"

enum l_state
{
	LIGHT_OFF,	//Backlight²¨Áü
	LIGHT_ON	//BacklightÄÑÁü
};

void TurnOnTheLight(MODE* md)	//Backlight On
{
	md->LIGHT_STATE = 1;
}
void TurnOffTheLight(MODE* md)	//Backlight Off
{
	md->LIGHT_STATE = 0;
}

void LightControl(int button_info, MODE* md, ALARM* r)
{
	static enum l_state state = LIGHT_OFF;
	static int two_second;

	switch (state)
	{
	case LIGHT_OFF:
		if (button_info == 4 && r->CHECK_ALARM == 0)
		{
			two_second = 0;
			TurnOnTheLight(md);
			state = LIGHT_ON;
		}
		break;
	case LIGHT_ON:
		if (button_info == 4 && r->CHECK_ALARM == 0)
		{
			two_second = 0;
		}
		else if (!(button_info == 4) && (two_second < 200))
		{
			two_second++;
		} 
		else if (!(button_info == 4) && (two_second >= 200)) { //
			TurnOffTheLight(md); //solved light not turned off after 2 seconds
			state = LIGHT_OFF;
		}//
		break;
	}

	if (md->LIGHT_STATE == 1)
	{
		SetColor(14, 0);
	}
	else if (md->LIGHT_STATE == 0)
	{
		SetColor(7, 0);
	}
	//SetColor()·Î Light Interface.
}
