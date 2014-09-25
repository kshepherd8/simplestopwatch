/************************************************************************//**
 *
 * \file LCDRenderer.h
 *
 * \addtogroup LCDRenderer LCDRenderer
 * \{
 *
 * \brief
 *
 * \note
 *
 * \author jlockett & kshep (CIS541)
 * \date 2014-09-25
 *
 ****************************************************************************/

#ifndef _LCDRENDERER_H
#define _LCDRENDERER_H

/****************************************************************************
 *                              INCLUDE FILES                               *
 ****************************************************************************/
#include "StopWatch.h"

/****************************************************************************
 *                     EXPORTED TYPES and DEFINITIONS                       *
 ****************************************************************************/

typedef struct
{
    void (* RenderTime)(StopWatchTime);
    void (* RenderText)(void *);

} LCDRenderer;

/****************************************************************************
 *                              EXPORTED DATA                               *
 ****************************************************************************/

/****************************************************************************
 *                     EXPORTED FUNCTION DECLARATIONS                       *
 ****************************************************************************/
LCDRenderer * LCDRenderer_Init(void);

#endif /* _LCDRENDERER_H */

/** \}*/
