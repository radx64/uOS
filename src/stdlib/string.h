#ifndef STRING_H
#define STRING_H

unsigned int strlen(const char* s)
{
    unsigned int len = 0;
    while(s[len] != '\0')
    {
        ++len;
    }
    return len;
}



#endif // STRING_H