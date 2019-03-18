#pragma NOIV                    // Do not generate interrupt vectors
//-----------------------------------------------------------------------------
//   File:      tcxmaster.c
//   Contents:  Hooks required to implement USB peripheral function.
//              Code written for FX2 56-pin REVD...
//              This firmware is used to test the FX ext. master CY3682 DK
//   Copyright (c) 2001 Cypress Semiconductor All rights reserved
//-----------------------------------------------------------------------------
#include "fx2.h"
#include "fx2regs.h"
#include "fx2sdly.h"            // SYNCDELAY macro



extern BOOL GotSUD;             // Received setup data flag
extern BOOL Sleep;
extern BOOL Rwuen;
extern BOOL Selfpwr;




BYTE Configuration;             // Current configuration
BYTE AlternateSetting;          // Alternate settings

void TD_Init( void )
{ // Called once at startup
CPUCS = 0x10; // CLKSPD[1:0]=10, for 48 MHz operation
SYNCDELAY;


REVCTL=0x03;

// Registers which require a synchronization delay, see section 15.14
// FIFORESET FIFOPINPOLAR
// INPKTEND 
// EPxBCH:L REVCTL
// EPxFIFOPFH:L EPxAUTOINLENH:L
// EPxFIFOCFG 
// PINFLAGSxx 


#ifdef FREE
//IFCONFIG = 0x53;
IFCONFIG = 0x03; // IFCLK Source external (i.e.) connected to MPEG_CLK minimum should be 5 MHz
				 // Synchronous Mode, Free Running MPEG_CLK,  MPEG_VALID is used as SLWR strobe
				 // FX2LP in SLAVE FIFO Mode
SYNCDELAY;
#endif

#ifdef GATED
IFCONFIG = 0xCB; // IFCLK Source internal (i.e.) Gated MPEG_CLK,  MPEG_CLK is connected to SLWR
				 // FX2LP in SLAVE FIFO Mode
SYNCDELAY;
#endif



FIFORESET = 0x80; // activate NAK-ALL to avoid race conditions
SYNCDELAY; // see TRM section 15.14

FIFORESET = 0x82; // reset, FIFO 2
SYNCDELAY; //

FIFORESET = 0x84; // reset, FIFO 4
SYNCDELAY; //

FIFORESET = 0x86; // reset, FIFO 6
SYNCDELAY; //

FIFORESET = 0x88; // reset, FIFO 8
SYNCDELAY; //

FIFORESET = 0x00; // deactivate NAK-ALL
SYNCDELAY;

PINFLAGSAB = 0x00; //
SYNCDELAY;

PINFLAGSCD = 0x00; //
SYNCDELAY;

PORTACFG = 0x00; //
SYNCDELAY;

FIFOPINPOLAR = 0x04; // SLWR is configured as active HIGH : Can be changed to 0x00 for SLWR to be active Low
SYNCDELAY;

EP2CFG = 0xE0;   // VALID - 1,DIR - IN,Type- Bulk, Size - 512 Bytes, Quad Buffered 
SYNCDELAY;

EP4CFG = 0x00; // clear valid bit
SYNCDELAY; //

EP6CFG = 0x00;	 // clear valid bit
SYNCDELAY; //

EP8CFG = 0x00; // clear valid bit
SYNCDELAY;

EP2FIFOCFG = 0x08; // AUTO IN, NO Zero Length Packets, 8- bit Wide 
SYNCDELAY;

EP2AUTOINLENH = 0x02; // Auto-commit 512-byte packets
SYNCDELAY;

EP2AUTOINLENL = 0x00;
SYNCDELAY;


}
void TD_Poll( void )
{ // Called repeatedly while the device is idle
// nothing to do;slave fifo's are in AUTO mode
}

BOOL TD_Suspend( void )          
{ // Called before the device goes into suspend mode
   return( TRUE );
}

BOOL TD_Resume( void )          
{ // Called after the device resumes
   return( TRUE );
}

//-----------------------------------------------------------------------------
// Device Request hooks
//   The following hooks are called by the end point 0 device request parser.
//-----------------------------------------------------------------------------
BOOL DR_GetDescriptor( void )
{
   return( TRUE );
}

BOOL DR_SetConfiguration( void )   
{ // Called when a Set Configuration command is received
  
  if( EZUSB_HIGHSPEED( ) )
  { // ...FX2 in high speed mode

    EP2AUTOINLENH = 0x02;
    SYNCDELAY;
 
    
    EP2AUTOINLENL = 0x00;
    SYNCDELAY;


  }
  else
  { // ...FX2 in full speed mode

    EP2AUTOINLENH = 0x00;
    SYNCDELAY;

    
    EP2AUTOINLENL = 0x40;
    SYNCDELAY;
 
  }
      
  Configuration = SETUPDAT[ 2 ];
  return( TRUE );        // Handled by user code
}

BOOL DR_GetConfiguration( void )   
{ // Called when a Get Configuration command is received
   EP0BUF[ 0 ] = Configuration;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);          // Handled by user code
}

BOOL DR_SetInterface( void )       
{ // Called when a Set Interface command is received
   AlternateSetting = SETUPDAT[ 2 ];
   return( TRUE );        // Handled by user code
}

BOOL DR_GetInterface( void )       
{ // Called when a Set Interface command is received
   EP0BUF[ 0 ] = AlternateSetting;
   EP0BCH = 0;
   EP0BCL = 1;
   return( TRUE );        // Handled by user code
}

BOOL DR_GetStatus( void )
{
   return( TRUE );
}

BOOL DR_ClearFeature( void )
{
   return( TRUE );
}

BOOL DR_SetFeature( void )
{
   return( TRUE );
}

BOOL DR_VendorCmnd( void )
{
  return( TRUE );
}

//-----------------------------------------------------------------------------
// USB Interrupt Handlers
//   The following functions are called by the USB interrupt jump table.
//-----------------------------------------------------------------------------

// Setup Data Available Interrupt Handler
void ISR_Sudav( void ) interrupt 0
{
   GotSUD = TRUE;         // Set flag
   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmSUDAV;      // Clear SUDAV IRQ
}

// Setup Token Interrupt Handler
void ISR_Sutok( void ) interrupt 0
{
   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmSUTOK;      // Clear SUTOK IRQ
}

void ISR_Sof( void ) interrupt 0
{
   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmSOF;        // Clear SOF IRQ
}

void ISR_Ures( void ) interrupt 0
{
   if ( EZUSB_HIGHSPEED( ) )
   {
      pConfigDscr = pHighSpeedConfigDscr;
      pOtherConfigDscr = pFullSpeedConfigDscr;
   }
   else
   {
      pConfigDscr = pFullSpeedConfigDscr;
      pOtherConfigDscr = pHighSpeedConfigDscr;
   }
   
   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmURES;       // Clear URES IRQ
}

void ISR_Susp( void ) interrupt 0
{
   Sleep = TRUE;
   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmSUSP;
}

void ISR_Highspeed( void ) interrupt 0
{
   if ( EZUSB_HIGHSPEED( ) )
   {
      pConfigDscr = pHighSpeedConfigDscr;
      pOtherConfigDscr = pFullSpeedConfigDscr;
   }
   else
   {
      pConfigDscr = pFullSpeedConfigDscr;
      pOtherConfigDscr = pHighSpeedConfigDscr;
   }

   EZUSB_IRQ_CLEAR( );
   USBIRQ = bmHSGRANT;
}
void ISR_Ep0ack( void ) interrupt 0
{
}
void ISR_Stub( void ) interrupt 0
{
}
void ISR_Ep0in( void ) interrupt 0
{
}
void ISR_Ep0out( void ) interrupt 0
{
}
void ISR_Ep1in( void ) interrupt 0
{
}
void ISR_Ep1out( void ) interrupt 0
{
}
void ISR_Ep2inout( void ) interrupt 0
{
}
void ISR_Ep4inout( void ) interrupt 0
{
}
void ISR_Ep6inout( void ) interrupt 0
{
}
void ISR_Ep8inout( void ) interrupt 0
{
}
void ISR_Ibn( void ) interrupt 0
{
}
void ISR_Ep0pingnak( void ) interrupt 0
{
}
void ISR_Ep1pingnak( void ) interrupt 0
{
}
void ISR_Ep2pingnak( void ) interrupt 0
{
}
void ISR_Ep4pingnak( void ) interrupt 0
{
}
void ISR_Ep6pingnak( void ) interrupt 0
{
}
void ISR_Ep8pingnak( void ) interrupt 0
{
}
void ISR_Errorlimit( void ) interrupt 0
{
}
void ISR_Ep2piderror( void ) interrupt 0
{
}
void ISR_Ep4piderror( void ) interrupt 0
{
}
void ISR_Ep6piderror( void ) interrupt 0
{
}
void ISR_Ep8piderror( void ) interrupt 0
{
}
void ISR_Ep2pflag( void ) interrupt 0
{
}
void ISR_Ep4pflag( void ) interrupt 0
{
}
void ISR_Ep6pflag( void ) interrupt 0
{
}
void ISR_Ep8pflag( void ) interrupt 0
{
}
void ISR_Ep2eflag( void ) interrupt 0
{
}
void ISR_Ep4eflag( void ) interrupt 0
{
}
void ISR_Ep6eflag( void ) interrupt 0
{
}
void ISR_Ep8eflag( void ) interrupt 0
{
}
void ISR_Ep2fflag( void ) interrupt 0
{
}
void ISR_Ep4fflag( void ) interrupt 0
{
}
void ISR_Ep6fflag( void ) interrupt 0
{
}
void ISR_Ep8fflag( void ) interrupt 0
{
}
void ISR_GpifComplete( void ) interrupt 0
{
}
void ISR_GpifWaveform( void ) interrupt 0
{
}
