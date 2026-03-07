/* File that reunite Input/Output registers to configure peripherals for GB SOC
Uses the different sub-systems such as timer, LCD, etc... to read all mapped registers

Start	End	    First appeared	Purpose
$FF00		          DMG	    Joypad input
$FF01	$FF02	      DMG       Serial transfer
$FF04	$FF07	      DMG	    Timer and divider
$FF0F		          DMG	    Interrupts
$FF10	$FF26	      DMG	    Audio
$FF30	$FF3F	      DMG	    Wave pattern
$FF40	$FF4B	      DMG	    LCD Control, Status, Position, Scrolling, and Palettes
$FF46		          DMG	    OAM DMA transfer
$FF4C	$FF4D	      CGB	    KEY0 and KEY1
$FF4F		          CGB	    VRAM Bank Select
$FF50		          DMG	    Boot ROM mapping control
$FF51	$FF55	      CGB	    VRAM DMA
$FF56		          CGB	    IR port
$FF68	$FF6B	      CGB	    BG / OBJ Palettes
$FF6C		          CGB	    Object priority mode
$FF70		          CGB	    WRAM Bank Select 
*/

#pragma once

#include "common.h"

uint8_t io_read(uint16_t addr);
void io_write(uint16_t addr, uint8_t data);