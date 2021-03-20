#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 color_) {
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	color = color_;
}

LightSource::~LightSource() {

}

glm::vec3 LightSource::GetPosition() {
	return position;
}

float LightSource::GetAmbient() {
	return ambient;
}

float LightSource::GetDiffuse() {
	return diffuse;
}

float LightSource::GetSpecular() {
	return specular;
}

glm::vec3 LightSource::GetColor() {
	return color;
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetAmbient(float ambient_) {
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_) {
	diffuse = diffuse_;
}

void LightSource::SetSpecular(float specular_) {
	specular = specular_;
}

void LightSource::SetColor(glm::vec3 color_) {
	color = color_;
}
