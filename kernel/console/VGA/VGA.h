#ifndef _VGACON_H
#define _VGACON_H
#define VGA_SCREEN_MAX_X 80
#define VGA_SCREEN_MAX_Y 25
#define VGA_INDEX 0x3D4
#define VGA_GREEN 0x02
#define VGA_RED 0x04
#define VGA_BLUE 0x01
#define VGA_WHITE 0x0F
#define VGA_LIGHTBLUE 0x09
#define VGA_GREY 0x07
#define VGA_DARKGREY 0x08
#define VGA_LIGHTRED 0x0C
#define VGA_YELLOW 0x0E
#include <stdint.h>
void VGA_putch(char c);
void VGA_clear();
void VGA_MoveCursor(uint8_t x, uint8_t y);
void VGA_Init(void);
uint8_t VGA_GetX(void);
uint8_t VGA_GetY(void);
uint8_t VGA_GetC(void);
void VGA_SetC(uint8_t c);
void VGA_writeline(const char *format, ...);
void VGA_clear(void);
extern uint8_t VGA_X, VGA_Y;
#endif
