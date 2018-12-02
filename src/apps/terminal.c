#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "drivers/vga.h"

#define ENTER_KEY_CODE 0x1C

#define CURSOR_UP 0x48
#define CURSOR_DOWN 0x50
#define BACKSPACE 0x0E


#define COLUMNS 80
#define LINES 50
#define VISIBLE_LINES 25

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint16_t top_line_index = 0;

unsigned char terminal_buffer[LINES][COLUMNS] = {};

unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

void terminal_init()
{
  vga_move_cursor_xy(0,0);
}

void move_buffer_up()
{
  for(uint16_t line = 1; line < LINES; ++line)
  {
    for(uint8_t column = 0; column < COLUMNS; ++column) terminal_buffer[line - 1][column] = terminal_buffer[line][column];
  }
  for(uint8_t column = 0; column < COLUMNS; ++column) terminal_buffer[LINES-1][column] = 0;
}


uint8_t last_keycode = 0;

void print_debugs()
{
      vga_move_cursor_xy(COLUMNS - 20, 0);
      printf("cursor_x,y = %d,%d\n" , cursor_x, cursor_y);
      vga_move_cursor_xy(COLUMNS - 20, 1);
      printf("top_line_index = %d\n" , top_line_index);
      vga_move_cursor_xy(COLUMNS - 20, 2);
      printf("last_keycode = %x\n" , last_keycode);
}

void recalculate_topline_index()
{
    if (cursor_y - top_line_index > VISIBLE_LINES - 1) top_line_index = cursor_y - VISIBLE_LINES + 1;
}

void terminal_on_keyboard_press(const uint8_t key_code)
{
    last_keycode = key_code;
    if(key_code == ENTER_KEY_CODE)
    {
        ++cursor_y;
        cursor_x = 0;
        if (cursor_y >= LINES)
        {
          move_buffer_up();
          cursor_y--;
        }
        recalculate_topline_index();
    }
    else if(key_code == CURSOR_UP)
    {
        if (top_line_index > 0) top_line_index--;
    }
    else if(key_code == CURSOR_DOWN)
    {
        if (top_line_index + VISIBLE_LINES < LINES) top_line_index++;
    }
    else if(key_code == BACKSPACE)
    {
      if(cursor_x > 0) cursor_x--;
      terminal_buffer[cursor_y][cursor_x] = 0;
    }
    else
    {
      terminal_buffer[cursor_y][cursor_x] = keyboard_map[(unsigned char)key_code];
      ++cursor_x;
      if (cursor_x >= COLUMNS)
      {
        cursor_x = 0;
        ++cursor_y;
      }
      recalculate_topline_index();
    }

    for (uint16_t line = 0 + top_line_index; line < VISIBLE_LINES + top_line_index; ++line)
    {
      for(uint8_t column = 0; column <= COLUMNS; ++column)
      {
        vga_write_cell_xy(column, line - top_line_index, terminal_buffer[line][column], C_WHITE, C_BLACK);
      }
    }

    print_debugs();

    vga_move_cursor_xy(cursor_x, cursor_y - top_line_index);
}