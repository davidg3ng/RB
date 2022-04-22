#include "nnxt.h"

void detektiereObjekt(uint8_t *);

int main(){

    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    SensorConfig(Port_1, SensorUS);
    uint8_t dist = 0;

    while(1){
        detektiereObjekt(&dist);
        if(dist < 20){
            Motor_Stop(Port_A, Motor_stop_break);
            Motor_Stop(Port_B, Motor_stop_break);
            Delay(500);
            Motor_Drive(Port_A, Motor_dir_backward, 35);
            Motor_Drive(Port_B, Motor_dir_forward, 35);
            Delay(1000);
        }
        else{
            Motor_Drive(Port_A, Motor_dir_forward, 35);
            Motor_Drive(Port_B, Motor_dir_forward, 35);
            Delay(500);
        }
    }

   	return 0;
}

void detektiereObjekt(uint8_t * dist){
    sensor_error_t err;

    char distStr[20];

    err = US_GetDistance(Port_1, dist);
    if (err!=sensor_error_NoError){
        NNXT_LCD_DisplayStringAtLine(0, "Sensor Error!!!!   ");
    } else {
        sprintf(distStr, "Entfernung:%d   ",(int)(*dist));
        NNXT_LCD_DisplayStringAtLine(0, distStr);
    }
}

