#pragma once

#ifdef _GRAPH_C_
#define	LIB_API	__declspec(dllexport)
#else
#define	LIB_API	__declspec(dllimport)
#endif // _GRAPH_C_

#include <stdlib.h>
#include <stdio.h>

#define INFINITY_DIST		0xFFFF

typedef struct sDijkstraNode dijkstraNode;
typedef struct sGraph graph;
typedef struct sNode node;

enum eGroundMask
{
	NOTHING		= 0b00000000,

	GRASS		= 0b00000001,
	FOREST		= 0b00000010,
	MOUNTAIN	= 0b00000100,
	CITY		= 0b00001000,
	ROAD		= 0b00010000,
	WATER		= 0b00100000,

	EVERYTHING	= 0b11111111
};

enum eGroundID
{
	GRASS_ID,
	FOREST_ID,
	MOUNTAIN_ID,
	CITY_ID,
	ROAD_ID,
	WATER_ID,
	NB_GROUND
};

static const char s_groundChar[NB_GROUND] = {
	'G',
	'F',
	'M',
	'C',
	'R',
	'W'
};

struct sGraph
{
	int m_sizeX; //Taille graphe X/Y
	int m_sizeY;
	node** m_data; //Tableau des noeuds du graphe
};

struct sNode
{
	int m_id; //Indice du noeud
	unsigned char m_posX; //Position X/Y du noeud dans le graphe
	unsigned char m_posY;
	unsigned char m_layer; //Masque du type de terrain (egroundmask)
	unsigned char m_layerID; //L'ID du type de terrain (egroundid)
	node* m_neighbors[4]; //Tableau statique des 4 voisins (haut bas gauche droite) du noeud
	void* m_data; //Pointeur g�n�rique  
};

struct sDijkstraNode
{
	node* m_node; //Noeud initial	
	int m_distance; //Distance parcourue depuis le d�part
	char m_flag; //Noeud d�j� trait�o ou non
	node* m_prev; //Noeud pr�c�dent
};

LIB_API	graph* LoadGraphFromFile(char* fichier);
LIB_API	void freeGraph(graph* monGraph);
LIB_API	int GetLayerIDFromChar(char c);
LIB_API	dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask);
LIB_API	void FreeDijkstra(dijkstraNode** d, graph* g);
LIB_API	node* GetNodeFromPosition(graph* G, unsigned char X, unsigned char Y);
LIB_API	int GetManhattanDistance(node* a, node* b);
LIB_API	int GetLayerIDFromChar(char character);
LIB_API	char IsNeighbour(node* a, node* b);
LIB_API	void SetNodeData(node* noeud, void* data); //mettre data dans le champ de noeud
LIB_API	void* GetNodeData(node* noeud);