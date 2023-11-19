#ifndef _core1_h
#define _core1_h

#pragma once
#include <Arduino.h>
#include <Audio.h>

extern Audio audio;
extern const char* reconnect;

void core1(void *p);

#endif