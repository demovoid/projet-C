#include "graph.h"

#include <string.h>

void afficherGraphByTID(graph* g){
	if(!g || !g->m_data)
		return;

	char couleur[20];
	
	for(int i = 0; i < g->m_sizeY; i++){
		for(int j = 0; j < g->m_sizeX; j++){
			switch(g->m_data[i*g->m_sizeX + j]->m_layerID){
				case GRASS_ID:
					strcpy(couleur,"\x1b[38;2;0;255;127m");
					break;
				case FOREST_ID:
					strcpy(couleur,"\033[0;32;40m");
					break;
				case MOUNTAIN_ID:
					strcpy(couleur,"\033[0;31;40m");
					break;
				case CITY_ID:
					strcpy(couleur,"\033[0;33;40m");
					break;
				case ROAD_ID:
					strcpy(couleur,"\x1b[38;2;255;215;0m");
					break;
				case WATER_ID:
					strcpy(couleur,"\033[0;36;40m");
					break;
				default:
					strcpy(couleur,"");
			}
			printf("%s%c\x1b[0m ", couleur, s_groundChar[g->m_data[i*g->m_sizeX + j]->m_layerID]);
		}
		printf("\n");
	}
}

void afficherGraphByID(graph* g){
	if(!g || !g->m_data)
		return;

	for(int i = 0; i < g->m_sizeY; i++){
		for(int j = 0; j < g->m_sizeX; j++){
			printf("%03d ", g->m_data[i*g->m_sizeX + j]->m_id);
		}
		printf("\n");
	}
}

void afficherDijkstra(dijkstraNode** d, graph* g){
	if(!d)
		return;

	for(int i = 0; i < g->m_sizeY; i++){
		for(int j = 0; j < g->m_sizeX; j++)
			printf("%s%05d\x1b[0m ", d[i * g->m_sizeX + j]->m_distance == INFINITY_DIST ? "\033[0;31;40m" : (d[i * g->m_sizeX + j]->m_distance ? "" : "\033[0;32;40m"), d[i * g->m_sizeX + j]->m_distance);
		printf("\n");
	}
}

int main(int argc, char** argv){
	int val;
	
	//Test de création du graphe
	graph* monGraph = LoadGraphFromFile("./map.ini");
	printf("Pointeur: %p\n",monGraph);
	printf("Dim: %d %d\n\n", monGraph->m_sizeX, monGraph->m_sizeY);
	afficherGraphByID(monGraph);
	printf("\n\n",monGraph);
	afficherGraphByTID(monGraph);
	
	printf("\n");	
	for(int i = 0; i < NB_GROUND; i++){
		val = GetLayerIDFromChar(s_groundChar[i]);
		//printf("Pour %c: %d\n", s_groundChar[i], val);
	}
	
	dijkstraNode** new = Dijkstra(monGraph, GetNodeFromPosition(monGraph,1,0),0b111);
	printf("Pointeur: %p\n", new);

	afficherDijkstra(new,monGraph);

	FreeDijkstra(new,monGraph->m_sizeX*monGraph->m_sizeY);
	
	//Test de libération du graphe
	freeGraph(monGraph);
	
	return 0;
}