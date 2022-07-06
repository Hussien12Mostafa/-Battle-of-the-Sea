#pragma once

#include "../ecs/world.hpp"
#include "../components/objmove.hpp"
#include "../components/objmove.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>
#include <random>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class objsys
    {
    public:
        Application *app;
        float tt = 0;
        void enter(Application *app)
        {
            this->app = app;
        }
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime, bool &misstat)
        {
            // For each entity in the world

            //    CameraComponent* camera = nullptr;
            objmove *objm = nullptr;
            MovementComponent *missle = nullptr;
            MovementComponent *enemy = nullptr;
            for (auto entity : world->getEntities())
            {
                missle = entity->getComponent<MovementComponent>();
                if (missle && entity->name == "missle")
                    break;
            }
            for (auto entity : world->getEntities())
            {
                enemy = entity->getComponent<MovementComponent>();
                if (enemy && entity->name == "enemy")
                    break;
            }
            for (auto entity : world->getEntities())
            {
                objm = entity->getComponent<objmove>();
                if (objm)
                    break;
            }

            if (objm)
            {

                Entity *entity = objm->getOwner();
                glm ::mat4 matrix = entity->localTransform.toMat4();
                glm ::vec3 right = glm ::vec3(matrix * glm ::vec4(1, 0, 0, 0));

                // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return

                if (app->getKeyboard().isPressed(GLFW_KEY_D))
                    entity->localTransform.position += deltaTime * objm->linearVelocity;
                if (app->getKeyboard().isPressed(GLFW_KEY_A))
                    entity->localTransform.position -= deltaTime * objm->linearVelocity;

                entity->localTransform.position.x = (20 < entity->localTransform.position.x) ? 20 : entity->localTransform.position.x;
                entity->localTransform.position.x = (-20 > entity->localTransform.position.x) ? -20 : entity->localTransform.position.x;

                if (app->getKeyboard().isPressed(GLFW_KEY_SPACE))
                {
                    misstat = 1;
                    missle->linearVelocity.z = -10;
                }


                if (misstat == 0)
                    missle->getOwner()->localTransform.position = entity->localTransform.position;

                if (missle->getOwner()->localTransform.position.z < -5)
                {
                    misstat = 0;
                    missle->linearVelocity.z = 0;
                }

                if (enemy->getOwner()->localTransform.position.z > 50)
                {
                    int randNum = rand() % (41) - 20;
                    enemy->getOwner()->localTransform.position.z = -10;
                    enemy->getOwner()->localTransform.position.x = randNum;
                    randNum = rand() % (20) +5;
                    enemy->linearVelocity.z=randNum;
                }
            }
        }
    };

}
