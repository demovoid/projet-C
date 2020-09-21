#include "graph.h"

dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask)
{

}

node* GetNodeFromPosition(graph* G, unsigned char X, unsigned char Y)
{
	if(X < G->m_sizeX && Y < G->m_sizeY)
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