#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define COLUMNS 80
#define ROWS 25
#define CELL_SIZE 2

void fb_write_cell(
    unsigned int location,
    char character,
    unsigned char foreground,
    unsigned char background);

void fb_write_at_location(
    unsigned char x,
    unsigned char y,
    char character,
    unsigned char
    foreground,
    unsigned char background);

void fb_clear();

void fb_move_cursor(unsigned char x, unsigned char y);

#endif // FRAMEBUFFER_H