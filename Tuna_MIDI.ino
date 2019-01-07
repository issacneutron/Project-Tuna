#include <MIDI.h>
#define startPin 2
#define endPin 13
#define HOLD_TIME 130
MIDI_CREATE_DEFAULT_INSTANCE();
int Row = 0;
int Column = 0;
void readKey(void);
char decodeKey(void);
//Sa 240 Hz, Re 270 Hz, Ga 300 Hz, Ma 320 ,Pa 360 Hz,Dha 400 and Ni 450 Hz.
int Note[10] = {59,62,64,65,68,70,72,75,35,36};
char keyPressed;
char lastKey;
long start;
void setup() {
  MIDI.begin(4);
  Serial.begin(115200);
  for(int i = startPin;i<=endPin;i++){
    pinMode(i,INPUT_PULLUP);
  }
}
int temp;
void loop() {
  readKey();
  delay(10);
  if(Row != 0){
    keyPressed = decodeKey();
    //Serial.println(keyPressed);
    start = millis();
    while((millis() - start) < HOLD_TIME){
      if(keyPressed != lastKey){
        temp = int(keyPressed - '0');
        //Serial.println(temp);
        MIDI.sendNoteOn(Note[temp], 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
        lastKey = keyPressed;
      }
    }
    MIDI.sendNoteOff(Note[temp], 0, 1);
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
