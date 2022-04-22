#include "nnxt.h"


int main(){
    sensor_touch_clicked_t touch, before;
    char msg[40];
    uint16_t zeit = 0, zaehler = 0, durchschnitt = 0;
    uint32_t GetSysTime();
    SensorConfig(Port_0, SensorTouch);
    before = SensorTouch_released;
    while(1) {
       Delay(30);
       Touch_Clicked(Port_0, &touch);
       if (touch == SensorTouch_clicked && before == SensorTouch_released){
            zaehler++;
       }
       durchschnitt = ((int)zaehler / GetSysTime()) / 1000;
       sprintf(msg,"Klick/s:%d            ",(int)durchschnitt);
       NNXT_LCD_DisplayStringAtLine(0,msg);
       before = touch;
    }
   	return 0;
}

