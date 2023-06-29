#pragma once

#include "../engine/Gui/gui.h"

#include <functional>
#include <vector>

namespace test {

    class TestApp {
    public:
        TestApp() {}

        virtual ~TestApp() {}

        /**
         * @brief Called once when the test is selected
         * 
         * This is where you should initialize all the data
         * 
         * @param deltaTime 
         */
        virtual void onUpdate(float deltaTime) { (void)deltaTime; }

        /**
         * @brief Called every frame
         * 
         * This is where you should render all the data
         * 
         */
        virtual void onRender() {}

        /**
         * @brief Called every frame
         * 
         * This is where you should render all the GUI data
         * 
         */
        virtual void onGuiRender() {}
    };

    class TestMenu  : public TestApp
    {
    public:
        TestMenu(TestApp *&currentTestPointer);
        ~TestMenu();

        void onGuiRender() override;

        template <typename T> 
        void registerTest(const std::string &name) {
            std::cout << "Registering test " << name << std::endl;
            m_tests.push_back(std::make_pair(name, []() { return new T(); }));
        }
        

    private:
        TestApp *&m_currentTest;
        std::vector<std::pair<std::string, std::function<TestApp *()>>> m_tests;
    };

} // namespace test
