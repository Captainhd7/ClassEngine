#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 color;
};

class Mesh {
public:
	Mesh(std::vector<Vertex>&vertexList_, GLuint shaderProgram_);
	~Mesh();

	void Render(glm::mat4 transform_);

private:
	void GenerateBuffers();
	//VBO holds data, VAO tells GPU how data is split up
	GLuint VAO, VBO;	
	std::vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint modelLoc;

};

#endif