#include <Adafruit_LiquidCrystal.h>

#define BTN_UP 2
#define BTN_DOWN 3
#define MOTOR_PIN 13
//distancia dos anderes em metros
int meters = 10 * 1000;
int distance[6];
//distance = {2 * meters,3 * meters, 4 * meters, 30 * meters, 10 * meters,8 * meters}
Adafruit_LiquidCrystal lcd(0);

enum class State {
  
  GoingUp,
  GoingDown,
  Stopped
    
    
};


class Elevator {

private:

  int currentFloor;
  int targetFloor;

  State state;

public:

  Elevator() {
    currentFloor = 0;
    targetFloor = 0;
    state = State::Stopped;
  }

  void begin() {
   	lcd.begin(16, 1);
   	lcd.print("veri brabo");
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    

    for (int pin = 4; pin <= 13; pin++) {
      
      
        pinMode(pin, OUTPUT); 

        digitalWrite(pin, LOW);
    }

    updateLed();
  }

  int floorToPin(int floor) {
    if (floor >  0 ){
      return floor +3;
    }
  }
 
  void motorstart(){
  
  	
 digitalWrite(MOTOR_PIN, HIGH);
      delay(1000);
        if (targetFloor == currentFloor) {
      digitalWrite(MOTOR_PIN,LOW);}
  }
  
  void updateLed() {

    for (int pin = 4; pin <= 13; pin++) {
        digitalWrite(pin, LOW);
        
    }

    digitalWrite(floorToPin(currentFloor), HIGH);
    
  }

  void goToFloor(int floor) {

   

    targetFloor = floor;

    if (targetFloor > currentFloor) {
      
      state = State::GoingUp;
      
    }
    else if (targetFloor < currentFloor) {
      
      state = State::GoingDown;
    }
    else {
      state = State::Stopped;
      
      
    }
  }

  void goUp() {

    if (currentFloor  < 6) {
         
		
      goToFloor(currentFloor + 1);
      
      
    }else  {
      
    targetFloor = 0;
    currentFloor = 0;
    }
  }
  

  void goDown() {

    if (currentFloor > 1)
    {
      
      goToFloor(currentFloor - 1);
      
      
    }else{
      
        targetFloor = 7;
   		currentFloor = 7;

    }
  
  }
  void emergency(){
  
  	if(currentFloor );
  }

  void stop() {
    state = State::Stopped;
  }
  

  void update() {


    switch (state) {

      case State::Stopped:
        break;

      case State::GoingUp:
	
        currentFloor++;
        updateLed();

      
        if (currentFloor == targetFloor) 
        {
          
          Serial.print("SObe ai bro: ");
          Serial.println(currentFloor);

          lcd.clear();
          lcd.print("Andar: " + String(currentFloor));
            stop();
        }

      
        delay(100);
     
        break;

      case State::GoingDown:
	
   	
        currentFloor--;
        updateLed();

     
       
        if (currentFloor == targetFloor) 
        {
          	lcd.clear();
   		lcd.print("Andar: " + String(currentFloor));
          
        Serial.print("deicendo: ");
        Serial.println(currentFloor);
      	
          stop();
        }

        delay(100);
        break;
    }
  }

  int getCurrentFloor() {
    return currentFloor;
  }
};

Elevator elevator;

void setup() {

  elevator.begin();
}

void loop() {

  int upButton = digitalRead(BTN_UP);
  int downButton = digitalRead(BTN_DOWN);

  if (upButton == LOW) 
  {
   elevator.motorstart();
    elevator.goUp(); 
    
    elevator.update();
    
     
  }
  else if (downButton == LOW)
  {
    elevator.motorstart();
    elevator.goDown();
    
    elevator.update();
    
    
    
  }else{
     elevator.update();
  }


}
