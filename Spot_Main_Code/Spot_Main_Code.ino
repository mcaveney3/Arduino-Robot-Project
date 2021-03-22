// -----------Imports-------------------------------
#include <Servo.h>

// --------Instantiations---------------------------
              //   LEG #     1      |     2     |     3      |     4   
              //         Front Left |Front Right|Back Left   | Back Right
              //        SHD HIP KNE|SHD  HIP KNE|SHDHIP KNE  |SHD  HIP KNE
Servo s[12];  //         2   3   4    5   6   7   8   9  10   11  12   13
int zeroPositions[12] = {83, 90, 92, 90, 88, 98, 87, 85, 88,  90, 97, 90};

int directions[12] = {-1, -1, -1, -1, +1, +1, +1, -1, -1, +1, +1, +1};

const float l = 5;
const float L = 14.5;

// -------------Set Up-------------------------------

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  for(int i=0; i<12; i++){
     s[i].attach(i+2);
     delay(100);
  }
  for(int i=0; i<12; i++){
     s[i].write(zeroPositions[i]);
     delay(100);
  }
  translate(-5,0,5);
  delay(5000);
  translate(0,0,9);
  delay(5000);
  translate(-5,0,5);
  delay(5000);
}


//-----------Main Loop-------------------------------


void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
}


// -----------Functions------------------------------

void pos(float x, float y, float z, int leg){
  float groinRadians = atan(y/z);
  float groinDegrees = groinRadians * (180/PI);

  float hipRadians1 = atan(x/z);

  float z1 = sqrt(sq(z) + sq(y) + sq(x)); 
  
  float hipRadians2 = acos(z1/(2*l));
  float hipDegrees = (hipRadians1 + hipRadians2) * (180/PI);
  
  float kneeRadians = PI - 2*hipRadians2;
  float kneeDegrees = 180 - kneeRadians * (180/PI);

//  Serial.println(groinDegrees);
//  Serial.println(hipDegrees);
//  Serial.println(kneeDegrees);
  
  s[3*leg].write(zeroPositions[3*leg] + directions[3*leg]*groinDegrees);
  s[3*leg+1].write(zeroPositions[3*leg+1] + directions[3*leg+1]*hipDegrees);
  s[3*leg+2].write(zeroPositions[3*leg+2] + directions[3*leg+2]*kneeDegrees);
}

void translate(float x, float y, float z){
  for (int leg = 0; leg<=3; leg++){
    pos(x,y,z,leg);
  }
}

void rotate(float theta){
    float thetaRadians = theta * (PI/180);
    float d = tan(thetaRadians) * (L/2);

    Serial.println(d);

     pos(0,0,8.0+d,0);
     pos(0,0,8.0+d,1);
     pos(0,0,8.0-d,2);
     pos(0,0,8.0-d,3);
}

void takeStep(float stepSpeed, float stepLength){
     pos(+stepLength,0,9,0);
     pos(-stepLength,0,9,1);
     pos(-stepLength,0,9,2);
     pos(+stepLength,0,9,3);
     delay(stepSpeed);
     pos(+stepLength,0,8,0);
     pos(-stepLength,0,9,1);
     pos(-stepLength,0,9,2);
     pos(+stepLength,0,8,3);
     delay(stepSpeed);
     pos(-stepLength,0,8,0);
     pos(+stepLength,0,9,1);
     pos(+stepLength,0,9,2);
     pos(-stepLength,0,8,3);
     delay(stepSpeed);
     pos(-stepLength,0,9,0);
     pos(+stepLength,0,9,1);
     pos(+stepLength,0,9,2);
     pos(-stepLength,0,9,3);
     delay(stepSpeed);
     pos(-stepLength,0,9,0);
     pos(+stepLength,0,8,1);
     pos(+stepLength,0,8,2);
     pos(-stepLength,0,9,3);
     delay(stepSpeed);
     pos(+stepLength,0,9,0);
     pos(-stepLength,0,8,1);
     pos(-stepLength,0,8,2);
     pos(+stepLength,0,9,3);
    delay(stepSpeed);
}

void sideStep(){
  pos(0,0,8,0);
  pos(0,0,8,1);
  pos(0,0,8,2);
  pos(0,0,8,3);
  delay(100);
  pos(0,0,10,0);
  pos(0,2,8,1);
  pos(0,0,10,2);
  pos(0,2,8,3);
  delay(100);
  pos(0,3,9,0);
  pos(0,-3,9,1);
  pos(0,3,9,2);
  pos(0,-3,9,3);
  delay(500);
  pos(0,0,9,0);
  pos(0,-3,9,1);
  pos(0,0,9,2);
  pos(0,-3,9,3);
  delay(100);
  pos(0,0,9,0);
  pos(0,0,9,1);
  pos(0,0,9,2);
  pos(0,0,9,3);
  delay(1000); 
} 

void creep(){
  float in_step = 1;
  float med_step = 5;
  float big_step = 9;
  float z = 8;

  //Start
  pos(med_step,-med_step,z,0);
  pos(-in_step,med_step,z,1);
  pos(-med_step,-med_step,z,2);
  pos(in_step,med_step,z,3);
  delay(100);

  //step
  pos(big_step, med_step,z,1);
  delay(100);
  
  //move
  pos(-in_step,-med_step,z,0);
  pos(med_step,med_step,z,1);
  pos(-big_step,-med_step,z,2);
  pos(-med_step,med_step,z,3);
  delay(100);

  //step
  pos(in_step,-med_step,z,2);
  delay(100);

  //step
  pos(big_step,-med_step,z,0);
  delay(100);

  //move
  pos(med_step,-med_step,z,0);
  pos(-in_step,med_step,z,1);
  pos(-med_step,-med_step,z,2);
  pos(-big_step,med_step,z,3);
  delay(100);
  //step
  pos(in_step,med_step,z,3);
  delay(100);
}

