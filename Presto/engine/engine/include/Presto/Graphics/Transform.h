#ifndef PRESTO_GRAPHICS_TRANSFORM_H
#define PRESTO_GRAPHICS_TRANSFORM_H

#include <Presto/Common.h>
#include <Presto/Math.h>

typedef struct
{
	Vector3 position;
	Vector3 scale;
	Quaternion orientation;
} Transform;

#define TransformIdentity \
(Transform) \
{ \
	{ 0.0f, 0.0f, 0.0f }, \
	{ 1.0f, 1.0f, 1.0f }, \
	QuaternionIdentity \
} \

forceinline Transform TransformMultiply(const Transform* parentSpace, const Transform* localSpace)
{
	Transform worldSpace;
	Vector3 localSpaceScaled = Vector3Multiply(&localSpace->position, &parentSpace->scale);
	Vector3 localSpaceOriented = QuaternionMultiplyByVector3(&parentSpace->orientation, &localSpaceScaled);
	worldSpace.position = Vector3Add(&parentSpace->position, &localSpaceOriented);
	worldSpace.orientation = QuaternionMultiply(&parentSpace->orientation, &localSpace->orientation);
	Vector3 parentSpaceOrientationScaled = QuaternionMultiplyByVector3(&parentSpace->orientation, &localSpace->scale);
	worldSpace.scale = Vector3Multiply(&parentSpaceOrientationScaled, &parentSpace->scale);

	return(worldSpace);
}

forceinline Transform* TransformMultiplyEquals(Transform* parentSpace, const Transform* localSpace)
{
	(*parentSpace) = TransformMultiply(parentSpace, localSpace);
	return(parentSpace);
}

forceinline Transform TransformDivide(const Transform* worldSpace, const Transform* parentSpace)
{
	Transform localSpace;
	Quaternion parentSpaceConjugation = QuaternionConjugate(&parentSpace->orientation);
	Vector3 positionNegation = Vector3Minus(&worldSpace->position, &worldSpace->position);
	Vector3 rotate = QuaternionMultiplyByVector3(&parentSpaceConjugation, &positionNegation);
	localSpace.position = Vector3Divide(&rotate, &parentSpace->scale);
	localSpace.orientation = QuaternionMultiply(&parentSpaceConjugation, &worldSpace->orientation);
	Vector3 scaleUnrotated = Vector3Divide(&worldSpace->scale, &parentSpace->scale);
	localSpace.scale = QuaternionMultiplyByVector3(&parentSpaceConjugation, &scaleUnrotated);

	return(localSpace);
}

forceinline Transform* TransformDivideEquals(Transform* worldSpace, const Transform* parentSpace)
{
	(*worldSpace) = TransformMultiply(worldSpace, parentSpace);
	return(worldSpace);
}

forceinline Vector3 TransformVector3(const Transform* transform, const Vector3* point)
{
	Quaternion orientationConjugate = QuaternionConjugate(&transform->orientation);
	Vector3 positionDifference = Vector3Minus(&transform->position, &point);
	Vector3 unscaledTransformation = QuaternionMultiplyByVector3(&orientationConjugate, &positionDifference);
	return(Vector3Divide(&unscaledTransformation, &transform->scale));
}

forceinline Transform TransformInverse(const Transform* transform)
{
	Transform inverseTransform;

	inverseTransform.orientation = QuaternionConjugate(&transform->orientation);

	Vector3 negativePosition = Vector3Negative(&transform->position);
	Vector3 rotatedNegativeUnscaled = QuaternionMultiplyByVector3(&inverseTransform.orientation, &negativePosition);
	inverseTransform.position = Vector3Divide(&rotatedNegativeUnscaled, &transform->scale);

	Vector3 numerator = (Vector3) { 1.0f, 1.0f, 1.0f };
	Vector3 reciprocalScale = Vector3Divide(&numerator, &transform->scale);
	inverseTransform.scale = QuaternionMultiplyByVector3(&inverseTransform.orientation, &reciprocalScale);

	return(inverseTransform);

}

#endif