#include "nnxt.h"
#define TimerCount 16

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

#define TIMER_0 (uint8_t) 0
#define TIMER_1 (uint8_t) 1
#define TIMER_2 (uint8_t) 2

volatile uint16_t event = 0;
typedef uint8_t EventType;
typedef uint8_t TimerType;

void setEvent(EventType);
uint8_t eventIsSet(EventType);
void clearEvent(EventType);
uint16_t setBit(uint8_t, uint16_t, EventType);
uint8_t getBit(uint16_t, char);

void setTimer(TimerType, int, EventType);
void startTimer(TimerType);
void cancelTimer(TimerType);


typedef struct Timer{
    TimerType timer;
    int time;
    EventType ev;
    uint32_t sysTime;
    uint8_t timerActive; //0: inaktiv, 1: initialisiert, 2: aktiv
}Timer;

volatile Timer timers[TimerCount] = {0};

void Task1(){
    while(1){
        setTimer(TIMER_1, 5000, Event1);
        startTimer(TIMER_1);
        Delay(5000);
        setTimer(TIMER_2, 5000, Event2);
        startTimer(TIMER_2);
        Delay(100000);
    }
}

void Task2(){
    while(1){
        setTimer(TIMER_0, 5000, Event0);
        startTimer(TIMER_0);
        Delay(100000);
    }
}

void timerTask(){
    while(1){
        Delay(10);
        for(int i = 0; i < TimerCount; i++){
            if((GetSysTime() - timers[i].sysTime)>= timers[i].time && timers[i].timerActive == 2){
                setEvent(timers[i].ev);
                cancelTimer(timers[i].timer);
            }
        }
    }
}

void eventTask(){
    while(1){
        Delay(300);
        uint8_t event0 = eventIsSet(Event0);
        char msg[20];
        sprintf(msg, "Event0: %d ", event0);
        NNXT_LCD_DisplayStringAtLine(msg, 1);
        uint8_t event1 = eventIsSet(Event1);
        char msg1[20];
        sprintf(msg1, "Event1: %d ", event1);
        NNXT_LCD_DisplayStringAtLine(msg1, 2);
        uint8_t event2 = eventIsSet(Event2);
        char msg2[20];
        sprintf(msg2, "Event2: %d ", event2);
        NNXT_LCD_DisplayStringAtLine(msg2, 3);
    }
}


int main(){
    CreateAndStartTask(Task1);
    CreateAndStartTask(Task2);
    CreateAndStartTask(timerTask);
    CreateAndStartTask(eventTask);
    StartScheduler();
   	return 0;
}

void setTimer(TimerType t, int time, EventType timerEvent){
    for(int i = 0; i < TimerCount; i++){
        if(timers[i].timerActive == 0){
            taskENTER_CRITICAL();
            timers[i].timerActive = 1;
            timers[i].timer = t;
            timers[i].sysTime = 0;
            timers[i].ev = timerEvent;
            timers[i].time = time;
            taskEXIT_CRITICAL();
            break;
        }
    }
}

void startTimer(TimerType t){
    for(int i = 0; i < TimerCount; i++){
            if(timers[i].timer == t){
                taskENTER_CRITICAL();
                timers[i].timerActive = 2;
                timers[i].sysTime = GetSysTime();
                taskEXIT_CRITICAL();
                break;
            }
    }
}


void cancelTimer(TimerType t){
    for(int i = 0; i < TimerCount; i++){
        if(timers[i].timer == t){
                taskENTER_CRITICAL();
                timers[i].timerActive = 0;
                taskEXIT_CRITICAL();
        }
    }
}

void setEvent(EventType ev){
    taskENTER_CRITICAL();
    event = setBit(1, event, ev);
    taskEXIT_CRITICAL();
}

uint8_t eventIsSet(EventType ev){
    return getBit(event, ev);
}

void clearEvent(EventType ev){
    taskENTER_CRITICAL();
    event = setBit(0, event, ev);
    taskEXIT_CRITICAL();
}

uint16_t setBit(uint8_t value, uint16_t var, EventType ev){
    //fängt bei Index 0  an
    var = (var & ~(1UL << ev)) | (value << ev);
    return var;
}

uint8_t getBit(uint16_t var, char index){
    return ((var >> index) & 1);
}
