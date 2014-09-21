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
#include <ncurses.h>
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
void makeDisplay(void);

//int MAIN(int argc, char *argv[])
int MAIN(void)
{
    SystemTimerDevice * sysTimer = SystemTimer_Init();
    StopWatch * stopWatch = StopWatch_Init(sysTimer);

    char input = 5;

    //stopWatch->Start();
    initscr();
    refresh();
    //makeDisplay();


    while(1)
    {
	scanf("%d", &input);
	switch(input)
	{
	    case 0:
		printf("Thanks for playin', brah! \n");
		clear();
		refresh();
		sleep(3);
		endwin();
		return 0;
	    case 1:
		stopWatch->Start();
		//StopWatch_RenderTime();
		//printf("\nOption -> ");
		break;
	    case 2:
		stopWatch->Stop();
		//StopWatch_RenderTime();
		//printf("\nOption -> ");
		break;
	    case 3:
		stopWatch->Reset();
		//StopWatch_RenderTime();
		//printf("\nOption -> ");
		break;
	    case 4:
		StopWatch_RenderTime();
		//printf("\nOption -> ");
		break;
	}
	input = 5;
    }

    curs_set(1);
    clear();
    refresh();
    sleep(3);
    endwin();
    return 0;
}

void makeDisplay(void)
{
    //this should be moved.
    printw("Stopwatch Options \n");
    printw("0 -> quit \n");
    printw("1 -> start \n");
    printw("2 -> stop \n");
    printw("3 -> reset \n");
    printw("4 -> print time \n");
    printw("\nOption -> ");
    refresh();
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
