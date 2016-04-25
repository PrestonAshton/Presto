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
		f32 distance = 0.5 * (camera->farClippingPlane - camera->nearClippingPlane);
		return(
			Matrix4Ortho(
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
  Vector3 numerator = (Vector3){1.0f, 1.0f, 1.0f};
  Vector3 scaleReciprocal = Vector3Divide(&numerator, &camera->transform.scale);
  // is used as return value below also
  Matrix4 scaleMatrix = Matrix4Scale(&scaleReciprocal);
  Quaternion orientationConjugate = QuaternionConjugate(&camera->transform.orientation);
  Matrix4 conjugateMatrix = QuaternionToMatrix4(&orientationConjugate);
  Vector3 negativePosition = Vector3Negative(&camera->transform.position);
  Matrix4 negativeTranslationMatrix = Matrix4Translate(&negativePosition);

  // scale
  Matrix4HadamardEquals(&scaleMatrix, &conjugateMatrix);
  Matrix4HadamardEquals(&scaleMatrix, &negativeTranslationMatrix);

  return(scaleMatrix);
}
