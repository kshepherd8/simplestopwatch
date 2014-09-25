/************************************************************************//**
 *
 * \file main.c
 *
 * \addtogroup main main
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author kjshepherd ()
 * \date 2014-09-09
 *
 ****************************************************************************/

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "main.h"
#include "CommonDefines.h"
#include "StopWatch.h"
#include "SysTimer.h"
#include "LCDRenderer.h"

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define TIMEARRAYLENGTH 8
//error message

/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/
bool timeEqual(StopWatchTime * time1, StopWatchTime * time2);

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/
//int MAIN(int argc, char *argv[])
int MAIN(void)
{
    SystemTimerDevice * sysTimer = SystemTimer_Init();
    StopWatch * stopWatch = StopWatch_Init(sysTimer);
    LCDRenderer * lcd = LCDRenderer_Init();
    StopWatchTime lcdTime;
    StopWatchTime currentTime;

    int input = 5;

    while(1)
    {
	//TODO: keyboard input logic
	currentTime = StopWatch.GetTime();
	if(!timeEqual(&lcdTime, &currentTime))
	{
	    lcdTime = currentTime;
	    lcd->RenderTime(lcdTime);
	}
    }

    return 0;
}

/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/
bool timeEqual(StopWatchTime * time1, StopWatchTime * time2)
{
   int * time1array = (int *)time1;
   int * time2array = (int *)time2;
    
   return (memcmp(time1array, time2array, sizeof(int)*TIME_ARRAY_LEN) ? 1 : 0);

}

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
