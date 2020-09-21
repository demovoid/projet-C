#include "graph.h";

int main(int argc, char** argv)
{
	node* a = NULL;
	node* b = NULL;
	a = (node*)calloc(1, sizeof(node));
	a->m_posX = 6;
	a->m_posY = 6;

	b = (node*)calloc(1, sizeof(node));
	b->m_posX = 3;
	b->m_posY = 4;
	printf("Distance de manhattan = %d", GetManhattanDistance(a, b));
	return 0;
}