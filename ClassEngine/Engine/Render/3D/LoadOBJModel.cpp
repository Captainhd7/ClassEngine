#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() {
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMesh() {
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const {
	return boundingBox;
}

void LoadOBJModel::PostProcessing() {
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("cannot open OBJ file: " + filePath_, __FILE__, __LINE__);
		return;
	}

	std::string line;

	boundingBox.minVert = glm::vec3(FLT_MAX);
	boundingBox.maxVert = glm::vec3(FLT_MIN);

	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			boundingBox.minVert.x = x < boundingBox.minVert.x ? x : boundingBox.minVert.x;
			boundingBox.maxVert.x = x > boundingBox.maxVert.x ? x : boundingBox.maxVert.x;

			boundingBox.minVert.y = y < boundingBox.minVert.y ? y : boundingBox.minVert.y;
			boundingBox.maxVert.y = y > boundingBox.maxVert.y ? y : boundingBox.maxVert.y;

			boundingBox.minVert.z = z < boundingBox.minVert.z ? z : boundingBox.minVert.z;
			boundingBox.maxVert.z = z > boundingBox.maxVert.z ? z : boundingBox.maxVert.z;
		}

		//TEXTURE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//FACE DATA
		else if (line.substr(0, 2) == "f ") {
			std::stringstream v(line.substr(2));
			char slash;
			int x, y, z, xT, yT, zT, xN, yN, zN;
			v >> x >> slash >> xT >> slash >> xN >> y >> slash >> yT >> slash >> yN >> z >> slash >> zT >> slash >> zN;

			x--; y--; z--;
			xT--; yT--; zT--;
			xN--; yN--; zN--;

			indices.push_back(x);
			indices.push_back(y);
			indices.push_back(z);

			normalIndices.push_back(xN);
			normalIndices.push_back(yN);
			normalIndices.push_back(zN);

			textureIndices.push_back(xT);
			textureIndices.push_back(yT);
			textureIndices.push_back(zT);
		}

		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}
