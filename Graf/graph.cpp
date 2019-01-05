#include "graph.h"
#include "PQueue.h"
#include "FIFOQueue.h"

double Dijkstra( Vertex* city, int nSize, int nFirst )
{
	PQueue* q = PQInit( nSize ); 
	double* Distance = ( double* )calloc( 1, nSize * sizeof( double ) );
	int* Path = ( int* )calloc( nSize, sizeof( int ) ); 
	if ( !Distance || !Path )
	{
		printf( "Dijkstra: allocation error" );
		return -1;
	}

	city[ nFirst ].ShopRoad = Path;
	for ( int i = 0; i < nSize; i++ )
		Distance[ i ] = INT_MAX;

	PQEnqueue( q, nFirst, 0 );
	Distance[ nFirst ] = 0; 
	double len = 0; 

	while ( !( PQIsEmpty( q ) ) )
	{
		int k = PQDequeueu( q );

		if ( city[ k ].Type )
		{
			city[ nFirst ].NearestShop = k;
			PQRelease( &q );
			len = Distance[ k ];
			//return Distance[k];
			break;
		}

		else
		{
			ListItem* j = city[ k ].nList;
			while ( j )
			{
				int nNode = j->nKey;

				if ( Distance[ k ] + j->len < Distance[ nNode ] )
				{
					Distance[ nNode ] = Distance[ k ] + j->len;
					city[ nFirst ].ShopRoad[ nNode ] = k;
					PQEnqueue( q, nNode, Distance[ nNode ] );
				}
				j = j->pNext;
			}
		}
	}
	free( Distance );

	return len;
}



//==================================
void BFS( Vertex* city, int u, int* V )
{
	QueueFIFO *q = ( QueueFIFO* )calloc( 1, sizeof( QueueFIFO ) );
	if ( !q )
		perror( "BFS: allocation error" );
	QFCreate( q );

	V[ u ] = -1;
	QFEnqueue( q, u );
	while ( !QFEmpty( q ) )
	{
		u = QFDequeue( q );
		ListItem* v = city[ u ].nList;
		while ( v )
		{
			if ( !V[ v->nKey ] )
			{
				V[ v->nKey ] = -1;
				QFEnqueue( q, v->nKey );
			}
			v = v->pNext;
		}
		V[ u ] = 1;
	}
}