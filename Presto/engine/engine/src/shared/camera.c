Matrix4 CameraProjection(const Camera* camera)
{
	if (camera->projectionType == Perspective)
	{
		return(
			Matrix4Perspective(
				camera->fieldOfView,
				camera->viewportAspectRatio,
				camera->nearClippingPlane,
				camera->farClippingPlane
			));
	}
	else if (camera->projectionType == Orthographic)
	{
		f32 distance = 0.5f * (camera->farClippingPlane - camera->nearClippingPlane);
		return(
			Matrix4OrthoClipped(
				-camera->orthographicScale * camera->viewportAspectRatio,
				camera->orthographicScale + camera->viewportAspectRatio,
				-camera->orthographicScale,
				camera->orthographicScale,
				-distance,
				distance
			));
	}
	else if (camera->projectionType == InfinitePerspective)
	{
		return(
			Matrix4InfinitePerspective(
				camera->fieldOfView,
				camera->viewportAspectRatio,
				camera->nearClippingPlane
			)
			);
	}
	else
	{
		AssertMsg(0 == 1, V("Umm... we shouldn't get here... EVER!"));
		return(Matrix4Identity);
	}
}

void CameraOffsetOrientationEquals(Camera* camera, const Radian yaw, const Radian pitch)
{
	Vector3 staticUp = (Vector3) { 0.0f, 1.0f, 0.0f };
	Quaternion yawRot = QuaternionAngleAxis(yaw, &staticUp);
	// pitch
	Vector3 cameraRight = CameraRight(camera);
	Quaternion pitchRot = QuaternionAngleAxis(pitch, &cameraRight);
	// multiply yaw and pitch
	QuaternionMultiplyEquals(&yawRot, &pitchRot);
	// multiply that with current rotation
	QuaternionMultiplyEquals(&camera->transform.orientation, &yawRot);
}


/*
Matrix4 view(const Camera& camera)
{
  Matrix4 view = Matrix4Identity;

  view = scale(Vector3{ 1, 1, 1 } / camera.transform.scale) *
	quaternionToMatrix4(conjugate(&camera.transform.orientation)) *
	translate(-camera.transform.position);

  return view;
}
*/

Matrix4 CameraView(const Camera* camera)
{
	// return Math::scale(Vector3{1, 1, 1} / c.transform.scale) * quaternionToMatrix4(conjugate(c.transform.orientation)) * Math::translate(-c.transform.position);

	// Math::scale(Vector3{1, 1, 1} / c.transform.scale)
	Vector3 numerator = { 1.0f, 1.0f, 1.0f };
	Vector3 scaleReciprocal = Vector3Divide(&numerator, &camera->transform.scale);
	Matrix4 scaledReciprocatedScale = Matrix4Scale(&scaleReciprocal);
	// ^^ product

	// quaternionToMatrix4(conjugate(c.transform.orientation))
	Quaternion orientationConjugate = QuaternionConjugate(&camera->transform.orientation);
	Matrix4 orientationConjugateMatrix = QuaternionToMatrix4(&orientationConjugate);
	// ^^ product

	// Math::translate(-c.transform.position);
	Vector3 negativePosition = Vector3Negative(&camera->transform.position);
	Matrix4 negativeTranslationMatrix = Matrix4Translate(&negativePosition);
	// ^^ product

	// scaledReciprocatedScale is resultant.
	// Math::scale(Vector3{1, 1, 1} / c.transform.scale) * quaternionToMatrix4(conjugate(c.transform.orientation)) * Math::translate(-c.transform.position);

	Matrix4HadamardEquals(&scaledReciprocatedScale, &orientationConjugateMatrix);
	Matrix4HadamardEquals(&scaledReciprocatedScale, &negativeTranslationMatrix);

	return scaledReciprocatedScale;
}
