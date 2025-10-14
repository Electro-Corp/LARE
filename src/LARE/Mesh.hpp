/*
    Holder for Mesh's
*/
#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include <Transform.hpp>
#include <Camera.hpp>

namespace LARE{
    struct Vertex {
		glm::vec3 pos;
        glm::vec3 normal;
		glm::vec2 texCoord;
    };

    struct Texture {
        unsigned int id;
        std::string type, path;
    };

    class Mesh {
	private:
		// Pretty self explanatory, just the ends of our triangle
		std::vector<Vertex> vertices;
		/*
		 * Ooh goody optimization
		 * Often, triangles will share multiple verticies, as shown here in this simple example:
		 *      v0 --------------- v1
		 *     v5 | *              |
		 *        |     *          |
		 *        |         *      |
		 *        |             *  |
		 *      v4 ---------------- v2
		 *                         v3
		 *  So why bother using that many verts when v0 and v5 are the same and v3 and v2 are?
		 *  Yay for index buffers
		 */
		std::vector<uint16_t> indices;
        // Textures 
        std::vector<Texture> textures;
	public:
		// Has our mesh been modified?
		bool modified = false;
        // Base object

        /*
         *  VAO -> Tells OpenGL how our vertices are laid out
         *  VBO -> for our vertices
         *  EBO -> for our indices
         */
        unsigned int VBO, VAO, EBO;

		Mesh(std::vector<Vertex> verts, std::vector<uint16_t> inds, std::vector<Texture> textures);

        void initMesh();

        void drawMesh(unsigned int sPr, Transform transform, Camera* cam);

		// Getters/Setters
		float* packVerts();

		unsigned int* packInds();

		std::vector<Vertex> getVertices() {
			return vertices;
		}

		void setVertices(std::vector<Vertex> verts) {
			this->vertices = verts;
			modified = true;
		}

		std::vector<uint16_t> getIndicies() {
			return indices;
		}

		void setIndicies(std::vector<uint16_t> inds) {
			this->indices = inds;
			modified = true;
		}

		int getVertsRealSize() {
			return sizeof(float) * (8 * vertices.size());
		}

		int getIndsRealSize() {
			return sizeof(float) * indices.size();
		}
	};
}