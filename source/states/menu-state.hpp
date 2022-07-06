#pragma once

#include <application.hpp>
#include <systems/menu.hpp>
#include "../common/components/mesh-renderer.hpp"
#include <systems/movement.hpp>
#include <asset-loader.hpp>

class Menustate : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::MenuSystem menuSystem;

    void onInitialize() override
    {
        auto &config = getApp()->getConfig()["scene"];

        if (config.contains("assets"))
            our::deserializeAllAssets(config["assets"]);

            

        if (config.contains("menu"))
            world.deserialize(config["menu"]);            

        cameraController.enter(getApp());
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
        menuSystem.enter(getApp());
    }

    void onDraw(double deltaTime) override
    {

        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        // And finally we use the renderer system to draw the scene
        renderer.render(&world);

        //renderer.render(&world);

        // if (menuSystem.update(&world, (float)deltaTime))
        // {
        //     getApp()->changeState("game");
        // }
    }

    void onDestroy() override
    {
        world.clear();
        our::clearAllAssets();
    }
};