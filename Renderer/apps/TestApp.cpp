#include "TestApp.h"

test::TestMenu::TestMenu(TestApp *&currentTestPointer)
    : m_currentTest(currentTestPointer) 
{

}

test::TestMenu::~TestMenu() 
{

}

void test::TestMenu::onGuiRender() 
{
    for (auto &test : m_tests) {
        if (ImGui::Button(test.first.c_str())) {
            m_currentTest = test.second();
        }
    }
}