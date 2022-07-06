#pragma once

#include "../ecs/world.hpp"
#include "../components/collider.hpp"
#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/objmove.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>
#include <random>

namespace our
{

    class CollisionSystem
    {
        // std::vector<CollisionObject *> missles, enemies, boats;
        MovementComponent *missle = nullptr;
        MovementComponent *enemy = nullptr;
        MovementComponent *obj = nullptr;
        objmove *objm = nullptr;
        objmove *boat = nullptr;

    public:
        bool update(World *world, float deltaTime, bool &misstat)
        {
            for (auto entity : world->getEntities())
            {
                obj = entity->getComponent<MovementComponent>();
                objm = entity->getComponent<objmove>();
                if (obj && entity->name == "enemy")
                {
                    enemy = obj;
                }
                else if (obj && entity->name == "missle")
                {
                    missle = obj;
                }
                else if (objm && entity->name == "boat")
                {
                    boat = objm;
                }
            }

            if (checkCollision(missle, enemy))
            {
                int randNum = rand() % (41) - 20;
                enemy->getOwner()->localTransform.position.z = -10;
                enemy->getOwner()->localTransform.position.x = randNum;
                randNum = rand() % (20) + 5;
                enemy->linearVelocity.z=randNum;
                missle->getOwner()->localTransform.position = boat->getOwner()->localTransform.position;
                misstat = 0;
                missle->linearVelocity.z = 0;
            }

            if (checkCollision(boat, enemy))
                return true;

            return false;
        }

        bool checkCollision(MovementComponent *missleComponent, MovementComponent *enemyComponent)
        {
            auto missle = missleComponent->getOwner();
            auto enemy = enemyComponent->getOwner();

            glm::vec3 missleCenter = missle->localTransform.position;
            glm::vec3 enemyCenter = enemy->localTransform.position;
            glm::vec3 difference = missleCenter - enemyCenter;
            if (difference.x > -5 && difference.x < 5 && difference.z > 0 && difference.z < 2)
                return true;
            else
                return false;
        }

        bool checkCollision(objmove *boatComponent, MovementComponent *enemyComponent)
        {
            auto boat = boatComponent->getOwner();
            auto enemy = enemyComponent->getOwner();

            glm::vec3 boatCenter = boat->localTransform.position;
            glm::vec3 enemyCenter = enemy->localTransform.position;
            glm::vec3 difference = boatCenter - enemyCenter;

            if (difference.x > -5 && difference.x < 5 && difference.z > 0 && difference.z < 5)
                return true;
            else
                return false;
        }
    };

}