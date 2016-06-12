; --------------------------------------------------------------------------------
; @Title: BeagleBone STM Demo Scripts - README
; @Description: -
; @Author: JBO, HLG
; @Board: BeagleBone
; @Chip: AM3359
; @Copyright: (C) 1989-2014 Lauterbach GmbH, licensed for use with TRACE32(R) only
; --------------------------------------------------------------------------------
; $Id: readme.txt 7358 2014-07-07 12:59:17Z hlohn $

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Note that this demo has exclusively been designed for a beaglebone rev. A3. !
! If you want to use it for a different target, you may need to adapt the     !
! included scripts.                                                           !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Startup
------------------------------------------------------------------------------
Please use 'demo_stm.cmm' as startup script for the sieve demo. It will
output "Hello World!", followed by the prime numbers via STM.
Depending on your hardware configuration the script will automatically
route STM data to either the onchip buffer or package pins to an offchip
trace sink.


Onchip trace
------------------------------------------------------------------------------
- Connect the debugger to the target, do not
  attach a PowerTrace to the debugger!
- You may use LA-3780 to connect to the target.
- Power up the target and run the demo.


Offchip trace via CombiProbe
------------------------------------------------------------------------------
- Connect the CombiProbe cable to the target.
- You may use adaptor LA-3782 (CTI20->MIPI34) to connect to the CTI JTAG header (P7)
  However you have to modify LA-3782 to ensure that EMU0/EMU1/EMU3 connect to
  the right pins. (see below)
- Remove any SD-card from the slot, otherwise
  the trace will not work correctly!
- Power up the target and run the demo.
  +--------------------+---------------+---------------+
  |Preprocessor        | CombiProbe    | CombiProbe    |
  |Order code          | LA-4502       | LA-4502       |
  +--------------------+---------------+---------------+
  |STM.PortSize        |  4e           |  4e           |
  |SYS.CONFIG CONNECTOR|  MIPI34       |  MIPI20T      |
  +--------------------+---------------+---------------+
  |emu0        TP0     |  pin 24       |  pin 14       |
  |emu1        TP1     |  pin 26       |  pin 16       |
  |emu3        TP2     |  pin 28       |  pin 18       |
  |emu4        TP3     |  pin 30       |  pin 20       |
  +--------------------+---------------+---------------+
  |emu2     TRACECLK   |  pin 22       |  pin 12       |
  |vtref    VREF-TRACE |  pin 34       |  pin  1       |
  |gnd         GND     |  pin 23       |  pin 13       |
  +--------------------+---------------+---------------+


Offchip trace via PowerTrace
------------------------------------------------------------------------------
- Connect the debugger to the target and attach a PowerTrace to the debugger.
- You may use LA-3782 (CTI20->MIPI34) with LA-3842 (MIPI34->ARM20+Mictor38)
  to connect to the CTI JTAG header (P7).
  However you have to modify LA-3782 to ensure that EMU0/EMU1/EMU3 connect to
  the right pins. (see below)
- Alternativly use can use LA-3780 to connect the debug cable and
  use flying leads to connect signals emu0-emu4 from LA-3780 to the
  trace preprocessor as follows (see mapping of TP0..TP3 below):
      emu0 -> TP0
      emu1 -> TP1
      emu2 -> TRACECLK
      emu3 -> TP2
      emu4 -> TP3
- Remove any SD-card from the slot, otherwise
  the trace will not work correctly!
- Power up the target and run the demo.

  Default pin mapping for LA-7992 and LA-7993:
  +--------------------+---------------+---------------+
  |Preprocessor        | AUTOFOCUS II  | AUTOFOCUS MIPI|
  |Order code          | LA-7992       | LA-7993       |
  +--------------------+---------------+---------------+
  |STM.PortSize        |  4e           |  4e           |
  +--------------------+---------------+---------------+
  |emu0        TP0     |  pin 38       |  pin 19       |
  |emu1        TP1     |  pin 28       |  pin 21       |
  |emu3        TP2     |  pin 36       |  pin 17       |
  |emu4        TP3     |  pin 26       |  pin 23       |
  +--------------------+---------------+---------------+
  |emu2     TRACECLK   |  pin 6        |  pin 13       |
  |vtref    VREF-TRACE |  pin 12       |  pin 12       |
  |gnd         GND     |  GND          |  pin 58       |
  +--------------------+---------------+---------------+
  You can view or modify the pin mapping for TP0..TP3 via Analyzer.REMAP.state

  Pinout in style of ARM ETMv3 (Used in demo_stm.cmm):
  +--------------------+---------------+---------------+
  |Preprocessor        | AUTOFOCUS II  | AUTOFOCUS MIPI|
  |Order code          | LA-7992       | LA-7993       |
  +--------------------+---------------+---------------+
  |STM.PortSize        |  4e           |  4e           |
  |Analyzer.REMAP.PIN  |  TP2 26.      |  TP2 23.      |
  |Analyzer.REMAP.PIN  |  TP3 24.      |  TP3 25.      |
  +--------------------+---------------+---------------+
  |emu0        TP0     |  pin 38       |  pin 19       |
  |emu1        TP1     |  pin 28       |  pin 21       |
  |emu3        TP2     |  pin 26       |  pin 23       |
  |emu4        TP3     |  pin 24       |  pin 25       |
  +--------------------+---------------+---------------+
  |emu2     TRACECLK   |  pin 6        |  pin 13       |
  |vtref    VREF-TRACE |  pin 12       |  pin 12       |
  |gnd         GND     |  GND          |  pin 58       |
  +--------------------+---------------+---------------+

