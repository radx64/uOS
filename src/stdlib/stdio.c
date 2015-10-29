#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "drivers/vga.h"

#define BUFFER_SIZE 1024

static char writeBuffer[BUFFER_SIZE];

void printf(const char* format, ...)
{
    va_list currentParam;
    const char* formatIter = format;
    char* bufferIter = writeBuffer;
    va_start(currentParam, format);

    while(*formatIter != '\0')
    {
        if (*formatIter != '%')
        {
            *bufferIter = *formatIter;
            ++bufferIter;
        }
        else
        {
            //escape sequence detected
            ++formatIter;
            switch (*formatIter)
            {
                case '\0': break;
                case '%' :  *bufferIter = '%'; break;
                case 's' :  
                {
                    char* arg = va_arg(currentParam, char*);
                    uint32_t arglen = strlen(arg);
                    memcpy((void *)(bufferIter), (void *)arg, arglen);
                    bufferIter += arglen-1;
                    break;
                }
                case 'd' :  
                {
                    bool isNegative = false;
                    const char numberBufferSize = 12;
                    char buffer[numberBufferSize];
                    int32_t arg = va_arg(currentParam, int);
                    if (arg < 0)
                    {
                        isNegative = true;
                        arg = -arg;
                    }

                    char* startIter = itoa(arg, buffer+numberBufferSize, 10);
                    if (isNegative)
                    {
                        *--startIter = '-';
                    }
                    uint32_t numberlen = strlen(startIter);
                    memcpy((void *)(bufferIter), (void *)startIter, numberlen);
                    bufferIter += numberlen; 
                    break;
                }
                case 'f' :  *bufferIter = 'f'; break;
                case 'l' :  *bufferIter = 'l'; break;
            }
            ++bufferIter;
        }
        ++formatIter;
    }
    *bufferIter = 0;
    va_end(currentParam);
    vga_write(writeBuffer);
}