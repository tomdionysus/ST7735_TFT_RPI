/*
 * Project Name: ST7735, 128 by 128, 1.44", red pcb,SPI TFT module, lib
 * File: ST7735_TFT.h
 * Description: library header file
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 */

#ifndef _st7735_tft_lcd_h
#define _st7735_tft_lcd_h

// Section Libraries 
#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ST7735_TFT_graphics.h" // Custom


// Section:  Defines

// ST7735 registers 
#define ST7735_NOP     0x00 // Non operation
#define ST7735_SWRESET 0x01 // Soft Reset
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10 // Sleep ON
#define ST7735_SLPOUT  0x11 // Sleep OFF
#define ST7735_PTLON   0x12 // Partial mode
#define ST7735_NORON   0x13 // Normal Display
#define ST7735_INVOFF  0x20 // Display invert off
#define ST7735_INVON   0x21 // Display Invert on
#define ST7735_DISPOFF 0x28 // Display off
#define ST7735_DISPON  0x29 // Display on

#define ST7735_TFT_Idle_modeON 0x39 //Idle Mode ON
#define ST7735_TFT_Idle_modeOF  0x38 //Idle Mode OFF

#define ST7735_CASET   0x2A // Column address set
#define ST7735_RASET   0x2B // Page address set
#define ST7735_RAMWR   0x2C // Memory write
#define ST7735_RAMRD   0x2E // Memory read
#define ST7735_PTLAR   0x30 // Partial Area
#define ST7735_VSCRDEF 0x33 // Vertical scroll def
#define ST7735_COLMOD  0x3A // Interface Pixel Format
#define ST7735_MADCTL  0x36 // Memory Access Control
#define ST7735_VSCRSADD 0x37 // Vertical Access Control

// Frame Rate Control
#define ST7735_FRMCTR1 0xB1 // Normal
#define ST7735_FRMCTR2 0xB2 // idle
#define ST7735_FRMCTR3 0xB3 // Partial

#define ST7735_INVCTR  0xB4 // Display Inversion control
#define ST7735_DISSET5 0xB6 // Display Function set

// Power_Control
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_PWCTR6  0xFC

#define ST7735_VMCTR1  0xC5 // VCOM_Control 1

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_GMCTRP1 0xE0 // Positive Gamma Correction Setting
#define ST7735_GMCTRN1 0xE1 // Negative Gamma Correction Setting

#define ST7735_MADCTL_MY 0x80
#define ST7735_MADCTL_MX 0x40
#define ST7735_MADCTL_MV 0x20
#define ST7735_MADCTL_ML 0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

// Color definitions 16-Bit Color Values R5G6B5
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF
#define   ST7735_TAN     0xED01
#define   ST7735_GREY    0x9CD1
#define   ST7735_BROWN   0x6201

// GPIO
#define TFT_DC_SetHigh  bcm2835_gpio_write(_TFT_DC, HIGH)
#define TFT_DC_SetLow  bcm2835_gpio_write(_TFT_DC, LOW)
#define TFT_RST_SetHigh  bcm2835_gpio_write(_TFT_RST, HIGH)
#define TFT_RST_SetLow  bcm2835_gpio_write(_TFT_RST, LOW)
#define TFT_CS_SetHigh bcm2835_gpio_write(_TFT_CS, HIGH) // SW SPI last 6 lines
#define TFT_CS_SetLow bcm2835_gpio_write(_TFT_CS, LOW)
#define TFT_SCLK_SetHigh bcm2835_gpio_write(_TFT_SCLK, HIGH)
#define TFT_SCLK_SetLow  bcm2835_gpio_write(_TFT_SCLK, LOW)
#define TFT_SDATA_SetHigh bcm2835_gpio_write(_TFT_SDATA, HIGH)
#define TFT_SDATA_SetLow  bcm2835_gpio_write(_TFT_SDATA,LOW)

#define TFT_DC_SetDigitalOutput bcm2835_gpio_fsel(_TFT_DC, BCM2835_GPIO_FSEL_OUTP)
#define TFT_RST_SetDigitalOutput bcm2835_gpio_fsel(_TFT_RST, BCM2835_GPIO_FSEL_OUTP)
#define TFT_SCLK_SetDigitalOutput bcm2835_gpio_fsel(_TFT_SCLK, BCM2835_GPIO_FSEL_OUTP) // SW SPI last 3 lines
#define TFT_SDATA_SetDigitalOutput bcm2835_gpio_fsel(_TFT_SDATA, BCM2835_GPIO_FSEL_OUTP)
#define TFT_CS_SetDigitalOutput bcm2835_gpio_fsel(_TFT_CS, BCM2835_GPIO_FSEL_OUTP)

#define TFT_HIGHFREQ_DELAY 0 //Software SPI delay


// Section: Enums

typedef enum  {
	TFT_Normal_mode = 0, 
	TFT_Partial_mode, 
	TFT_Idle_mode, 
	TFT_Sleep_mode, 
	TFT_Invert_mode, 
	TFT_Display_on_mode, 
	TFT_Display_off_mode
}TFT_modes_e; // TFT display modes

typedef enum  {
	TFT_Degress_0 = 0, TFT_Degress_90, TFT_Degress_180, TFT_Degress_270
}TFT_rotate_e; // TFT rotate modes in degrees 

typedef enum {
	TFT_ST7735R_Red = 0, // ST7735R Red Tab 
	TFT_ST7735R_Green, // ST7735R Green Tab
	TFT_ST7735S_Black, // ST7735S Black Tab
	TFT_ST7735B, // ST7735B controller
}TFT_PCBtype_e; // type of PCB

// Section: class's

// Class to control ST7735 TFT basic functionality.
 
class ST7735_TFT : public ST7735_TFT_graphics
{

public:

	ST7735_TFT();
	~ST7735_TFT(){};
	
	TFT_modes_e TFT_mode;
	TFT_rotate_e TFT_rotate;
	TFT_PCBtype_e TFT_PCBtype;
	
	void TFTSetupGPIO(int8_t, int8_t, int8_t, int8_t, int8_t);
	void TFTInitScreenSize(uint8_t xOffset, uint8_t yOffset, uint16_t w, uint16_t h);
	void TFTInitPCBType(TFT_PCBtype_e);
	void TFTInitSPIClockFrequency(uint32_t hertz);
	void TFTPowerDown(void);
	
	void TFTsetRotation(TFT_rotate_e r);
	void TFTchangeInvertMode(bool invertModeOn);
	void TFTchangeMode(TFT_modes_e m);
	void TFTsetScrollDefinition(uint8_t th, uint8_t tb, bool sd);
	void TFTVerticalScroll(uint8_t vsp);
	
private:

	void TFTResetPIN(void);
	void TFTSPIInitialize(void);
	void TFTST7735BInitialize(void);
	void TFTGreenTabInitialize(void);
	void TFTBlackTabInitialize(void);
	void TFTRedTabInitialize(void);
	void Rcmd1(void);
	void Rcmd2red(void);
	void Rcmd3(void);
	void Bcmd(void);
	void Rcmd2green(void);
	
	uint8_t  _rotation = 0; 

}; //end of class

#endif // file header guard

// ********************** EOF *********************
