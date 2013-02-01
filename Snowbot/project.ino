#include <AccelStepper.h>
#include "string.h"
#include "stdio.h"

//Motor
AccelStepper left(4, 2, 3, 4, 5);
AccelStepper right(4, 6, 7, 8, 9);
/*int left = 2;
int left_dir = 3;
int right = 6;
int right_dir = 7;*/
int run_state = LOW;
long interval = 100;

//Serial
char line[20];
int line_pos = 0;
char action[10];
unsigned long duration;
boolean data_ready = false;

void setup()
{
  /*pinMode(right, OUTPUT);
  pinMode(right_dir, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(left_dir, OUTPUT);*/
  
  left.setMaxSpeed(300.0);
  left.setAcceleration(100.0);
  right.setMaxSpeed(300.0);
  right.setAcceleration(100.0);
  
  Serial.begin(9600);
  delay(1500);
  Serial.println("Ready!");
}

void loop()
{
    char state;
    if(Serial.available()>0)
    {
        state = Serial.read();
        
        if(state == '!')
        {
          data_ready = true;
          line[line_pos] = state;
          line_pos = 0;
        }
        else
        {
          line[line_pos] = state;
          line_pos = line_pos + 1;
        }
        
        if(data_ready == true)
        {
            split(line);
            
            if(strcmp(action, "left") == 0)
            {
                turnLeft(duration);
                Serial.println("Received left for duration: ");
                delay(20);
                Serial.println(duration);
            }
            else if(strcmp(action, "right") == 0)
            {
                turnRight(duration);
                Serial.println("Received right for duration: ");
                Serial.println(duration);
            }
            else if(strcmp(action, "straight") == 0)
            {
                straight(duration);
                Serial.println("Received straight for duration: ");
                Serial.println(duration);
            }
            
            memset(line, 0, 20);
            memset(action, 0, 10);
            duration = 0;
            data_ready = false;
        }
    }
}  

//Serial
void split(char input[20])
{
    char *param, *ptr;
    
    param = strtok_r(input, "#", &ptr);
    strncpy(action, param, sizeof(action));
    action[sizeof(action)-1] = '\0';
    
    param = strtok_r(NULL, "!", &ptr);
    duration = strtoul(param, &param, 10);
}

//Motor
void runRight(boolean dir, long duration)
{
    /*digitalWrite(right_dir, dir);
     tone(right, 1000, duration);*/
}

void runLeft(boolean dir, long duration)
{
     /*digitalWrite(left_dir, dir);
     tone(left, 1000, duration);*/
}

void turn(boolean direction, long startMillis, long duration)
{
     /*unsigned long currentMillis = millis();
     unsigned long previousMillis = startMillis;

     if(currentMillis - startMillis < duration)
     { 
       if(currentMillis - previousMillis > interval)
       {
         previousMillis = currentMillis;   
         if(run_state == LOW)
         {
           run_state = HIGH;
           runRight(direction, 10);
         }
         else
         {
           run_state = LOW;
           runLeft(!direction, 10);
         }
       }
     }*/
}

void turnRight(long duration)
{
  /*unsigned long startMillis = millis();
  turn(HIGH, startMillis, duration);*/  
  right.moveTo(duration);
  right.run();
}

void turnLeft(long duration)
{
  /*unsigned long startMillis = millis();
  turn(LOW, startMillis, duration);*/
  left.moveTo(duration);
  left.run();
}

void straight(long duration)
{
     /*unsigned long startMillis = millis();
     unsigned long currentMillis = millis();
     unsigned long previousMillis = startMillis;
     
     if(currentMillis - startMillis < duration)
     {
       if(currentMillis - previousMillis > interval)
       {
         previousMillis = currentMillis;   
         if(run_state == LOW)
         {
           run_state = HIGH;
           runRight(HIGH, 10);
         }
         else
         {
           run_state = LOW;
           runLeft(HIGH, 10);
         }
       }
     }*/
     left.moveTo(duration);
     right.moveTo(duration);
     left.run();
     right.run();     
}
