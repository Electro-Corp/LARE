/*
    Class for the camera
*/
#pragma once

#include <Transform.hpp>
#include <Object.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LARE{
	//
	class Script;

    struct CameraData {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	class Camera : public Object{
	public:
		Camera(std::string name);

		Vector3 position, front;
		CameraData camData;
		double pAngle;

		void initScript() override;
		void update() override;
		void updateScript() override;
	};
}