/************************************************************************//**
 *
 * \file StopWatch.c
 *
 * \addtogroup StopWatch StopWatch
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author kjshepherd ()
 * \date 2014-09-08
 *
 ****************************************************************************/

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "StopWatch.h"
#include <ncurses.h>

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define NUM_SEGMENTS 8

#define TEN_MS 10
#define STOP_TIMER 0

ClockSegment HUNDREDTH_SEG;
ClockSegment TENTH_SEG;
ClockSegment SEC_SEG;
ClockSegment TENSEC_SEG;
ClockSegment MINUTE_SEG;
ClockSegment TENMINUTE_SEG;
ClockSegment HOUR_SEG;
ClockSegment TENHOUR_SEG;

/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/
static StopWatch Watch;
static SystemTimerDevice * Timer;

/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/
void start_clock(void);
void stop_clock(void);
void reset_clock(void);
StopWatchTime current_time(void);

void incrementSegment(ClockSegment * seg);
TimerInterrupt clockTick(void);

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/
StopWatch * StopWatch_Init(SystemTimerDevice * tim)
{
    //create a new screen 
    initscr();
    refresh();

    //save a pointer to the source timer
    Timer = tim;

    //register the timer interrupt
    Timer->RegisterInterruptCallback(clockTick);

    //give Watch the correct handler functions
    Watch.Start = start_clock;
    Watch.Stop = stop_clock;
    Watch.Reset = reset_clock;
    Watch.GetTime = current_time;

    Watch.state = STOPWATCH_NOT_STARTED;

    //build the clock segments
    HUNDREDTH_SEG.rollover = 10;
    HUNDREDTH_SEG.currentValue = 0;
    HUNDREDTH_SEG.nextSegment = &TENTH_SEG;
    HUNDREDTH_SEG.prevSegment = NULL;

    TENTH_SEG.rollover = 10;
    TENTH_SEG.currentValue = 0;
    TENTH_SEG.nextSegment = &SEC_SEG;
    TENTH_SEG.prevSegment = &HUNDREDTH_SEG;

    SEC_SEG.rollover = 10;
    SEC_SEG.currentValue = 0;
    SEC_SEG.nextSegment = &TENSEC_SEG;
    SEC_SEG.prevSegment = &TENTH_SEG;

    TENSEC_SEG.rollover = 6;
    TENSEC_SEG.currentValue = 0;
    TENSEC_SEG.nextSegment = &MINUTE_SEG;
    TENSEC_SEG.prevSegment = &SEC_SEG;

    MINUTE_SEG.rollover = 10;
    MINUTE_SEG.currentValue = 0;
    MINUTE_SEG.nextSegment = &TENMINUTE_SEG;
    MINUTE_SEG.prevSegment = &TENSEC_SEG;

    TENMINUTE_SEG.rollover = 6;
    TENMINUTE_SEG.currentValue = 0;
    TENMINUTE_SEG.nextSegment = &HOUR_SEG;
    TENMINUTE_SEG.prevSegment = &MINUTE_SEG;

    HOUR_SEG.rollover = 10;
    HOUR_SEG.currentValue = 0;
    HOUR_SEG.nextSegment = &TENHOUR_SEG;
    HOUR_SEG.prevSegment = &TENMINUTE_SEG;

    TENHOUR_SEG.rollover = 2;
    TENHOUR_SEG.currentValue = 0;
    TENHOUR_SEG.nextSegment = NULL;
    TENHOUR_SEG.prevSegment = &HOUR_SEG;

    StopWatch_RenderTime();

    return &Watch;
}

void StopWatch_RenderTime(void)
{
    clear();
    printw("%d%d:%d%d:%d%d.%d%d \n", TENHOUR_SEG.currentValue,
	    HOUR_SEG.currentValue, TENMINUTE_SEG.currentValue,
	    MINUTE_SEG.currentValue, TENSEC_SEG.currentValue,
	    SEC_SEG.currentValue, TENTH_SEG.currentValue,
	    HUNDREDTH_SEG.currentValue);
    printw("\nStopwatch Options \n");
    printw("0 -> quit \n");
    printw("1 -> start \n");
    printw("2 -> stop \n");
    printw("3 -> reset \n");
    printw("4 -> print time \n");
    printw("\nOption -> ");
    refresh();
}

/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/
void start_clock(void)
{
    if(STOPWATCH_NOT_STARTED == Watch.state)
    {
	Timer->SetTimer(TEN_MS);
    }
    Watch.state = STOPWATCH_RUNNING;
}

void stop_clock(void)
{
    Watch.state = STOPWATCH_IDLE;
    Timer->SetTimer(0);
}

void reset_clock(void)
{
    HOUR_SEG.rollover = 10;

    HUNDREDTH_SEG.currentValue = 0;
    TENTH_SEG.currentValue = 0;
    SEC_SEG.currentValue = 0;
    TENSEC_SEG.currentValue = 0;
    MINUTE_SEG.currentValue = 0;
    TENMINUTE_SEG.currentValue = 0;
    HOUR_SEG.currentValue = 0;
    TENHOUR_SEG.currentValue = 0;

    StopWatch_RenderTime();
    
}

//not actually used
StopWatchTime current_time(void)
{
    StopWatchTime time;

    return time;
}

void incrementSegment(ClockSegment * seg)
{
    seg->currentValue = seg->currentValue + 1;
    if(seg->currentValue == seg->rollover)
    {
	seg->currentValue = 0;
    }

    if(0 == seg->currentValue && seg->nextSegment != NULL)
    {
	incrementSegment((ClockSegment *)(seg->nextSegment));
    }

	switch(TENHOUR_SEG.currentValue)
	{
	    case 0:
		HOUR_SEG.rollover = 10;
		break;
	    case 1:
		HOUR_SEG.rollover = 2;
		break;
	}
    
}

TimerInterrupt clockTick(void)
{
    if(Watch.state == STOPWATCH_RUNNING)
    {
	incrementSegment(&HUNDREDTH_SEG);
	StopWatch_RenderTime();
    }
}

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
