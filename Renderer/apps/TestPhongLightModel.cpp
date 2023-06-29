#include "TestPhongLightModel.h"

test::TestPhongLightModel::TestPhongLightModel()
    :   m_Camera(std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f))),
        m_CubeShader(std::make_unique<Shader>("", "")),
        m_LightCubeShader(std::make_unique<Shader>("", "")),
        m_Vertices({
            }),
        m_Projection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
        m_View(glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f))),
        m_Model(glm::mat4(1.0f))
{
    
}
