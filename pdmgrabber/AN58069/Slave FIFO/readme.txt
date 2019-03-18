This directory contains 8051 firmware for the Cypress Semiconductor EZ-USB FX2 
chip.

The purpose of this code is to demonstrate how to utilize EZUSB FX2 Slave FIFOs.

It configures FX2 as follows:
01).  EP2 512 2x BULK OUT - 8-bit async AUTO mode
02).  EP4 512 2x BULK IN  - 8-bit async AUTO mode
03).  EP6 512 2x BULK OUT - 8-bit async AUTO mode
04).  EP8 512 2x BULK IN  - 8-bit async AUTO mode
05).  FIFO strobes and flags are all active low
06).  FLAGA - fixed EP2EF
07).  FLAGB - fixed EP4FF
08).  FLAGC - fixed EP6EF
09).  FLAGD - fixed EP8FF
10).  SLCS isn't being used
11).  FX2 can't signal zerolen OUT token to the master

.....from the ext. master (xmaster in this case is FX in GPIF mode, CY3671 DK)
01).  512 byte buffer for EP2 OUT -> EP6 IN data
02).  512 byte buffer for EP4 OUT -> EP8 IN data
03).  xmaster just loops back the data
05).  xmaster supervises "not empty" / "not full" / "pktend" status
06).  peripheral interface functions in 8-bit async mode

.....from "the user":
01).  CY3681 DK is connected to a HS host controller
02).  EP2 512 2x BULK OUT data is looped back to EP6 512 2x BULK IN
03).  EP4 512 2x BULK OUT data is looped back to EP8 512 2x BULK IN
04).  EZUSB Control Panel to download "FX2" example firmware
05).  EZUSB Control Panel to xfr OUT/IN tokens via CY3681 DK


The "tcxmaster.hex" file loads into internal memory.
...issue "build -i" at the command prompt...

This example is for illustrative purpose(s) and unless you have an ext. master
that emulates the testing environment this example won't actually produce 
expected results when downloaded via Control Panel.  The external master in this
case is EZUSB FX (CY3671 DK) running in GPIF master mode



Some thoughts about xmaster pseudo code:
========================================

 Burst Read from slave EP2
 =========================
 if endp "not empty event", (EP2EF=1)
  init localbuf ef, ff, bc
  while localbuf not full
   if slave empty event
    break
   else
    enqueue(localbuf, currentbyte)
  end while
  
  ...turn around and fire data back out to FX2

 Burst Write to slave EP6
 ========================
 if endp "not full" (EP6FF=1)
  while localbuf not empty
   if slave full event
    break
   else
    dequeue(localbuf, currentbyte)
  end while
  
  ...now for the other paired loopback endp's

 Burst Read from slave EP4
 =========================
 if endp "not empty event", (EP4EF=1)
  init localbuf ef, ff, bc
  while localbuf not full
   if slave empty event
    break
   else
    enqueue(localbuf, currentbyte)
  end while
  
  ...turn around and fire data back out to FX2

 Burst Write to slave EP8
 ========================
 if endp "not full" (EP8FF=1)
  while localbuf not empty
   if slave full event
    break
   else
    dequeue(localbuf, currentbyte)
  end while



Below is an example of the physical interface between FX2 in slave fifo mode 
and FX in GPIF master mode.  This information is only useful as a reference
study.  If you're not familiar with the GPIF feature EZUSB then perhaps it would
be best to just think about it as a programmable state machine that can be 
programmed to meet almost any parallel peripheral interface bus timing... 
...In addition, FX has a pair of interface fifo(s) (AFIFO/BFIFO) that the GPIF 
uses during burst transactions... 
  



A little about the physical interface:
======================================
- testing flags during burst reads...
 * FX2 fadr assert to flags valid, >9.1nsec
 * FX async RDY setup time, >62.4nsec
 
- testing flags during burst writes...
 * FX2 fadr assert to flags valid, >9.1nsec
 * FX async RDY setup time, >62.4nsec


EP2RdAs: (11 cycles * 20.8nsec * 512 bytes/pkt ~ 117usec/pkt until GPIFDONE)
 * S0: wait 83.2nsec, handle async RDYn (62.4nsec) 
       and EP2EF setup time (70nsec)
       and SLRD pulse width high (50nsec)
 * S1: test EP2EF, if empty jump S6 (signal "pre-abort") else S2
 * S2: test FIFOFlag (AINPFPIN), throttle on AINPFPIN (infull)
 * S3: assert SLRD/SLOE for ~62.4nsec to meet pulse width low (50nsec)
       and turn-on to data valid (7.5nsec)
 * S4: keep SLRD/SLOE asserted and sample data
 * S5: loop S0, this waveform never terminates "naturally", using TC=1 scheme
 * S6: EP2EF detected, signal "pre-abort" to 8051, loop S6 until 8051 ABORT
 * S7: IDLE, not used in this scheme

EP6WrAs: (11 cycles * 20.8nsec * 512 bytes/pkt ~ 117usec/pkt until GPIFDONE)
 * S0: wait 83.2nsec, handle async RDYn (62.4nsec)
       and EP6FF setup time (70nsec)
       and SLWR pulse width high (70nsec)
 * S1: test FIFOFlag (AOUTPFPIN), throttle on AOUTPFPIN (outempty)
 * S2: test EP6FF, if full jump S0 (wait for host to drain the data) else S3
       and drive the data to meet SLWR to data setup time (2.7nsec)
 * S3: assert SLWR for 62.4nsec to meet pulse width low (50nsec)
       and drive the data
 * S4: drive the data to meet data to SLWR hold time (2.7nsec)
 * S5: inc. AFIFO data pointer, "NextData"
       and loop S0, this waveform never terminates "naturally", using TC=1 scheme
 * S6: not used in this waveform
 * S7: IDLE, not used in this scheme

EP4RdAs: (11 cycles * 20.8nsec * 512 bytes/pkt ~ 117usec/pkt until GPIFDONE)
 * S0: wait 83.2nsec, handle async RDYn (62.4nsec)
       and EP2EF setup time (70nsec)
       and SLRD pulse width high (50nsec)
 * S1: test EP4EF, if empty jump S6 (signal "pre-abort") else S2
 * S2: test FIFOFlag (BINPFPIN), throttle on BINPFPIN (infull)
 * S3: assert SLRD/SLOE for 62.4nsec to meet pulse width low (50nsec)
       and turn-on to data valid (7.5nsec)
 * S4: keep SLRD/SLOE asserted and sample data
 * S5: loop S0, this waveform never terminates "naturally", using TC=1 scheme
 * S6: EP4EF detected, signal "pre-abort" to 8051, loop S6 until 8051 ABORT
 * S7: IDLE, not used in this scheme

EP8WrAs: (11 cycles * 20.8nsec * 512 bytes/pkt ~ 117usec/pkt until GPIFDONE)
 * S0: wait 83.2nsec, handle async RDYn (62.4nsec)
       and EP6FF setup time (70nsec)
       and SLWR pulse width high (70nsec)
 * S1: test FIFOFlag (AOUTPFPIN), throttle on AOUTPFPIN (outempty)
 * S2: test EP6FF, if full jump S0 (wait for host to drain the data) else S3
       and drive the data to meet SLWR to data setup time (2.7nsec)
 * S3: assert SLWR for 62.4nsec to meet pulse width low (50nsec)
       and drive the data
 * S4: drive the data to meet data to SLWR hold time (2.7nsec)
 * S5: inc. AFIFO data pointer, "NextData"
       and loop S0, this waveform never terminates "naturally", using TC=1 scheme
 * S6: not used in this waveform
 * S7: IDLE, not used in this scheme
