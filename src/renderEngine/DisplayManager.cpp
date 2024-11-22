#include "DisplayManager.h"
#include "entities/Camera.h"
#include <iostream>
#include <thread>
#include <chrono>

GLFWwindow* DisplayManager::window = nullptr;
const int DisplayManager::WIDTH = 1280;
const int DisplayManager::HEIGHT = 720;
const int DisplayManager::FPS_CAP = 120;
const char* DisplayManager::TITLE = "Our First Display";

long DisplayManager::lastFrameTime = getCurrentTime();
float DisplayManager::delta = 0.0f;

void DisplayManager::createDisplay() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Set GLFW window hints for OpenGL 3.2 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
}

void DisplayManager::updateDisplay() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS_CAP));

    long currentFrameTime = getCurrentTime();
    delta = (currentFrameTime - lastFrameTime)/1000.0f;
    lastFrameTime = currentFrameTime;
    
}

bool DisplayManager::isCloseRequested() {
    return glfwWindowShouldClose(window);
}

float DisplayManager::getFrameTimeSeconds()
{
    return delta;
}



void DisplayManager::closeDisplay() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

long DisplayManager::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}