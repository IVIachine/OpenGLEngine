#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include <Trackable.h>
#include <glm.hpp>

struct HE_Face;
struct HE_Vert;
struct HE_Edge;

struct HE_Edge
{


	HE_Vert* vert;
	HE_Edge* opposite;
	HE_Face* face;
	HE_Edge* next;
};

struct HE_Face
{
	HE_Edge* edge;
};

struct HE_Vert
{
	glm::vec3 mPos;
	HE_Edge* edge;
};
#endif