#pragma once
#define SPEED 4

/* struktura Vertex zawiera: liste sasiedztwa (lista prosta), odleglosci do kazdego,
czas przejscia (4km/h), czy sklep czy dom,
numer wezla ktory jest najblizszym sklepem,
droga do niego, czas przejscia calosci*/

typedef struct tabList
{
	int nKey; // nr wierzcho�ka sasiada
	double len; // d�ugo��
	double time;
	tabList* pNext; //next box w li�cie s�siedztwa
} ListItem;

typedef struct
{
	int Number;
	ListItem* nList; //lista s�siedztwa //
	int Type; //sklep - nie sklep
	int NearestShop; //indeks najbli�szy sklep //
	double Distance; //pathlong
	int* ShopRoad; // droga do sklepu
	double TimeAll; //czas przej�cia ca�o�ci //
} Vertex;

double Dijkstra( Vertex*, int, int ); //header priorque
void BFS( Vertex*, int, int* ); // metoda przegladania grafu w glab obliczyc czasy przejscia pomiedzy wierzcholkami
