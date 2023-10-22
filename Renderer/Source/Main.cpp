#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <array>
#include <format>
#include <iostream>

#include "Shader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"

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
	
	const std::array<const float, 9> vertices {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
	
	GLuint vao {0};
	GLuint vbo {0};
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	Renderer::Shader* shader;
	
	try {
		shader = new Renderer::Shader("Shaders/Test.vert", "Shaders/Test.frag");
		
	} catch (const Renderer::ShaderCompilationException& exception) {
		std::cerr << exception.what() << '\n';
		shader = nullptr;
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} catch (const Renderer::ShaderLinkingException& exception) {
		std::cerr << exception.what() << '\n';
		shader = nullptr;
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	
	while (!glfwWindowShouldClose(window)) {
		const auto currentFrame {calculateDeltaTime(deltaTime, lastFrame)};
		
		setWindowTitleWithFPS(window, deltaTime);
		
		backgroundColor.x = (std::cos(currentFrame) / 2.0f + 0.5f);
		backgroundColor.y = (std::cos(currentFrame) / 2.0f + 0.5f);
		backgroundColor.z = (std::cos(currentFrame) / 2.0f + 0.5f);
		
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (shader != nullptr) {
			shader->use();
			
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
	delete shader;
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}