#include <Skybox.hpp>

#include <stb_image.h>

namespace LARE{

Skybox::Skybox(std::string directory, std::string format){
    // Get faces
    std::vector<std::string> faces = {
        directory + "/right." + format,
        directory + "/left." + format,
        directory + "/top." + format,
        directory + "/bottom." + format,
        directory + "/front." + format,
        directory + "/left." + format
    };

    glGenTextures(1, &cubeMapTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);

    int w, h, n;
    for(int i = 0; i < faces.size(); i++){
        unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &n, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else{
            LOG(ERROR, "LOG_ERROR") << "Skybox: Failed to load " << faces[i].c_str() << "!\n";
            exit(-1);
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

     // Load shaders 
    vertexSkyboxShader = new Shader("assets/shaders/skybox/sky_vert.gl");
    fragSkyboxShader = new Shader("assets/shaders/skybox/sky_frag.gl");
    // Compile vertex shader
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vTemp = vertexSkyboxShader->readShader();
    const char* vertexCode = vTemp.c_str();
    glShaderSource(vShader, 1, &vertexCode, NULL);
    glCompileShader(vShader);
    // Compile fragment shader
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fTemp = fragSkyboxShader->readShader();
    const char* fragmentCode = fTemp.c_str();
    glShaderSource(fShader, 1, &fragmentCode, NULL);
    glCompileShader(fShader);
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vShader);
    glAttachShader(shaderID, fShader);
    glLinkProgram(shaderID);
     // Did it error out...
    int suc;
    char log[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &suc);
    if (!suc) {
        glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
        LOG(ERROR, "LOG_ERROR") << "Skybox: Error linking shader program, log: " <<  std::string{log};
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    // Load VAO/VBO
    // Cube
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    // Load
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

}