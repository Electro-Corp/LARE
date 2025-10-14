/*
    Class for the camera
*/
#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LARE{
    struct CameraData {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	class Camera {
	public:
		CameraData camData;
		double pAngle;
	};
}