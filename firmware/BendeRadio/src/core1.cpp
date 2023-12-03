#include "driver/timer.h"
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
        TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
        TIMERG0.wdt_feed = 1;
        TIMERG0.wdt_wprotect = 0;
    }
}
