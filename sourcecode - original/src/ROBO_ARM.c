//Servo motor PWM Programming For PIC 18f4431.

#include<htc.h>

void Load_Servo();
void Load_Base();
void Load_Elbow();
void Load_Wrist();
void Load_R_Grip();
void Load_Grip();

void Automatic();
//void Manual();
/* 	A manual mode of operation can be implemented such that the controller 
	generates interrupts or polls the key press on a keypad and corresponding
	joint servo angles can be increamented or decremented 
*/

void Load_Default();

void Pick(unsigned char d_servo, unsigned char d_base, unsigned char d_elbow, 
	unsigned char d_wrist, unsigned char d_r_grip, unsigned char d_grip);
	
void Place(unsigned char d_servo, unsigned char d_base, unsigned char d_elbow, 
	unsigned char d_wrist, unsigned char d_r_grip, unsigned char d_grip);
	
void delay(unsigned int);

unsigned char deg_servo = 31;
unsigned char deg_base  = 20;
unsigned char deg_elbow = 10;
unsigned char deg_wrist = 31;
unsigned char deg_r_grip = 31;
unsigned char deg_grip = 31;

unsigned const char reg_CON[4] = { 0x0C, 0x1C, 0x2C, 0x3C };

unsigned const char reg_CCP[64] = { 0x04, 0x04, 0x04, 0x04,
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
                                    
unsigned const char reg_PDCH[4] = { 0x01, 0x02, 0x03, 0x04 };

unsigned const char reg_PDCL[16] = { 0x00, 0x10, 0x20, 0x30,
                                     0x40, 0x50, 0x60, 0x70, 
                                     0x80, 0x90, 0xA0, 0xB0, 
                                     0xC0, 0xD0, 0xE0, 0xF0 };

void main()
{
	ANSEL0	= 0x00;		// Configures port pins as digital I/O
	ANSEL1  = 0x00; 	// Configures port pins as digital I/O
    TRISA   = 0x8C; 	// Configures the pins on port A as either In/Out 
    TRISB	= 0XC0; 	// Configures the pins on port B as either In/Out 
    TRISC	= 0xF9; 	// Configures the pins on port C as either In/Out 
    TRISD	= 0x3F; 	// Configures the pins on port D as either In/Out 
    TRISE	= 0x04; 	// Configures the pins on port E as either In/Out 
    OSCCON	= 0X3E; 	// Setting Internal Oscillator to run at 500KHZ.
 
//-----------------------CCP module registers----------------------------- 
    PR2		= 0x9B;        // Loads value 155 for gentrating time period of 20mSecs.
    T2CON	= 0x06;        // Configure Timer 2.

//-----------------------PWM control Module Registers --------------------
    PWMCON0	= 0xDF;
    PTCON0	= 0x00;
    PTPERL	= 0xC4;
    PTPERH	= 0x09;
    PTMRL	= 0xC4;
    PTMRH	= 0x09;
    PTCON1	= 0x80;
	PORTA   = 0xFF;
	
	delay(1000);
	// Loads the default angles for each servo
	Load_Default();

		// Starts the automatic routine for pre programmed positions
		Automatic();

	while(1);	//Stops controller execution
}

//---------------- Delay function ------------------//

void delay(unsigned int count)
{
	unsigned int i;
	for(i=0;i<count;i++);
}                     

//---------------- Loads the rotating base servo ----------------//
void Load_Servo()
{
    CCPR1L = reg_CCP[deg_servo];
    CCP1CON = reg_CON[deg_servo & 0x03];
}

//---------------- Loads the shoulder joint servos ----------------//
void Load_Base()
{
    CCPR2L = reg_CCP[deg_base];
    CCP2CON = reg_CON[deg_base & 0x03];
}

//---------------- Loads the elbow joint servo ----------------//
void Load_Elbow()
{
    PDC0H = reg_PDCH[deg_elbow >> 4];
    PDC0L = reg_PDCL[deg_elbow & 0x0F];
}

//---------------- Loads the wrist joint servo ----------------//
void Load_Wrist()
{
    PDC1H = reg_PDCH[deg_wrist >> 4];
    PDC1L = reg_PDCL[deg_wrist & 0x0F];
}

//---------------- Loads the rotating grip joint servo ----------------//
void Load_R_Grip()
{
    PDC2H = reg_PDCH[deg_r_grip >> 4];
    PDC2L = reg_PDCL[deg_r_grip & 0x0F];
}

//---------------- Loads the gripper servo ----------------//
void Load_Grip()
{
    PDC3H = reg_PDCH[deg_grip >> 4];
    PDC3L = reg_PDCL[deg_grip & 0x0F];
}

//---------------- Loads the default values to each join ----------------//
void Load_Default()
{
	while(deg_base != 15)
	{
		if( deg_base < 15)
		{
			deg_base++;
			Load_Base();
			delay(500);
		}
		else
		{
			deg_base--;
			Load_Base();
			delay(500);
		}
	}
	Load_Base();
	while(deg_elbow != 5)
	{
		if( deg_elbow < 5)
		{
			deg_elbow++;
			Load_Elbow();
			delay(300);
		}
		else
		{
			deg_elbow--;
			Load_Elbow();
			delay(300);
		}
	}
	Load_Elbow();
	delay(1000);
	while(deg_servo != 31)
	{
		if( deg_servo < 31 )
		{
			deg_servo++;
			Load_Servo();
			delay(300);
		}
		else
		{
			deg_servo--;
			Load_Servo();
			delay(300);
		}
	}
	Load_Servo();
	while(deg_wrist != 10)
	{
		if( deg_wrist < 10)
		{
			deg_wrist++;
			Load_Wrist();
			delay(300);
		}
		else
		{
			deg_wrist--;
			Load_Wrist();
			delay(300);
		}
	}
	Load_Wrist();
	while(deg_r_grip != 31)
	{
		if( deg_r_grip < 31)
		{
			deg_r_grip++;
			Load_R_Grip();
			delay(300);
		}
		else
		{
			deg_r_grip--;
			Load_R_Grip();
			delay(300);
		}
	}    
	Load_R_Grip();
	
}

void Automatic()
{
	Load_Default();
	// Picks the object from the starting co-ordinates
	Pick(15, 37, 7, 20, 0, 30);
	// Arm moves back to the default position with the object
	Load_Default();
	// Places the object in the end co-ordinates
	Place(63, 37, 7, 20, 31, 55);
	// Arm moves back to the default position 
	Load_Default();
	// Picks another object from the second location co-ordinates
	Pick(47, 37, 7, 20, 0, 30);
	// Arm moves back to the default position with the object
	Load_Default();
	// Places the object in the end co-ordinates
	Place(0, 37, 7, 20, 63, 55);
	// Arm moves back to the default position 
	Load_Default();
	
}

/*  Navigates the joint in a proper order to go to the specified 
	picking point co-ordinates */
	
void Pick(unsigned char d_servo, unsigned char d_base, unsigned char d_elbow, 
	unsigned char d_wrist, unsigned char d_r_grip, unsigned char d_grip)
{
	while(deg_servo != d_servo)
	{
		if( deg_servo < d_servo )
		{
			deg_servo++;
			Load_Servo();
			delay(300);
		}
		else
		{
			deg_servo--;
			Load_Servo();
			delay(300);
		}
	}
	Load_Servo();
	delay(1000);
	while(deg_elbow != d_elbow)
	{
		if( deg_elbow < d_elbow )
		{
			deg_elbow++;
			Load_Elbow();
			delay(300);
		}
		else
		{
			deg_elbow--;
			Load_Elbow();
			delay(300);
		}
	}
	Load_Elbow();
	while(deg_base != d_base)
	{
		if( deg_base < d_base )
		{
			deg_base++;
			Load_Base();
			delay(500);
		}
		else
		{
			deg_base--;
			Load_Base();
			delay(500);
		}
	}
	Load_Servo();
	while(deg_wrist != d_wrist)
	{
		if( deg_wrist < d_wrist )
		{
			deg_wrist++;
			Load_Wrist();
			delay(300);
		}
		else
		{
			deg_wrist--;
			Load_Wrist();
			delay(300);
		}
	}
	Load_Wrist();    
	while(deg_r_grip != d_r_grip)
	{
		if( deg_r_grip < d_r_grip )
		{
			deg_r_grip++;
			Load_R_Grip();
			delay(100);
		}
		else
		{
			deg_r_grip--;
			Load_R_Grip();
			delay(100);
		}
	}
	Load_R_Grip();
	delay(5000);
	while(deg_grip != d_grip)
	{
		if( deg_grip < d_grip )
		{
			deg_grip++;
			Load_Grip();
			delay(100);
		}
		else
		{
			deg_grip--;
			Load_Grip();
			delay(100);
		}
	}
	Load_Grip();	
}

/*  Navigates the joint in a proper order to go to the specified 
	placing point co-ordinates */
	
void Place(unsigned char d_servo, unsigned char d_base, unsigned char d_elbow, 
	unsigned char d_wrist, unsigned char d_r_grip, unsigned char d_grip)
{
	while(deg_servo != d_servo)
	{
		if( deg_servo < d_servo )
		{
			deg_servo++;
			Load_Servo();
			delay(300);
		}
		else
		{
			deg_servo--;
			Load_Servo();
			delay(300);
		}
	}
	Load_Servo();
	while(deg_elbow != d_elbow)
	{
		if( deg_elbow < d_elbow )
		{
			deg_elbow++;
			Load_Elbow();
			delay(300);
		}
		else
		{
			deg_elbow--;
			Load_Elbow();
			delay(300);
		}
	}
	Load_Elbow();
	delay(1000);
	while(deg_base != d_base)
	{
		if( deg_base < d_base )
		{
			deg_base++;
			Load_Base();
			delay(500);
		}
		else
		{
			deg_base--;
			Load_Base();
			delay(500);
		}
	}
	Load_Base();
	while(deg_wrist != d_wrist)
	{
		if( deg_wrist < d_wrist )
		{
			deg_wrist++;
			Load_Wrist();
			delay(300);
		}
		else
		{
			deg_wrist--;
			Load_Wrist();
			delay(300);
		}
	}
	Load_Wrist();   
	while(deg_r_grip != d_r_grip)
	{
		if( deg_r_grip < d_r_grip )
		{
			deg_r_grip++;
			Load_R_Grip();
			delay(100);
		}
		else
		{
			deg_r_grip--;
			Load_R_Grip();
			delay(100);
		}
	}
	Load_R_Grip();
	delay(5000);
	while(deg_grip != d_grip)
	{
		if( deg_grip < d_grip )
		{
			deg_grip++;
			Load_Grip();
			delay(100);
		}
		else
		{
			deg_grip--;
			Load_Grip();
			delay(100);
		}
	}
	Load_Grip();	
}
