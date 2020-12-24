/*
 * (C) Copyright 2003
 * Gerry Hamel, geh@ti.com, Texas Instruments
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <circbuf.h>

volatile circbuf_t SendToUartData;

static int is_power_of_two (unsigned int size)
{
	assert (size > 0);
	return ((size & (size - 1)) == 0);
}

int buf_init (volatile circbuf_t * buf)
{
	assert (buf != NULL);
	assert (is_power_of_two(UART_DATA_SIZE));

	buf->size = UART_DATA_SIZE;
	
	assert (buf->data != NULL);

	buf->head = 0;
	buf->tail = 0;

	return 1;
}
int buf_pop (volatile circbuf_t * buf, char *dest, unsigned int len)
{
	int head, tail;
	unsigned int cnt, i;

	assert (buf != NULL);
	assert (dest != NULL);

	head = buf->head;
	tail = buf->tail;

	cnt = CIRC_CNT(head, tail, buf->size);
	if (len > cnt)
		len = cnt;

	for (i = 0; i < len; i++) {
		dest[i] = buf->data[tail];
		tail++;
		if (tail == buf->size) {
			tail = 0;
		}
	}

	buf->tail = tail;

	return len;
}

int buf_push (volatile circbuf_t * buf, const char *src, unsigned int len)
{
	int head, tail;
	unsigned int space, i;

	assert (buf != NULL);
	assert (src != NULL);

	head = buf->head;
	tail = buf->tail;

	space = CIRC_SPACE(head, tail, buf->size);
	if (len > space)
		len = space;

	for (i = 0; i < len; i++) {
		buf->data[head] = src[i];
		head++;
		if (head == buf->size) {
			head = 0;
		}
	}

	buf->head = head;

	return len;
}


