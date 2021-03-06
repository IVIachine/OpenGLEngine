#ifndef MOUSE_PICKER_H
#define MOUSE_PICKER_H

#include "Graphics.h"
#include "Camera.h"
#include "Vector3.h"
#include "NavMesh.h"
#include "Node.h"

struct RayCastHit
{
	Vec3 point;
};

class MousePicker 
{
public:
	MousePicker(NavMesh* mesh) { m_navMesh = mesh; };
	~MousePicker() {};

	void update()
	{
		// these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height] After these lines the mouse X and y are still greater than and less than -1
		float mouseX = GRAPHICS->getLastX() / ((float)GRAPHICS->getWidth() * .5f)  - 1.0f;
		float mouseY = GRAPHICS->getLastY() / ((float)GRAPHICS->getHeight() * .5f) - 1.0f;

		glm::mat4 proj = GRAPHICS->getCamera()->getViewMatrix(); 
		glm::mat4 view = GRAPHICS->getCamera()->getProjectionMatrix();
		//glm::mat4 proj = GRAPHICS->getCamera()->getPerspective();
		//glm::mat4 view = GRAPHICS->getCamera()->getViewProjection(); //May need to swap these


		glm::mat4 invVP = glm::inverse(proj * view);
		glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f); //First 1.0f may need to be negative
		glm::vec4 worldPos = invVP * screenPos;

		Vec3 dir = glm::normalize(Vec3(worldPos));
		//std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
		m_Ray = worldPos;

		getCollision();
	}

	//Check for collision between mesh and ray
	Node* getCollision();


	Vec3 getRay() const { return m_Ray; };

	bool raycast(Vec3 origin, Vec3 dir, RayCastHit& hit);

private:
	Vec3		m_Ray;
	NavMesh*	m_navMesh;
	Node*		m_currentCollision;
};
#endif // !MOUSE_PICKER_H


/*
public Vector3f getCurrentTerrainPoint() {
		return currentTerrainPoint;
	}

	public Vector3f getCurrentRay() {
		return currentRay;
	}

	public void update() {
		viewMatrix = Maths.createViewMatrix(camera);
		currentRay = calculateMouseRay();
		if (intersectionInRange(0, RAY_RANGE, currentRay)) {
			currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, currentRay);
		} else {
			currentTerrainPoint = null;
		}
	}

	private Vector3f calculateMouseRay() {
		float mouseX = Mouse.getX();
		float mouseY = Mouse.getY();
		Vector2f normalizedCoords = getNormalisedDeviceCoordinates(mouseX, mouseY);
		Vector4f clipCoords = new Vector4f(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		Vector4f eyeCoords = toEyeCoords(clipCoords);
		Vector3f worldRay = toWorldCoords(eyeCoords);
		return worldRay;
	}

	private Vector3f toWorldCoords(Vector4f eyeCoords) {
		Matrix4f invertedView = Matrix4f.invert(viewMatrix, null);
		Vector4f rayWorld = Matrix4f.transform(invertedView, eyeCoords, null);
		Vector3f mouseRay = new Vector3f(rayWorld.x, rayWorld.y, rayWorld.z);
		mouseRay.normalise();
		return mouseRay;
	}

	private Vector4f toEyeCoords(Vector4f clipCoords) {
		Matrix4f invertedProjection = Matrix4f.invert(projectionMatrix, null);
		Vector4f eyeCoords = Matrix4f.transform(invertedProjection, clipCoords, null);
		return new Vector4f(eyeCoords.x, eyeCoords.y, -1f, 0f);
	}

	private Vector2f getNormalisedDeviceCoordinates(float mouseX, float mouseY) {
		float x = (2.0f * mouseX) / Display.getWidth() - 1f;
		float y = (2.0f * mouseY) / Display.getHeight() - 1f;
		return new Vector2f(x, y);
	}
	
	//**********************************************************
	
	private Vector3f getPointOnRay(Vector3f ray, float distance) {
		Vector3f camPos = camera.getPosition();
		Vector3f start = new Vector3f(camPos.x, camPos.y, camPos.z);
		Vector3f scaledRay = new Vector3f(ray.x * distance, ray.y * distance, ray.z * distance);
		return Vector3f.add(start, scaledRay, null);
	}
	
	private Vector3f binarySearch(int count, float start, float finish, Vector3f ray) {
		float half = start + ((finish - start) / 2f);
		if (count >= RECURSION_COUNT) {
			Vector3f endPoint = getPointOnRay(ray, half);
			Terrain terrain = getTerrain(endPoint.getX(), endPoint.getZ());
			if (terrain != null) {
				return endPoint;
			} else {
				return null;
			}
		}
		if (intersectionInRange(start, half, ray)) {
			return binarySearch(count + 1, start, half, ray);
		} else {
			return binarySearch(count + 1, half, finish, ray);
		}
	}

	private boolean intersectionInRange(float start, float finish, Vector3f ray) {
		Vector3f startPoint = getPointOnRay(ray, start);
		Vector3f endPoint = getPointOnRay(ray, finish);
		if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
			return true;
		} else {
			return false;
		}
	}

	private boolean isUnderGround(Vector3f testPoint) {
		Terrain terrain = getTerrain(testPoint.getX(), testPoint.getZ());
		float height = 0;
		if (terrain != null) {
			height = terrain.getHeightOfTerrain(testPoint.getX(), testPoint.getZ());
		}
		if (testPoint.y < height) {
			return true;
		} else {
			return false;
		}
	}

	private Terrain getTerrain(float worldX, float worldZ) {
		return terrain;
	}*/