/*
 * (C) Copyright 2003
 * Gerry Hamel, geh@ti.com, Texas Instruments
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#ifdef DEBUG
#define _DEBUG	1
#else
#define _DEBUG	0
#endif

#define UART_DATA_SIZE    2048

void __assert_fail(const char *assertion, const char *file, unsigned line,
		   const char *function);
#define assert(x) \
	({ if (!(x) && _DEBUG) \
		__assert_fail(#x, __FILE__, __LINE__, __func__); })

/* Return count in buffer.  */
#define CIRC_CNT(head,tail,size) (((head) - (tail)) & ((size)-1))

/* Return space available, 0..size-1.  We always leave one free char
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#define CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))

/* Return count up to the end of the buffer.  Carefully avoid
   accessing head and tail more than once, so they can change
   underneath us without returning inconsistent results.  */
#define CIRC_CNT_TO_END(head,tail,size) \
	({int end = (size) - (tail); \
	  int n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;})

/* Return space available up to the end of the buffer.  */
#define CIRC_SPACE_TO_END(head,tail,size) \
	({int end = (size) - 1 - (head); \
	  int n = (end + (tail)) & ((size)-1); \
	  n <= end ? n : end+1;})


typedef struct circbuf {
	char data[UART_DATA_SIZE];
	int size; /* the total size of the buffer, MUST be power-of-2 */
	int head; /* the point at which the producer inserts items. */
	int tail; /* the point at which the consumer finds the next item. */
} circbuf_t;

extern volatile circbuf_t SendToUartData;

int buf_init (volatile circbuf_t * buf);
int buf_pop (volatile circbuf_t * buf, char *dest, unsigned int len);
int buf_push (volatile circbuf_t * buf, const char *src, unsigned int len);

#endif
