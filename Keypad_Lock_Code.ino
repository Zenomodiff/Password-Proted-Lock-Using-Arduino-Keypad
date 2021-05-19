//feel free to contact
//sreeramaj53@gmail.com
//www.youtube.com/ZenoModiff

#include <Wire.h>
#include <Keypad.h>                 
#include <LiquidCrystal_I2C.h>
#include<EEPROM.h>
LiquidCrystal_I2C liquid_crystal_display(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

char password[4];
char initial_password[4],new_password[4];
int i=0;
int Led_pin = 12;
char key_pressed=0;
const byte rows = 4; 
const byte columns = 4; 

char hexaKeys[rows][columns] = {

{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}

};

byte row_pins[rows] = {5,4,3,2};
byte column_pins[columns] = {6,7,8,9};   
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

byte locked[8] = { 
  B01110,
  B01010,
  B01010,
  B01010,
  B11111,
  B11111,
  B11111,
  B00000,
};
byte unlocked[8] = { 
  B01110,
  B01010,
  B00010,
  B00010,
  B11111,
  B11111,
  B11111,
  B00000,
};

byte key[8] = {
  B11111,
  B10001,
  B10001,
  B11111,
  B00100,
  B01100,
  B00100,
  B01100
};

void setup()

{

  pinMode(Led_pin, OUTPUT);

  liquid_crystal_display.begin(16,2);
  liquid_crystal_display.createChar(0, locked);
  liquid_crystal_display.createChar(1, unlocked);
  liquid_crystal_display.createChar(2, key);
  liquid_crystal_display.setCursor(1,0);
  liquid_crystal_display.print("  ZenoModiff");
  liquid_crystal_display.setCursor(0,1);
  liquid_crystal_display.write(byte(2));
  liquid_crystal_display.print(" Arduino Lock ");
  liquid_crystal_display.write(byte(2));
  delay(2000);
  liquid_crystal_display.clear();
  liquid_crystal_display.print(" Enter Password");
  liquid_crystal_display.setCursor(0,1);
  initialpassword();

}
void loop()
{
digitalWrite(Led_pin, LOW);
key_pressed = keypad_key.getKey();
if(key_pressed=='#')
change();
if (key_pressed)
{
password[i++]=key_pressed;
liquid_crystal_display.print(key_pressed);
}
if(i==4)
{
delay(200);
for(int j=0;j<4;j++)
initial_password[j]=EEPROM.read(j);
if(!(strncmp(password, initial_password,4)))
{
liquid_crystal_display.clear();
liquid_crystal_display.print(" Pass Accepted");
liquid_crystal_display.setCursor(7,1);
liquid_crystal_display.write(byte(1));

digitalWrite(Led_pin, HIGH);
delay(2000);

liquid_crystal_display.clear();
liquid_crystal_display.setCursor(0,1);
liquid_crystal_display.print("Pres # to change");
delay(2000);
liquid_crystal_display.clear();
liquid_crystal_display.print(" Enter Password:");
 liquid_crystal_display.setCursor(0,1);

i=0;
}
else
{

digitalWrite(Led_pin, LOW);

liquid_crystal_display.clear();
liquid_crystal_display.print(" Wrong Password");
liquid_crystal_display.setCursor(7,1);
liquid_crystal_display.write(byte(0));
delay(2000);
liquid_crystal_display.clear();
liquid_crystal_display.setCursor(0,1);
liquid_crystal_display.print("Pres # to change");
delay(2000);
liquid_crystal_display.clear();
liquid_crystal_display.print(" Enter Password:");
liquid_crystal_display.setCursor(0,1);

i=0;

}
}
}

void change()

{

int j=0;

liquid_crystal_display.clear();
liquid_crystal_display.print("Current Password");
liquid_crystal_display.setCursor(0,1);

while(j<4)
{
char key=keypad_key.getKey();
if(key)
{
new_password[j++]=key;
liquid_crystal_display.print(key);
}
key=0;
}
delay(500);
if((strncmp(new_password, initial_password, 4)))
{
liquid_crystal_display.clear();
liquid_crystal_display.print("Wrong Password");
liquid_crystal_display.setCursor(0,1);
liquid_crystal_display.print("Try Again");
delay(1000);
}
else
{
j=0;
liquid_crystal_display.clear();
liquid_crystal_display.print("New Password:");
liquid_crystal_display.setCursor(0,1);
while(j<4)
{
char key=keypad_key.getKey();
if(key)
{
initial_password[j]=key;
liquid_crystal_display.print(key);

EEPROM.write(j,key);
j++;
}
}
liquid_crystal_display.print("Pass Changed");
 delay(1000);
}
liquid_crystal_display.clear();
liquid_crystal_display.print("Enter Password");
liquid_crystal_display.setCursor(0,1);
key_pressed=0;
}
void initialpassword(){
  
for(int j=0;j<4;j++)
 EEPROM.write(j, j+49);
for(int j=0;j<4;j++)
initial_password[j]=EEPROM.read(j);
}
