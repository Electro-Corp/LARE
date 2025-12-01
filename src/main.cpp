/*
    Example LARE usage
*/

#include <LARE.hpp>
#include <Light.hpp>
#include <Skybox.hpp>
#include <Transform.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

int main(){
    LARE::EngineOptions eOptions{"LARE Test", 800, 600, 4};
    LARE::LARE engine(eOptions);

    // Load skybox
    LARE::Skybox skybox("assets/night_skybox", "png");
    engine.getRenderer()->setSkybox(&skybox);

    LARE::Scene* testScene = new LARE::Scene("Test Scene 1");

    LARE::Object object("Test Object 1");
    object.model = new LARE::Model(&object, "assets/backpack/backpack.obj");
    object.vertexShader = LARE::Shader("assets/shaders/vert.gl");
    object.fragmentShader = LARE::Shader("assets/shaders/frag.gl");
    object.script = engine.getScriptMan()->initScript("assets/scripts/testObj.lua", &object);

    //                           amibient             specular             diffuse
    LARE::Light lightBulb({0.005f, 0.005f, 0.005f}, {0.05f, 0.05f, 0.05f}, {0.2f, 0.2f, 0.2f});
    lightBulb.model = new LARE::Model(&lightBulb, "assets/backpack/backpack.obj");
    lightBulb.vertexShader = LARE::Shader("assets/shaders/vert_uni.gl");
    lightBulb.fragmentShader = LARE::Shader("assets/shaders/frag_uni.gl");
    lightBulb.script = engine.getScriptMan()->initScript("assets/scripts/testLight.lua", &lightBulb);


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
    lightBulb.initScript();

    // Camera init
    LARE::Camera camera("Main Camera");

    camera.position = LARE::Vector3(0.0f, 0.0f, 0.0f);
    camera.script = engine.getScriptMan()->initScript("assets/scripts/camera.lua", &camera);
    camera.initScript();

    engine.getRenderer()->setCamera(&camera);

    // Capture mouse
    engine.captureMouse();

    while(1){
        object.update();
        lightBulb.update();
        camera.update();

        if(engine.Tick(testScene) == -1){
            break;
        }
    }

    printf("[test program] Exiting LARE Test!\n");

    delete testScene;
    return 0;
}