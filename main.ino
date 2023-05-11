#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo ENTER_SERVO;
#define FIRE_SENSOR 2 
#define BUZZER 11
#define IR_ENTER 3 
#define IR_EXIT 7
#define LED_1 8 
#define LED_2 10
#define LED_3 12
#define LED_4 13
#define DELAY_TIME 250
#define ENTERservo 6 
#define EXITservo 5

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and dimensions
Servo entservo;
Servo extservo;

int Pspaces = 0;  // 4
char message [10]= "";

void setup() 
{ 
  lcd.init();                      
  lcd.init();
  lcd.backlight();
  lcd.clear();
  entservo.attach(6);
  extservo.attach(5);
  Serial.begin (9600);
  pinMode (IR_ENTER , INPUT);
  pinMode (IR_EXIT , INPUT);
  pinMode (FIRE_SENSOR , INPUT);
  pinMode (LED_1 , OUTPUT);
  pinMode (LED_2 , OUTPUT);
  pinMode (LED_3 , OUTPUT);
  pinMode (LED_4 , OUTPUT);

  servo(ENTERservo,0);
}

void loop(){
  
 bool IR1status = digitalRead(IR_ENTER);
 bool FlameStatus = digitalRead(FIRE_SENSOR);
 bool IR2status = digitalRead(IR_EXIT);
 
 if (FlameStatus == false){
  alarming();
}
 else if (IR1status == false) {
  enter();
}
else if (IR2status == false) {
  exitir();
}


 // sprintf (message, "%d, %d, %d, %d" , Pspaces[0], Pspaces[1], Pspaces[2], Pspaces[3]);
 sprintf (message, "%d" , Pspaces);
 //Serial.println(message);
 delay(100);
}

void enter (){
     switch(Pspaces){
        case 0:
        Pspaces=1;
        digitalWrite(LED_1, HIGH);
        //sprintf(message, "%d", ) 
        LCDWrite(0,7,"1");
        servo(ENTERservo,90);
        break;
        case 1:
        Pspaces=2;
        digitalWrite(LED_2, HIGH); 
        LCDWrite(0,7,"2");
        servo(ENTERservo,90);
        break;
        case 2:
        Pspaces=3;
        digitalWrite(LED_3, HIGH); 
        LCDWrite(0,7,"3");
        servo(ENTERservo,90);
        break;
        case 3:
        Pspaces=4;
        digitalWrite(LED_4, HIGH); 
        LCDWrite(0,7,"4");
        servo(ENTERservo,90);
        break;
        default:
        digitalWrite(LED_1, LOW); 
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_3, LOW);
        digitalWrite(LED_4, LOW);
        LCDWrite(0,0,"Garage is FULL!");
   }
   delay (2000);
   lcd.clear(); 
   servo(ENTERservo,0);
}

void exitir(){
       switch(Pspaces){
        case 1:
        Pspaces=0;
        digitalWrite(LED_1, LOW);
     
        servo(EXITservo,90);
        break;
        case 2:
        Pspaces=1;
        digitalWrite(LED_2, LOW);
        servo(EXITservo,90);
        break;
        case 3:
        Pspaces=2;
        digitalWrite(LED_3, LOW);
        
        servo(EXITservo,90); 
        break;
        case 4:
        Pspaces=3;
        digitalWrite(LED_4, LOW);
        servo(EXITservo,90); 
        break;
   } 
   delay (2000);
   servo(EXITservo,0);
}

void LCDWrite(int x, int y, char mes[]){
    lcd.clear(); 
    lcd.setCursor(y, x);
    lcd.print(mes);
}

void alarming()
{
  while(!digitalRead(FIRE_SENSOR)){
  tone(BUZZER , 1000);
  ledblink();
  servo(ENTERservo,90);
  servo(EXITservo,90);
  LCDWrite (0,5,"fire !!");
  bluetooth(0);
  }
   lcd.clear();
   bluetooth(1);
   
  
}

void ledblink(){
  digitalWrite (LED_1 ,HIGH);
  digitalWrite (LED_2 ,HIGH);
  digitalWrite (LED_3 ,HIGH);
  digitalWrite (LED_4 ,HIGH);

  delay(DELAY_TIME);

  digitalWrite (LED_1 ,LOW);
  digitalWrite (LED_2 ,LOW);
  digitalWrite (LED_3 ,LOW);
  digitalWrite (LED_4 ,LOW);

  delay(DELAY_TIME);
}

void servo(int pin, int deg){
  if(pin == 6){
  entservo.write(deg);                 
  delay(15); 
  }
  else if (pin == 5){
  extservo.write(deg);
  delay(15);  
  }
}
void bluetooth(int reading){
  Serial.println(reading);
}
