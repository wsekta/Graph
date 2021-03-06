
//dla każdego domu obliczyć najbliższą ścieżkę po piwo
//ścieżka, długość i czas przejścia (prędkość 5 km - jako stała)
//graf nie skierowany 


// input : [nr węzła] [0-dom, 1-monopol] [lista jego sąsiadów: [sąsiad] [odległość]] 
//realokacja listy co trzy węzły

// metodą przeszukiwania w szerz wyszukać następnika i 
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "graph.h"

#define REALLOC_SIZE 3

int ReadData( FILE* fin, Vertex** city );
void PrintData( FILE*, Vertex*, int );

int main( int argc, char** argv )
{
	if ( argc != 2 )
	{
		printf( "Graf.exe [input file]" );
		return 1;
	}

	FILE* fin = NULL;
	if ( ( fin = ( fopen( argv[ 1 ], "rt" ) ) ) == NULL )
	{
		printf( "main: file open error" );
		return 1;
	}
	Vertex* city = NULL;
	int nSize = ReadData( fin, &city );
	printf( "%d", nSize );

	int* v = ( int* )calloc( nSize, sizeof( int ) );
	if ( !v )
	{
		printf( "main: allocation error" );
		return 1;
	}
	BFS( city, 0, v );

	for ( int i = 0; i < nSize; i++ )
	{
		if ( !city[ i ].Type )
		{
			city[ i ].Distance = Dijkstra( city, nSize, i );
			city[ i ].TimeAll = city[ i ].Distance / SPEED;

			int* Path = ( int* )calloc( nSize, sizeof( int ) );
			if ( !Path )
			{
				printf( "main: allocation error" );
				return 1;
			}

			int tmp = city[ i ].NearestShop;
			int p = 0;
			while ( Path[ p - 1 ] != i && p < nSize )
			{
				Path[ p ] = tmp;
				tmp = city[ i ].ShopRoad[ tmp ];
				p++;
			}

			for ( int k = 0; k < p / 2; k++ )
			{
				int temp = Path[ p - k - 1 ];
				Path[ p - k - 1 ] = Path[ k ];
				Path[ k ] = temp;
			}

			city[ i ].ShopRoad = Path;
		}
	}

	FILE* fout = NULL;
	if ( ( fout = ( fopen( "out.txt", "w+" ) ) ) == NULL )
	{
		printf( "main: file open error" );
		return 1;
	}
	PrintData( fout, city, nSize );
	fclose( fout );

	for ( int j = 0; j < nSize; j++ )
	{
		while ( ListItem* tmp = city[ j ].nList )
		{
			city[ j ].nList = tmp->pNext;
			free( tmp );
		}
		free( city[ j ].ShopRoad );
	}
	free( city );
	city = NULL;
	return 0;
}



//==================================
int ReadData( FILE* fin, Vertex** city )
{
	int nSize = 0;
	char c;
	while ( !feof( fin ) )
	{
		if ( !( nSize%REALLOC_SIZE ) )
		{
			Vertex* tmp = ( Vertex* )realloc( *city, sizeof( Vertex )*( nSize + REALLOC_SIZE ) );
			if ( !tmp )
			{
				printf( "ReadData: allocation error" );
				return 0;
			}
			*city = tmp;
			memset( ( *city + nSize ), 0, sizeof( Vertex ) * REALLOC_SIZE );
		}

		Vertex* p = &( ( *city )[ nSize++ ] );
		fscanf( fin, "%d %d", &p->Number, &p->Type );

		while ( !feof( fin ) && ( ( c = fgetc( fin ) ) != '\n' ) )
		{
			if ( c >= '0' && c <= '9' )
			{
				ungetc( c, fin );
				ListItem* tmp = ( ListItem* )calloc( 1, sizeof( ListItem ) );
				if ( !tmp )
				{
					printf( "ReadData: allocation error" );
					return 0;
				}
				fscanf( fin, "%d %lf", &tmp->nKey, &tmp->len );
				tmp->time = tmp->len / SPEED;
				if ( !p->nList )
					tmp->pNext = p->nList;
				p->nList = tmp;
			}
		}
	}
	fclose( fin );
	return nSize;
}



//==================================
void PrintData( FILE* fout, Vertex* city, int nSize )
{
	for ( int i = 0; i < nSize; i++ )
	{
		fprintf( fout, "Number of vertex: %d\n", i );

		if ( city[ i ].Type )
			fprintf( fout, "Shop\n\n" );
		else
		{
			fprintf( fout, "House\n" );
			fprintf( fout, "Index of the nearest shop: %d\n", city[ i ].NearestShop );
			fprintf( fout, "Distance to shop: %fkm\n", city[ i ].Distance );

			fprintf( fout, "Way to the shop: " );
			int j = 0;
			while ( city[ i ].ShopRoad[ j ] != city[ i ].NearestShop )
				fprintf( fout, "%d->", city[ i ].ShopRoad[ j++ ] );
			fprintf( fout, "%d", city[ i ].ShopRoad[ j ] );


			fprintf( fout, "\nTrack time: %.2lf h = %.2lf min \n \n", city[ i ].TimeAll, city[ i ].TimeAll * 60 );
		}
	}
}