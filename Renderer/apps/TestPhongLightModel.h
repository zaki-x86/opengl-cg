#pragma once

#include <memory>

#include "../engine/Gui/gui.h"
#include "../engine/core/Window.h"
#include "../engine/opengl/OpenGLApp.h"
#include "../engine/opengl/OpenGLPipeline.h"
#include "TestApp.h"

#include "../engine/core/Camera.hpp"
#include "../engine/core/Shader.h"
#include "../engine/core/Texture.h"
#include "../engine/core/Vertex.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Phong lighting model test app
 * 
 */
namespace test {
    class TestPhongLightModel : public TestApp {
    public:
        TestPhongLightModel();
        ~TestPhongLightModel();

        void onUpdate(float deltaTime) override;

        void onRender() override;

        void onGuiRender() override;
    
    private:
        std::unique_ptr<Camera> m_Camera;
        std::unique_ptr<Shader> m_CubeShader;
        std::unique_ptr<Shader> m_LightCubeShader;
        std::vector<float> m_Vertices;
        GLuint m_VBO;
        GLuint m_CubeVAO;
        GLuint m_LightCubeVAO;

        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::mat4 m_Model;
    };
        
}

