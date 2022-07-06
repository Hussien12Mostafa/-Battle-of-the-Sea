#pragma once

#include "../ecs/component.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "../shader/shader.hpp"
//! LIGHT
namespace our {

    class LightComponent : public Component {
    public:
        int lightType;
        //glm::vec3 position; should be calculated from the entity componnt
        //glm::vec3 direction;
        glm::vec3 diffuse = {0,0,0};
        glm::vec3 specular = {0,0,0};
        glm::vec3 attenuation = {0,0,0}; // x*d^2 + y*d + z
        glm::vec2 cone_angles = {0,0}; // x: inner_angle, y: outer_angle
        glm::vec3 ambient = {0,0,0};
        
        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads Light parameters from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}
