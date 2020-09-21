#include "./data/graph.h"

void afficherGraphByTID(graph* g){
	if(!g || !g->m_data)
		return;
	
	for(int i = 0, l = 0; i < g->m_sizeY; i++){
		for(int j = 0; j < g->m_sizeX; j++)
			printf("%c ", s_groundChar[g->m_data[i*g->m_sizeX + j]->m_layerID]);
		printf("\n");
	}
}

void afficherGraphByID(graph* g){
	if(!g || !g->m_data)
		return;
	
	for(int i = 0, l = 0; i < g->m_sizeY; i++){
		for(int j = 0; j < g->m_sizeX; j++)
			printf("%03d ", g->m_data[i*g->m_sizeX + j]->m_id);
		printf("\n");
	}
}

int main(){
	int val;
	
	//Test de création du graphe
	graph* monGraph = LoadGraphFromFile("./data/map.ini");
	printf("Pointeur: %p\n",monGraph);
	printf("Dim: %d %d\n\n", monGraph->m_sizeX, monGraph->m_sizeY);
	afficherGraphByID(monGraph);
	printf("\n\n",monGraph);
	afficherGraphByTID(monGraph);
	
	
	/*
	for(int i = 0; i < NB_GROUND; i++){
		val = GetLayerIDFromChar(s_groundChar[i]);
		printf("Pour %c: %d\n", s_groundChar[i], val);
	}
	*/
	
	/*
		
	*/
	
	//Test de libération du graphe
	freeGraph(monGraph);
	
	return 0;
}