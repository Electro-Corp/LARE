/*
    Example LARE usage
*/

#include <LARE.hpp>
#include <Light.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

int main(){
    LARE::EngineOptions eOptions{"LARE Test", 800, 600, 4};
    LARE::LARE engine(eOptions);

    LARE::Scene* testScene = new LARE::Scene("Test Scene 1");

    LARE::Object object("Test Object 1");
    object.model = new LARE::Model(&object, "assets/backpack/backpack.obj");
    object.vertexShader = LARE::Shader("shaders/vert.gl");
    object.fragmentShader = LARE::Shader("shaders/frag.gl");
    object.script = engine.getScriptMan()->initScript("assets/scripts/testObj.lua", &object);

    //                           amibient             specular             diffuse
    LARE::Light lightBulb({0.05f, 0.05f, 0.06f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f});
    lightBulb.model = new LARE::Model(&lightBulb, "assets/backpack/backpack.obj");
    lightBulb.vertexShader = LARE::Shader("shaders/vert_uni.gl");
    lightBulb.fragmentShader = LARE::Shader("shaders/frag_uni.gl");

    testScene->addObject(&object);
    testScene->addObject(&lightBulb);

    // Sort lights
    testScene->findLights();

    printf("[test program] Lights: %d\n", testScene->lights.size());

    // Generate Shaders
    for(auto& gm : testScene->objects){
        printf("[test program] Generating shaders for %s\n", gm->getName().c_str());
        engine.getRenderer()->GenerateShaders(gm);
    }

    printf("[test program] Shader generation finished.\n");

    // Init script
    object.initScript();

    // Camera init
    LARE::Camera camera;

    camera.position = LARE::Vector3(0.0f, 0.0f, 0.0f);

    engine.getRenderer()->setCamera(&camera);

    object.transform.Rotate(45, {0.5f, 0.0f, 1.0f});
    object.transform.Scale({0.6f, 0.6f, 0.6f});

    lightBulb.transform.Translate({0.5f, 0.0f, 1.0f});
    lightBulb.transform.Scale({0.03f, 0.031f, 0.03f});

    while(1){
        // Update time
        static auto sT = std::chrono::high_resolution_clock::now();
        auto cT = std::chrono::high_resolution_clock::now();
        float t = std::chrono::duration<float, std::chrono::seconds::period>(cT - sT).count();

        // Update camera
        camera.camData = LARE::CameraData{};
        camera.camData.model = glm::rotate(glm::mat4(0.5f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        camera.camData.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        camera.pAngle = 45;

        object.update();


        if(engine.Tick(testScene) == -1){
            break;
        }
    }

    printf("[test program] Exiting LARE Test!\n");

    delete testScene;
    return 0;
}