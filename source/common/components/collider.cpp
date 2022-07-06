#include "collider.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    void ColliderComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
    }
}