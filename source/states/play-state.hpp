#pragma once

#include <application.hpp>
#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include <systems/objsys.hpp>
#include <systems/collision.hpp>
#include <systems/menu.hpp>

#include <windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
typedef unsigned int MMVERSION;

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{
    public:
        bool overstate =0;

    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::CollisionSystem collisionSystem;
    our::objsys objsystem;
    our::MenuSystem menusystem;
    bool misstat = 0;
    

    void onInitialize() override
    {

        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("game"))
        {
            world.deserialize(config["game"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // Then we initialize the renderer
        objsystem.enter(getApp());
        menusystem.enter(getApp());

        mciSendString("open \"assets\\theme\\Caribbean.mp3\" type mpegvideo alias mp3 ", NULL, 0, NULL);
        mciSendString("play mp3 repeat", NULL, 0, NULL);
        
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override
    {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        

        objsystem.update(&world, (float)deltaTime, misstat);
                if (collisionSystem.update(&world, (float)deltaTime, misstat))
        {
            //getApp()->changeState("game");
            overstate =1;
            std::cout << "LOST!!" << std::endl;
        }

        renderer.render(&world);
    }

    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        world.clear();
        our::clearAllAssets();
    }
};