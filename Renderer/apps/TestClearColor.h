#pragma once

#include "../engine/Gui/gui.h"
#include "../engine/core/Window.h"
#include "../engine/opengl/OpenGLApp.h"
#include "TestApp.h"



namespace test
{    
    class TestClearColor : public test::TestApp
    {
    private:
        float m_color[4];
    public:
        TestClearColor();
        ~TestClearColor();

        void onUpdate(float deltaTime) override;

        void onRender() override;

        void onGuiRender() override;
    };

    TestClearColor::TestClearColor(/* args */)
        : m_color{0.2f, 0.3f, 0.8f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::onUpdate(float deltaTime)
    {
        (void)deltaTime;
    }

    void TestClearColor::onRender()
    {
        glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestClearColor::onGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_color);
    }
} // namespace test

