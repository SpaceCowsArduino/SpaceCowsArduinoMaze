#include <LiquidCrystal.h>
#include <AFMotor.h>
AF_DCMotor MotorLH(1, MOTOR12_64KHZ);
AF_DCMotor MotorLV(4, MOTOR34_64KHZ);
AF_DCMotor MotorRV(3, MOTOR34_64KHZ);
AF_DCMotor MotorRH(2, MOTOR12_64KHZ);
int URPWM1=26;   //rechts1
int URTRIG1=27;
int URPWM2=24  //rechts2
int URTRIG2=25
int URPWM3=26;   //links1
int URTRIG3=27;
int URPWM4=24  //links2
int URTRIG4=25
int URPWM5=26;   //vorne1
int URTRIG5=27;
int URPWM6=24  //vorne2
int URTRIG6=25

uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // distance measure command

unsigned int entfernung1=0; //rechts
unsigned int entfernung2=0;
unsigned int entfernung3=0; //links
unsigned int entfernung4=0;
unsigned int entfernung5=0; //vorne
unsigned int entfernung6=0;
long dauer1=0;
long dauer2=0;
long dauer3=0;
int rot1;
int rot2;
int test;
int LED = 20;
int val;
int val2;
int speedRnormal = 255;
int speedLnormal = 255;
int speedD = 255;

void setup() 
{
 Serial.begin (9600);
 MotorRV.setSpeed(speedRnormal);
 MotorRH.setSpeed(speedRnormal);
 MotorLV.setSpeed(speedLnormal);
 MotorLH.setSpeed(speedLnormal);
 PWM_Mode_Setup();
}

  void loop() 
{
 Vorwaerts();
 delay(3212 900); //nächste Platte
 stopp();
 delay(1000);
 //Rot(); 
 Test();
}


void PWM_Mode_Setup() {
  pinMode(URTRIG1,OUTPUT);                     // A low pull on pin COMP/TRIG 1
  digitalWrite(URTRIG1,HIGH);                  // Set to HIGH
  pinMode(URTRIG2,OUTPUT);                     // A low pull on pin COMP/TRIG 2
  digitalWrite(URTRIG2,HIGH);                  // Set to HIGH
  pinMode(URTRIG3,OUTPUT);                     // A low pull on pin COMP/TRIG 3
  digitalWrite(URTRIG3,HIGH);                  // Set to HIGH
  pinMode(URTRIG4,OUTPUT);                     // A low pull on pin COMP/TRIG 4 
  digitalWrite(URTRIG4,HIGH);                  // Set to HIGH
  pinMode(URTRIG5,OUTPUT);                     // A low pull on pin COMP/TRIG 5
  digitalWrite(URTRIG5,HIGH);                  // Set to HIGH
  pinMode(URTRIG6,OUTPUT);                     // A low pull on pin COMP/TRIG 6
  digitalWrite(URTRIG6,HIGH);                  // Set to HIGH

  pinMode(URPWM1, INPUT);                      // Sending Enable PWM mode command 1
  pinMode(URPWM2, INPUT);                      // Sending Enable PWM mode command 2
  pinMode(URPWM3, INPUT);                      // Sending Enable PWM mode command 3
  pinMode(URPWM4, INPUT);                      // Sending Enable PWM mode command 4
  pinMode(URPWM5, INPUT);                      // Sending Enable PWM mode command 5
  pinMode(URPWM6, INPUT);                      // Sending Enable PWM mode command 6
  

  for(int i=0;i<4;i++)
    {
       Serial.write(EnPwmCmd[i]);
    } 


 
void Test()
{
 digitalWrite(trigger1, LOW);
 delay(5);
 digitalWrite(trigger1, HIGH);
 delay(10);
 digitalWrite(trigger1, LOW);
 dauer1 = pulseIn(echo1, HIGH);
 entfernung1 = (dauer1/2) * 0.03432;
 digitalWrite(trigger2, LOW);
 delay(5);
 digitalWrite(trigger2, HIGH);
 delay(10);
 digitalWrite(trigger2, LOW);
 dauer2 = pulseIn(echo2, HIGH);                                                            
 entfernung2 = (dauer2/2) * 0.03432;
 digitalWrite(trigger3, LOW);
 delay(5);
 digitalWrite(trigger3, HIGH);
 delay(10);
 digitalWrite(trigger3, LOW);
 dauer3 = pulseIn(echo3, HIGH);
 entfernung3 = (dauer3/2) * 0.03432;
 
 if (entfernung1 >= 10)  //RECHTS
 {
  Rueckwaerts();
  delay(150);
  aufRechts();
  loop();
 }
 else if (entfernung3 >= 10) //VORNE
 {
  loop();
  }
 
 else if (entfernung2 >= 10)  //LINKS
 {
  aufLinks();
  loop();
 }
 else                       //HINTEN
 {
 MotorRV.setSpeed(speedRnormal);
 MotorRH.setSpeed(speedRnormal);
 MotorRV.run(FORWARD);
 MotorRH.run(FORWARD);
 MotorLV.run(BACKWARD);
 MotorLH.run(BACKWARD);
 delay(6000);
 MotorRV.setSpeed(speedRnormal);
 MotorRH.setSpeed(speedRnormal);
 MotorLV.setSpeed(speedLnormal);
 MotorLH.setSpeed(speedLnormal);
  loop();
 }
}

/*void LinksTest()
{
 digitalWrite(trigger2, LOW);
 delay(5);
 digitalWrite(trigger2, HIGH);
 delay(10);
 digitalWrite(trigger2, LOW);
 dauer2 = pulseIn(echo2, HIGH);                                                            
 entfernung2 = (dauer2/2) * 0.03432;
 if (entfernung2 <= 5)
 {
  aufLinks(); //180 Grad
  aufLinks();
  loop();
 }
}

void VorneTest()
{
 digitalWrite(trigger3, LOW);
 delay(5);
 digitalWrite(trigger3, HIGH);
 delay(10);
 digitalWrite(trigger3, LOW);
 dauer3 = pulseIn(echo3, HIGH);
 entfernung3 = (dauer3/2) * 0.03432;
 if (entfernung3 <= 5)
 {
  aufLinks();
  aufLinks(); //180 Grad
  loop();
 }
  else
 {
  loop();
 }
}*/


void Vorwaerts()
{
 MotorRV.run(FORWARD);
 MotorRH.run(FORWARD);
 MotorLV.run(FORWARD);
 MotorLH.run(FORWARD);
}

void Rueckwaerts()
{
 MotorRV.run(BACKWARD);
 MotorRH.run(BACKWARD);
 MotorLV.run(BACKWARD);
 MotorLH.run(BACKWARD);
}

void aufRechts()
{
 MotorLV.setSpeed(speedD);
 MotorLH.setSpeed(speedD);
 MotorRV.setSpeed(245);
 MotorRH.setSpeed(245);
 MotorRV.run(BACKWARD);
 MotorRH.run(BACKWARD);
 MotorLV.run(FORWARD);
 MotorLH.run(FORWARD);
 delay(2450);
 MotorLV.setSpeed(speedLnormal);
 MotorLH.setSpeed(speedLnormal);
 MotorRV.setSpeed(speedRnormal);
 MotorRH.setSpeed(speedRnormal);
}

void aufLinks()
{
 MotorLV.setSpeed(speedD);
 MotorLH.setSpeed(speedD);
 MotorRV.setSpeed(245);
 MotorRH.setSpeed(245);
 MotorRV.run(FORWARD);
 MotorRH.run(FORWARD);
 MotorLV.run(BACKWARD);
 MotorLH.run(BACKWARD);
 delay(2550);
 MotorLV.setSpeed(speedLnormal);
 MotorLH.setSpeed(speedLnormal);
 MotorRV.setSpeed(speedRnormal);
 MotorRH.setSpeed(speedRnormal);
} 


void stopp()
{
 MotorRV.run(RELEASE);
 MotorRH.run(RELEASE);
 MotorLV.run(RELEASE);
 MotorLH.run(RELEASE);
}

/*void Rot()
{
      val=analogRead(14);   //connect grayscale sensor to Analog 0
      val2=analogRead(7);
      Serial.println(val,DEC);//print the value to serial        
      delay(100);

     if ((val>=170 && val<=230) && (val2>=170 && val2<=230))
     {
       delay(1000);
       val=analogRead(14);   //connect grayscale sensor to Analog 0
       val2=analogRead(7);
       if ((val>=170 && val<=230) && (val2>=170 && val2<=230))
       {
        delay(1000);
        val=analogRead(14);   //connect grayscale sensor to Analog 0
        val2=analogRead(7);
        if ((val>=170 && val<=230) && (val2>=170 && val2<=230))
        {
          digitalWrite(LED, HIGH);
          delay(2000);
          digitalWrite(LED, LOW);
          delay(1000);
}
      }
    }
}   
*/

