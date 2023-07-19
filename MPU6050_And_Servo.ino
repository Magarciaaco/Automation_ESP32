/*
  MPU 6050 And Servo Control
  Coded by: Miguel Angel Garcia Acosta
  Contact: MAGA.DevCS@Gmail.com

  Task: Sync movement from Gyro Acceleration I/O : (MPU6050 module)
*/
#include <Wire.h>
#include <Servo.h>

// HELPING CLASS --> MPU6050
class MPU6050 {
  private:
  
  #define Active Wire.available()
  
  const int // readOnly // Refer to MPU6050 Datasheet
            MPU           = 0x68, // MPU 6050 ID
            PWR_MGMT_1    = 0x6B, // Power Management 1
            RESET         = 0X00, // Reset all Data Except for default 0x68
            ACCEL_CONFIG  = 0x1C, // ACCEL CONFIG
            ACCEL_XOUT_H  = 0x3B, // ACCEL OUT DATA // High
            PLUS_MINUS_2  = 0x10,  // FULL SCALE +/- 2g
            LSB_2         = 16384; // LSB/g Sensitivity for +/- 2g
            
  float
        // Acceleration Data
        ACCEL_X,
        ACCEL_Y,
        ACCEL_Z;

public:
    MPU6050() {}; //Empty Constructor
    // Get / Set //
    float setAccel_X(float e) { // SET ACCEL DATA X
      ACCEL_X = e/LSB_2;
    }
    float setAccel_Y(float e) { // SET ACCEL DATA Y
      ACCEL_Y = e/LSB_2;
    }
    float setAccel_Z(float e) { // SET ACCEL DATA Z
      ACCEL_Z = e/LSB_2;
    }
    float getAccel_X() {        // GET ACCEL DATA X
      return ACCEL_X;
    }
    float getAccel_Y() {        // GET ACCEL DATA Y
      return ACCEL_Z;
    }
    float getAccel_Z() {        // GET ACCEL DATA Z
      return ACCEL_Z;
    }

    // init //
    void _init_() {
      Wire.beginTransmission(MPU);     // Initialize MPU-6050 Communications // Wake UP from sleep mode (Default)
      Wire.write(PWR_MGMT_1);          // Accessing the register 6B - Power Management
      Wire.endTransmission(false);      // End Comms (Arduino -- MPU 6050)
      delay(20);
    }
    // Accel to Full Scale +/- 2g //
    void _ACCEL_FULL_SCALE_2G_() {
      if (Active) {
        Wire.beginTransmission(MPU); // Initialize MPU-6050 communication
        Wire.write(ACCEL_CONFIG);        // Accessing the register 1C - ACCEL_CONFIG
        Wire.write(PLUS_MINUS_2);        // Setting the accel to +/- 2g
        Wire.endTransmission(true);      // End        MPU-6050 communication
      } delay(20);
    }

    void _read_Accel_() {
      Wire.beginTransmission(MPU);
      Wire.write(ACCEL_XOUT_H);
      Wire.requestFrom(MPU, 14, true);
      /* shift left 8 bits | read */
      setAccel_X(Wire.read()<<8 | Wire.read());
      setAccel_Y(Wire.read()<<8 | Wire.read());
      setAccel_Z(Wire.read()<<8 | Wire.read());
    }
    
}; MPU6050 _MPU_;

// Servo
#define _Servo_Pin_X_ 2
#define _Servo_Pin_Y_ 4
#define _Servo_Pin_Z_ 7
Servo _Servo_X_;
Servo _Servo_Y_;
Servo _Servo_Z_;
// Helper Method: Servo
void _Servo_init_() {
  _Servo_X_.attach(_Servo_Pin_X_);
  _Servo_Y_.attach(_Servo_Pin_Y_);
  _Servo_Z_.attach(_Servo_Pin_Z_);
}

void setup() {
  _MPU_._init_();
  _MPU_._ACCEL_FULL_SCALE_2G_();
  _Servo_init_();
}

void _Servo_MPU_Sync_() {
  _MPU_._read_Accel_();
  _Servo_X_.write(map(_MPU_.getAccel_X(), -10, 10, 180, 0));
  _Servo_Y_.write(map(_MPU_.getAccel_Y(), -10, 10, 180, 0));
  _Servo_Z_.write(map(_MPU_.getAccel_Z(), -10, 10, 180, 0));
  delay(100);
}

void loop() {
  _Servo_MPU_Sync_();
}
