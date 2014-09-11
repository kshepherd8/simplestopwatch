/************************************************************************//**
 *
 * \file SysTimer.h
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

#ifndef _SYSTIMER_H
#define _SYSTIMER_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/
typedef void (*TimerInterrupt)(void);

typedef struct SystemTimerDevice
{
    void (*SetTimer)(double);
    void (*RegisterInterruptCallback)(TimerInterrupt);
} SystemTimerDevice;

/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/
SystemTimerDevice * SystemTimer_Init();


#endif /* _SYSTIMER_H */

/** \}*/
