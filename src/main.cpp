/*
    Example LARE usage
*/

#include <LARE.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

int main(){
    LARE::EngineOptions eOptions{"LARE Test", 800, 600};
    LARE::LARE engine(eOptions);

    LARE::Scene* testScene = new LARE::Scene("Test Scene 1");

    // Object
    // std::vector<LARE::Vertex> verts = {
	// 	{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
	// 	{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
	// 	{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
	// 	{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	// };

	// std::vector<uint16_t> inds = {
	// 	0, 1, 3, 1, 2, 3
	// };

    LARE::Object object("Test Object 1");
    object.model = new LARE::Model(&object, "assets/backpack/backpack.obj");
    object.vertexShader = LARE::Shader("shaders/vert.gl");
    object.fragmentShader = LARE::Shader("shaders/frag.gl");

    testScene->addObject(&object);

    // Generate Shaders
    for(auto& gm : testScene->objects){
        engine.getRenderer()->GenerateShaders(gm);
    }

    // Camera init
    LARE::Camera camera;

    engine.getRenderer()->setCamera(&camera);

    object.transform.Rotate(45, {1.0f, 0.0f, 1.0f});

    while(1){
        // Update time
        static auto sT = std::chrono::high_resolution_clock::now();
        auto cT = std::chrono::high_resolution_clock::now();
        float t = std::chrono::duration<float, std::chrono::seconds::period>(cT - sT).count();

        // Update camera
        camera.camData = LARE::CameraData{};
        camera.camData.model = glm::rotate(glm::mat4(0.5f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        camera.camData.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        camera.pAngle = 90;

        // Update transform of object for fun
        object.transform.Rotate(sin(t), {0.0f, 1.0f, 0.0f});
        //object.transform.Translate({0.0f, 0.0f, 0.5f});

        if(engine.Tick(testScene) == -1){
            break;
        }
    }

    delete testScene;
    return 0;
}