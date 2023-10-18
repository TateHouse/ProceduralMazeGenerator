#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <format>
#include <iostream>

static constexpr auto WINDOW_WIDTH {1280};
static constexpr auto WINDOW_HEIGHT {720};
static constexpr auto WINDOW_TITLE {"Procedural Maze Generator 2D Renderer"};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

float calculateDeltaTime(float& deltaTime, float& lastFrame) noexcept {
	auto currentFrame {static_cast<float>(glfwGetTime())};
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
	return currentFrame;
}

void setWindowTitleWithFPS(GLFWwindow* window, float deltaTime) noexcept {
	const auto fps {1.0f / deltaTime};
	const auto title {std::format("{} - FPS: {:.2f}", WINDOW_TITLE, fps)};
	glfwSetWindowTitle(window, (title.c_str()));
}

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		std::cerr << "ERROR: Failed to initialize GLFW" << '\n';
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(1);
	
	auto* window {glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr)};
	if (window == nullptr) {
		std::cerr << "ERROR: Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cerr << "ERROR: Failed to initialize GLAD" << '\n';
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	
	auto deltaTime {0.0f};
	auto lastFrame {0.0f};
	
	auto backgroundColor {glm::vec3(0.0f, 0.0f, 0.0f)};
	
	while (!glfwWindowShouldClose(window)) {
		const auto currentFrame {calculateDeltaTime(deltaTime, lastFrame)};
		
		setWindowTitleWithFPS(window, deltaTime);
		
		backgroundColor.x = (std::cos(currentFrame) / 2.0f + 0.5f);
		backgroundColor.y = (std::cos(currentFrame) / 2.0f + 0.5f);
		backgroundColor.z = (std::cos(currentFrame) / 2.0f + 0.5f);
		
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}