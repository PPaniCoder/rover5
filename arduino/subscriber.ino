/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <rover5/moveRover5.h>
#include "DualMC33926MotorShield.h"

DualMC33926MotorShield motors;
int spd = 0;  int offset = 5;
ros::NodeHandle  nh;

void forward(){
  delay(2);
  motors.setSpeeds(spd, spd);
  digitalWrite( 8, 1 );  digitalWrite( 7, 0 );
}

void back(){
  delay(2);
  motors.setSpeeds(spd, spd);
  digitalWrite( 8, 0 );  digitalWrite( 7, 1 );
}

void left(){
  delay(2);
  motors.setSpeeds(spd, spd);
  digitalWrite( 8, 1 );  digitalWrite( 7, 1 );
}

void right(){
  delay(2);
  motors.setSpeeds(spd, spd);
  digitalWrite( 8, 0 ); // left
  digitalWrite( 7, 0 ); // right
}

void speedUp(){
  if( spd < 400 )  spd = spd + offset;
  else             spd = 400;
  OCR1A = OCR1B = spd;
}

void speedDown(){
  if( spd > 0 )  spd = spd - offset;
  else           spd = 0;
  OCR1A = OCR1B = spd;
}

void brake()
{  motors.setSpeeds( 0, 0 );  }



void messageCb( const rover5::moveRover5& move_msg){
  switch (move_msg.direction) {
      case( 'i'):
        forward();
        break;
          
      case( 'k' ):
        back();
        break;
           
      case( 'l' ):
        right();
        break;
        
      case( 'j' ):
        left();   
        break;
        
      case( 'q' ):
        brake();
        break;
        
      case( '.' ):
        speedUp();
        break;
        
      case( ',' ):
        speedDown();
        break;
  }
  
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<rover5::moveRover5> sub("rover5_move_msg", messageCb );




void setup(){
  pinMode(13, OUTPUT);
  nh.initNode();
  //nh.advertise(chatter);
  nh.subscribe(sub);
  motors.init();  
  forward();
}

void loop(){
  nh.spinOnce();
  delay(500);
}
