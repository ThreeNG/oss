#include "SW.h"

char ch;
int matchtime;
char status;
int recordflag;
extern int timesave;
extern volatile int G_elapsedTime;   // Timer Counter
boolean currstate;
boolean prevstate;
//extern boolean prevsw3;
//boolean fallingedge;
//boolean prevfallingedge;
boolean currstatus;
boolean prevstatus;
//char current;
//char previous;
void delay_10CentiS();
void scrollfunction();
void resetall();


/******************************************************************************
* Function Name: checksw1orsw2
* Description  : check switch 1 switch 2
* Arguments    : none
* Return Value : none
******************************************************************************/
void sw1sw2function()
{	
	if (pollingSW1()){
		timesave = G_elapsedTime;
		while (timesave >= G_elapsedTime - 35 ){
			if (pollingSW2()){
				if (status == 'p') {
					resetall();
				} else {
					status = 'p';
					DisplayLCD(LCD_LINE1,(unsigned char *)"Pausing...");
					delay_10CentiS();
				}
				
			} else {
				if ((status != 'p')||(!recordflag)) {
					scrollfunction();
				} else {
					if (recordflag) {
						scrollfunction();
					} else {
						/* do nothing */
					}	
				}
			}
		}
	}

	if (pollingSW2()){
		timesave = G_elapsedTime;
		while (timesave >= G_elapsedTime - 35){
			if (pollingSW1()){
				if (status == 'p') {
					resetall();
				} else {
					status = 'p';
					DisplayLCD(LCD_LINE1,(unsigned char *)"Pausing...");
					delay_10CentiS();
					
				}
			} else {
				if ((status != 'p')||(!recordflag)) {
					scrollfunction();
				} else {
					if (recordflag) {
						scrollfunction();
					} else {
						/* do nothing */
					}
				}
			}
		}
	}
}


/******************************************************************************
* Function Name: pollingSW1
* Description  : check SW1 is pressed return value only when release button
* Arguments    : none
* Return Value : ON/OFF
******************************************************************************/
boolean pollingSW1(void)
	{	
		ch = P7; 
		
		if (ch & SW1_MASK){
			matchtime = 0;
			return OFF;
		}else {
			matchtime++;
			if (matchtime >=7) {
				matchtime = 0;
				return ON;
			}
		}
	}

/******************************************************************************
* Function Name: pollingSW2
* Description  : check SW2 is pressed return value only when release button
* Arguments    : none
* Return Value : ON/OFF
******************************************************************************/
boolean pollingSW2(void)
	{	
		ch = P7; 
		if(ch & SW2_MASK){
			matchtime = 0;
			return OFF;
		}else {
			matchtime++;
			if (matchtime >=7) {
				matchtime = 0;
				return ON;
			}
		}
	}
/******************************************************************************
* Function Name: pollingSW3
* Description  : check SW3 is pressed return value only when release button
* Arguments    : none
* Return Value : ON/OFF
******************************************************************************/
boolean pollingSW3()
	{	
		ch = P7; 
		//currstate =
		return (!(ch&SW3_MASK));
		/*if ((!currstate)&&(prevstate)) {
			currstatus = ON;
			prevstate = currstate;
		} else {
			currstatus = OFF;
		}
		
		if (currstatus!=prevstatus){
			matchtime = 0;
			prevstatus = currstatus;
			//return OFF;
		}
		else {
			matchtime++;
			if (matchtime >=3) {
				matchtime = 0;
				return ON;
			}
		}*/
	}

