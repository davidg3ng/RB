#include "nnxt.h"

//Port A: rechts
//Port B: links
int main(){

    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    int i = 1;

    while(1){
    /*TEILAUFGABE A
        Motor_Drive(Port_A, Motor_dir_forward, 35);
        Motor_Drive(Port_B, Motor_dir_forward, 35);
        Delay(1000);
        Motor_Stop(Port_A, Motor_stop_break);
        Motor_Stop(Port_B, Motor_stop_break);
        Delay(500);
        Motor_Drive(Port_A, Motor_dir_backward, 35);
        Motor_Drive(Port_B, Motor_dir_forward, 35);
        Delay(1000);*/
    /*TEILAUFGABE B */
        for(int j = 0; j < 2; j++){
            Motor_Drive(Port_A, Motor_dir_forward, 35);
            Motor_Drive(Port_B, Motor_dir_forward, 35);
            Delay(500 * i);
            Motor_Stop(Port_A, Motor_stop_break);
            Motor_Stop(Port_B, Motor_stop_break);
            Delay(500);
            Motor_Drive(Port_A, Motor_dir_backward, 35);
            Motor_Drive(Port_B, Motor_dir_forward, 35);
            Delay(1000);
        }
        i++;

    }

   	return 0;
}

