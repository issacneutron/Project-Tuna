#define startPin 2
#define endPin 13
int Row = 0;
int Column = 0;
void setup() {
  Serial.begin(9600);
  for(int i = startPin;i<=endPin;i++){
    pinMode(i,INPUT_PULLUP);
  }
}

void loop() {
  int i = 0;
  int j = 0;
  for(i = startPin;i<=endPin;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
    for(j = startPin;j<=endPin;j++){
      if(i != j){
        if(digitalRead(j) == LOW){
          Row = (i-1);
          Column = (j-1);
          Serial.print(Row);Serial.print(",");Serial.println(Column);
          goto END;
        } //Loop to check which pin is high, if any then print its row and column number
      }//avoid setting the pin as output and input simultaneously
    }// loop  through all input pins
    delay(5);
    pinMode(i,INPUT_PULLUP);//set back pin as input for next scan cycle
  }//loop through all pins and set them as output, one at a time
 END:
  delay(5);
  pinMode(i,INPUT_PULLUP);//if break statement fails to set the pin as input again
}
