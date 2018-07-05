#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include "console.h"
#include "ftp.h"

#include <switch.h>

#include "util.h"

#define ERPT_SAVE_ID 0x80000000000000D1
#define TITLE_ID 0x4200000000000000
#define HEAP_SIZE 0x000640000

// we aren't an applet
u32 __nx_applet_type = AppletType_None;

// setup a fake heap (we don't need the heap anyway)
char fake_heap[HEAP_SIZE];

// we override libnx internals to do a minimal init
void __libnx_initheap(void)
{
    extern char *fake_heap_start;
    extern char *fake_heap_end;

    // setup newlib fake heap
    fake_heap_start = fake_heap;
    fake_heap_end = fake_heap + HEAP_SIZE;
}

void __appInit(void)
{
    Result rc;
    svcSleepThread(40000000000L);
    rc = smInitialize();
    if (R_FAILED(rc))
        fatalLater(rc);
    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalLater(rc);
    rc = fsdevMountSdmc();
    if (R_FAILED(rc))
        fatalLater(rc);
    rc = timeInitialize();
    if (R_FAILED(rc))
        fatalLater(rc);
}

void __appExit(void)
{
    fsdevUnmountAll();
    fsExit();
    smExit();
    audoutExit();
    timeExit();
}

static loop_status_t loop(loop_status_t (*callback)(void))
{
    loop_status_t status = LOOP_CONTINUE;

    while (appletMainLoop())
    {
        status = callback();
        console_render();
        if (status != LOOP_CONTINUE)
            return status;
        svcSleepThread(100000000L);
    }
    return LOOP_EXIT;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    mkdir("/logs", 0700);
    FILE *f = fopen("/logs/ftpd.log", "a");
    stdout = f;
    stderr = f;
    printf("---------------------------------\n");

    loop_status_t status = LOOP_RESTART;

    while (status == LOOP_RESTART)
    {
        /* initialize ftp subsystem */
        if (ftp_init() == 0)
        {
            /* ftp loop */
            status = loop(ftp_loop);

            /* done with ftp */
            ftp_exit();
        }
        else
            status = LOOP_EXIT;
    }

    printf("Done!\n");

    fclose(f);

    return 0;
}
