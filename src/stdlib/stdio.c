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
					uint32_t stringLength = strlen(arg);
					memcpy((void *)(bufferIter), (void *)arg, stringLength);
					bufferIter += stringLength-1;
					break;
				}
				case 'd' :  *bufferIter = 'd'; break;
				case 'f' :  *bufferIter = 'f'; break;
				case 'l' :  *bufferIter = 'l'; break;
			}
			++bufferIter;
		}
		++formatIter;
	}
	*bufferIter = 0;
	vga_write(writeBuffer);
}