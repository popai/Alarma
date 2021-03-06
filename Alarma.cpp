// Do not remove the include below
#include "Alarma.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

/* project interface include file. */
#include "pinDef.h"
#include "user_input.h"
#include "password_manager.h"

#define	DEBUG	1

#include "lib/keypad/keypad.h"
#include "lib/eeprom/eeprom.h"
#include "lib/timer/timer.h"
//#include "lib/usart/usart.h"
#include "lib/sound/sound.h"

#ifdef portHD44780_LCD
/* LCD (Freetronics 16x2) interface include file. */
#include "hd44780.h"
#endif

/*-----------------------------------------------------------*/

// Declare Buzezer variables...
volatile uint8_t buzzerFinished; // flag: 0 whilst playing
const int8_t *buzzerSequence;
//uint8_t buzzerInitialized;

/*Alarm variables*/
static uint16_t pass_save = 254;
static uint16_t password = 255;
static int8_t taskAlarm = 0;
static uint8_t martor = 0;
unsigned long tmr_millis = 0; //, time for delay action ;
unsigned long curet_milles = 0;
extern uint8_t armat;
extern uint8_t alarm;

static void TasKeypad(); // keibord imput
static void TaskSenzorL(); // senzor intarziat
static void TaskSenzorR(); // senzor instant
static void TaskAlarma(); // actiuni alarma
static void TaskSemnale(); // actiuni alarma

static void SystemInit();

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	SystemInit();
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	TasKeypad();

	if (taskAlarm)
		TaskAlarma();

	TaskSenzorR();

	TaskSenzorL();

	TaskSemnale();
	//_delay_ms(10);

}

static void TasKeypad()
{

	_delay_ms(50);
	static uint8_t keyCode = 255;
	static uint8_t i = 0;
	static uint8_t key[] = "####";

	char tmp[] = "################";
	keyCode = GetKeyPressed(); //Get the keycode of pressed key
	if (keyCode == 255)
		return;

	if (keyCode == 11)
	{
		i = 0;
		Serial.println("Anulat!\r");
	}
	else if (i < 4 && (keyCode != 10))
	{
		key[i] = keyCode;
		sprintf(tmp, "key[%i] = %i", i, keyCode);
		Serial.println(tmp);
		++i;
	}

	if (i == 4 && keyCode == 10)
	{

		i = 0;
		password =
				(((1000 * key[0]) + (100 * key[1]) + (10 * key[2]) + key[3])); //save the password in 16 bit integer
#ifdef DEBUG
		tmp[0] = 0;
		sprintf(tmp, "%i", password);
		Serial.println(tmp);
#endif
		//xTaskNotifyGive( xTaskAlarma);
		taskAlarm = 1;
	}

}

/*-----------------------------------------------------------*/
static void TaskAlarma()
{

	static uint8_t gresit = 0;
	static int8_t passOK = 0;
	static int8_t changepas = 0;

	//Match Password
	contor_s = 1;

	if ((password == pass_save) && !changepas)
	{
#ifdef DEBUG
		Serial.println("Parola OK!");
#endif
		gresit = 0;
		taskAlarm = 0;
		Buzer_PassOK();
		//playFrequency( 523, 150); // ok tone
		if (armat || alarm)
		{
			ALARMOff();
			ARMOff();
#ifdef DEBUG
			Serial.println("Dezarmat!");
#endif
			password = 255;
		}
		else
		{
#ifdef DEBUG
			Serial.println("Armeaza!");
#endif
			//while (GetSeconds() - time_sst < 15);
			//vTaskDelayUntil( &xLastWakeTime, ( 15000 / portTICK_PERIOD_MS ) );
			/*
			 while (contor_s < 30) //weit 15s
			 {
			 playFrequency(5230, 100); // ok tone
			 _delay_ms(500);
			 }
			 */
			//playFrequency( 150, 50); // armare tone
			//OSGiveSema(&sema_senzor);
			ALARMOff();
			//wdt_reset();
			ARMOn();
			password = 255;
			tmr_millis = millis();
		}

	}
	else if (password == 0 || changepas)
	{

		//If user enters 0000 as password it
		//indicates a request to change password
		playFrequency(1500, 50); // armare tone

#ifdef DEBUG
		Serial.println("Schimba parola");
#endif

		taskAlarm = 0;
		changepas = 1;
		if (password == pass_save || passOK)
		{
			//Allowed to change password
			//password = 1234;
#ifdef DEBUG
			Serial.println("parola noua:");
#endif
			taskAlarm = 0;
			if (password != 255 && password != 0 && passOK)
			{
				WritePassToEEPROM(password);

				Buzer_PassOK();
				//playFrequency( 523, 150); // ok tone
				pass_save = password;
#ifdef DEBUG
				Serial.println("Parola schimbata");
#endif
				changepas = 0;
				passOK = 0;
				return;
			}
			password = 255;
			passOK = 1;

		}
		else if (password != 0)
		{
			//Not Allowed to change password
			Buzer_PassNotOK();
#ifdef DEBUG
			Serial.println("Parola neschimbata");
#endif

			//playFrequency( 2500, 500); // notOK tone
			taskAlarm = 0;
			changepas = 0;
		}

	}
	else if (password != 255)
	{
		++gresit;
		Buzer_PassNotOK();
		taskAlarm = 0;
		//playFrequency( 2500, 500); // notOK tone
		if ((gresit == 4) && armat)
		{
			//ARMOn();
			ALARMOn();
			Serial.println("Sirena pornita");
			gresit = 0;
			contor_m = 0;
		}
	}
}

/*-----------------------------------------------------------*/
static void TaskSenzorR()
{

	if (armat && !alarm)
	{
		if ((millis() - tmr_millis) > 30 * 1000)
		{
			if ((PIND & (1 << PD4)) || (PIND & (1 << PD5)))
			{
				Serial.println("Senzor rapid activat");
				ALARMOn();
				contor_m = 0;
				//senzor_pull = 1;
				martor = 1;
				Serial.println("Sirena pornita");
			}
		}
		else if ((millis() - curet_milles) > 1000)
		{
			playFrequency(1500, 50);
			curet_milles = millis();
		}
		//playFrequency(5230, 100); // ok tone
	}
	/*
	 else if (!armat && !alarm)
	 {
	 if (PINC & (1 << PC3)) //Buton panica
	 {
	 ALARMOn();
	 contor_m = 0;
	 //senzor_pull = 0;
	 #ifdef DEBUG
	 Serial.println("Sirena pornita BP!");
	 #endif
	 }
	 }
	 //else if ((PINC & (1 << PC3)) == 0)
	 //senzor_pull = 1;

	 /*
	 //opresc sirena dupa 2min
	 if (contor_m == 2 && senzor_pull)
	 {
	 ALARMOff();
	 senzor_pull = 0;
	 Serial.println("Sirena oprita"));
	 }
	 */
#ifdef portHD44780_LCD
	lcd_Locate (0, 0);
	lcd_Printf_P(PSTR("Sys Tick:%7lu"), time(NULL));
	lcd_Locate (1, 0);
	lcd_Printf_P(PSTR("Min Heap:%7u"), xPortGetMinimumEverFreeHeapSize() ); // needs heap_4 for this function to succeed.
#endif // portHD44780_LCD
//		Serial.println("Senzor rapid HighWater @ %u\r\n"), uxTaskGetStackHighWaterMark(NULL));
}

/*-----------------------------------------------------------*/
static void TaskSenzorL()
{
	static int8_t senzorL = 0;
	if (armat && !alarm)
	{
		if ((millis() - tmr_millis) > 30 * 1000)
		{
			if ((SENZOR_PINS & (1 << SENZOR_PIN)) && !senzorL) //(PIND & (1 << PD2)) == 1)
			{
				Serial.println("Senzor intarziat activat");
				contor_s = 1;
				senzorL = 1;

				//playFrequency( 1500, 50); // senzor activ tone
				//while (contor_s < 12)
				//;
				//vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_PERIOD_MS));

			}
		}
	}

	if (senzorL && armat)
	{
		if ((millis() - curet_milles) > 1000)
		{
			playFrequency(1500, 50);
			curet_milles = millis();

		}
		if (contor_s % 20 == 0)
		{
			senzorL = 0;
			if (!alarm)
			{
				ALARMOn();
				contor_m = 0;
				martor = 2;
				Serial.println("Sirena pornita senzorL");
			}
		}
	}
	else senzorL = 0;

#ifdef portHD44780_LCD
	lcd_Locate (0, 0);
	lcd_Printf_P(PSTR("Sys Tick:%7lu"), time(NULL));
	lcd_Locate (1, 0);
	lcd_Printf_P(PSTR("Min Heap:%7u"), xPortGetMinimumEverFreeHeapSize() ); // needs heap_4 for this function to succeed.
#endif // portHD44780_LCD
//		Serial.println("GreenLED HighWater @ %u\r\n"), uxTaskGetStackHighWaterMark(NULL));
}

static void TaskSemnale() // actiouni alarma
{
	//Lipsa tensiune alimentare
	if (((PIND & (1 << PD6)) == 0) && (contor_s % 20 == 15))
	{
		//play(">ARR>ARR>A");
		playFrequency(3000, 180);
		//vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));

	}

	//senzor activat = led armare trece pe intermitent
	if ((martor == 1) && (contor_s % 2 == 1))
		ARMLED_PORT &= ~(1 << ARMLED_PIN);			//sting ledul
	else if ((martor == 2) && (contor_s % 3 == 0))
		ARMLED_PORT &= ~(1 << ARMLED_PIN);			//sting ledul
	if (((martor == 1) || (martor == 2)) && (contor_s % 2 == 0))
		ARMLED_PORT |= (1 << ARMLED_PIN);			//aprind ledul

	if (!armat)
	{
		martor = 0;
		ARMLED_PORT &= ~(1 << ARMLED_PIN);
	}
	//opresc sirena dupa 2min
	if (contor_m == 2 && alarm)
	{
		ALARMOff();
		Serial.println("Sirena oprita");
	}

}

/*-----------------------------------------------------------*/
/**
 * @brief : initialize the parameter of the system
 *
 * @param : no parameters
 * @return: no return
 */
static void SystemInit()
{
	//wdt_disable();
	// turn on the serial port for debugging or for other USART reasons.
	//USARTInit(8); //bud rate 115200
	Serial.begin(115200);
	Serial.println("\r\n\n\nHello World!\r\n"); // Ok, so we're alive...

#ifdef	portHD44780_LCD
	lcd_Init();

	lcd_Print_P(PSTR("Hello World!"));
	lcd_Locate (0, 0);
#endif

	pinSetUp();
	_delay_ms(20);
	Timer1_Init();
	if ((PINC & (1 << PC4)) == 0)
	{
#ifdef DEBUG
		Serial.println("Scriu parola implicita 1234");
#endif
		WritePassToEEPROM(1234);
	}

	ARMLED_PORT &= (~(1 << ARMLED_PIN));
	ALARMOff();
	//if(eeprom_read_byte((uint8_t*)3))
	ARMOn();
	//_delay_ms(50);

	//Check if the EEPROM has a valid password or is blank
	if (ReadPassFromEEPROM() == 25755)
	{
		//Password is blank so store a default password
#ifdef DEBUG
		Serial.println("Scriu parola implicita 1234");
#endif
		WritePassToEEPROM(1234);
	}

	pass_save = ReadPassFromEEPROM();
	//wdt_enable(WDTO_1S);
}

/*-----------------------------------------------------------*/

