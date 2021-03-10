
int pinC0  =53; // C0/carry input

// Data byte on Arduino Analogue 0-7 = PORT F = INPUT (5 bits, 0-3 + Carry)
// Address byte A0-A7 (2600) pins 22-29 = PORT A = OUTPUT (nibble A)
// Address "high" byte (A8, A9, A10) pins 37-30 = PORTC = OUTPUT (nibble B)

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
//  digitalWrite(pinOE0, HIGH);
  
  //DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input
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
      output = PINF & B00011111;
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
