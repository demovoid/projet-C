#include "./graph.h"

int main(){
	int val;
	
	//Test de création du graphe
	/*
	
	graph* monGraph = LoadGraphFromFile("./map.ini");
	
	*/
	
	for(int i = 0; i < NB_GROUND; i++){
		val = GetLayerIDFromChar(s_groundChar[i]);
		printf("Pour %c: %d\n", s_groundChar[i], val);
	}
	
	/*
		
	*/
	
	//Test de libération du graphe
	/*
	
	freeGraph(monGraph);
	
	*/
	
	return 0;
}