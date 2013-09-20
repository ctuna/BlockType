#include <time.h>

boolean key_R1_been_pressed;
boolean key_R2_been_pressed;
boolean key_R3_been_pressed;
boolean key_L1_been_pressed;
boolean key_L2_been_pressed;
boolean key_L3_been_pressed;
char letter[8][8]={
{'0', '1', '2', '3', '4', '5', '6', '7'},  
{'X', 'b', 'c', 'd', 'e', 'f', 'g', '7'},
{'x', 'b', 'c', 'd', 'e', 'f', 'g', '7'},
{'Y', 'b', 'c', 'd', 'e', 'f', 'g', '7'},
{'y', 'b', 'c', 'd', 'e', 'f', 'g', '7'},
{'U', 'b', 'c', 'd', 'e', 'f', 'g', '7'},
{'u', 'b', 'c', 'd', 'e', 'f', 'F', 'P'}};

unsigned long last_press, current;
unsigned long elapsed;
int threshold = 1000;

void reset(){
  key_R1_been_pressed = false;
  key_R2_been_pressed = false;
  key_R3_been_pressed = false;
  key_L1_been_pressed = false;
  key_L2_been_pressed = false;
  key_L3_been_pressed = false;
}
void setup(){
  //start serial connection
  Serial.begin(9600);
  reset();
  
  
  
  
  //initiate last press 
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
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
  
  int key_L1 = digitalRead(3);
  int key_L2 = digitalRead(5);
  int key_L3 = digitalRead(7);
  
  boolean r1Pressed = check(key_R1, &key_R1_been_pressed);
  boolean r2Pressed = check(key_R2, &key_R2_been_pressed); 
  boolean r3Pressed = check(key_R3, &key_R3_been_pressed);   
  
  boolean l1Pressed = check(key_L1, &key_L1_been_pressed);
  boolean l2Pressed = check(key_L2, &key_L2_been_pressed); 
  boolean l3Pressed = check(key_L3, &key_L3_been_pressed);   
     

    //IF ANY KEY WAS PRESSED
   if (r1Pressed||r2Pressed ||   r3Pressed || l1Pressed ||
     l2Pressed|| l3Pressed ){
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
  int rightIndex=0;
  int leftIndex = 0;
  char toPrint[20];
  strcpy(toPrint, "");
  if (key_R1_been_pressed || key_R2_been_pressed || 
  key_R3_been_pressed ){
    if (key_R1_been_pressed){
      //1XX
       if (key_R2_been_pressed){
         //11X
         if (key_R3_been_pressed){
           ///111  R7
           strcat(toPrint, "R7");
           rightIndex=7;
         }
         else {
           //110  R6
           strcat(toPrint, "R6");
           rightIndex=6;
         }
       }
       else {
         //10X
         if (key_R3_been_pressed){
           //101  R5
           strcat(toPrint, "R5");
           rightIndex=5;
         }
         else{
         //100  R4
         strcat(toPrint, "R4");
         rightIndex=4;
         }
       }
    }
      else{
        //0XX
        if (key_R2_been_pressed){
          //01X  
          if (key_R3_been_pressed){
            //011  R3
            strcat(toPrint, "R3");
            rightIndex=3;
          }
          else {
            //010  R2
            strcat(toPrint, "R2");
            rightIndex=2;
          }
        }
        else{
        //00X
           if (key_R3_been_pressed){
            //001  R1
             strcat(toPrint, "R1");
             rightIndex=1;
          }
  
        }
       
      }
    strcat(toPrint, '\0');
    //Serial.println(toPrint);
  } 
  
       if (key_L1_been_pressed || key_L2_been_pressed || 
  key_L3_been_pressed ){
    if (key_L1_been_pressed){
      //1XX
       if (key_L2_been_pressed){
         //11X
         if (key_L3_been_pressed){
           ///111  R7
           strcat(toPrint, "L7");
           leftIndex=7;
         }
         else {
           //110  R6
           strcat(toPrint, "L6");
           leftIndex=6;
         }
       }
       else {
         //10X
         if (key_L3_been_pressed){
           //101  R5
           strcat(toPrint, "L5");
           leftIndex=5;
         }
         else{
         //100  R4
         strcat(toPrint, "L4");
         leftIndex=4;
         }
       }
    }
      else{
        //0XX
        if (key_L2_been_pressed){
          //01X  
          if (key_L3_been_pressed){
            //011  R3
            strcat(toPrint, "L3");
            leftIndex=3;
          }
          else {
            //010  R2
            strcat(toPrint, "L2");
            leftIndex=2;
          }
        }
        else{
        //00X
           if (key_L3_been_pressed){
            //001  R1
             strcat(toPrint, "L1");
             leftIndex=1;
          }
          
        }
       
        
      }
    strcat(toPrint, '\0');
    //Serial.println(toPrint);
  }

   if (! (rightIndex==0 && leftIndex == 0)){
    Serial.println(letter[rightIndex][leftIndex]);     
   }  
    
    
    
    //if (key_a_been_pressed) {strcat(toPrint, "a");}
    //if (key_b_been_pressed) {strcat(toPrint, "b");}
    //if (key_c_been_pressed) {strcat(toPrint, "c");}
    //if (key_d_been_pressed) {strcat(toPrint, "d");}

 
}
