#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "models/RawModel.h"
#include "renderEngine/EntityRenderer.h"
#include "shaders/StaticShader.h"
#include "models/TexturedModel.h"
#include "textures/ModelTexture.h"
#include "entities/Entity.h"
#include "renderEngine/ModelLoader.h"
#include "entities/Light.h"
#include "renderEngine/MasterRenderer.h"
#include "terrains/Terrain.h"
#include "entities/Player.h"
#include <glm/gtc/random.hpp>

int main() {
    DisplayManager::createDisplay();
    Loader loader;
    Light light(glm::vec3(400.0f, 10.0f, 390.0f), glm::vec3(1, 0.6, 0.6));

    TexturedModel christmastree(ModelLoader::loadModel(ASSETS_PATH "ChristmasTree/ChristmasTree.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "ChristmasTree/Handle1Tex.png")));

    TexturedModel tree(ModelLoader::loadModel(ASSETS_PATH "tree.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "tree.png")));

    TexturedModel grass(ModelLoader::loadModel(ASSETS_PATH "grassModel.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "grassTexture.png")));
    grass.getTexture().setHasTransparency(true);
    grass.getTexture().setUseFakeLighting(true);

    TexturedModel flower(ModelLoader::loadModel(ASSETS_PATH "grassModel.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "flower.png")));
    flower.getTexture().setHasTransparency(true);
    flower.getTexture().setUseFakeLighting(true);

    Entity fireplace(TexturedModel(ModelLoader::loadModel(ASSETS_PATH "christmasfireplace/christmasfireplace.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "christmasfireplace/fireplace02.png"))),
        glm::vec3(400, 0, 400), 0, 180, 0, 7);

    Entity santaHat(TexturedModel(ModelLoader::loadModel(ASSETS_PATH "SantaHat/santa hat.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "SantaHat/lambert2.png"))),
        glm::vec3(398, 0, 401), 0, 0, 0, 2);

    Entity sign(TexturedModel(ModelLoader::loadModel(ASSETS_PATH "sign/kingeddysign.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "sign/SB_SBCU_signs_eds_01.png"))),
        glm::vec3(390, 0, 397), 0, 150, 0, 0.2);

    Terrain terrain(0, 0, loader, ModelTexture(loader.loadTexture(ASSETS_PATH "snow.png")));

    std::vector<Entity> allTrees;
    for (int i = 0; i < 200; i++)
    {
        float x = glm::linearRand(0, 800);
        float z = glm::linearRand(0, 800);
        if ((x > 450 || x < 350) || (z > 450 || z < 350))
            allTrees.push_back(Entity(christmastree, glm::vec3(x, 0, z), 0, 0, 0, 15.0f));
        else
            i--;

        x = glm::linearRand(0, 800);
        z = glm::linearRand(0, 800);
        if ((x > 450 || x < 350) || (z > 450 || z < 350))
            allTrees.push_back(Entity(tree, glm::vec3(x, 0, z), 0, 0, 0, 15.0f));
        else
            i--;
    }

    std::vector<Entity> allGrass;
    std::vector<Entity> allFlowers;
    for (int i = 0; i < 200; i++)
    {
        float x = glm::linearRand(0, 800);
        float z = glm::linearRand(0, 800);
        allGrass.push_back(Entity(grass, glm::vec3(x, 0, z), 0, 0, 0, 3.0f));
        x = glm::linearRand(0, 800);
        z = glm::linearRand(0, 800);
        allFlowers.push_back(Entity(flower, glm::vec3(x, 0, z), 0, 0, 0, 3.0f));
    }

    MasterRenderer renderer;

    TexturedModel playerModel(ModelLoader::loadModel(ASSETS_PATH "Elf/AnnoyingElfKeith.obj", loader),
        ModelTexture(loader.loadTexture(ASSETS_PATH "Elf/Handle1Tex.png")));


    Player player(playerModel, glm::vec3(400, 0, 390), 0, 0, 0, 3);
    Camera camera(player);

    while (!DisplayManager::isCloseRequested()) {
        camera.move();
        player.move();
        renderer.processEntity(player);
        renderer.processTerrain(terrain);
        renderer.processEntity(fireplace);
        renderer.processEntity(santaHat);
        renderer.processEntity(sign);
        for (const Entity& tree : allTrees)
        {
            renderer.processEntity(tree);
        }
        for (const Entity& grass : allGrass)
        {
            renderer.processEntity(grass);
        }
        for (const Entity& flower : allFlowers)
        {
            renderer.processEntity(flower);
        }
        renderer.render(light, camera);
        DisplayManager::updateDisplay();
    }

    renderer.cleanUp();
    loader.cleanUp();
    DisplayManager::closeDisplay();
    return 0;
}