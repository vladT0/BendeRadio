#include "core1.h"

void core1(void *p)
{
    for(;;) { 	
        audio.loop();

        if (reconnect) {
            audio.connecttohost(reconnect);
            if (!audio.isRunning()) audio.pauseResume();
            reconnect = nullptr;
        }
    }
}
