/*
  ESP32 4 BIT uint8_t COUNTER
  Coded by: Miguel Angel Garcia Acosta
  Contact: MAGA.DevCS@Gmail.com

  A binary state system is a system/machine that cycles through its states (Low | High) for each clock signal.
  This 4 BIT Counter is constructed by:
   - 4 Led Signal indicators (linked to 330 Ohm resistors, individually grounded)
   - ESP32 BOARD

  Task: Create a 4 BIT uint8_t Binary counter that follows the same operational mode as a 4 bit Flip-Flop JK counter.


  Binary Count:
  - 4 bit
   -- 0x00000000 --> 0 to 16

   4 bit binary Table:
   ------------------------------------
   |   B   |   C  |    D   |   A   | #
   |   0       0       0       0   | 0
   |   0       0       0       1   | 1
   |   0       0       1       0   | 2
   |   0       0       1       1   | 3
   |   0       1       0       0   | 4
   |   0       1       0       1   | 5
   |   0       1       1       0   | 6
   |   0       1       1       1   | 7
   |   1       0       0       0   | 8
   |   1       0       0       1   | 9
   |   1       0       1       0   | 10
   |   1       0       1       1   | 11
   |   1       1       0       0   | 12
   |   1       1       0       1   | 13
   |   1       1       1       0   | 14
   |   1       1       1       1   | 15
   ------------------------------------


  ALGORITHM ANALYSIS:
  START
     - DEFINE AND INITIALIZE HARDWARE SETUP
       -- SET I\O PINS
         --- DIGITAL CHANNELS 1 TO 4 AS OUTPUT {B, C, D, A}
     - INITIALIZE BYTE ARRAY __4Bit__
       -- Size 16 array
     LOOP START
     - RECURSIVE TRAVERSE: COUNT FROM 16 TO 0
       -- DISPLAY TRAVERSE STATUS TO LEDs
     LOOP END
  END
*/
// START
//
// DEFINE AND INITIALIZE HARDWARE SETUP
#define B 2 // Digital pin D2
#define C 3 // Digital pin D3
#define D 4 // Digital pin D4
#define A 5 // Digital pin D5
static const uint8_t _BCDA_[] = {B, C, D, A};
// __4Bit__ Recursive traverse size
static const uint8_t __4Bit__ = 16;
//      0b00000000, // 0  0b 0000 0000
//      0b00000001, // 1  0b 0000 0001
//      0b00000010, // 2  0b 0000 0010
//      0b00000011, // 3  0b 0000 0011
//      0b00000100, // 4  0b 0000 0100
//      0b00000101, // 5  0b 0000 0101
//      0b00000110, // 6  0b 0000 0110
//      0b00000111, // 7  0b 0000 0111
//      0b00001000, // 8  0b 0000 1000
//      0b00001001, // 9  0b 0000 1001
//      0b00001010, // 10 0b 0000 1010
//      0b00001011, // 11 0b 0000 1011
//      0b00001100, // 12 0b 0000 1100
//      0b00001101, // 13 0b 0000 1101
//      0b00001110, // 14 0b 0000 1110
//      0b00001111  // 15 0b 0000 1111
uint8_t _mask_8_ = 8; //  0b 0000 1000
uint8_t _mask_4_ = 4; //  0b 0000 0100
uint8_t _mask_2_ = 2; //  0b 0000 0010
uint8_t _mask_1_ = 1; //  0b 0000 0001
//
// SET I\O PINS
/*
   _IO_(int e) takes pin data e to initialize as OUTPUT
   @param e key data integer
*/
void _IO_(int e) {  // DIGITAL CHANNELS 1 TO 4 AS OUTPUT {B, C, D, A}
  if (e < sizeof(_BCDA_) + 1)_IO_(e + 1);
  //delay(500);
  pinMode(_BCDA_[e], OUTPUT);
  digitalWrite(e, HIGH);
  delay(500);
}
// LOOP START
/*
 * _4bit_Traverse_() Helper method
 */
void _4bit_Traverse_() {
  _4bit_Traverse_(0);
}
// - RECURSIVE TRAVERSE: COUNT FROM 16 TO 0
/*
 * _4bit_Traverse_(uint8_t e) takes input key e and
 * recursively traverses to execute a binary 4 bit count
 * @param e key data uint8_t
 */
void _4bit_Traverse_(uint8_t e) {
  if (e < __4Bit__ )  _4bit_Traverse_(e + 1);       // RECURSIVE CONDITION
  digitalWrite (_BCDA_[0], boolean ((e & _mask_8_) >> 3)); // DISPLAY TRAVERSE STATUS TO LEDs
  digitalWrite (_BCDA_[1], boolean ((e & _mask_4_) >> 2)); // DISPLAY TRAVERSE STATUS TO LEDs
  digitalWrite (_BCDA_[2], boolean ((e & _mask_2_) >> 1)); // DISPLAY TRAVERSE STATUS TO LEDs
  digitalWrite (_BCDA_[3], boolean (e &  _mask_1_));       // DELAY
  delay(1000); // delay: 1s
}
// LOOP END
void setup() {
  _IO_(0); // SET I\O PINS
}
void loop() {
  _4bit_Traverse_();
}
// END
