OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

ENTRY(loader)               /* name of the entry label */

SECTIONS 
{
    . = 1M;         /* the code should be loaded at 1 MB of memory */

    .text BLOCK(4K) : ALIGN (4K) /* align to 4 KB */
    {
        *(.multiboot)
        *(.text)            /* link all text sections from all files */
    }

    .rodata BLOCK(4K) : ALIGN (4K) /* align to 4 KB */
    {
        *(.rodata)          /* all read-only data sections from all files */
    }

    .data BLOCK(4K) : ALIGN (4K) /* align to 4 KB */
    {
        *(.data)            /* all data sections from all files */
    }

    .bss BLOCK(4K) : ALIGN (4K)    /* align to 4 KB */
    {
        *(COMMON)           /* all COMMON sections from all files */
        *(.bss)             /* all bss sections from all files */
    }
}