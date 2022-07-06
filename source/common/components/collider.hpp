#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{
    // This component denotes that the ColliderSystem
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/collision.hpp"
    class ColliderComponent : public Component
    {
    public:
        static std::string getID() { return "Collider"; }

        void deserialize(const nlohmann::json &data) override;
    };

}