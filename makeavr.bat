@echo off
REM ============================================
REM TurboAVR Compilation Script
REM Version: 1.2
REM Author: Ivan Ling
REM ============================================
REM 
REM This batch script automates the AVR compilation process
REM for Il Matto boards (ATmega644P microcontroller).
REM 
REM Usage: makeavr.bat yourfile.c
REM 
REM Process:
REM 1. Compile C source using avr-gcc
REM 2. Generate Intel HEX file using avr-objcopy
REM 3. Program microcontroller using avrdude
REM 
REM Target: ATmega644P @ 12MHz with USB ASP programmer
REM ============================================

echo STARTING PROGRAMMER...
echo V 1.2 Author: Ivan Ling

REM Compile C source to ELF executable
REM -mmcu=atmega644p: Target ATmega644P microcontroller
REM -DF_CPU=12000000: Define CPU frequency as 12MHz
REM -Wall: Enable all warnings for better code quality
REM -Os: Optimize for size (important for microcontrollers)
avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os %1 -o prog.elf

REM Convert ELF to Intel HEX format for programming
avr-objcopy -O ihex prog.elf prog.hex

REM Program the microcontroller via USB ASP
REM -c usbasp: Use USB ASP programmer
REM -p m644p: Target ATmega644P chip
REM -U flash:w:prog.hex: Write HEX file to flash memory
avrdude -c usbasp -p m644p -U flash:w:prog.hex