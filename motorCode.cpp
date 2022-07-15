//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(10,11);
RoboClaw roboclaw(&serial,12000);
#define address 0x80

class Robot {
public:
    int state = 0;
    int dataIn = 0;
    int vel;


    Robot(){};
    void UpdateMove();
    void ChangeSpeed();
    int check();
    int determinant;
};




class RollingRobot : public Robot {
public:
    RollingRobot(){}
    void UpdateMove();
    void ChangeSpeed();
    void MakeSounds();
    int check();
};
void RollingRobot::MakeSounds(){

};


void RollingRobot::ChangeSpeed(){

   if(Serial.available() > 0){
         dataIn = Serial.read();

       }

        if (dataIn == '0'){
          vel = 0;
          }
        else if (dataIn == '1'){
          vel = 12;
          }
        else if (dataIn == '2'){
          vel = 24;
          }
        else if (dataIn == '3'){
          vel = 36;
          }
        else if (dataIn == '4'){
          vel = 48;
          }
        else if (dataIn == '5'){
          vel = 60;
          }
        else if (dataIn == '6'){
          vel = 72;
          }
        else if (dataIn == '7'){
          vel = 84;
          }
        else if (dataIn == '8'){
          vel = 96;
          }
        else if (dataIn == '9'){
          vel = 108;
          }
        else if (dataIn == 'q'){
          vel = 120;
          }

}
void RollingRobot::UpdateMove() {

       if(Serial.available() > 0){
         state = Serial.read();
         roboclaw.ForwardM1(address, 0);
         roboclaw.BackwardM2(address, 0);
       }



      if (state == 'F') {  // F, move forward
        roboclaw.ForwardM1(address, vel); //det = check();
        roboclaw.ForwardM2(address, vel); // det = check();
        state = check();
        }

      else if (state == 'B') {  // B, move back
        roboclaw.BackwardM1(address, vel); //det = check();
        roboclaw.BackwardM2(address, vel); // det = check();
        state = check();
        }

      else if (state == 'L') {  // L, move wheels left
        roboclaw.ForwardM1(address, vel); //det = check();
        roboclaw.BackwardM2(address, vel); // det = check();
        state = check();
        }

      else if (state == 'R') { // R, move wheels right
        roboclaw.ForwardM1(address, vel); //det = check();
        roboclaw.BackwardM2(address, vel); // det = check();
        state = check();
        }

      else if (state == 'I') {  // I, turn right forward
       roboclaw.BackwardM1(address, vel/2); //det = check();
        roboclaw.ForwardM2(address, vel); // det = check();
        state = check();
        }
else if (state == 'J') {  // J, turn right back
        roboclaw.ForwardM1(address, vel); //det = check();
        roboclaw.BackwardM2(address, vel/2); // det = check();
        state = check();
        }

      else if (state == 'G') {  // G, turn left forward
        roboclaw.BackwardM1(address, vel); //det = check();
        roboclaw.ForwardM2(address, vel/2); // det = check();
        state = check();
        }

      else if (state == 'H') {  // H, turn left back
        roboclaw.ForwardM1(address, vel/2); //det = check();
        roboclaw.BackwardM2(address, vel); // det = check();
        state = check();
        }

      else if (state == 'S') {  // S, stop
        roboclaw.ForwardM1(address,0); //det = check();
        roboclaw.BackwardM2(address, 0); // det = check();
        state = check();
        }
}
int RollingRobot:: check() {
  if (Serial.available() > 0) {dataIn = Serial.read(); 
        if (dataIn == 'F'){determinant = 'F';} 
        else if (dataIn == 'B'){determinant = 'B';}else if (dataIn == 'L'){determinant = 'L';}
        else if (dataIn == 'R'){determinant = 'R';}else if (dataIn == 'I'){determinant = 'I';} 
        else if (dataIn == 'J'){determinant = 'J';}else if (dataIn == 'G'){determinant = 'G';}
        else if (dataIn == 'H'){determinant = 'H';}else if (dataIn == 'S'){determinant = 'S';}
        else if (dataIn == '0'){vel = 0;}else if (dataIn == '1'){vel = 12;}
        else if (dataIn == '2'){vel = 24;}else if (dataIn == '3'){vel = 36;}
        else if (dataIn == '4'){vel = 48;}else if (dataIn == '5'){vel = 60;}
        else if (dataIn == '6'){vel = 72;}else if (dataIn == '7'){vel = 84;}
        else if (dataIn == '8'){vel = 96;}else if (dataIn == '9'){vel = 108;}
        else if (dataIn == 'q'){vel = 120;}
        else if (dataIn == 'U'){determinant = 'U';}else if (dataIn == 'u'){determinant = 'u';}
        else if (dataIn == 'W'){determinant = 'W';}else if (dataIn == 'w'){determinant = 'w';}

        }}
RollingRobot BB8;

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);

  Serial.begin(9600); // Default connection rate for my BT module

}


void loop() {

    BB8.UpdateMove();
    BB8.ChangeSpeed();
}
