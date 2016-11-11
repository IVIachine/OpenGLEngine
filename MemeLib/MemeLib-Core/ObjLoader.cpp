#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);
static inline size_t FindNextChar(size_t start, const char* str, size_t length, char token);
static inline size_t ParseOBJIndexValue(const std::string& token, size_t start, size_t end);
static inline float ParseOBJFloatValue(const std::string& token, size_t start, size_t end);
static inline std::vector<std::string> SplitString(const std::string &s, char delim);

OBJModel::OBJModel(const std::string& fileName)
{
	hasUVs = false;
	hasNormals = false;
	std::ifstream file;
	file.open(fileName.c_str());

	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			size_t lineLength = line.length();

			if (lineLength < 2)
				continue;

			const char* lineCStr = line.c_str();

			switch (lineCStr[0])
			{
			case 'v':
				if (lineCStr[1] == 't')
					this->uvs.push_back(ParseOBJVec2(line));
				else if (lineCStr[1] == 'n')
					this->normals.push_back(ParseOBJVec3(line));
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
					this->vertices.push_back(ParseOBJVec3(line));
				break;
			case 'f':
				CreateOBJFace(line);
				break;
			default: break;
			};
		}
	}
	else
	{
		std::cerr << "Unable to load mesh: " << fileName << std::endl;
	}
}

void IndexedModel::CalcNormals()
{
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		Vec3 v1 = positions[i1] - positions[i0];
		Vec3 v2 = positions[i2] - positions[i0];

		Vec3 normal = glm::normalize(glm::cross(v1, v2));

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	for (size_t i = 0; i < positions.size(); i++)
		normals[i] = glm::normalize(normals[i]);
}

IndexedModel OBJModel::ToIndexedModel()
{
	IndexedModel result;
	IndexedModel normalModel;
	result.actualPositions = vertices;
	result.actualIndices = indices;
	size_t numIndices = OBJIndices.size();

	std::vector<OBJIndex*> indexLookup;

	for (size_t i = 0; i < numIndices; i++)
		indexLookup.push_back(&OBJIndices[i]);

	std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

	std::map<OBJIndex, size_t> normalModelIndexMap;
	std::map<size_t, size_t> indexMap;

	for (size_t i = 0; i < numIndices; i++)
	{
		OBJIndex* currentIndex = &OBJIndices[i];

		Vec3 currentPosition = vertices[currentIndex->vertexIndex];
		Vec2 currentTexCoord;
		Vec3 currentNormal;

		if (hasUVs)
			currentTexCoord = uvs[currentIndex->uvIndex];
		else
			currentTexCoord = Vec2(0, 0);

		if (hasNormals)
			currentNormal = normals[currentIndex->normalIndex];
		else
			currentNormal = Vec3(0, 0, 0);

		size_t normalModelIndex;
		size_t resultModelIndex;

		//Create model to properly generate normals on
		std::map<OBJIndex, size_t>::iterator it = normalModelIndexMap.find(*currentIndex);
		if (it == normalModelIndexMap.end())
		{
			normalModelIndex = normalModel.positions.size();

			normalModelIndexMap.insert(std::pair<OBJIndex, size_t>(*currentIndex, normalModelIndex));
			normalModel.positions.push_back(currentPosition);
			normalModel.texCoords.push_back(currentTexCoord);
			normalModel.normals.push_back(currentNormal);
		}
		else
			normalModelIndex = it->second;

		//Create model which properly separates texture coordinates
		size_t previousVertexLocation = FindLastVertexIndex(indexLookup, currentIndex, result);

		if (previousVertexLocation == (size_t)-1)
		{
			resultModelIndex = result.positions.size();

			result.positions.push_back(currentPosition);
			result.texCoords.push_back(currentTexCoord);
			result.normals.push_back(currentNormal);
		}
		else
			resultModelIndex = previousVertexLocation;

		normalModel.indices.push_back(normalModelIndex);
		result.indices.push_back(resultModelIndex);
		indexMap.insert(std::pair<size_t, size_t>(resultModelIndex, normalModelIndex));
	}

	if (!hasNormals)
	{
		normalModel.CalcNormals();

		for (size_t i = 0; i < result.positions.size(); i++)
			result.normals[i] = normalModel.normals[indexMap[i]];
	}

	return result;
};

size_t OBJModel::FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result)
{
	size_t start = 0;
	size_t end = indexLookup.size();
	size_t current = (end - start) / 2 + start;
	size_t previous = start;

	while (current != previous)
	{
		OBJIndex* testIndex = indexLookup[current];

		if (testIndex->vertexIndex == currentIndex->vertexIndex)
		{
			size_t countStart = current;

			for (size_t i = 0; i < current; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current - i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;

				countStart--;
			}

			for (size_t i = countStart; i < indexLookup.size() - countStart; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current + i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;
				else if ((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
					&& (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
				{
					Vec3 currentPosition = vertices[currentIndex->vertexIndex];
					Vec2 currentTexCoord;
					Vec3 currentNormal;

					if (hasUVs)
						currentTexCoord = uvs[currentIndex->uvIndex];
					else
						currentTexCoord = Vec2(0, 0);

					if (hasNormals)
						currentNormal = normals[currentIndex->normalIndex];
					else
						currentNormal = Vec3(0, 0, 0);

					for (size_t j = 0; j < result.positions.size(); j++)
					{
						if (currentPosition == result.positions[j]
							&& ((!hasUVs || currentTexCoord == result.texCoords[j])
								&& (!hasNormals || currentNormal == result.normals[j])))
						{
							return j;
						}
					}
				}
			}

			return -1;
		}
		else
		{
			if (testIndex->vertexIndex < currentIndex->vertexIndex)
				start = current;
			else
				end = current;
		}

		previous = current;
		current = (end - start) / 2 + start;
	}

	return -1;
}

void OBJModel::CreateOBJFace(const std::string& line)
{
	std::vector<std::string> tokens = SplitString(line, ' ');

	this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
	this->OBJIndices.push_back(ParseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
	this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));

	if ((int)tokens.size() > 4)
	{
		this->OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
		this->OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
		this->OBJIndices.push_back(ParseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
	}
}

OBJIndex OBJModel::ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
{
	size_t tokenLength = token.length();
	const char* tokenString = token.c_str();

	size_t vertIndexStart = 0;

	OBJIndex result;
	if (token.find("//") == std::string::npos)
	{
		size_t vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
		result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
		indices.push_back(result.vertexIndex);
		result.uvIndex = 0;
		result.normalIndex = 0;

		if (vertIndexEnd >= tokenLength)
			return result;

		vertIndexStart = vertIndexEnd + 1;
		vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');


		result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
		*hasUVs = true;
		if (vertIndexEnd >= tokenLength)
			return result;

		vertIndexStart = vertIndexEnd + 1;
		vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

		result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);

		*hasNormals = true;
	}
	else
	{
		size_t vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');
		result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
		indices.push_back(result.vertexIndex);
		result.uvIndex = 0;
		result.normalIndex = 0;

		if (vertIndexEnd >= tokenLength)
			return result;

		vertIndexStart = vertIndexEnd + 2;

		result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, tokenLength);

		*hasNormals = true;
	}
	return result;
}

Vec3 OBJModel::ParseOBJVec3(const std::string& line)
{
	size_t tokenLength = line.length();
	const char* tokenString = line.c_str();

	size_t vertIndexStart = 2;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	size_t vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return Vec3(x, y, z);

	//Vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))
}

Vec2 OBJModel::ParseOBJVec2(const std::string& line)
{
	size_t tokenLength = line.length();
	const char* tokenString = line.c_str();

	size_t vertIndexStart = 3;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	size_t vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return Vec2(x, y);
}

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b)
{
	return a->vertexIndex < b->vertexIndex;
}

static inline size_t FindNextChar(size_t start, const char* str, size_t length, char token)
{
	size_t result = start;
	while (result < length)
	{
		result++;
		if (str[result] == token)
			break;
	}

	return result;
}

static inline size_t ParseOBJIndexValue(const std::string& token, size_t start, size_t end)
{
	return atoi(token.substr(start, end - start).c_str()) - 1;
}

static inline float ParseOBJFloatValue(const std::string& token, size_t start, size_t end)
{
	return std::stof(token.substr(start, end - start).c_str());
}

static inline std::vector<std::string> SplitString(const std::string &s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	size_t strLength = s.length();
	size_t start = 0;
	size_t end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}