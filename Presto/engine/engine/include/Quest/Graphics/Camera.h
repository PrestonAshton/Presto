#ifndef QUEST_GRAPHICS_CAMERA_H
#define QUEST_GRAPHICS_CAMERA_H

#include <Quest/Common.h>
#include <Quest/Graphics/Transform.h>
#include <Quest/Math/Angle.h>

typedef enum
{
	Perspective = 0,
	InfinitePerspective = 1,
	Orthographic
} ProjectionType;

typedef struct
{
	ProjectionType projectionType;
	Radian fieldOfView;
	f32 orthographicScale;
	f32 nearClippingPlane;
	f32 farClippingPlane;
	f32 viewportAspectRatio;
	Transform transform;
} Camera;

Vector3 g_straightUp =  { 0.0f, 1.0f, 0.0f };

forceinline void CameraLookAtEquals(Camera* camera, const Vector3* position, const Vector3* up)
{
	Quaternion rotatedQuaternion = QuaternionLookAt(&camera->transform.position, position, up);
	camera->transform.orientation = QuaternionConjugate(&rotatedQuaternion);
}

void CameraOffsetOrientationEquals(Camera* camera, const Radian yaw, const Radian pitch);
Matrix4 CameraProjection(const Camera* camera);
Matrix4 CameraView(const Camera* camera);

forceinline Vector3 CameraForward(const Camera* camera)
{
	Vector3 forward = (Vector3) { 0.0f, 0.0f, -1.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &forward));
}

forceinline Vector3 CameraBackwards(const Camera* camera)
{
	Vector3 backwards = (Vector3) { 0.0f, 0.0f, 1.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &backwards));
}

forceinline Vector3 CameraRight(const Camera* camera)
{
	Vector3 right = (Vector3) { 1.0f, 0.0f, 0.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &right));
}

forceinline Vector3 CameraLeft(const Camera* camera)
{
	Vector3 left = (Vector3) { -1.0f, 0.0f, 0.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &left));
}
forceinline Vector3 CameraUp(const Camera* camera)
{
	Vector3 up = (Vector3) { 0.0f, 1.0f, 0.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &up));
}

forceinline Vector3 CameraDown(const Camera* camera)
{
	Vector3 down = (Vector3) { 0.0f, -1.0f, 0.0f };
	return(QuaternionMultiplyByVector3(&camera->transform.orientation, &down));
}

forceinline Matrix4 CameraMatrix(const Camera* camera)
{
	Matrix4 cameraProjection = CameraProjection(camera);
	Matrix4 cameraView = CameraView(camera);
	Matrix4HadamardEquals(&cameraProjection, &cameraView);
	return cameraProjection;
}

#endif
