/************************************************************************//**
 *
 * \file StopWatch.h
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

#ifndef _STOPWATCH_H
#define _STOPWATCH_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "CommonDefines.h"
#include "SysTimer.h"
#include "ClockDigit.h"

/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/
typedef enum
{
    STOPWATCH_UNITIALIZED,
    STOPWATCH_IDLE,
    STOPWATCH_RUNNING    
} StopwatchState;

typedef struct StopWatchTime
{
    int hour_high;
    int hour_low;
    int min_high;
    int min_low;
    int sec_high;
    int sec_low;
    int tenth;
    int hundredth;
} StopWatchTime;

typedef struct StopWatch
{
    StopwatchState state;
    void (*Start)(void);
    void (*Stop)(void);
    void (*Reset)(void);
    StopWatchTime (*GetTime)(void);
} StopWatch;

/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/
StopWatch * StopWatch_Init(SystemTimerDevice * tim);
void StopWatch_RenderTime(void);

#endif /* _STOPWATCH_H */

/** \}*/
