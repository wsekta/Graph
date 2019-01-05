#include "FIFOQueue.h"

void QFCreate( QueueFIFO* q )
{
	q->pHead = NULL;
	q->pTail = NULL;
}



//=======================================
int QFEmpty( QueueFIFO* q )
{
	return !( q->pHead );
}



//=======================================
void QFEnqueue( QueueFIFO* q, int x )
{
	QFIFOItem *p = ( QFIFOItem* )calloc( 1, sizeof( QFIFOItem ) );
	if ( !p )
		perror( "QFEnqueue: allocation error" );
	p->nKey = x;
	if ( !QFEmpty( q ) )
		q->pTail->pNext = p;
	else
		q->pHead = p;
	q->pTail = p;
}



//=======================================
int QFDequeue( QueueFIFO* q )
{
	if ( !QFEmpty( q ) )
	{
		int res = q->pHead->nKey;
		QFDel( q );
		return res;
	}
	perror( "QFDequeue: queueu empty" );
	return 0;
}



//=======================================
void QFClear( QueueFIFO* q )
{
	while ( !QFEmpty( q ) )
		QFDel( q );
}



//=======================================
void QFRemove( QueueFIFO* q )
{
	QFClear( q );
}



//=======================================
void QFDel( QueueFIFO* q )
{
	if ( !QFEmpty( q ) )
	{
		QFIFOItem *p = NULL;
		if ( q->pHead->pNext )
			p = q->pHead->pNext;
		else
			q->pTail = NULL;
		free( q->pHead );
		q->pHead = p;
	}
}