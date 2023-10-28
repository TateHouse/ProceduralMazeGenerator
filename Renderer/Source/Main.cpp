#include "Application.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    Renderer::Application application {};

    try {
        application.initialize();
        application.postInitialize();

        while (application.getIsRunning()) {
            application.update();
            application.postUpdate();
            application.render();
            application.postRender();
        }

        application.destroy();

        return 0;
    } catch (const std::runtime_error& exception) {
        std::cerr << exception.what() << '\n';
        return -1;
    }
}