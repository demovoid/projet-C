#include "./graph.h"

graph* LoadGraphFromFile(char* fichier){
	
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

void freeGraph(graph* monGraph){
	if(!monGraph || !monGraph->m_data)
		return;
	
	for(int i = 0; i < monGraph->m_sizeY*monGraph->m_sizeX; i++)
		free(monGraph->m_data[i]);

	free(monGraph->m_data);
	free(monGraph);
}

dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask)
{
	int nbCells = G->m_sizeX * G->m_sizeY;
	dijkstraNode* nd = (dijkstraNode*)calloc(1, sizeof(dijkstraNode));
	
}

node* GetNodeFromPosition(graph* G, unsigned char X, unsigned char Y)
{
	if(X < (unsigned int)G->m_sizeX && Y < (unsigned int)G->m_sizeY)
		return G->m_data[Y * G->m_sizeX + X];
	return NULL;
}

int GetManhattanDistance(node* a, node* b)
{
	int dx = b->m_posX - a->m_posX;
	int dy = b->m_posY - a->m_posY;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	return dx + dy;
}

char IsNeighbour(node* a, node* b)
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