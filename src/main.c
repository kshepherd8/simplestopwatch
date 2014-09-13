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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "StopWatch.h"
#include "SysTimer.h"

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/

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
void testcb(void);

//int MAIN(int argc, char *argv[])
int MAIN(void)
{
    //printf("Stopwatch \n");

    SystemTimerDevice * sysTimer = SystemTimer_Init();
    //printf("sysTimer = %p \n", sysTimer);
    //StopWatch * stopWatch = StopWatch_Init(sysTimer);

    printf("about to start stopwatch \n");
    //stopWatch->Start();
    sysTimer->RegisterInterruptCallback(testcb);
    sysTimer->SetTimer(10);
    printf("stopwatch started \n");
    //StopWatch_RenderTime();

    while(1)
    {
	//StopWatch_RenderTime();
    }

    return 0;
}

void testcb(void)
{
    printf("testing \n");
}

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
