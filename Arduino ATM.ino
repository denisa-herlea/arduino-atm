#include  <Wire.h>
#include <Keypad.h>
#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  

const byte ROWS = 4; 
const byte COLS = 4; 
char password[2][5]= {"1234" ,"5678"};
char lang;
char optiune;
char address1[7]= "123456";
char address2[7]= "654321";
char PIN[4]; 
int balance1 = 10000;
int balance2 = 20000;

const int buzzer = 11;


char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void keybuzz()
{
  tone(buzzer, 5000);
  delay(100);
  noTone(buzzer);
}

void setup()
{
    lcd.init();                      
    lcd.backlight();
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    lcd.print( " Welcome to my Bank! ");
	
    lcd.setCursor(0,0);
	for (int scrollCounter = 0; scrollCounter <20 ; scrollCounter++)
	{
		lcd.scrollDisplayLeft();
		delay(500);   
	}
	
	lcd.clear();
    lcd.setCursor(0, 0);
	lcd.print( "LIMBA/LANGUAGE:");
	delay(1000);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print( "1)Romana");
	lcd.setCursor(0, 1);
	lcd.print( "2)English");
	delay(2000);
	lcd.clear();
	
	char key = customKeypad.waitForKey();

	if (key)
	{
    keybuzz();
		lang = key;
		lcd.setCursor(0,0);
		lcd.print(lang);
		delay(2000);
	}
	
	lcd.setCursor(0, 0);
	if(lang == '1') lcd.print( "Introduceti card");
	else if(lang == '2') lcd.print( "Insert card");
	delay(2000);
	lcd.clear(); 
}

void loop()
{
	lcd.setCursor(0, 0);
	if(lang == '1') lcd.print( "Introduceti PIN:");
	else if(lang == '2') lcd.print( "Insert PIN:");
	lcd.setCursor(0, 1);
	
	int count=0;
	while(count<4)
	{	
		char key = customKeypad.waitForKey();
	
		if (key)
		{
      keybuzz();
			lcd.setCursor (count,1);
			PIN [count]=key;
			lcd.print(PIN [count]);
			count++ ;
			if (count ==4)
			{
				delay (1000);
				lcd.clear();
				delay (1000);
			}
		}
	}
	if ((PIN[0] == password[0][0]||PIN[0] == password[1][0]) &&
		(PIN[1] == password[0][1]||PIN[1] == password[1][1]) && 
		(PIN[2] == password[0][2]||PIN[2] == password[1][2]) &&
		(PIN[3] == password[0][3]||PIN[3] == password[1][3]))
	{
		if(lang == '1') lcd.print( "PIN VALID");
		else if(lang == '2') lcd.print( "VALID PIN CODE");
		delay (2000);
		lcd.clear();      
		lcd.setCursor (0,0);
		
		if(lang == '1') lcd.print( "Alegeti optiunea:");
		else if(lang == '2') lcd.print( "Choose option:");
		delay (2000);
		lcd.clear();     
		
		lcd.setCursor (0,0);
		if(lang == '1') lcd.print( "1)Vedeti sold");
		else if(lang == '2') lcd.print( "1)See balance");
		lcd.setCursor (0,1);
		if(lang == '1') lcd.print( "2)Retragere sold");
		else if(lang == '2') lcd.print( "2)Withdraw money");
		delay (2000);
		lcd.clear();  
		
		lcd.setCursor (0,0);
		if(lang == '1') lcd.print( "3)Depunere sold");
		else if(lang == '2') lcd.print( "3)Deposit money");
		lcd.setCursor (0,1);
		if(lang == '1') lcd.print( "4)Transfer sold");
		else if(lang == '2') lcd.print( "4)Transfer money");
		delay (2000);
		lcd.clear();     
		
		char key = customKeypad.waitForKey();
		if (key)
		{
		    keybuzz();
			optiune = key;
			lcd.setCursor (0,0);
			lcd.print(optiune);
			delay(2000);
			lcd.clear();
		}
		
		if (optiune == '1') 
		{
			lcd.setCursor (0,0);
			if(lang == '1') lcd.print( "Soldul dvs este:");
			else if(lang == '2') lcd.print( "Balance:");
			
			if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
			{
				lcd.setCursor (0,1);
				lcd.print(balance1);
				delay(2000);
				lcd.clear();
			}
		
			if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
			{
				lcd.setCursor (0,1);
				lcd.print(balance2);
				delay(2000);
				lcd.clear();
			}
			
			
		}
	
		if (optiune == '2')
		{
			lcd.setCursor (0,0);
			if(lang == '1') lcd.print( "Alegeti suma:");
			else if(lang == '2') lcd.print( "Choose amount:");
			delay (2000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			lcd.print("1)100$ ");
			lcd.setCursor (8,0);
			lcd.print("2)500$ ");      
			lcd.setCursor (0,1);
			lcd.print("3)1000$ ");
			lcd.setCursor (8,1);
			lcd.print("4)5000$ ");
			delay (4000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			char key = customKeypad.waitForKey();
			if (key)
			{
                keybuzz();        
				lcd.setCursor (0,0);
				lcd.print(key);
				delay(2000);
				lcd.clear();
			}
			
			if(key == '1' || key == '2' || key == '3' || key == '4')
			{
				lcd.setCursor (0,0);
				if(lang == '1') lcd.print( "Va rog asteptati");
				else if(lang == '2') lcd.print( "Please wait!");
				delay(4000);
				lcd.clear();
				
				if(key == '1')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 - 100;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 - 100;
				}
				if(key == '2')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 - 500;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 - 500;
				}
				if(key == '3')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 - 1000;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 - 1000;
				}
				if(key == '4')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 - 5000;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 - 5000;
				}
				
				if(lang == '1')
				{					
					lcd.setCursor (0,0);
					lcd.print( "TRANZACTIE");
					lcd.setCursor (0,1);
					lcd.print( "FINALIZATA");
				}
				else if(lang == '2')
				{					
					lcd.setCursor (0,0);
					lcd.print( "TRANSACTION");
					lcd.setCursor (0,1);
					lcd.print( "COMPLETED");
				}
				delay(3000);
				lcd.clear();
			}
		}
	
		if (optiune == '3')
		{
			lcd.setCursor (0,0);
			if(lang == '1') lcd.print("Alegeti suma:");
			else if(lang == '2') lcd.print("Choose amount:");
			delay (2000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			lcd.print("1)100$ ");
			lcd.setCursor (8,0);
			lcd.print("2)500$ ");      
			lcd.setCursor (0,1);
			lcd.print("3)1000$ ");
			lcd.setCursor (8,1);
			lcd.print("4)5000$ ");
			delay (4000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			char key = customKeypad.waitForKey();
			if (key)
			{
                keybuzz();
				lcd.setCursor (0,0);
				lcd.print(key);
				delay(2000);
				lcd.clear();
			}
			
			if(key == '1' || key == '2' || key == '3' || key == '4')
			{
				lcd.setCursor (0,0);
				if(lang == '1') lcd.print("Introduceti $$$!");
				else if(lang == '2') lcd.print("Insert $$$!");
				delay(5000);
				lcd.clear();
				
				if(key == '1')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 + 100;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 + 100;
				}
				if(key == '2')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 + 500;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 + 500;
				}
				if(key == '3')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 + 1000;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 + 1000;
				}
				if(key == '4')
				{
					if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
						balance1 = balance1 + 5000;
					if (PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
						balance2 = balance2 + 5000;
				}
				if(lang == '1')
				{
					lcd.setCursor (0,0);
					lcd.print("DEPUNERE");
					lcd.setCursor (0,1);
					lcd.print("FINALIZATA");
					delay(3000);
					lcd.clear();
				}
				else if (lang == '2')
				{
					lcd.setCursor (0,0);
					lcd.print("DEPOSIT");
					lcd.setCursor (0,1);
					lcd.print("COMPLETED");
					delay(3000);
					lcd.clear();
				}
			}
		}
	
		if (optiune == '4')
		{
			int ok = 0;
			char adresa[6];
			lcd.setCursor(0,0); 
			if(lang == '1') lcd.print( "Introduceti adresa@ de 6 cifre.");
			else if (lang == '2') lcd.print( "Insert the 6 digit address.");
			for (int scrollCounter = 0; scrollCounter <20 ; scrollCounter++)
			{
				lcd.scrollDisplayLeft();
				delay(500);   
			}
			lcd.clear();
			
			count=0;
			while(count<6)
			{	
				char key = customKeypad.waitForKey();
	
				if (key)
				{
                    keybuzz();
					lcd.setCursor (count,1);
					adresa[count]=key;
					lcd.print(adresa[count]);
					count++ ;
					if (count ==6)
					{
						delay (1000);
						lcd.clear();
						delay (1000);
					}
				}
			}
			
			lcd.setCursor (0,0);
			if(lang == '1') lcd.print("Alegeti suma:");
			else if (lang == '2') lcd.print("Choose amount:");
			delay (2000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			lcd.print("1)100$ ");
			lcd.setCursor (8,0);
			lcd.print("2)500$ ");      
			lcd.setCursor (0,1);
			lcd.print("3)1000$ ");
			lcd.setCursor (8,1);
			lcd.print("4)5000$ ");
			delay (4000);
			lcd.clear();
			
			lcd.setCursor (0,0);
			char key = customKeypad.waitForKey();
			if (key)
			{
                keybuzz();        
				lcd.setCursor (0,0);
				lcd.print(key);
				delay(2000);
				lcd.clear();
			}
			
			if(key == '1' || key == '2' || key == '3' || key == '4')
			{
				if (PIN[0] == '1' && PIN[1] == '2' && PIN[2] == '3' && PIN[3] == '4')
				{
					if (adresa[0] == address1[0] && adresa[1] == address1[1] && adresa[2] == address1[2] && adresa[3] == address1[3] && adresa[4] == address1[4] && adresa[5] == address1[5])
					{	
						lcd.setCursor (0,0);
						if(lang == '1') lcd.print("Adresa invalida!");
						else if (lang == '2') lcd.print("Invalid address!");
						delay (2000);
						lcd.clear();
						ok = 1;
					}
					
					if (adresa[0] == address2[0] && adresa[1] == address2[1] && adresa[2] == address2[2] && adresa[3] == address2[3] && adresa[4] == address2[4] && adresa[5] == address2[5])
					{	
						if(key == '1')
						{
							balance2 = balance2 + 100;
							balance1 = balance1 - 100;
						}
						if(key == '2')
						{
							balance2 = balance2 + 500;
							balance1 = balance1 - 500;
						}
						if(key == '3')
						{
							balance2 = balance2 + 1000;
							balance1 = balance1 - 1000;
						}
						if(key == '4')
						{
							balance2 = balance2 + 5000;
							balance1 = balance1 - 5000;
						}
					}
					
				}	
				
				if(PIN[0] == '5' && PIN[1] == '6' && PIN[2] == '7' && PIN[3] == '8')
				{
					if (adresa[0] == address2[0] && adresa[1] == address2[1] && adresa[2] == address2[2] && adresa[3] == address2[3] && adresa[4] == address2[4] && adresa[5] == address2[5])
					{	
						lcd.setCursor (0,0);
						if(lang == '1') lcd.print("Adresa invalida!");
						else if (lang == '2') lcd.print("Invalid address!");
						delay (2000);
						lcd.clear();
						ok = 1;
					}
					
					if (adresa[0] == address1[0] && adresa[1] == address1[1] && adresa[2] == address1[2] && adresa[3] == address1[3] && adresa[4] == address1[4] && adresa[5] == address1[5])
					{	
						if(key == '1')
						{
							balance1 = balance1 + 100;
							balance2 = balance2 - 100;
						}
						if(key == '2')
						{
							balance1 = balance1 + 500;
							balance2 = balance2 - 500;
						}
						if(key == '3')
						{
							balance1 = balance1 + 1000;
							balance2 = balance2 - 1000;
						}
						if(key == '4')
						{
							balance1 = balance1 + 5000;
							balance2 = balance2 - 5000;
						}
					}
				}
			}
			if(ok == 0)
			{
				lcd.setCursor (0,0);
				if(lang == '1') lcd.print("SOLD TRIMIS!");
				else if (lang == '2') lcd.print("MONEY SENT!");
				delay (3000);
				lcd.clear();  
			}
		}
		
	}
	else
	{
		if(lang == '1') lcd.print("PIN INVALID!");
		else if (lang == '2') lcd.print("INVALID PIN CODE!");
		delay (2000);
		lcd.clear();      
		lcd.setCursor (0,0);
	}	
}