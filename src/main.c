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
void listOptions(void);

//int MAIN(int argc, char *argv[])
int MAIN(void)
{
    SystemTimerDevice * sysTimer = SystemTimer_Init();
    StopWatch * stopWatch = StopWatch_Init(sysTimer);

    char input = 5;

    //stopWatch->Start();
    listOptions();


    while(1)
    {
	scanf("%d", &input);
	switch(input)
	{
	    case 0:
		printf("Thanks for playin' brah! \n");
		return 0;
	    case 1:
		stopWatch->Start();
		StopWatch_RenderTime();
		printf("\nOption -> ");
		break;
	    case 2:
		stopWatch->Stop();
		StopWatch_RenderTime();
		printf("\nOption -> ");
		break;
	    case 3:
		stopWatch->Reset();
		StopWatch_RenderTime();
		printf("\nOption -> ");
		break;
	    case 4:
		StopWatch_RenderTime();
		printf("\nOption -> ");
		break;
	}
	input = 5;
    }

    return 0;
}

void listOptions(void)
{
    printf("Stopwatch Options \n");
    printf("0 -> quit \n");
    printf("1 -> start \n");
    printf("2 -> stop \n");
    printf("3 -> reset \n");
    printf("4 -> print time \n");
    printf("\nOption -> ");
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
