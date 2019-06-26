#include <string.h>
#include <switch.h>

#include "util.h"

void flash_led_connect()
{
    HidsysNotificationLedPattern pattern;
    memset(&pattern, 0, sizeof(pattern));

    pattern.baseMiniCycleDuration = 0x2;
    pattern.totalMiniCycles = 0x2;
    pattern.totalFullCycles = 0x1;
    pattern.startIntensity = 0x0;

    pattern.miniCycles[0].ledIntensity = 0xF;
    pattern.miniCycles[0].transitionSteps = 0xF;
    pattern.miniCycles[0].finalStepDuration = 0x0;
    pattern.miniCycles[1].ledIntensity = 0x0;
    pattern.miniCycles[1].transitionSteps = 0xF;
    pattern.miniCycles[1].finalStepDuration = 0x0;

    u64 uniquePadIds[2];
    memset(uniquePadIds, 0, sizeof(uniquePadIds));

    size_t total_entries = 0;

    Result rc = hidsysGetUniquePadsFromNpad(hidGetHandheldMode() ? CONTROLLER_HANDHELD : CONTROLLER_PLAYER_1, uniquePadIds, 2, &total_entries);
    if (R_FAILED(rc) && rc != MAKERESULT(Module_Libnx, LibnxError_IncompatSysVer))
        fatalLater(rc);

    for (int i = 0; i < total_entries; i++)
        hidsysSetNotificationLedPattern(&pattern, uniquePadIds[i]);
}
