#include "Mesh.hpp"

namespace LARE{

Mesh::Mesh(std::vector<Vertex> verts, std::vector<uint16_t> inds, std::vector<Texture> textures) {
	this->vertices = verts;
	this->indices = inds;
    this->textures = textures;
	this->modified = true;
}

void Mesh::initMesh(){
     // Lets get our data in !
    glGenVertexArrays(1, &(VAO));
    glGenBuffers(1, &(VBO));
    glGenBuffers(1, &(EBO));
    // bind the Vertex Array Object
    glBindVertexArray(VAO);

    // Bind the Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, getVertsRealSize(), packVerts(), GL_STATIC_DRAW);

    // Bind the Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndsRealSize(), packInds(), GL_STATIC_DRAW);
    
    float* vals = packVerts();

    // Attributes!
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);
    // Texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Bind our vertex array
    glBindVertexArray(0);
}

void Mesh::drawMesh(unsigned int shaderProgram, Transform transform, Camera* cam){
    // Use shader program
    glUseProgram(shaderProgram);
    // Apply transform
    int transformLocation = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform.transform));
    // Setup camera
    int modelLocation = glGetUniformLocation(shaderProgram, "model");
    int viewLocation = glGetUniformLocation(shaderProgram, "view");
    int projLocation = glGetUniformLocation(shaderProgram, "proj");
    // Set values within shader
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform.transform));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam->camData.view));
    // Projection matrix... lets set it up
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(cam->camData.proj));
    // Textures
    unsigned int diffuseN = 1;
    unsigned int specN = 1;
    unsigned int normalN = 1;
    for(int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        std::string num;
        std::string name = textures[i].type;
        // Spec or diff
        if(name == "texture_diffuse"){
            num = std::to_string(diffuseN++);
        }else if(name == "texture_specular"){
            num = std::to_string(specN++);
        }else if (name == "texture_normal"){
            num = std::to_string(normalN++);
        }
        int matLocation = glGetUniformLocation(shaderProgram, std::string{"material." + name + num}.c_str());
        glUniform1i(matLocation, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    // Draw
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, getIndsRealSize(), GL_UNSIGNED_INT, 0);
}

float* Mesh::packVerts() {
	float* fVerts = (float*)malloc(this->getVertsRealSize());
	if (fVerts) {
		for (int i = 0; i < vertices.size(); i++) {
			int baseMod = i * 8;
			fVerts[baseMod] = vertices[i].pos.x;
			fVerts[1 + baseMod] = vertices[i].pos.y;
			fVerts[2 + baseMod] = vertices[i].pos.z;
			fVerts[3 + baseMod] = vertices[i].normal.x;
			fVerts[4 + baseMod] = vertices[i].normal.y;
			fVerts[5 + baseMod] = vertices[i].normal.z;
            fVerts[6 + baseMod] = vertices[i].texCoord.x;
			fVerts[7 + baseMod] = vertices[i].texCoord.y;
		}
	}
	return fVerts;
}

unsigned int* Mesh::packInds() {
	unsigned int* iVerts = (unsigned int*)malloc(sizeof(unsigned int) * indices.size());
	for (int i = 0; i < indices.size(); i++) {
		iVerts[i] = (unsigned int)indices[i];
	}
	return iVerts;
}

}