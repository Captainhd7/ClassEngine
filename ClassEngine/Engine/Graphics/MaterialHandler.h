#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

struct Material {
	GLuint diffuseMap = 0; //newmtl

	float shininess = 32.0f; //Ns
	float transparency = 1.0f; //d

	glm::vec3 ambient = glm::vec3(1.0f); //Ka
	glm::vec3 diffuse = glm::vec3(1.0f); //Kd
	glm::vec3 specular = glm::vec3(1.0f); //Ks

	std::string name = "";
};

class MaterialHandler {
public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();
	void AddMaterial(Material mat_);
	Material GetMaterial(const std::string& matName_) const;
	void OnDestroy();

private:
	MaterialHandler();
	~MaterialHandler();

	static std::unique_ptr<MaterialHandler> materialInstance;
	friend std::default_delete<MaterialHandler>;

	static std::vector<Material> materials;
};

#endif