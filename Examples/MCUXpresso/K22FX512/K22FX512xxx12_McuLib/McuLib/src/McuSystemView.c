/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuSystemView.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : SeggerSystemView
**     Version     : Component 01.070, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-05-30, 10:44, # CodeGen: 534
**     Abstract    :
**          This component implements and integrates the SEGGER Systemview library for FreeRTOS.
**     Settings    :
**          Component name                                 : McuSystemView
**          Version                                        : V2.52b
**          Application Name                               : "Demo Application"
**          Device Name                                    : "Cortex"
**          RAM Base                                       : 0x20000000
**          ID Base                                        : 0x10000000
**          ID Shift                                       : 2
**          Number of tasks                                : 10
**          Static Buffer                                  : yes
**          Post Mortem                                    : no
**          Implicit Format for printf()                   : no
**          RTT Channel                                    : 
**            Segger RTT                                   : McuRTT
**            Name                                         : "SysView"
**            Channel Index                                : 1
**            Up Buffer size                               : 1024
**          SDK                                            : McuLib
**          Source Folders                                 : 
**            Source Folder                                : SEGGER_Sysview
**            Config Folder                                : SEGGER_Sysview
**     Contents    :
**         OnUserStart    - void McuSystemView_OnUserStart(unsigned UserId);
**         OnUserStop     - void McuSystemView_OnUserStop(unsigned UserId);
**         RecordEnterISR - void McuSystemView_RecordEnterISR(void);
**         RecordExitISR  - void McuSystemView_RecordExitISR(void);
**         Print          - void McuSystemView_Print(const char *s);
**         PrintfHost     - void McuSystemView_PrintfHost(const char *s, ...);
**         PrintfTarget   - void McuSystemView_PrintfTarget(const char *s, ...);
**         Warn           - void McuSystemView_Warn(const char *s);
**         WarnfHost      - void McuSystemView_WarnfHost(const char *s, ...);
**         WarnfTarget    - void McuSystemView_WarnfTarget(const char *s, ...);
**         Error          - void McuSystemView_Error(const char *s);
**         ErrorfHost     - void McuSystemView_ErrorfHost(const char *s, ...);
**         ErrorfTarget   - void McuSystemView_ErrorfTarget(const char *s, ...);
**         EnableEvents   - void McuSystemView_EnableEvents(uint32_t EnableMask);
**         DisableEvents  - void McuSystemView_DisableEvents(uint32_t DisableMask);
**         Deinit         - void McuSystemView_Deinit(void);
**         Init           - void McuSystemView_Init(void);
**
** * (c) Copyright Segger, 2019
**  * http      : www.segger.com
**  * See separate Segger licensing terms.
**  *
**  * Processor Expert port: Copyright (c) 2016-2019, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuSystemView.h
** @version 01.00
** @brief
**          This component implements and integrates the SEGGER Systemview library for FreeRTOS.
*/         
/*!
**  @addtogroup McuSystemView_module McuSystemView module documentation
**  @{
*/         

/* MODULE McuSystemView. */

#include "McuSystemView.h"

/*
** ===================================================================
**     Method      :  Init (component SeggerSystemView)
**
**     Description :
**         Driver Initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuSystemView_Init(void)
{
  SEGGER_SYSVIEW_Conf(); /* initialize Segger System Viewer */
}

/*
** ===================================================================
**     Method      :  OnUserStart (component SeggerSystemView)
**
**     Description :
**         Send a user event start, such as start of a subroutine for
**         profiling.
**     Parameters  :
**         NAME            - DESCRIPTION
**         UserId          - User defined ID for the event
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuSystemView_OnUserStart(unsigned UserId)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  OnUserStop (component SeggerSystemView)
**
**     Description :
**         Send a user event stop, such as return of a subroutine for
**         profiling.
**     Parameters  :
**         NAME            - DESCRIPTION
**         UserId          - User defined ID for the event
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuSystemView_OnUserStop(unsigned UserId)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  RecordEnterISR (component SeggerSystemView)
**
**     Description :
**         Records the enter of an ISR. Place this call at the
**         beginning of the interrupt service routine.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_RecordEnterISR(void)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  RecordExitISR (component SeggerSystemView)
**
**     Description :
**         Records the end of the ISR. Call this function at the end of
**         the ISR to be recorded.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_RecordExitISR(void)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  Print (component SeggerSystemView)
**
**     Description :
**         Prints a string to the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_Print(const char *s)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  Warn (component SeggerSystemView)
**
**     Description :
**         Prints a warning string to the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_Warn(const char *s)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  Error (component SeggerSystemView)
**
**     Description :
**         Prints an error string to the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_Error(const char *s)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  PrintfHost (component SeggerSystemView)
**
**     Description :
**         Prints a string using printf() to the host which is
**         processed on the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_PrintfHost(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  PrintfTarget (component SeggerSystemView)
**
**     Description :
**         Prints a string using printf() to the host which is
**         processed first on the target
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_PrintfTarget(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  WarnfHost (component SeggerSystemView)
**
**     Description :
**         Prints a warning string using printf() to the host which is
**         processed on the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_WarnfHost(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  WarnfTarget (component SeggerSystemView)
**
**     Description :
**         Prints a warning string using printf() to the host which is
**         processed first on the target
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_WarnfTarget(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  ErrorfHost (component SeggerSystemView)
**
**     Description :
**         Prints an error string using printf() to the host which is
**         processed on the host
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_ErrorfHost(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  ErrorfTarget (component SeggerSystemView)
**
**     Description :
**         Prints an error string using printf() to the host which is
**         processed first on the target
**     Parameters  :
**         NAME            - DESCRIPTION
**       * s               - Pointer to string
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_ErrorfTarget(const char *s, ...)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  DisableEvents (component SeggerSystemView)
**
**     Description :
**         Disable standard SystemView events to not be generated.
**     Parameters  :
**         NAME            - DESCRIPTION
**         DisableMask     - Events to be disabled.
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_DisableEvents(uint32_t DisableMask)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  EnableEvents (component SeggerSystemView)
**
**     Description :
**         Enables standard SystemView events to be generated.
**     Parameters  :
**         NAME            - DESCRIPTION
**         EnableMask      - Events to be enabled
**     Returns     : Nothing
** ===================================================================
*/
/*
void McuSystemView_EnableEvents(uint32_t EnableMask)
{
  Implemented as macro on the header file.
}
*/

/*
** ===================================================================
**     Method      :  Deinit (component SeggerSystemView)
**
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuSystemView_Deinit(void)
{
  /* nothing needed */
}

/* END McuSystemView. */

/*!
** @}
*/
