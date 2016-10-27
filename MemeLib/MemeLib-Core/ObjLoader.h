#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include <string>
#include <Trackable.h>

struct OBJIndex : public Trackable
{
	size_t vertexIndex;
	size_t uvIndex;
	size_t normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel : public Trackable
{
public:
	std::vector<Vec3> positions;
	std::vector<Vec2> texCoords;
	std::vector<Vec3> normals;
	std::vector<size_t> indices;
	std::vector<Vec3> actualPositions;
	std::vector<size_t> actualIndices;
	void CalcNormals();
};

class OBJModel : public Trackable
{
public:
	std::vector<OBJIndex> OBJIndices;
	std::vector<Vec3> vertices;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<size_t> indices;
	bool hasUVs;
	bool hasNormals;

	OBJModel(const std::string& fileName);

	IndexedModel ToIndexedModel();
private:
	size_t FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
	void CreateOBJFace(const std::string& line);

	Vec2 ParseOBJVec2(const std::string& line);
	Vec3 ParseOBJVec3(const std::string& line);
	OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

#endif // OBJ_LOADER_H_INCLUDED