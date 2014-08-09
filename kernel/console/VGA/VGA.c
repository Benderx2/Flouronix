/* Mini VGA Console Driver */
#include <stdint.h>
#include <klib/string.h>
#include <arch/x86/x86.h>
#include <kernel/console/VGA/VGA.h>
uint8_t VGA_X;
uint8_t VGA_Y;
uint8_t VGA_C;
uint16_t* VGA_BUFFER;
void VGA_Init(void)
{
	VGA_X = 0;	
	VGA_Y = 0;
	VGA_C = 0x0F; /** White on Black **/
	VGA_BUFFER = (uint16_t*)(PHYSICAL_TO_VIRTUAL(0xB8000));
}
void VGA_MoveCursor(uint8_t x, uint8_t y)
{
	/* Change the location of the hardware cursor */
	uint16_t position = y * VGA_SCREEN_MAX_X + x;
	// cursor LOW port to vga INDEX register
    	CPU_x86.outportb(0x3D4, 0x0F);
    	CPU_x86.outportb(0x3D5, (uint8_t)(position&0xFF));
    	// cursor HIGH port to vga INDEX register
    	CPU_x86.outportb(0x3D4, 0x0E);
    	CPU_x86.outportb(0x3D5, (uint8_t)((position>>8)&0xFF));
	//VGA_X = x;
	//VGA_Y = y;
}
void VGA_clear(void)
{
	for(int i = 0; i < VGA_SCREEN_MAX_X * VGA_SCREEN_MAX_Y * 2; i++)
	{	
		VGA_BUFFER[i] = 0x0000;	
	}
	VGA_MoveCursor(0, 0);
}
static void scroll()
{

   // Get a space character with the default colour attributes.
   uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(VGA_Y >= VGA_SCREEN_MAX_Y)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0; i < (VGA_SCREEN_MAX_Y - 1) * VGA_SCREEN_MAX_X; i++)
       {
           VGA_BUFFER[i] = VGA_BUFFER[i+VGA_SCREEN_MAX_X];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = (VGA_SCREEN_MAX_Y - 1) * VGA_SCREEN_MAX_X; i < VGA_SCREEN_MAX_Y * VGA_SCREEN_MAX_X; i++)
       {
           VGA_BUFFER[i] = blank;
       }
       VGA_Y = VGA_SCREEN_MAX_Y - 1;
   }
} 
void VGA_putch(char c)
{	
	uint16_t attr_word = VGA_C << 8;
	uint16_t* mm_VGA;
	if(c == '\n')
	{
		VGA_X = 0;
		VGA_Y++;
	}
	else if(c == '\b')
	{	
		if(VGA_X == 0)
		{
			VGA_X = VGA_SCREEN_MAX_X - 1;
			VGA_Y--;
		}
		else if(VGA_Y == 0 && VGA_X == 0)
		{
			//return;
		}
		else {
			VGA_X--;
		}	
		mm_VGA = VGA_BUFFER + (VGA_Y * VGA_SCREEN_MAX_X + VGA_X);
		*mm_VGA = ' ' | 0x0F;
		VGA_MoveCursor(VGA_X, VGA_Y);
		//VGA_X++;
	}
	else if(c >= ' ')
	{
		mm_VGA = VGA_BUFFER + (VGA_Y * VGA_SCREEN_MAX_X + VGA_X);
		*mm_VGA = c | attr_word;
		VGA_X++;
	}
	if(VGA_X >= VGA_SCREEN_MAX_X)
	{		
		VGA_X = 0;
		VGA_Y++;
	}
	scroll();
	VGA_MoveCursor(VGA_X, VGA_Y);
	
}
void VGA_SetC(uint8_t color)
{
	VGA_C = color;
}
uint8_t VGA_GetX(void)
{
	return VGA_X;
}
uint8_t VGA_GetY(void)
{
	return VGA_Y;
}
uint8_t VGA_GetC(void)
{
	return VGA_C;
}
void VGA_writeline(const char *format, ...)
{
       char **arg = (char **) &format;
       int c;
       char buf[64];
       arg++;
       while ((c = *format++) != 0)
         {
           if (c != '%')
             VGA_putch(c);
           else if(c == '%')
             {
               char *p;
     
               c = *format++;
               switch (c)
                 {
                 case 'd':
                 case 'u':
                 case 'x':
                   itoa(buf, c, *((int *) arg++));
                   p = buf;
                   goto string;
                   break;
		 case 'f':
		    ftoa(buf, *((float *)arg++));	
		    p = buf;
		    goto string;
		    break;
		 case 'q':
			VGA_SetC(*((int*)arg++));
			break;
		 case 'y':
			VGA_SetC(VGA_WHITE);
			break;
                 case 's':
                   p = *arg++;
                   if (! p)
                     p = "(null)";
     
                 string:
                   while (*p)
                     VGA_putch(*p++);
                   break;
     
                 default:
                   VGA_putch(*((int *) arg++));
                   break;
                 }
             }
	}
}
    
