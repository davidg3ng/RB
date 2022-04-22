#include "nnxt.h"
#include <stdbool.h>

volatile bool leftPressed = false, rightPressed = false;

void task1(){
    while(1){
       sensor_touch_clicked_t touch, prevTouch;
       Delay(100);
       Touch_Clicked(Port_2, &touch);
       if(touch == SensorTouch_clicked && prevTouch == SensorTouch_released){
            leftPressed = true;
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
          rightPressed = true;
       }
       prevTouch = touch;
    }
}

void task3(){
    char msg[50];
    motor_dir_t direction = Motor_dir_forward;
    while(1){
        Delay(100);
        if(leftPressed){
            Motor_Drive(Port_A, direction, 35);
            Motor_Drive(Port_B, direction, 35);
            Delay(1000);
            Motor_Stop(Port_A, Motor_stop_float);
            Motor_Stop(Port_B, Motor_stop_float);
            leftPressed = false;
        }
        if(rightPressed){
          if(direction == Motor_dir_forward){
                direction = Motor_dir_backward;
          }else{
                direction = Motor_dir_forward;
          }
          sprintf(msg, "Richtung: %d", direction);
          NNXT_LCD_DisplayStringAtLine(1, msg);
          rightPressed = false;
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

    StartScheduler();

   	return 0;
}

