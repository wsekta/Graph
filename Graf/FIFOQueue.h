#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct tagQFIFOItem
{
	int nKey;	/* info (int)    - n_Key */
	tagQFIFOItem* pNext;	/* ptr to the next Qitem - pNext; */
} QFIFOItem;

typedef struct
{
	QFIFOItem* pHead;
	QFIFOItem* pTail;
} QueueFIFO;



void QFCreate( QueueFIFO* q ); // queue inititating // ustawic tylko dwa wskazniki na NLL
int QFEmpty( QueueFIFO* q ); // if fifo empty return 1 else 0
void QFEnqueue( QueueFIFO* q, int x ); // insert new item at the end , wstawia do kolejki
int QFDequeue( QueueFIFO* q ); // take out the first item; sciagniecie( tak jak pop na stosie )
void QFClear( QueueFIFO* q ); // clears the queeu czysci kolejke, usuwa wszystkie dynamiczne elementy i ustawic wskazniki na NULL
void QFRemove( QueueFIFO* q ); // czysci cala kolejke , w pierwszym przypadku nie rozni sie niczym od QFClear
void QFDel( QueueFIFO* q ); // removes only first item