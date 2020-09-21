#pragma once

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
	int m_posX; //Position X/Y du noeud dans le graphe
	int m_posY;
	unsigned char m_layer; //Masque du type de terrain (egroundmask)
	char m_layerID; //L'ID du type de terrain (egroundid)
	node* m_neighbors[4]; //Tableau statique des 4 voisins (haut bas gauche droite) du noeud
	void* m_data; //Pointeur générique  
};

struct sDijkstraNode
{
	node* m_node; //Noeud initial	
	int m_distance; //Distance parcourue depuis le départ
	char m_flag; //Noeud déjà traitéo ou non
	node* m_prev; //Noeud précédent
};

graph* LoadGraphFromFile(char* fichier);

void freeGraph(graph* monGraph);