#define startPin 2
#define endPin 13
#define HOLD_TIME 200
int Row = 0;
int Column = 0;
void readKey(void);
char decodeKey(void);
char keyPressed;
char lastKey;
long start;
void setup() {
  Serial.begin(9600);
  for(int i = startPin;i<=endPin;i++){
    pinMode(i,INPUT_PULLUP);
  }
}

void loop() {
  readKey();
  if(Row != 0){
    keyPressed = decodeKey();
    //Serial.println(keyPressed);
    start = millis();
    while((millis() - start) < HOLD_TIME){
      if(keyPressed != lastKey){
        Serial.println(keyPressed);
        lastKey = keyPressed;
      }
    }
    lastKey = keyPressed = ' ';
    Row=Column=0;
    }
}
void readKey(void){
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
          //Serial.print(Row);Serial.print(",");Serial.println(Column);
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

char decodeKey(void){
  if(Column == 7 && Row < 7){
    return(char(Row-2+48));
  }//keys 0-4 are mapped as (0,4) -> [(2,7),(6,7)] and 48 added to convert to ascii
  else if(Column == 11 && Row < 6){
    return(char(Row+52));
  }//keys 6-9 are mapped as (6,9) -> [(2,11),(5,7)]
  else if(Column == 11 && Row == 9){
    return('5');
  }//value for 5 is (9,11)

}

