#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource {
public:
	
	LightSource(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 color_);
	~LightSource();

	glm::vec3 GetPosition();
	float GetAmbient();
	float GetDiffuse();
	float GetSpecular();
	glm::vec3 GetColor();

	void SetPosition(glm::vec3 position_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
	void SetColor(glm::vec3 color_);


private:
	glm::vec3 position;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 color;
};

#endif