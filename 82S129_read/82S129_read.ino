
int pin_CS =22;
int pinO[4]={46,48,50,52};

int pinA[8]={24,26,28,30,32,34,36,38};

int nibblesToRead = 256;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_CS, OUTPUT);
  int i;
  for (i=0;i<4;i++)
  {
    pinMode(pinO[i],INPUT);
  
  }
  for (i=0;i<8;i++)
  {
    pinMode(pinA[i],OUTPUT);
  
  }
  Serial.println("Setup done");
  digitalWrite(pin_CS, LOW);
  
  int j;
  int value;
      Serial.println("Start read");

  for (i=0;i<nibblesToRead;i++) {
    value =0;
    if ((i & 0x0F) == 0) {
      Serial.println("");
      Serial.print(i, HEX);
      Serial.print(": ");
    }
    for (j=0;j<8;j++) {
      if ((i & (1<<j)) >0) {
        digitalWrite(pinA[j], HIGH);
      } else {
        digitalWrite(pinA[j], LOW);
      }
    }
    delay(20);
    if (digitalRead(pinO[0])==HIGH){
      value += 1;    
    }
    if (digitalRead(pinO[1])==HIGH){
      value += 2;    
    }
    if (digitalRead(pinO[2])==HIGH){
      value += 4;    
    }
    if (digitalRead(pinO[3])==HIGH){
      value += 8;    
    }
    Serial.print(value, HEX);
    Serial.print(" ");
    delay(20);
  }
    Serial.println("");
    Serial.println("Done ");
  
    delay(3000); // 3 second delay before restart
      // put your setup code here, to run once:

  Serial.println("------------------");
  digitalWrite(pin_CS, HIGH);
  Serial.println("Start read (disabled)");

  for (i=0;i<nibblesToRead;i++) {
    value =0;
    if ((i & 0x0F) == 0) {
      Serial.println("");
      Serial.print(i, HEX);
      Serial.print(": ");
    }
    for (j=0;j<8;j++) {
      if ((i & (1<<j)) >0) {
        digitalWrite(pinA[j], HIGH);
      } else {
        digitalWrite(pinA[j], LOW);
      }
    }
    delay(20);
    if (digitalRead(pinO[0])==HIGH){
      value += 1;    
    }
    if (digitalRead(pinO[1])==HIGH){
      value += 2;    
    }
    if (digitalRead(pinO[2])==HIGH){
      value += 4;    
    }
    if (digitalRead(pinO[3])==HIGH){
      value += 8;    
    }
    Serial.print(value, HEX);
    Serial.print(" ");
    delay(20);
  }
    Serial.println("");
    Serial.println("Done ");
  
    delay(3000); // 3 second delay before restart
}

void loop() {
  // put your main code here, to run repeatedly:
}
