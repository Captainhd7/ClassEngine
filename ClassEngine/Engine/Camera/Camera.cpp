#include "Camera.h"

#include "../Core/CoreEngine.h"

std::vector<LightSource*> Camera::lights = std::vector<LightSource*>();

Camera::Camera() {
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenWidth() / CoreEngine::GetInstance()->GetSCreenHeight(), nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(), 0.0f, CoreEngine::GetInstance()->GetSCreenHeight(), -1.0f, 1.0f);

	UpdateCameraVectors();

}

Camera::~Camera() {
	if (lights.size() > 0) {
		for (auto t : lights) {
			delete t;
			t = nullptr;
		}
		lights.clear();
	}
}

void Camera::AddLight(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 color_) {
	LightSource* t = new LightSource(position_, ambient_, diffuse_, specular_, color_);
	lights.push_back(t);
}

void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_) {
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const {

	return view;
}

glm::mat4 Camera::GetPerspective() const {

	return perspective;
}

glm::mat4 Camera::GetOrthographic() const {

	return orthographic;
}

glm::vec3 Camera::GetPosition() const {

	return position;
}

std::vector<LightSource*> Camera::GetLightSources() const {
	return lights;
}

void Camera::UpdateCameraVectors() {
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(position, position + forward, up);
}
