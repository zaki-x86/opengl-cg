#include "TestTexture2D.h"

#include <filesystem>



test::TestTexture2D::TestTexture2D()
    : m_cube(std::make_unique<Cube>(CubeType::POS_TEX)),
      m_shader(std::make_unique<Shader>()),
      m_texture(std::make_unique<Texture>()),
      m_model(std::make_unique<glm::mat4>(glm::mat4(1.0f))),
      m_view(std::make_unique<glm::mat4>(glm::mat4(1.0f))),
      m_projection(std::make_unique<glm::mat4>(glm::mat4(1.0f))),

      m_fov(45),
      m_cubeRotation(0),
      m_cubeTranslation(glm::vec3(0))
{
    std::filesystem::path path = std::filesystem::current_path();
    std::string texturePath = path.string() + "/assets/images/container.jpg";
    std::string vertPath = path.string() + "/assets/shaders/texture/cube.vert";
    std::string fragPath = path.string() + "/assets/shaders/texture/cube.frag";

    m_cube->setShaders(vertPath, fragPath);
    m_cube->setTexture(texturePath);

    // Define view matrix
    // Note that we're translating the scene in the reverse direction of where we want to move
    *m_view = glm::translate(*m_view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Define projection matrix
    // Note that we're using glm::perspective instead of glm::ortho
    // glm::perspective takes in fov in degrees, so we convert it to radians
    *m_projection = glm::perspective(glm::radians(m_fov), (float)1200 / (float)900, 0.1f, 100.0f);
    
}

test::TestTexture2D::~TestTexture2D() {}

void test::TestTexture2D::onUpdate(float deltaTime) {
    (void)deltaTime;
    
}

void test::TestTexture2D::onRender() {
    m_cube->bindTexture();
    m_cube->useShader();

    m_cube->getShader().setUniform("model", *m_model);
    m_cube->getShader().setUniform("view", *m_view);
    m_cube->getShader().setUniform("projection", *m_projection);

    m_cube->draw();
}

void test::TestTexture2D::onGuiRender() {
    ImGui::SliderFloat("FOV", &m_fov, 0.0f, 180.0f);
    ImGui::SliderFloat3("Cube Translation", glm::value_ptr(m_cubeTranslation), -1.0f, 1.0f);
    ImGui::SliderFloat("Cube Rotation Y-axis ", &m_cubeRotation, 0.0f, 360.0f);

    *m_model = glm::mat4(1.0f);
    *m_model = glm::translate(*m_model, m_cubeTranslation);
    *m_model = glm::rotate(*m_model, glm::radians(m_cubeRotation), glm::vec3(0.0f, 1.0f, 0.0f));

    *m_projection = glm::perspective(glm::radians(m_fov), (float)1200 / (float)900, 0.1f, 100.0f);
}
