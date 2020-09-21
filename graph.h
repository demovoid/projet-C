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
	// TODO
};

struct sNode
{
	// TODO
};

struct sDijkstraNode
{
	// TODO
};

// TODO
