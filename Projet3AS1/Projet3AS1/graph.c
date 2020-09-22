#define _GRAPH_C_

#include "./graph.h"

/**
 * \file graph.c
 * \brief Fonctions de la librairie comprenant la gestion de graph et le calcul du plus court chemin via Dijkstra
 * \author DIDIER Thomas et ROUSSEAU Martin
 * \version 1.0
 * \date 22/09/2020
*/

/**
 * \brief Charge le graphe depuis un fichier donné
 *
 * @param fichier Chemin vers le fichier à lire
 *
 * @return Pointeur sur un graphe
*/
graph* LoadGraphFromFile(char* fichier){

LIB_API	graph* LoadGraphFromFile(char* fichier){
	
		graph* monGraph = NULL;
		FILE* monFichier = fopen(fichier,"r");
	
		if(!monFichier)
			return NULL;
	
		int sizeX, sizeY;
		fscanf(monFichier,"%d%d", &sizeX, &sizeY);
	
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
	
		for(int i = 0; i < sizeY*sizeX && !feof(monFichier); i++){
			do{
				fscanf(monFichier,"%c",&c); //erreur si fichier non complet !!!
			}while((c < 'A' || c > 'Z') && !feof(monFichier));
			monGraph->m_data[i]->m_id = i;
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
			monGraph->m_data[i]->m_neighbors[0] = monGraph->m_data[i]->m_posY ? monGraph->m_data[i-sizeX] : NULL;
			monGraph->m_data[i]->m_neighbors[1] = monGraph->m_data[i]->m_posX ? monGraph->m_data[i-1] : NULL;
			monGraph->m_data[i]->m_neighbors[2] = (monGraph->m_data[i]->m_posX+1) < sizeX ? monGraph->m_data[i+1] : NULL;
			monGraph->m_data[i]->m_neighbors[3] = (monGraph->m_data[i]->m_posY+1) < sizeY ? monGraph->m_data[i+sizeX] : NULL;
			monGraph->m_data[i]->m_data = NULL;
		}

		fclose(monFichier);
	
		return monGraph;
	}

/**
 * \brief Libère la mémoire allouée pour le graph
 *
 * @param monGraph Graphe à libérer
*/
LIB_API	void freeGraph(graph* monGraph){
		if(!monGraph || !monGraph->m_data)
			return;
	
		for(int i = 0; i < monGraph->m_sizeY*monGraph->m_sizeX; i++)
			free(monGraph->m_data[i]);

	free(monGraph->m_data);
	free(monGraph);
}

/**
 * \brief Applique l'algorithme de Dijkstra à un graphe
 *
 * @param G Pointeur sur le graphe sur lequel appliquer l'algo
 * @param init Point de départ (noeud par lequel le chemin commence)
 * @param mask Masque indiquant les types de terrain qui sont traversables
 *
 * @return Tableau de noeud avec les caractisques calculées par l'algo de Dijkstra
*/
dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask)
{
	int nbCells = G->m_sizeX * G->m_sizeY;
	dijkstraNode** nd = malloc(sizeof(dijkstraNode*) * nbCells);
	for(int i = 0; i < nbCells; i++){
		nd[i] = malloc(sizeof(dijkstraNode));
		nd[i]->m_node = G->m_data[i]; 
		nd[i]->m_distance = INFINITY_DIST;
		nd[i]->m_flag = 0; 
		nd[i]->m_prev = NULL;
	}

LIB_API	dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask)
	{
		int nbCells = G->m_sizeX * G->m_sizeY;
		dijkstraNode** nd = malloc(sizeof(dijkstraNode*) * nbCells);
		for(int i = 0; i < nbCells; i++){
			nd[i] = malloc(sizeof(dijkstraNode));
			nd[i]->m_node = G->m_data[i]; 
			nd[i]->m_distance = INFINITY_DIST;
			nd[i]->m_flag = 0; 
			nd[i]->m_prev = NULL;
		}

		int indice = init->m_posY*G->m_sizeX + init->m_posX;

		nd[indice]->m_distance = 0;
		nd[indice]->m_flag = 1;

		dijkstraNode* target = NULL;
		dijkstraNode* next;

		do{
			next = NULL;
			for(int i = 0; i < 4; i++){
				if(nd[indice]->m_node->m_neighbors[i] && nd[indice]->m_node->m_neighbors[i]->m_layer & mask){
					target = nd[G->m_data[indice]->m_neighbors[i]->m_posY*G->m_sizeX + G->m_data[indice]->m_neighbors[i]->m_posX];
					if(!target->m_flag){
						if(target->m_distance > nd[indice]->m_distance + 1)
							target->m_distance = nd[indice]->m_distance + 1;
						if(!next || next->m_distance > target->m_distance)
							next = target;
					}
				}
			}

			if(!next)
				next = nd[indice]->m_prev;
			else{
				next->m_flag = 1;
				next->m_prev = nd[indice];
			}

			indice = next ? next->m_node->m_posY*G->m_sizeX + next->m_node->m_posX : -1;
		
		}while(next);
	
		return nd;

	}

/**
 * \brief Libère la mémoire allouée par Dijkstra
 *
 * @param d Tableau de noeux issu de l'algo de Dijkstra
 * @param size Nombre de cases allouées dans le tableau
*/
LIB_API	void FreeDijkstra(dijkstraNode** d, graph* g){
		if(!d)
			return;
	
	for(int i = 0; i < size; i++)
		free(d[i]);
		
		free(d);
	}

/**
 * \brief Permet de récuperer la position d'un noeud dans un graphe
 *
 * @param G Pointeur sur le graphe dans lequel chercher
 * @param X Valeur en abscisse (longueur) du noeud cherché
 * @param Y Valeur en ordonnée (hauteur) du noeud cherché
 *
 * @return Pointeur sur le noeud recherché (s'il existe, NULL sinon)
*/
LIB_API	node* GetNodeFromPosition(graph* G, unsigned char X, unsigned char Y)
	{
		if(X < (unsigned int)G->m_sizeX && Y < (unsigned int)G->m_sizeY)
			return G->m_data[Y * G->m_sizeX + X];
		return NULL;
	}

/**
 * \brief Permet d'obtenir la distance de Manhattan entre deux noeux
 *
 * @param a Premier noeud
 * @param b Second noeud
 *
 * @return La distance de Manhattan entre les deux noeud
*/
LIB_API	int GetManhattanDistance(node* a, node* b)
	{
		int dx = b->m_posX - a->m_posX;
		int dy = b->m_posY - a->m_posY;
		if (dx < 0)
			dx = -dx;
		if (dy < 0)
			dy = -dy;
		return dx + dy;
	}

/**
 * \brief Verifie si deux noeud sont voisins
 *
 * @param a Premier noeud
 * @param b Second noeud
 *
 * @return 1 si les noeud sont voisins, 0 sinon
*/
LIB_API	char IsNeighbour(node* a, node* b)
{
	for (int i = 0; i < 4; i++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a->m_neighbors[i])
			{
				if (a->m_neighbors[i] == b)
					return 1;
			}
		}
		return 0;
	}

int GetLayerIDFromChar(char c){
	switch(c){
		case 'G':
			return GRASS_ID;
		case 'F':
			return FOREST_ID;
		case 'M':
			return MOUNTAIN_ID;
		case 'C':
			return CITY_ID;
		case 'R':
			return ROAD_ID;
		case 'W':
			return WATER_ID;
		default:
			return -1;

		}
	}

void SetNodeData(node* node, void* valeur){
	node->m_data = valeur;
}

void* GetNodeData(node* node){
	return node->m_data;
}