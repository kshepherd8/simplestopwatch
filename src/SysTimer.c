/************************************************************************//**
 *
 * \file SysTimer.c
 *
 * \addtogroup SysTimer SysTimer
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author kjshepherd ()
 * \date 2014-09-10
 *
 ****************************************************************************/

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "SysTimer.h"
//#include "types.h"
#ifndef LINUX
#define LINUX
#endif
#include "CommonDefines.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

/****************************************************************************
 *                      PRIVATE TYPES and DEFINITIONS                       *
 ****************************************************************************/
#define MILLI_TO_NANO 1000000

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

/****************************************************************************
 *                              PRIVATE DATA                                *
 ****************************************************************************/
SystemTimerDevice Timer;
TimerInterrupt timerCallback = NULL;

/****************************************************************************
 *                             EXTERNAL DATA                                *
 ****************************************************************************/

/****************************************************************************
 *                     PRIVATE FUNCTION DECLARATIONS                        *
 ****************************************************************************/
void set_timer(long long millisecs);
void register_callback(TimerInterrupt cb);
void executeTimerCallback(int sig, siginfo_t *si, void *uc);

/****************************************************************************
 *                     EXPORTED FUNCTION DEFINITIONS                        *
 ****************************************************************************/
SystemTimerDevice * SystemTimer_Init(void)
{
    Timer.SetTimer = set_timer;
    Timer.RegisterInterruptCallback = register_callback;
    return &Timer;
}

/****************************************************************************
 *                     PRIVATE FUNCTION DEFINITIONS                         *
 ****************************************************************************/
void set_timer(long long millisecs)
{
    printf("set_timer called \n");

    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    long long freq_nanosecs;
    sigset_t mask;
    struct sigaction sa;

    /* Establish handler for timer signal */
    
    printf("Establishing handler for signal %d\n", SIG);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = executeTimerCallback; //give the signal handler our timer callback
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG, &sa, NULL) == -1)
	errExit("sigaction");
    
    /* Block timer signal temporarily */

    printf("Blocking signal %d\n", SIG);
    sigemptyset(&mask);
    sigaddset(&mask, SIG);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
	errExit("sigprocmask");

    /* Create the timer */

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCKID, &sev, &timerid) == -1)
	errExit("timer_create");

    printf("timer ID is 0x%ln\n", (long) timerid);
    
    /* Start the timer */

    freq_nanosecs = millisecs*(long long)MILLI_TO_NANO;
    printf("millisecs = %ld \n", millisecs);
    printf("MILLI_TO_NANO = %ld \n", MILLI_TO_NANO);
    printf("freq_nanosecs = %ld \n", freq_nanosecs);
    its.it_value.tv_sec = freq_nanosecs / 1000000000;
    //its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = freq_nanosecs % 1000000000;
    //its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    if (timer_settime(timerid, 0, &its, NULL) == -1)
	errExit("timer_settime");

    printf("Sleeping for %d seconds\n", 1);
    //sleep(1);

    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
	errExit("sigprocmask");
}

void register_callback(TimerInterrupt cb)
{
    timerCallback = cb;
}

void executeTimerCallback(int sig, siginfo_t *si, void *uc)
{
    timerCallback();
}

/************************************************************************//**
 * \brief
 * \param
 * \return
 ****************************************************************************/

/** \}*/
