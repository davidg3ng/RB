#include "nnxt.h"


int main(){

    MotorPortInit(Port_A);
    MotorPortInit(Port_B);

    while(1){
        Motor_Drive(Port_A, Motor_dir_forward, 35);
        Motor_Drive(Port_B, Motor_dir_forward, 35);

        Delay(1000);

        Motor_Stop(Port_A, Motor_stop_float);
        Motor_Stop(Port_B, Motor_stop_float);

        Delay(1000);

        Motor_Drive(Port_A, Motor_dir_backward, 35);
        Motor_Drive(Port_B, Motor_dir_backward, 35);

        Delay(1000);

        Motor_Stop(Port_A, Motor_stop_float);
        Motor_Stop(Port_B, Motor_stop_float);

        Delay(1000);
    }

   	return 0;
}

