#include "nnxt.h"


//0 <= x <= 15
#define Event0 (uint8_t) 0
#define Event1 (uint8_t) 1
#define Event2 (uint8_t) 2
#define Event3 (uint8_t) 3
#define Event4 (uint8_t) 4
#define Event5 (uint8_t) 5
#define Event6 (uint8_t) 6
#define Event7 (uint8_t) 7
#define Event8 (uint8_t) 8

volatile uint16_t event = 0;
typedef uint8_t EventType;

void setEvent(EventType);
uint8_t eventIsSet(EventType);
void clearEvent(EventType);
uint16_t setBit(uint8_t, uint16_t, EventType);
uint8_t getBit(uint16_t, char);


void Task1(){
    char msg[20];
    while(1){
        setEvent(Event0);
        sprintf(msg, "Zahl:%d         ",(int)event);
        NNXT_LCD_DisplayStringAtLine(0, msg);
        Delay(3000);
        setEvent(Event3);
        sprintf(msg, "Zahl:%d         ",(int)event);
        NNXT_LCD_DisplayStringAtLine(0, msg);
        Delay(3000);
        setEvent(Event5);
        sprintf(msg, "Zahl:%d         ",(int)event);
        NNXT_LCD_DisplayStringAtLine(0, msg);
        Delay(3000);
        if(eventIsSet(event5)){
                clearEvent(Event5);
                sprintf(msg, "Zahl:%d         ",(int)event);
                NNXT_LCD_DisplayStringAtLine(0, msg);
        }
    }
}


int main(){
    CreateAndStartTask(Task1);
    StartScheduler();
   	return 0;
}


void setEvent(EventType ev){
    taskENTER_CRITCAL();
    event = setBit(1, event, ev);
    taskEXIT_CRITCAL();
}

uint8_t eventIsSet(EventType ev){
    return getBit(event, ev);
}

void clearEvent(EventType ev){
    taskENTER_CRITCAL();
    event = setBit(0, event, ev);
    taskEXIT_CRITCAL();
}

uint16_t setBit(uint8_t value, uint16_t var, EventType ev){
    //fängt bei Index 0  an
    var = (var & ~(1UL << ev)) | (value << ev);
    return var;
}

uint8_t getBit(uint16_t var, char index){
    return ((var >> index) & 1);
}
