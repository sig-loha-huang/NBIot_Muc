#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cortex_m4.h>
#include "uart.h"
#include <core_cm3.h>
int raise (int signum)
{
    return 0;
}

int _isatty(int file)
{
	return 1;
}

int _close(int file)
{
	return -1;
}

int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _read(int file, char *ptr, int len)
{
	if (len <= 0)
	{
		return 0;
	}
	else
	{
		*ptr = Dd_Uart2_Getc();
		return 1;
	}
}

int _write(int file, char *ptr, int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
		Dd_Uart2_Putc(*ptr++);
	}

	return len;
}
#if 0
caddr_t _sbrk(int incr)
{
	extern char _end;		/* Defined by the linker */
	static unsigned long heap_end = 0;
	char *prev_heap_end;

	prev_heap_end = &_end + heap_end;
    char * stack = (char*) __get_MSP();
	if ((heap_end + incr) > stack)
	{
		write (1, "Heap and stack collision\n", 25);
		while(1);
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}
#endif
caddr_t _sbrk(int incr) {

    extern char _end; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

char * stack = (char*) __get_MSP();
     if (heap_end + incr >  stack)
     {
		write (1, "Heap and stack collision\n", 25);
         return  (caddr_t) -1;
         //abort ();
     }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}
