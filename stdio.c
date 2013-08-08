#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)
 
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
	if (c == '\n')
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			for ( size_t y = 0; y < VGA_HEIGHT - 1; y++ ) /* First slide up every row. */
			{
				for ( size_t x = 0; x < VGA_WIDTH; x++ )
				{
					const size_t index = y * VGA_WIDTH + x;
					const size_t new_index = index + VGA_WIDTH;
					terminal_buffer[index] = terminal_buffer[new_index];
				}
			}
			terminal_row = VGA_HEIGHT - 1;
			for ( size_t x = 0; x < VGA_WIDTH; x++ ) /* Then blank out what used to be on the bottom row. */
			{
				const size_t index = ( VGA_HEIGHT - 1 ) * VGA_WIDTH + x;
				terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			}
		}
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			for ( size_t y = 0; y < VGA_HEIGHT - 1; y++ )
			{
				for ( size_t x = 0; x < VGA_WIDTH; x++ )
				{
					const size_t index = y * VGA_WIDTH + x;
					const size_t new_index = index + VGA_WIDTH;
					terminal_buffer[index] = terminal_buffer[new_index];
				}
			}
			terminal_row = VGA_HEIGHT - 1;
		}
	}
}
 
void print(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

void fprint(const char* string, uint32_t number) 
{
	size_t datalen = strlen(string);
	uint8_t working = number;
	uint8_t outcome[10];
	size_t numbersize = 0;
	for ( size_t index = 0; index < datalen; index++ )
	{
		if ( string[index] == '%' )
		{
			switch ( string[index + 1] )
			{
				case '%':
					terminal_putchar('%');
					index++; // Increment it twice to get it past the second '%'
					break;
				case 'd':

					while ( working != 0 )
					{
						outcome[numbersize] = working % 10;
						numbersize++;
						working /= 10;
					}
					numbersize--;
					for (; numbersize > 0; numbersize-- )
					{
						terminal_putchar('0' + outcome[numbersize]);
					}
					terminal_putchar('0' + outcome[0]); // Just to get the last char out of the array.

					index++; // Increment it again to get it past the 'n'
					break;
				case 'h':
					terminal_putchar('0');
					terminal_putchar('x');
					terminal_putchar(TO_HEX(((number & 0xF0000000) >> 28)));
					terminal_putchar(TO_HEX(((number & 0x0F000000) >> 24)));
					terminal_putchar(TO_HEX(((number & 0x00F00000) >> 20)));
					terminal_putchar(TO_HEX(((number & 0x000F0000) >> 16)));
					terminal_putchar(TO_HEX(((number & 0x0000F000) >> 12)));
					terminal_putchar(TO_HEX(((number & 0x00000F00) >> 8)));
					terminal_putchar(TO_HEX(((number & 0x000000F0) >> 4)));
					terminal_putchar(TO_HEX(((number & 0x0000000F))));
					index++;
					break;

			}
		}
		else
		{
			terminal_putchar(string[index]);
		}
	}
}