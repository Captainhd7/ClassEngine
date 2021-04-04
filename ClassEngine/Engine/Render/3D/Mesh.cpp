#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) {
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_) {
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3f(viewPositionLoc, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1f(lightAmbientLoc, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform1f(lightSpecularLoc, camera_->GetLightSources()[0]->GetSpecular());
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetColor()));

	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform3fv(matAmbientLoc, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuseLoc, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecularLoc, 1, glm::value_ptr(subMesh.material.specular));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(shaderProgram, "light.specular");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.color");
	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecularLoc = glGetUniformLocation(shaderProgram, "material.specular");
}
