
int pinOE0 =53; // High to enable output on 2600!
int pinOE1 =52; // High to enable output on 2600!

int pinAR = 50; // Tie high - not clocked mode

// Data byte on Arduino Analogue 0-7 = PORT F = INPUT
// Address byte A0-A7 (2600) pins 22-29 = PORT A = OUTPUT
// Address "high" byte (A8, A9, A10) pins 37-30 = PORTC = OUTPUT

int bytesToRead = 2048;

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
  pinMode(pinOE0, OUTPUT);
  digitalWrite(pinOE0, HIGH);
  pinMode(pinOE1, OUTPUT);
  digitalWrite(pinOE1, HIGH);
  pinMode(pinAR, OUTPUT);
  digitalWrite(pinAR, HIGH);
  
  //DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input
  //Set ports as I or O
  DDRF = B00000000;
  DDRA = B11111111;
  DDRC = B11111111;
  
  Serial.print("^B ,");
  int c=0;
  while (c<bytesToRead) {
    byte low = c;
    byte high = c >> 8;
    PORTA = low;
    PORTC = high;
    delay(10);
    byte read = PINF;
    Serial.print(" ");
    byte2serial(read);
    c++;
    delay(10);
  }
  Serial.println(" ^C");
}



void loop() {
  // put your main code here, to run repeatedly:

}
