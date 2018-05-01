/**
 * @file JabcMain.cpp
 * @author muecker
 * @date 4/20/2018
**/

#include "JabcMain.hpp"
#include "SimpleLogger.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include <Windows.h>
#include <glad\glad.h> // Includes gl/GL.h
#include <gl\GLU.h>
#include <GLFW\glfw3.h>

// Forward declarations for local GL function handlers.
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processKeyboardInput(GLFWwindow *window);

using namespace SimpleLogging;

int main(int argc, char** argv)
{
    SimpleLogger* mainLogger = new SimpleLogger();
    mainLogger->setLogLevel(LOG_LEVEL::TRACE);
    mainLogger->initializeLogFile("C:/Users/muecker/Downloads/JABC.log");
    mainLogger->log("Logger initialized.");

    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize the main window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Just Another Breakout Clone", NULL, NULL);
    if (window == NULL)
    {
        mainLogger->log("Unable to create OpenGL window. Terminating.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Use GLAD to load functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        mainLogger->log("Unable to initialize GLAD. Terminating.");
        return -1;
    }

    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        processKeyboardInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/**
 * Callback function for the frame size changes.
 *
 * @param window The main window handle.
 * @param width The new window width.
 * @param height The new window height.
**/
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/**
 * Check for key presses.
 *
 * @param window The main window handle.
**/
void processKeyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}