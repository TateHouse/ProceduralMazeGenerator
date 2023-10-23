#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <format>
#include <iostream>

#include "BinaryTreeMazeGenerator.hpp"
#include "Shader.hpp"
#include "ShaderCompilationException.hpp"
#include "ShaderLinkingException.hpp"
#include "SidewinderMazeGenerator.hpp"
#include "SquareGrid.hpp"

static constexpr auto WINDOW_WIDTH {1280};
static constexpr auto WINDOW_HEIGHT {720};
static constexpr auto WINDOW_TITLE {"Procedural Maze Generator Renderer"};

static constexpr auto UNIT_SCALE {0.01f}; // 1 unit = 1 cm

static constexpr auto SQUARE_GRID_SIZE {20};
static constexpr auto CELL_SIZE {25.0f * UNIT_SCALE};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

glm::mat4 createOrthographicProjection(const float width,
                                       const float height,
                                       const float near,
                                       const float far) noexcept {
	const auto left {-width * 0.5f};
	const auto right {width * 0.5f};
	const auto top {height * 0.5f};
	const auto bottom {-height * 0.5f};
	
	return glm::ortho(left, right, bottom, top, near, far);
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

void insertNorthernWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
	vertices.push_back(-halfWidth);
	vertices.push_back(halfHeight);
	vertices.push_back(0.0f);
	vertices.push_back(halfWidth);
	vertices.push_back(halfHeight);
	vertices.push_back(0.0f);
}

void insertWesternWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
	vertices.push_back(-halfWidth);
	vertices.push_back(-halfHeight);
	vertices.push_back(0.0f);
	vertices.push_back(-halfWidth);
	vertices.push_back(halfHeight);
	vertices.push_back(0.0f);
}

void insertSouthernWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
	vertices.push_back(-halfWidth);
	vertices.push_back(-halfHeight);
	vertices.push_back(0.0f);
	vertices.push_back(halfWidth);
	vertices.push_back(-halfHeight);
	vertices.push_back(0.0f);
}

void insertEasternWallVertices(std::vector<float>& vertices, const float halfWidth, const float halfHeight) noexcept {
	vertices.push_back(halfWidth);
	vertices.push_back(-halfHeight);
	vertices.push_back(0.0f);
	vertices.push_back(halfWidth);
	vertices.push_back(halfHeight);
	vertices.push_back(0.0f);
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
	
	auto projection {createOrthographicProjection(WINDOW_WIDTH * UNIT_SCALE, WINDOW_HEIGHT * UNIT_SCALE, -1.0f, 1.0f)};
	
	auto deltaTime {0.0f};
	auto lastFrame {0.0f};
	
	auto backgroundColor {glm::vec3(0.0f, 0.0f, 0.0f)};
	
	auto squareGrid {Core::SquareGrid<SQUARE_GRID_SIZE> {}};
	squareGrid.initialize();
	
	auto sidewinderMazeGenerator {Core::SidewinderMazeGenerator {}};
	sidewinderMazeGenerator.generate(&squareGrid, nullptr);
	
	std::vector<float> vertices {};
	const auto [gridWidth, gridHeight] {squareGrid.getSize()};
	const auto cellCount {gridWidth * gridHeight};
	vertices.reserve(cellCount * 3);
	
	GLuint vao {0};
	GLuint vbo {0};
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	
	const auto halfWidth {gridWidth * CELL_SIZE * 0.5f};
	const auto halfHeight {gridHeight * CELL_SIZE * 0.5f};
	
	for (auto row {gridHeight - 1}; row >= 0; --row) {
		for (auto column {0}; column < gridWidth; ++column) {
			const auto xGridPosition {static_cast<int>(column)};
			const auto yGridPosition {static_cast<int>(row)};
			const auto* const cell {squareGrid[{xGridPosition, yGridPosition}]};
			
			const auto xCoordinate {static_cast<float>(xGridPosition * CELL_SIZE) - halfWidth};
			const auto yCoordinate {static_cast<float>(yGridPosition * CELL_SIZE) - halfHeight};
			
			const auto* const eastNeighbor {cell->getEast()};
			const auto* const southNeighbor {cell->getSouth()};
			
			if (!cell->isLinked(eastNeighbor)) {
				vertices.push_back(xCoordinate + CELL_SIZE);
				vertices.push_back(yCoordinate);
				vertices.push_back(0.0f);
				
				vertices.push_back(xCoordinate + CELL_SIZE);
				vertices.push_back(yCoordinate + CELL_SIZE);
				vertices.push_back(0.0f);
			}
			
			if (!cell->isLinked(southNeighbor)) {
				vertices.push_back(xCoordinate);
				vertices.push_back(yCoordinate);
				vertices.push_back(0.0f);
				
				vertices.push_back(xCoordinate + CELL_SIZE);
				vertices.push_back(yCoordinate);
				vertices.push_back(0.0f);
			}
		}
	}
	
	insertNorthernWallVertices(vertices, halfWidth, halfHeight);
	insertWesternWallVertices(vertices, halfWidth, halfHeight);
	insertSouthernWallVertices(vertices, halfWidth, halfHeight);
	insertEasternWallVertices(vertices, halfWidth, halfHeight);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	const auto vertexCount {vertices.size() / 3};
	
	Renderer::Shader* shader {nullptr};
	
	try {
		shader = new Renderer::Shader("Shaders/Test.vert", "Shaders/Test.frag");
		
	} catch (const Renderer::ShaderCompilationException& exception) {
		std::cerr << exception.what() << '\n';
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} catch (const Renderer::ShaderLinkingException& exception) {
		std::cerr << exception.what() << '\n';
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	
	while (!glfwWindowShouldClose(window)) {
		const auto currentFrame {calculateDeltaTime(deltaTime, lastFrame)};
		
		setWindowTitleWithFPS(window, deltaTime);
		
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (shader != nullptr) {
			shader->use();
			
			shader->setMat4x4("projection", projection);
			
			glBindVertexArray(vao);
			glDrawArrays(GL_LINES, 0, vertexCount);
			glBindVertexArray(0);
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	delete shader;
	
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}