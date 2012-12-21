//Servo motor PWM Programming For PIC 18f4431.

#include<htc.h>

unsigned char deg2=10;

void Load_Base();

void Load_Elbow();

void s_switch_M_Wrist();

void delay(unsigned int);
unsigned int deg_base = 31;
unsigned int deg_elbow = 31;

unsigned const char reg_ccp[64] = { 0x04, 0x04, 0x04, 0x04,
									0x05, 0x05, 0x05, 0x05,
									0x06, 0x06, 0x06, 0x06,
									0x07, 0x07, 0x07, 0x07,
									0x08, 0x08, 0x08, 0x08,
									0x09, 0x09, 0x09, 0x09,
									0x0A, 0x0A, 0x0A, 0x0A,
									0x0B, 0x0B, 0x0B, 0x0B,
									0x0C, 0x0C, 0x0C, 0x0C,
									0x0D, 0x0D, 0x0D, 0x0D,
									0x0E, 0x0E, 0x0E, 0x0E,
									0x0F, 0x0F, 0x0F, 0x0F,
									0x10, 0x10, 0x10, 0x10,
									0x11, 0x11, 0x11, 0x11,
									0x12, 0x12, 0x12, 0x12,
									0x13, 0x13, 0x13, 0x13 };
										
unsigned const char reg_con[4] = { 0x0C, 0x1C, 0x2C, 0x3C };
void main()
{
        
	TRISB=0X00;		
	TRISC=0x00;		// Configuring as Output Port for RC2 17th Pin.
	TRISD=0xff;
	OSCCON=0X3E;  		// Selecting Internal Oscillator of 500KHZ.
	PR2=0x9B;		// Pr2 Value 155 for Pulse width Period and Pulse width duty Cycle.
	T2CON=0x06;		// Loading Timer2 Control Register with 0x06.


//-----------------------WristPWM-----------------------------
	PWMCON0	=0x2f;
	PTCON0	=0x00;
	PTPERL	=0xc4;
	PTPERH	=0x09;
	PTMRL	=0xc4;
	PTMRH	=0x09;
//-------------------------------Default Position Value---------------------------

	PTCON1	=0x80;

	Load_Base();
	Load_Elbow();
	s_switch_M_Wrist();


	while(1)
		{

		//------------Base---------------
			if((RD7==1)&&(deg_base<63))
				{
					deg_base++;
					Load_Base();
					delay(500);
				}
			else if((RD6==1)&&(deg_base>0))
				{   
					deg_base--;
					Load_Base();
					delay(500);
				}
		//------------Elbow---------------

			else if((RD5==1)&&(deg_elbow<63))
				{   
					deg_elbow++;
					Load_Elbow();
					delay(350);
				}
			else if((RD4==1)&&(deg_elbow>0))
				{   
					deg_elbow--;
					Load_Elbow();
					delay(350);
				}
		//------------Wrist----------------
			else if((RD3==1)&&(deg2<64))
				{   
					deg2++;
					s_switch_M_Wrist();
					delay(350);
				}
			else if((RD2==1)&&(deg2>0))
				{   
					deg2--;
					s_switch_M_Wrist();
					delay(350);
				}
			
		}

}


//-----------------------**Delay**-----------------------					



void delay(unsigned int count)
{
		unsigned int i;
		for(i=0;i<count;i++);
}					 

void Load_Base()
{
	unsigned char i;
	CCPR1L = reg_ccp[deg_base];
	i = deg_base & 0x0003;
	CCP1CON = reg_con[i];
}
void Load_Elbow()
{
	unsigned char i;
	CCPR2L = reg_ccp[deg_elbow];
	i = deg_elbow & 0x0003;
	CCP2CON = reg_con[i];
}




//-----------------------**Switch MOTOR_Wrist**----------------------

void s_switch_M_Wrist()
{
	switch(deg2)
	{
	case 1:
		PDC0L	=0x00;
		PDC0H	=0x01;
	break;
	case 2:
		PDC0L	=0x10;
		PDC0H	=0x01;
	break;
	case 3:
		PDC0L	=0x20;
		PDC0H	=0x01;
	break;
	case 4:
		PDC0L	=0x30;
		PDC0H	=0x01;
	break;
	case 5:
		PDC0L	=0x40;
		PDC0H	=0x01;
	break;
	case 6:
		PDC0L	=0x50;
		PDC0H	=0x01;
	break;
	case 7:
		PDC0L	=0x60;
		PDC0H	=0x01;
	break;
	case 8:
		PDC0L	=0x70;
		PDC0H	=0x01;
	break;
	case 9:
		PDC0L	=0x80;
		PDC0H	=0x01;
	break;
	case 10:
		PDC0L	=0x90;
		PDC0H	=0x01;
	break;
	case 11:
		PDC0L	=0xA0;
		PDC0H	=0x01;
	break;
	case 12:
		PDC0L	=0xB0;
		PDC0H	=0x01;
	break;
	case 13:
		PDC0L	=0xC0;
		PDC0H	=0x01;
	break;
	case 14:
		PDC0L	=0xD0;
		PDC0H	=0x01;
	break;
	case 15:
		PDC0L	=0xE0;
		PDC0H	=0x01;
	break;
	case 16:
		PDC0L	=0xF0;
		PDC0H	=0x01;
	break;
	case 17:
		PDC0L	=0x00;
		PDC0H	=0x02;
	break;
	case 18:
		PDC0L	=0x10;
		PDC0H	=0x02;
	break;
	case 19:
		PDC0L	=0x20;
		PDC0H	=0x02;
	break;
	case 20:
		PDC0L	=0x30;
		PDC0H	=0x02;;
	break;
	case 21:
		PDC0L	=0x40;
		PDC0H	=0x02;
	break;
	case 22:
		PDC0L	=0x50;
		PDC0H	=0x02;;
	break;
	case 23:
		PDC0L	=0x60;
		PDC0H	=0x02;;
	break;
	case 24:
		PDC0L	=0x70;
		PDC0H	=0x02;;
	break;
	case 25:
		PDC0L	=0x80;
		PDC0H	=0x02;;
	break;
	case 26:
		PDC0L	=0x90;
		PDC0H	=0x02;;
	break;
	case 27:
		PDC0L	=0xA0;
		PDC0H	=0x02;;
	break;
	case 28:
		PDC0L	=0xB0;
		PDC0H	=0x02;;
	break;
	case 29:
		PDC0L	=0xC0;
		PDC0H	=0x02;;
	break;
	case 30:
		PDC0L	=0xD0;
		PDC0H	=0x02;;
	break;
	case 31:
		PDC0L	=0xE0;
		PDC0H	=0x02;;
	break;
	case 32:
		PDC0L	=0xF0;
		PDC0H	=0x02;;
	break;
	case 33:
		PDC0L	=0x00;
		PDC0H	=0x03;;
	break;
	case 34:
		PDC0L	=0x10;
		PDC0H	=0x03;;
	break;
	case 35:
		PDC0L	=0x20;
		PDC0H	=0x03;;
	break;
	case 36:
		PDC0L	=0x30;
		PDC0H	=0x03;;
	break;
	case 37:
		PDC0L	=0x40;
		PDC0H	=0x03;;
	break;
	case 38:
		PDC0L	=0x50;
		PDC0H	=0x03;;
	break;
	case 39:
		PDC0L	=0x60;
		PDC0H	=0x03;;
	break;
	case 40:
		PDC0L	=0x70;
		PDC0H	=0x03;;
	break;
	case 41:
		PDC0L	=0x80;
		PDC0H	=0x03;;
	break;
	case 42:
		PDC0L	=0x90;
		PDC0H	=0x03;;
	break;
	case 43:
		PDC0L	=0xA0;
		PDC0H	=0x03;;
	break;
	case 44:
		PDC0L	=0xB0;
		PDC0H	=0x03;;
	break;
	case 45:
		PDC0L	=0xC0;
		PDC0H	=0x03;;
	break;
	case 46:
		PDC0L	=0xD0;
		PDC0H	=0x03;;
	break;
	case 47:
		PDC0L	=0xE0;
		PDC0H	=0x03;;
	break;
	case 48:
		PDC0L	=0xF0;
		PDC0H	=0x03;;
	break;
	case 49:
		PDC0L	=0x00;
		PDC0H	=0x04;;
	break;
	case 50:
		PDC0L	=0x10;
		PDC0H	=0x04;;
	break;
	case 51:
		PDC0L	=0x20;
		PDC0H	=0x04;;
	break;
	case 52:
		PDC0L	=0x30;
		PDC0H	=0x04;;
	break;
	case 53:
		PDC0L	=0x40;
		PDC0H	=0x04;;
	break;
	case 54:
		PDC0L	=0x50;
		PDC0H	=0x04;;
	break;
	case 55:
		PDC0L	=0x60;
		PDC0H	=0x04;;
	break;
	case 56:
		PDC0L	=0x70;
		PDC0H	=0x04;;
	break;
	case 57:
		PDC0L	=0x80;
		PDC0H	=0x04;;
	break;
	case 58:
		PDC0L	=0x90;
		PDC0H	=0x04;;
	break;
	case 59:
		PDC0L	=0xA0;
		PDC0H	=0x04;;
	break;
	case 60:
		PDC0L	=0xB0;
		PDC0H	=0x04;;
	break;
	case 61:
		PDC0L	=0xC0;
		PDC0H	=0x04;;
	break;
	case 62:
		PDC0L	=0xD0;
		PDC0H	=0x04;;
	break;
	case 63:
		PDC0L	=0xE0;
		PDC0H	=0x04;;
	break;
	case 64:
		PDC0L	=0xF0;
		PDC0H	=0x04;;
	break;
	}
}
					
	

