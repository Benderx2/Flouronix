/* Define's a console :D */
#ifndef _CONSOLE_H
#define _CONSOLE_H
#include <stdint.h>
struct FL_CONSOLE {
	uint8_t Green;
	uint8_t White;
	uint8_t Grey;
	uint8_t DarkGrey;
	uint8_t Red;
	uint8_t LightRed;
	uint8_t Yellow;
	uint8_t Blue;
	uint8_t LightBlue;
	int max_x;
	int max_y;
	void (*WriteChar)(char c);
	void (*WriteLine)(const char* fmt, ...);
	int (*ReadChar)(void);
	void (*SetCursor)(uint8_t x, uint8_t y);
	uint8_t (*GetCursorX)();
	uint8_t (*GetCursorY)();
	void (*SetColor)(uint8_t color);
	void (*Clear)(void);
	uint8_t (*GetColor)();
};
void Console_Init(void);
typedef struct FL_CONSOLE FL_CONSOLE_t;
extern FL_CONSOLE_t Console;
#endif
