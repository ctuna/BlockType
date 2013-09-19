

#include <time.h>

boolean key_a_been_pressed;
boolean key_b_been_pressed;
boolean key_c_been_pressed;
boolean key_d_been_pressed;


unsigned long last_press, current;
unsigned long elapsed;
int threshold = 1000;

void reset(){
  key_a_been_pressed = false;
  key_b_been_pressed = false;
  key_c_been_pressed = false;
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
  int key_a = digitalRead(8);
  int key_b = digitalRead(9);
  int key_c = digitalRead(10);
  int key_d = digitalRead(3);
  

    //IF ANY KEY WAS PRESSED
   if (check(key_a, &key_a_been_pressed)||check(key_b, &key_b_been_pressed) 
   ||   check(key_c, &key_c_been_pressed) ||    check(key_d, &key_d_been_pressed)){
      
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
  if (key_a_been_pressed || key_b_been_pressed || 
  key_c_been_pressed||key_d_been_pressed ){
    if (key_a_been_pressed) {strcpy(toPrint, "a");}
    if (key_b_been_pressed) {strcat(toPrint, "b");}
    if (key_c_been_pressed) {strcat(toPrint, "c");}
    if (key_d_been_pressed) {strcat(toPrint, "d");}
    strcat(toPrint, '\0');
    Serial.println(toPrint);
  }
}

