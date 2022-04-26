#include "nnxt.h"
#include <stdbool.h>
#include "events.h"
#define rightPressed Event0
#define leftPressed Event1
#define eventTimer1s Event2

#define Timer1s TIMER_0



//volatile bool leftPressed = false, rightPressed = false;
volatile motor_dir_t direction = Motor_dir_forward;
void task1(){
    while(1){
       sensor_touch_clicked_t touch, prevTouch;
       Delay(100);
       Touch_Clicked(Port_2, &touch);
       if(touch == SensorTouch_clicked && prevTouch == SensorTouch_released){
            //leftPressed = true;
            setEvent(leftPressed);
       }
       prevTouch = touch;
    }
}


void task2(){
    sensor_touch_clicked_t touch, prevTouch;
    while(1){
       Delay(100);
       Touch_Clicked(Port_0, &touch);
       if (touch == SensorTouch_clicked && prevTouch == SensorTouch_released){
          //rightPressed = true;
          setEvent(rightPressed);
       }
       prevTouch = touch;
    }
}

void task3(){
    setTimer(Timer1s, 1000, eventTimer1s);  //läuft ab letztem Tasterdruck
    char msg[50];

    while(1){
        Delay(100);
        if(eventIsSet(eventTimer1s)){
            Motor_Stop(Port_A, Motor_stop_float);
            Motor_Stop(Port_B, Motor_stop_float);
            clearEvent(eventTimer1s);
        }
        if(eventIsSet(leftPressed)){
            startTimer(Timer1s);
            Motor_Drive(Port_A, direction, 35);
            Motor_Drive(Port_B, direction, 35);
            clearEvent(leftPressed);
        }
        if(eventIsSet(rightPressed)){
          if(direction == Motor_dir_forward){
                direction = Motor_dir_backward;
          }else{
                direction = Motor_dir_forward;
          }
          sprintf(msg, "Richtung: %d", direction);
          NNXT_LCD_DisplayStringAtLine(1, msg);
          clearEvent(rightPressed);
        }
    }
}
//Taster links = 2
//Taster rechts = 0
int main(){


    SensorConfig(Port_0, SensorTouch);
    SensorConfig(Port_2, SensorTouch);
    MotorPortInit(Port_A);
    MotorPortInit(Port_B);

    CreateAndStartTask(task1);
    CreateAndStartTask(task2);
    CreateAndStartTask(task3);

    CreateAndStartTask(timerTask);

    StartScheduler();

   	return 0;
}
