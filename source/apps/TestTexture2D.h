#pragma once

#include <memory>

#include "../engine/Gui/gui.h"
#include "../engine/core/Window.h"
#include "../engine/opengl/OpenGLApp.h"
#include "TestApp.h"

#include "../engine/core/Shader.h"
#include "../engine/core/Texture.h"
#include "../engine/core/Cube.hpp"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace test {
    class TestTexture2D : public TestApp {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void onUpdate(float deltaTime) override;

        void onRender() override;

        void onGuiRender() override;
    
    private:
        std::unique_ptr<Cube> m_cube;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_texture;
        std::unique_ptr<glm::mat4> m_model;
        std::unique_ptr<glm::mat4> m_view;
        std::unique_ptr<glm::mat4> m_projection;
        
        float m_fov;
        float m_cubeRotation;
        glm::vec3 m_cubeTranslation;
    };
}