#include "MousePicker.h"
#include "NavMesh.h"

static int RECURSION_COUNT = 200;
static float RAY_RANGE = 600;

Node * MousePicker::getCollision()
{
	return m_currentCollision;
}

bool MousePicker::raycast(Vec3 origin, Vec3 dir, RayCastHit& hit)
{
	Vec3 targetPoint;
	float offset = .5f;
	std::vector<Vec3> verts = m_navMesh->getVerts();
	float minX, maxX, minY, maxY, minZ, maxZ;
	for (size_t i = 0; i < verts.size(); i++)
	{
		minX = verts[i].x - offset;
		maxX = verts[i].x + offset;
		minY = verts[i].y - offset;
		maxY = verts[i].y + offset;
		minZ = verts[i].z - offset;
		maxZ = verts[i].z + offset;

		float tmin = (minX - origin.x) / dir.x;
		float tmax = (maxX - origin.x) / dir.x;

		if (tmin > tmax) std::swap(tmin, tmax);

		float tymin = (minY - origin.y) / dir.y;
		float tymax = (maxY - origin.y) / dir.y;

		if (tymin > tymax) std::swap(tymin, tymax);

		if ((tmin > tymax) || (tymin > tmax))
		{
			continue;
		}

		if (tymin > tmin)
			tmin = tymin;

		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (minZ - origin.z) / dir.z;
		float tzmax = (maxZ - origin.z) / dir.z;

		if (tzmin > tzmax) std::swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
		{
			continue;
		}

		if (tzmin > tmin)
			tmin = tzmin;

		if (tzmax < tmax)
			tmax = tzmax;

		hit.point = verts[i];
		return true;
	}
	return false;
}
