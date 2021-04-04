#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {

}

void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, __FILE__, __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		else if (line.substr(0, 4) == "\tKa ") {
			std::stringstream v(line.substr(4));
			v >> m.ambient.x >> m.ambient.y >> m.ambient.z;
		}
		else if (line.substr(0, 4) == "\tKd ") {
			std::stringstream v(line.substr(4));
			v >> m.diffuse.x >> m.diffuse.y >> m.diffuse.z;
		}
		else if (line.substr(0, 4) == "\tKs ") {
			std::stringstream v(line.substr(4));
			v >> m.specular.x >> m.specular.y >> m.specular.z;
		}
		else if (line.substr(0, 4) == "\tNs ") {
			std::stringstream v(line.substr(4));
			v >> m.shininess;
		}
		else if (line.substr(0, 4) == "\td ") {
			std::stringstream v(line.substr(4));
			v >> m.transparency;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstace()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstace()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstace()->GetTexture(fileName_);
	}
	return currentTexture;
}
