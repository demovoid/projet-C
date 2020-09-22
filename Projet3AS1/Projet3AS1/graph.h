#ifndef _GRAPH_H_
#define _GRAPH_H

#ifdef _GRAPH_C_
#define	LIB_API	__declspec(dllexport)
#else
#define	LIB_API	__declspec(dllimport)
#endif // _LIB_C_

#include <stdlib.h>
#include <stdio.h>

/**
 * \file graph.h
 * \brief Librairie comprenant la gestion de graph et le calcul du plus court chemin via Dijkstra
 * \author DIDIER Thomas et ROUSSEAU Martin
 * \version 1.0
 * \date 22/09/2020
*/

#define INFINITY_DIST		0xFFFF /**< Valeur pour caractériser l'impossibilité d'accès au sommet */

typedef struct sDijkstraNode dijkstraNode; 
typedef struct sGraph graph;
typedef struct sNode node;

/**
 * \enum eGroundMask
 * \brief Valeur des masques pour les types de terrains. A additionner pour avoir un masque d'autorisation de déplacement dans le graphe
*/
enum eGroundMask
{
	NOTHING		= 0b00000000, /**< Rien */

	GRASS		= 0b00000001, /**< Seulement l'herbe */
	FOREST		= 0b00000010, /**< Seulement la foret */
	MOUNTAIN	= 0b00000100, /**< Seulement la montagne */
	CITY		= 0b00001000, /**< Seulement la ville */
	ROAD		= 0b00010000, /**< Seulement la route */
	WATER		= 0b00100000, /**< Seulement l'eau */

	EVERYTHING	= 0b11111111 /**< Tout */
};

/**
 * \enum eGroundID
 * \brief Identifiants des types de terrains
*/
enum eGroundID
{
	GRASS_ID, /**< 0 = Herbe */
	FOREST_ID, /**< 1 = Foret */
	MOUNTAIN_ID, /**< 2 = Montagne */
	CITY_ID, /**< 3 = Ville */
	ROAD_ID, /**< 4 = Route */
	WATER_ID, /**< 5 = Eau */
	NB_GROUND /**< 6 = nombre de terrain possible */
};


static const char s_groundChar[NB_GROUND] = {
	'G',
	'F',
	'M',
	'C',
	'R',
	'W'
}; /**< Caractère pour identifier un terrain */

enum eNeighbourPosition
{
	NP_UP,
	NP_LEFT,
	NP_RIGHT,
	NP_DOWN,
	NB_NEIGHBORS
};

/**
 * \struct sGraph
 * \brief Un graphe représenté avec une taille en deux dimensions et ses données(un tableau à une entrée)
*/
struct sGraph
{
	int m_sizeX; /**< Nombre de noeud sur la longueur */
	int m_sizeY; /**< Nombre de noeud sur la hauteur */
	node** m_data; /**< Tous les noeud en chaine sans retour à la ligne (pour la hauteur) */
};

/**
 * \struct sNode
 * \brief Un noeud de graphe
*/
struct sNode
{
	unsigned int m_id; /**< Identifiant du noeud */
	unsigned char m_posX; /**< Position du noeud abscisses(longueur) */
	unsigned char m_posY; /**< Position du noeud ordonnées(hauteur) */
	unsigned char m_layer; /**< Masque du noeud (type de terrain) */
	unsigned int m_layerID; /**< Identifiant du masque (id du terrain) */
	node* m_neighbors[NB_NEIGHBORS]; /**< Les voisins du noeud (NULL = pas de voisin). 0: Voisin nord, 1: voisin ouest, 2: voisin est, 3: voisin sud */
	void* m_data; /**< Pointeur générique de données. Permet de stocker n'importe quoi */
};

/**
 * \struct sDijkstraNode
 * \brief Un noeud de graphe avec les informations de l'algo de Dijkstra
*/
struct sDijkstraNode
{
	node* m_node; /**< Le noeud correspondant aux données de la structure */	
	int m_distance; /**< Distance parcourue entre le point de départ et ce noeud */
	unsigned char m_flag; /**< Indique si le noeud a déjà été parcouru */
	dijkstraNode* m_prev; /**< Noeud précédent (chemin) */
};

LIB_API	graph* LoadGraphFromFile(char* fichier);
LIB_API	void freeGraph(graph* monGraph);
LIB_API	int GetLayerIDFromChar(char c);
LIB_API	dijkstraNode** Dijkstra(graph* G, node* init, unsigned char mask);
LIB_API	void FreeDijkstra(dijkstraNode** d, int size);
LIB_API	node* GetNodeFromPosition(graph* G, unsigned char X, unsigned char Y);
LIB_API	int GetManhattanDistance(node* a, node* b);
LIB_API	int GetLayerIDFromChar(char character);
LIB_API	char IsNeighbour(node* a, node* b);
LIB_API	void SetNodeData(node* noeud, void* data); //mettre data dans le champ de noeud
LIB_API	void* GetNodeData(node* noeud);

#endif