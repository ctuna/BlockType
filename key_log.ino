

#include <time.h>

boolean key_R1_been_pressed;
boolean key_R2_been_pressed;
boolean key_R3_been_pressed;
boolean key_d_been_pressed;


unsigned long last_press, current;
unsigned long elapsed;
int threshold = 1000;

void reset(){
  key_R1_been_pressed = false;
  key_R2_been_pressed = false;
  key_R3_been_pressed = false;
  key_d_been_pressed = false;
}
void setup(){
  //start serial connection
  Serial.begin(9600);
  reset();
  //initiate last press 
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);  
}

boolean check(int key, boolean *key_been_pressed){

 if (key == LOW) {
      *key_been_pressed = true;
      last_press = millis();
      return true;
    }
  else {
    return false;
  }
  
}


  
void loop(){
  current = millis();
  //read the pushbutton value into a variable
  int key_R1 = digitalRead(8);
  int key_R2 = digitalRead(9);
  int key_R3 = digitalRead(10);
  int key_d = digitalRead(3);
  

    //IF ANY KEY WAS PRESSED
   if (check(key_R1, &key_R1_been_pressed)||check(key_R2, &key_R2_been_pressed) 
   ||   check(key_R3, &key_R3_been_pressed) ||    check(key_d, &key_d_been_pressed)){
      
     digitalWrite(13, HIGH);
  } 
  else {
    //NO KEY WAS PRESSED 
    digitalWrite(13, LOW);
    if (current - last_press > 1000){
      //SUBMIT GESTURE IF THERE WAS ONE
      //CLEAR ALL BOOLEANS 
      printKeys();
      reset();
    }
  }
}

void printKeys(){
  char toPrint[20];
  strcpy(toPrint, "");
  if (key_R1_been_pressed || key_R2_been_pressed || 
  key_R3_been_pressed||key_d_been_pressed ){
    if (key_R1_been_pressed){
      //1XX
       if (key_R2_been_pressed){
         //11X
         if (key_R3_been_pressed){
           //111  R7
         }
         else {
           //110  R6
         }
       }
       else {
         //10X
         if (key_3_been_pressed){
           //101  R5
         }
         else{
         //100  R4
         }
       }
    }
      else{
        //0XX
        if (key_R2_been_pressed){
          //01X  
          if (key_R3_been_pressed){
            //011  R3
          }
          else {
            //010  R2
          }
        }
        else{
        //00X
           if (key_R3_been_pressed){
            //001  R1
          }
  
        }
        
      }
         
       }
         
    
    
    
    if (key_a_been_pressed) {strcpy(toPrint, "a");}
    if (key_b_been_pressed) {strcat(toPrint, "b");}
    if (key_c_been_pressed) {strcat(toPrint, "c");}
    if (key_d_been_pressed) {strcat(toPrint, "d");}
    strcat(toPrint, '\0');
    Serial.println(toPrint);
  }
}

