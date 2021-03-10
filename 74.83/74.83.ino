// Quick and dirty sketch for testing 74.83 adder ICs.
// Connect the IC/ZIF socket to the Arduino Mega as follows:
//
// Arduino Pin  IC Pin  Description
//  -           5       +5/VCC
//  -           12      GND
//  53          13      Carry Input
//  PORT A
//  22          10      A1
//  23          8       A2
//  24          3       A3
//  25          1       A4
//  PORT C
//  37          11      B1
//  36          7       B2
//  35          4       B3
//  34          16      B4
//  PORT F
//  A0          9       Sum1
//  A1          6       Sum2
//  A2          2       Sum3
//  A3          15      Sum4
//  A4          14      Carry Output

int pinC0  =53; // C0/carry input

// Data byte on Arduino Analogue 0-7 = PORT F = INPUT (5 bits, 0-3 + Carry)
// Pins 22-29 = PORT A = OUTPUT (nibble A)
// Pins 37-30 = PORTC = OUTPUT (nibble B)

void byte2serial(byte toWrite) {
  if (toWrite<0x10) {
    Serial.print("0");
  }
  Serial.print(toWrite, HEX);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Set clock mode pin and Output Enable pins
  pinMode(pinC0, OUTPUT);

  //Set ports as I or O
  //      76543210
  DDRF = B00000000;
  DDRA = B11111111;
  DDRC = B11111111;
  
  Serial.println("Carry In (C0) low");
  digitalWrite(pinC0, LOW);

  byte a = 0;
  byte b = 0;
  byte output = 0;

  for (a=0;a<16;a++){
    PORTA = a;
    for (b=0;b<16;b++){
      PORTC = b;
      delay(5);
      output = PINF & B00011111; // Mask only the bits that are used.
      if (output != (a+b) ) {
        Serial.print("E: ");
        byte2serial(a);
        Serial.print("+");
        byte2serial(b);
        Serial.print("!=");
        byte2serial(output);
        Serial.println(" ");
      } else {
        Serial.print(".");
        byte2serial(output);
      }
    }
    Serial.println(" ");
  }
  Serial.println(" ");
  digitalWrite(pinC0, HIGH);

  for (a=0;a<16;a++){
    PORTA = a;
    for (b=0;b<16;b++){
      PORTC = b;
      delay(5);
      output = PINF & B00011111;
      if (output != (a+b+1) ) {
        Serial.print("E: 1+");
        byte2serial(a);
        Serial.print("+");
        byte2serial(b);
        Serial.print("!=");
        byte2serial(output);
        Serial.println(" ");
      }
      else {
        Serial.print(".");
        byte2serial(output);
      }
      
    }
        Serial.println(" ");
  }
  Serial.println(" ");
  Serial.println("Done");

  digitalWrite(pinC0, LOW);

    PORTA = 0;
    PORTC = 0;

}



void loop() {
  // put your main code here, to run repeatedly:

}
