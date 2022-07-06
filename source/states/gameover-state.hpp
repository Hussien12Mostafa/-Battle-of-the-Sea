#pragma once

#include <application.hpp>
#include <systems/menu.hpp>
#include "../common/components/mesh-renderer.hpp"
#include <systems/movement.hpp>
#include <asset-loader.hpp>

class Gameoverstate : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::MenuSystem menuSystem;

    void onInitialize() override
    {

        mciSendString("close mp3", NULL, 0, NULL);
        mciSendString("open \"assets\\theme\\endgame.mp3\" type mpegvideo alias mp3 ", NULL, 0, NULL);
        mciSendString("play mp3 repeat", NULL, 0, NULL);
        
        auto &config = getApp()->getConfig()["scene"];

        if (config.contains("assets"))
            our::deserializeAllAssets(config["assets"]);

            

        if (config.contains("gameover"))
            world.deserialize(config["gameover"]);            

        cameraController.enter(getApp());
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override
    {

        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        renderer.render(&world);

    }

    void onDestroy() override
    {
        mciSendString("close mp3", NULL, 0, NULL);
        world.clear();
        our::clearAllAssets();
    }
};