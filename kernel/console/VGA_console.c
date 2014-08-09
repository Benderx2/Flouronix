#include <kernel/console/console.h>
#include <kernel/console/VGA/VGA.h>
#include <kernel/console/PS2.h>
FL_CONSOLE_t Console;
void initialise_console(void)
{
	Console.Green = VGA_GREEN;
	Console.White = VGA_WHITE;
	Console.Yellow = VGA_YELLOW;	
	Console.Red = VGA_RED;
	Console.LightRed = VGA_LIGHTRED;
	Console.Blue = VGA_BLUE;
	Console.LightBlue = VGA_LIGHTBLUE;
	Console.Grey = VGA_GREY;
	Console.DarkGrey = VGA_DARKGREY;
	Console.max_x = VGA_SCREEN_MAX_X;
	Console.max_y = VGA_SCREEN_MAX_Y;
	Console.WriteChar = &VGA_putch;
	Console.WriteLine = &VGA_writeline;
	Console.SetCursor = &VGA_MoveCursor;
	Console.GetCursorX = &VGA_GetX;
	Console.GetCursorY = &VGA_GetY;
	Console.GetColor = &VGA_GetC;
	Console.ReadChar = &ps2_readc;
	Console.Clear = &VGA_clear;
	VGA_Init();
}
