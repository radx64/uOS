ENTRY(loader)               /* name of the entry label */

SECTIONS {
    . = 0x00100000;         /* the code should be loaded at 1 MB of memory */

    .text ALIGN (0x1000) :  /* align to 4 KB */
    {
        *(.text)            /* link all text sections from all files */
    }

    .rodata ALIGN (0x1000) :/* align to 4 KB */
    {
        *(.rodata)          /* all read-only data sections from all files */
    }

    .data ALIGN (0x1000) :  /* align to 4 KB */
    {
        *(.data)            /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :   /* align to 4 KB */
    {
        *(COMMON)           /* all COMMON sections from all files */
        *(.bss)             /* all bss sections from all files */
    }
}