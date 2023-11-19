#ifndef _core0_h
#define _core0_h

#pragma once
#include <Arduino.h>
#include <Audio.h>
#include "config.h"

//MAX_SPI_SPEED must be defined before #include <GyverMAX7219.h>
//in other case it will be redifined to 1000000
#define MAX_SPI_SPEED 250000

struct Data {
    bool state = 0;
    int8_t vol = 10;
    int8_t bright_eyes = 5;
    int8_t bright_mouth = 2;
    uint16_t trsh = 50;
    uint8_t mode = 0;
    int8_t station = 0;
};

extern SemaphoreHandle_t  xMutex;
extern Audio audio;
extern const char* reconnect;

void change_state();
void anim_search();
void core0(void *p);

#endif