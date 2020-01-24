/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuGenericSWI2C.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : GenericSWI2C
**     Version     : Component 01.025, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-04-25, 10:50, # CodeGen: 510
**     Abstract    :
**
**     Settings    :
**          Component name                                 : McuGenericSWI2C
**          Delay (ns)                                     : 1250
**          Trials                                         : 256
**          SDA                                            : SDK_BitIO
**          SCL                                            : SDK_BitIO
**          Wait                                           : McuWait
**          Yield                                          : no
**     Contents    :
**         ResetBus          - bool McuGenericSWI2C_ResetBus(void);
**         SendChar          - uint8_t McuGenericSWI2C_SendChar(uint8_t Chr);
**         RecvChar          - uint8_t McuGenericSWI2C_RecvChar(uint8_t *Chr);
**         SendBlock         - uint8_t McuGenericSWI2C_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt);
**         SendBlockContinue - uint8_t McuGenericSWI2C_SendBlockContinue(void *Ptr, uint16_t Siz, uint16_t...
**         RecvBlock         - uint8_t McuGenericSWI2C_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv);
**         RecvBlockCustom   - uint8_t McuGenericSWI2C_RecvBlockCustom(void *Ptr, uint16_t Siz, uint16_t...
**         SendAck           - void McuGenericSWI2C_SendAck(bool Ack);
**         SendStop          - uint8_t McuGenericSWI2C_SendStop(void);
**         SelectSlave       - uint8_t McuGenericSWI2C_SelectSlave(uint8_t Slv);
**         GetSelected       - uint8_t McuGenericSWI2C_GetSelected(uint8_t *Slv);
**         Deinit            - void McuGenericSWI2C_Deinit(void);
**         Init              - void McuGenericSWI2C_Init(void);
**
** * Copyright (c) 2014-2019, Erich Styger
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
** @file McuGenericSWI2C.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup McuGenericSWI2C_module McuGenericSWI2C module documentation
**  @{
*/         

/* MODULE McuGenericSWI2C. */

#include "McuGenericSWI2C.h"
#include "McuWait.h" /* waiting routines */
#include "McuLib.h" /* SDK defines */
#include "SDA1.h" /* SDA pin */
#include "SCL1.h" /* SCL pin */

#if McuLib_CONFIG_SDK_USE_FREERTOS
  /* include RTOS header files */
  #include "FreeRTOS.h" /* for yielding */
  #include "task.h"
#endif

#if McuLib_CONFIG_SDK_USE_FREERTOS && McuGenericSWI2C_CONFIG_DO_YIELD
  #define McuGenericSWI2C_OSYIELD() taskYIELD()
#else
  #define McuGenericSWI2C_OSYIELD() /* do nothing */
#endif

#define OUTPUT      1U
#define INPUT       0U
#define WRITE       0U
#define READ        1U

static uint8_t SlaveAddr;             /* destination slave address      */

#define SCL_SetDir(dir) SCL1_SetDir(dir)
#define SCL_ClrVal()    SCL1_ClrVal()
#define SCL_GetVal()    SCL1_GetVal()

#define SDA_SetDir(dir) SDA1_SetDir(dir)
#define SDA_ClrVal()    SDA1_ClrVal()
#define SDA_GetVal()    SDA1_GetVal()

#if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
  #define SCL_Init()      /* Init does not exist with Processor Expert API */
  #define SCL_Deinit()    /* Deinit does not exist with Processor Expert API */
  #define SDA_Init()      /* Init does not exist with Processor Expert API */
  #define SDA_Deinit()    /* Deinit does not exist with Processor Expert API */
#else
  #define SCL_Init()      SCL1_Init()
  #define SCL_Deinit()    SCL1_Deinit()
  #define SDA_Init()      SDA1_Init()
  #define SDA_Deinit()    SDA1_Deinit()
#endif

/* Internal method prototypes */
static void Delay(void);
static uint8_t Read(void);
static bool GetAck(void);
static void Write(uint8_t Data);
static void InternalStop(void);

/*
** ===================================================================
**     Method      :  Delay (component GenericSWI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void Delay(void)
{
  McuGenericSWI2C_OSYIELD();
  McuWait_Waitns(McuGenericSWI2C_CONFIG_DELAY_NS);
}

/*
** ===================================================================
**     Method      :  Write (component GenericSWI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void Write(uint8_t Data)
{
  uint8_t Shift;
  uint8_t I;
  uint16_t timeout;

  Shift = 0x80U;
  for (I = 0x08U; I != 0U; I--) {
    if (Data & Shift) {
      SDA_SetDir((bool)INPUT);   /* SDA HIGH */
    } else {
      SDA_SetDir((bool)OUTPUT);
      SDA_ClrVal();              /* SDA LOW */
    }
    Delay();
    Shift = (uint8_t)(Shift >> 1);
    SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
    Delay();
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SCL_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    Delay();
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
}

/*
** ===================================================================
**     Method      :  Read (component GenericSWI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static uint8_t Read(void)
{
  uint8_t Shift;
  uint8_t I;
  uint16_t timeout;

  Shift = 0U;
  SDA_SetDir((bool)INPUT);       /* SDA INPUT MODE */
  Delay(); /* give SDA setup time */
  for (I = 0x08U; I != 0U; I--) {
    SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
    Delay();
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SCL_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    Delay();
    Shift = (uint8_t)(Shift << 1);
    if (SDA_GetVal()) {
      Shift++;
    }
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
  return Shift;
}

/*
** ===================================================================
**     Method      :  GetAck (component GenericSWI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static bool GetAck(void)
{
  uint16_t timeout;

  SDA_SetDir((bool)INPUT);       /* SDA HIGH */
  Delay();
  SCL_SetDir((bool)INPUT);       /* CLOCK HIGH PULSE */
  Delay();
  timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
  while((SCL_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
    McuGenericSWI2C_OSYIELD();
  }
  return((bool)SDA_GetVal());    /* ACKNOWLEDGE VALUE */
}

/*
** ===================================================================
**     Method      :  SendAck (component GenericSWI2C)
**
**     Description :
**         The method sends ACK to the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ack             - If acknowledge is high or low
**     Returns     : Nothing
** ===================================================================
*/
void McuGenericSWI2C_SendAck(bool Ack)
{
  uint16_t timeout;

  Delay();
  if (Ack) {
    SDA_SetDir((bool)INPUT);     /* MASTER NOACKNOWLEDGE - SDA HIGH */
  } else {
    SDA_SetDir((bool)OUTPUT);
    SDA_ClrVal();                /* MASTER ACKNOWLEDGE - SDA LOW */
  }
  Delay();
  SCL_SetDir((bool)INPUT);       /* HIGH CLOCK PULSE */
  Delay();
  timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
  while((SCL_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
    McuGenericSWI2C_OSYIELD();
  }
  Delay();
  SCL_SetDir((bool)OUTPUT);
  SCL_ClrVal();                  /* LOW CLOCK PULSE */
  Delay();
  SDA_SetDir((bool)INPUT);       /* ACKNOWLEDGE END - SDA HIGH  */
  Delay();
}

/*
** ===================================================================
**     Method      :  InternalStop (component GenericSWI2C)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void InternalStop(void)
{
  Delay();
  SDA_SetDir((bool)OUTPUT);
  SDA_ClrVal();                  /* STOP SETUP */
  SCL_SetDir((bool)INPUT);       /* CLOCK HIGH PULSE + STOP SETUP TIME */
  Delay();
  SDA_SetDir((bool)INPUT);       /* STOP CONDITION */
  Delay();                       /* stop setup time to SCL low (which might follow) */
}

/*
** ===================================================================
**     Method      :  ResetBus (component GenericSWI2C)
**
**     Description :
**         Reset bus if needed.
**     Parameters  : None
**     Returns     :
**         ---             - TRUE if bus is idle, FALSE if bus is
**                           busy/hung
** ===================================================================
*/
bool McuGenericSWI2C_ResetBus(void)
{
  char i;

  if(SDA_GetVal() && SCL_GetVal()) {
    return TRUE;
  }
  SCL_SetDir((bool)INPUT);
  SDA_SetDir((bool)INPUT);
  Delay();
  if(!SCL_GetVal()) {
    return FALSE; /* SCL held low externally, nothing we can do */
  }
  for(i = 0; i<9; i++) { /* up to 9 clocks until SDA goes high */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();
    Delay();
    SCL_SetDir((bool)INPUT);
    Delay();
    if( SDA_GetVal()) {
      break; /* finally SDA high so we can generate a STOP */
    }
  } /* for */
  if(!SDA_GetVal()) {
    return FALSE; /* after 9 clocks still nothing */
  }
  InternalStop();
  return(SDA_GetVal() && SCL_GetVal()); /* both high then we succeeded */
}

/*
** ===================================================================
**     Method      :  SendChar (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 0 to the I2C bus and then writes one
**         character (byte) to the bus. The slave address must be
**         specified before by the "SelectSlave" method or in the
**         component initialization section of 'Slave address init'
**         property. When working as the SLAVE, this method writes one
**         character (byte) to the bus. If the ERR_NOTAVAIL error code
**         returned, the char is successfully sent to master but the
**         master device responds by an acknowledgment instead of no
**         acknowledgment at the end of transfer. 'OnError' event is
**         called in this case.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_NOTAVAIL - The master device sends
**                           acknowledgment instead of no acknowledgment
**                           after the last byte transfer (SLAVE mode
**                           only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_SendChar(uint8_t Chr)
{
  uint16_t Trial;
  bool Acknowledge;
  uint16_t timeout;

  Trial = McuGenericSWI2C_CONFIG_NOF_TRIALS;
  do {
    SDA_SetDir((bool)INPUT);     /* SDA HIGH - START SETUP*/
    SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
    Delay();                       /* CLOCK HIGH PULSE & BUS FREE TIME */
    /* check that we have a valid start condition: SDA needs to be high */
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    Delay();
    if (timeout==0) {
      InternalStop();
      return ERR_BUSY;
    }
    SDA_SetDir((bool)OUTPUT);
    SDA_ClrVal();                /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
    Write((uint8_t)(SlaveAddr + WRITE));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {               /* WRONG ACKNOWLEDGE */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  } else {
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
  Write(Chr);
  if (GetAck()) {                  /* WRONG ACKNOWLEDGE */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  } else {
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RecvChar (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 1 to the I2C bus and then reads one
**         character (byte) from the bus. The slave address must be
**         specified before by the "SelectSlave" method or in the
**         component initialization section of 'Slave address init'
**         property. When working as a SLAVE, this method reads one
**         character (byte) from the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_RecvChar(uint8_t *Chr)
{
  uint16_t Trial;
  bool Acknowledge;
  uint16_t timeout;

  Trial = McuGenericSWI2C_CONFIG_NOF_TRIALS;
  do {
    SDA_SetDir((bool)INPUT);     /* SDA HIGH - START SETUP */
    SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
    Delay();                     /* CLOCK HIGH PULSE & BUS FREE TIME */
    /* check that we have a valid start condition: SDA needs to be high */
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    Delay();
    if (timeout==0) {
      InternalStop();
      return ERR_BUSY;
    }
    SDA_SetDir((bool)OUTPUT);
    SDA_ClrVal();                /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
    Write((uint8_t)(SlaveAddr + READ));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  } else {
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
  *Chr = Read();
  McuGenericSWI2C_SendAck((bool)McuGenericSWI2C_NOACK);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SendBlock (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. If the component is disabled
**         (by the "Disable" method or initialization), the block is
**         moved to the output buffer if the 'Output buffer size'
**         property is different from zero. The content of the output
**         buffer is sent immediately with the stop condition at the
**         end when the component is enabled by the "Enable" method.
**         After the output buffer transmission, the whole output
**         buffer is cleared. The slave address must be specified
**         before by the "SelectSlave" method or in component
**         initialization section of 'Slave address init' property.
**         When working as a SLAVE, this method writes block of
**         characters to the bus. If the ERR_NOTAVAIL error code is
**         returned, the whole block is successfully sent to a master
**         but the master device responds by an acknowledgment instead
**         of no acknowledgment sent at the end of the last block byte
**         transfer. 'OnError' event is called in this case.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block of data to send
**         Siz             - The size of the block
**       * Snt             - A pointer to the number of data that are
**                           sent (copied to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_TXFULL - Output buffer is full (MASTER
**                           mode only)
**                           ERR_NOTAVAIL - The master device sends
**                           acknowledgment instead of no acknowledgment
**                           after the last byte transfer (SLAVE mode
**                           only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_SendBlock(void *Ptr, uint16_t Siz, uint16_t *Snt)
{
  register uint16_t I;
  bool Acknowledge;
  uint16_t Trial;
  uint16_t timeout;

  *Snt = 0U;
  Trial = McuGenericSWI2C_CONFIG_NOF_TRIALS;
  do {
    SDA_SetDir((bool)INPUT);     /* SDA HIGH  - START SETUP */
    SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
    Delay();                     /* CLOCK HIGH PULSE + BUS FREE TIME */
    /* check that we have a valid start condition: SDA needs to be high */
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    Delay();
    if (timeout==0) {
      return ERR_BUSY;
    }
    SDA_SetDir((bool)OUTPUT);
    SDA_ClrVal();                /* START CONDITION */
    Delay();                     /* START HOLD TIME */
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
    Write((uint8_t)(SlaveAddr + WRITE));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {
    return ERR_BUSY;
  } else {
    SCL_SetDir((bool)OUTPUT);
    SCL_ClrVal();                /* CLOCK LOW PULSE */
    Delay();
  }
  for (I = 0U; I < Siz; I++) {
    Write (*((const uint8_t*)Ptr + I) );
    if (GetAck()) {
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();              /* CLOCK LOW PULSE */
      InternalStop();
      return ERR_BUSY;
    } else {
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();              /* CLOCK LOW PULSE */
      Delay();
    }
    ++(*Snt);
  }
  Delay();
  timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
  while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
    McuGenericSWI2C_OSYIELD();
  }
  if (timeout==0) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SendBlockContinue (component GenericSWI2C)
**
**     Description :
**         Same is SendBlock() but does not send start condition. When
**         working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. If the component is disabled
**         (by the "Disable" method or initialization), the block is
**         moved to the output buffer if the 'Output buffer size'
**         property is different from zero. The content of the output
**         buffer is sent immediately with the stop condition at the
**         end when the component is enabled by the "Enable" method.
**         After the output buffer transmission, the whole output
**         buffer is cleared. The slave address must be specified
**         before by the "SelectSlave" method or in component
**         initialization section of 'Slave address init' property.
**         When working as a SLAVE, this method writes block of
**         characters to the bus. If the ERR_NOTAVAIL error code is
**         returned, the whole block is successfully sent to a master
**         but the master device responds by an acknowledgment instead
**         of no acknowledgment sent at the end of the last block byte
**         transfer. 'OnError' event is called in this case.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block of data to send
**         Siz             - The size of the block
**       * Snt             - A pointer to the number of data that are
**                           sent (copied to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_TXFULL - Output buffer is full (MASTER
**                           mode only)
**                           ERR_NOTAVAIL - The master device sends
**                           acknowledgment instead of no acknowledgment
**                           after the last byte transfer (SLAVE mode
**                           only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_SendBlockContinue(void *Ptr, uint16_t Siz, uint16_t *Snt)
{
  register uint16_t I;
  uint16_t timeout;

  *Snt = 0U;
  for (I = 0U; I < Siz; I++) {
    Write (*((const uint8_t*)Ptr + I) );
    if (GetAck()) {
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();              /* CLOCK LOW PULSE */
      InternalStop();
      return ERR_BUSY;
    } else {
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();              /* CLOCK LOW PULSE */
      Delay();
    }
    ++(*Snt);
  }
  Delay();
  timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
  while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
    McuGenericSWI2C_OSYIELD();
  }
  if (timeout==0) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RecvBlockCustom (component GenericSWI2C)
**
**     Description :
**         Same as RecvBlock(), but with additional flags to control
**         the bus transfer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data
**         Siz             - The size of the block
**       * Rcv             - A pointer to the number of actually
**                           received data
**         flagsStart      - Flags for start condition
**         flagsAck        - Flags for Ack after last byte
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_RecvBlockCustom(void *Ptr, uint16_t Siz, uint16_t *Rcv, McuGenericSWI2C_EnumStartFlags flagsStart, McuGenericSWI2C_EnumAckFlags flagsAck)
{
  register uint16_t I;
  bool Acknowledge;
  uint16_t Trial;
  uint16_t timeout;

  *Rcv = 0U;
  Trial = McuGenericSWI2C_CONFIG_NOF_TRIALS;
  if (flagsStart == McuGenericSWI2C_SEND_START) {
    do {
      SDA_SetDir((bool)INPUT);     /* SDA HIGH - START SETUP */
      SCL_SetDir((bool)INPUT);     /* CLOCK HIGH PULSE */
      Delay();                     /* CLOCK HIGH PULSE + BUS FREE TIME */
      /* check that we have a valid start condition: SDA needs to be high */
      timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
      while((SDA_GetVal()==0U) && (timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
        timeout--;
        McuGenericSWI2C_OSYIELD();
      }
      Delay();
      if (timeout==0) {
        /* InternalStop(); */
        return ERR_BUSY;
      }
      SDA_SetDir((bool)OUTPUT);
      SDA_ClrVal();                /* START CONDITION */
      Delay();                     /* START HOLD TIME */
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();                /* CLOCK LOW PULSE */
      Delay();
      Write((uint8_t)(SlaveAddr + READ));
      Acknowledge = GetAck();
      --Trial;
    } while ((Trial != 0U) && Acknowledge);
    if (Acknowledge) {
      /* SCL_SetDir((bool)OUTPUT); */
      /* SCL_ClrVal(); */               /* CLOCK LOW PULSE */
      /* InternalStop(); */
      return ERR_BUSY;
    } else {
      SCL_SetDir((bool)OUTPUT);
      SCL_ClrVal();                /* CLOCK LOW PULSE */
      Delay();
    }
  } /* McuGenericSWI2C_SEND_START */
  for (I = 0U; I < Siz; I++) {
    *((uint8_t *)Ptr + I) = Read();
    timeout = McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE;
    while((SDA_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
      McuGenericSWI2C_OSYIELD();
    }
    if (timeout==0) {
      /* InternalStop(); */
      return ERR_BUSY;
    }
    if (I == (Siz - 1U)) {
      if(flagsAck == McuGenericSWI2C_SEND_LAST_ACK){
        McuGenericSWI2C_SendAck((bool)McuGenericSWI2C_NOACK);
      }
    } else {
      McuGenericSWI2C_SendAck((bool)McuGenericSWI2C_ACK);
    }
    ++(*Rcv);
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RecvBlock (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 1 to the I2C bus and then reads the
**         block of characters from the bus. The slave address must be
**         specified before by the "SelectSlave" method or in component
**         initialization section of 'Slave address init' property.
**         When working as a SLAVE, this method reads the block of
**         characters from the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data
**         Siz             - The size of the block
**       * Rcv             - A pointer to the number of actually
**                           received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgment
**                           (MASTER mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
uint8_t McuGenericSWI2C_RecvBlock(void *Ptr, uint16_t Siz, uint16_t *Rcv)
{
  return McuGenericSWI2C_RecvBlockCustom(Ptr, Siz, Rcv, McuGenericSWI2C_SEND_START, McuGenericSWI2C_SEND_LAST_ACK);
}

/*
** ===================================================================
**     Method      :  SendStop (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, if the 'Automatic stop condition'
**         property value is 'no', this method sends a valid stop
**         condition to the serial data line of the I2C bus to
**         terminate the communication on the bus after using send
**         methods. This method is enabled only if the component is in
**         MASTER mode and 'Automatic stop condition' property value is
**         'no'
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
** ===================================================================
*/
uint8_t McuGenericSWI2C_SendStop(void)
{
  Delay();
  SDA_SetDir((bool)OUTPUT);
  SDA_ClrVal();                  /* STOP SETUP */
  Delay();
  SCL_SetDir((bool)INPUT);       /* HIGH CLOCK PULSE + STOP SETUP TIME */
  Delay();
  SDA_SetDir((bool)INPUT);       /* STOP CONDITION */
  Delay(); /* add stop time */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SelectSlave (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method selects a new slave
**         for communication by its slave address value. Any send or
**         receive method are directed to or from the selected device,
**         until a new slave device is selected by this method. If the
**         selected slave uses 10-bit slave addressing, as the
**         parameter 7 bits must be passed, which involves 10-bit
**         addressing (11110XX), including two MSBs of slave address
**         (XX). The second byte of the 10-bit slave address must be
**         sent to the slave as a general character of send methods.
**         This method is available only if the component is in MASTER
**         mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Slv             - Slave address value
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
** ===================================================================
*/
uint8_t McuGenericSWI2C_SelectSlave(uint8_t Slv)
{
  SlaveAddr = (uint8_t)(Slv<<1);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  GetSelected (component GenericSWI2C)
**
**     Description :
**         When working as a MASTER, this method returns the
**         identification address value of the slave, which is
**         currently selected for communication with the master. If the
**         current slave uses 10-bit slave addressing, the method
**         returns the first 7 bits only, which involves 10-bit
**         addressing (11110XX), including two MSBs of the slave
**         address (XX). This method is not able to return the rest
**         value of 10-bit slave address. This method is available only
**         if the component is in MASTER mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Slv             - A pointer to the current selected slave
**                           address value
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
uint8_t McuGenericSWI2C_GetSelected(uint8_t *Slv)
{
  *Slv = (uint8_t)(SlaveAddr>>1);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Init (component GenericSWI2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the components
**         internal variables.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuGenericSWI2C_Init(void)
{
  SlaveAddr = 0;
  SDA_Init();
  SCL_Init();
}

/*
** ===================================================================
**     Method      :  Deinit (component GenericSWI2C)
**
**     Description :
**         Driver de-initialization method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuGenericSWI2C_Deinit(void)
{
  SCL_Deinit();
  SDA_Deinit();
  SlaveAddr = 0;
}

/* END McuGenericSWI2C. */

/*!
** @}
*/
