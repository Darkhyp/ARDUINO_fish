#include <Servo.h> //используем библиотеку для работы с сервоприводом

int servopin = 10;
Servo servo; //объявляем переменную servo типа Servo
int val0=0;// rotation angle
unsigned long time0=3L*24L*60L*60L*1000L;// delay in milliseconds
unsigned long timing; // Переменная для хранения точки отсчета
bool runTimer = true;


int myangle;// initialize angle variable
int pulsewidth;// initialize width variable
void servopulse(int servopin,int myangle)// define a servo pulse function
{
  //pulsewidth=((myangle*50)/9)+1500;// SG90: convert angle to 1000-2000 pulse width
  // 1000 -> -90 DEG (myangle = 0)
  // 1500 -> 0 DEG (myangle = 90)
  // 2000 -> 90 DEG (myangle = 180)
//  pulsewidth=(myangle*11)+500;// SG90: convert angle to 500-2480 (1980/180=11) pulse width
  pulsewidth=(int)(myangle*8+550);// SG90: convert angle to 600-2100 pulse width

  digitalWrite(servopin,HIGH);// set the level of servo pin as “high”
  delayMicroseconds(pulsewidth);// delay microsecond of pulse width
  digitalWrite(servopin,LOW);// set the level of servo pin as “low”
  delayMicroseconds(20000-pulsewidth);
  //delay(20-pulsewidth/1000);
}


void setup() //процедура setup
{
  // method 1
//  pinMode(servopin,OUTPUT);// set servo pin as “output”

  // method 2
//  /*
  servo.attach(servopin); //привязываем привод к порту 10
  servo.write(0); //ставим вал под 0
//  */

  Serial.begin(9600);// connect to serial port, set baud rate at “9600”
  Serial.print("servo ready! fish nourrison every ") ;
  Serial.print(time0) ;
  Serial.println("sec.") ;
}

char c;
String readString;
void loop() //процедура loop
{

  if (runTimer && millis() - timing > time0){
    timing = millis();


    val0 += int(171/4);
    servo.write(val0); //ставим вал под angle
    if (val0>171){
      val0 = 0;
      servo.write(val0); //ставим вал под angle
      Serial.print("finish... ");
      runTimer = false;
    }
    Serial.print("goto ");
    Serial.println(val0);
  }

}
