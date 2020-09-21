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
	void* m_data; //Pointeur g�n�rique  
};

struct sDijkstraNode
{
	node* m_node; //Noeud initial	
	int m_distance; //Distance parcourue depuis le d�part
	char m_flag; //Noeud d�j� trait�o ou non
	node* m_prev; //Noeud pr�c�dent
};

graph* LoadGraphFromFile(char* fichier){
	
	graph* monGraph = NULL;
	FILE* monFichier = fopen(fichier,"r");
	
	if(!monFichier)
		return NULL;
	
	int sizeX, sizeY;
	fscanf("%d%d", &sizeX, &sizeY);
	
	if(sizeX <= 0 || sizeY <= 0){
		fclose(monFichier);
		return NULL;
	}
		
	monGraph = malloc(sizeof(graph));
	
	monGraph->m_sizeX = sizeX;
	monGraph->m_sizeY = sizeY;
	
	monGraph->m_data = malloc(sizeof(node*)*sizeY*sizeX);
	
	for(int i = 0; i < sizeX*sizeY; i++)
		monGraph->m_data[i] = malloc(sizeof(node));
	
	char c;
	
	for(int i = 0; i < sizeY*sizeX; i++){
		fscanf("%c",&c); //erreur si fichier non complet !!!
		monGraph->m_data[i]->id = i;
		printf("id: %d\n, monGraph->m_data[i]->id);
		monGraph->m_data[i]->m_posX = i%sizeX;
		monGraph->m_data[i]->m_posY = i/sizeX;
		
		switch(c){
			case 'G':
				monGraph->m_data[i]->m_layer = GRASS;
				monGraph->m_data[i]->m_layerID = GRASS_ID;
				break;
			case 'F':
				monGraph->m_data[i]->m_layer = FOREST;
				monGraph->m_data[i]->m_layerID = FOREST_ID;
				break;
			case 'M':
				monGraph->m_data[i]->m_layer = MOUNTAIN;
				monGraph->m_data[i]->m_layerID = MOUNTAIN_ID;
				break;
			case 'C':
				monGraph->m_data[i]->m_layer = CITY;
				monGraph->m_data[i]->m_layerID = CITY_ID;
				break;
			case 'R':
				monGraph->m_data[i]->m_layer = ROAD;
				monGraph->m_data[i]->m_layerID = ROAD_ID;
				break;
			case 'W':
				monGraph->m_data[i]->m_layer = WATER;
				monGraph->m_data[i]->m_layerID = WATER_ID;
				break;
			default:
				monGraph->m_data[i]->m_layer = NOTHING;
				monGraph->m_data[i]->m_layerID = -1; //Signifie que l'objet n'a pas d'ID
		}
		monGraph->m_data[i]->m_neighbors[0] = monGraph->m_data[i]->m_posY ? &monGraph->m_data[i-sizeX] : NULL;
		monGraph->m_data[i]->m_neighbors[1] = monGraph->m_data[i]->m_posX ? monGraph->m_data[i-1] : NULL;
		monGraph->m_data[i]->m_neighbors[2] = (monGraph->m_data[i]->m_posX+1) < sizeX ? monGraph->m_data[i+1] : NULL;
		monGraph->m_data[i]->m_neighbors[3] = ((monGraph->m_data[i]->m_posY+1)) < sizeY ? monGraph->m_data[i+sizeX] : NULL;
		monGraph->m_data[i]->m_data = NULL;
	}
	
	return graph;
}

void FreeGraph(graph* monGraph){
	if(!monGraph || !monGraph->m_data)
		return;
	
	for(int i = 0; i < sizeY*sizeX; i++){
		if(m_data)
			free(m_data); //peut causer des probl�mes si m_data est d'un type d�fini par l'utilisateur
		free(monGraph->m_data[i]);
	}
	free(monGraph->m_data);
	free(monGraph);
}