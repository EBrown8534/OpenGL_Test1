#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SOIL.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include "Headers/Shaders.h"
#include "Headers/Settings.h"
#include "Headers/Utilities.h"

bool dispatchEvent(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            return false;
        case sf::Event::KeyPressed:
            return event.key.code != sf::Keyboard::Escape;
        default:
            return true;
    }
}

int mainPump(sf::Window &window) {
    // Create Vertex Array Object
    GLuint vao = createVertexArray();
    GLuint elements[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            8, 9, 10,
            10, 11, 8,
            12, 13, 14,
            14, 15, 12
    };
    int triangleCount = sizeof(elements);

    float vertices[] = {
            -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
            0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            -1.0f, 0.0, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left

            -1.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
            0.0f,  -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left

            1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
            0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left

            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
            0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    // Create Buffer objects
    GLuint buffers[] = {
            createBindArrayBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices), GL_STATIC_DRAW),
            createBindArrayBuffer(GL_ELEMENT_ARRAY_BUFFER, elements, sizeof(elements), GL_STATIC_DRAW)
    };
    int bufferCount = sizeof(buffers);

    // Create and compile the vertex shader
    GLuint shaders[] = {
            createShader(GL_VERTEX_SHADER, readFile("Shaders/vertex-shader.glsl").c_str()),
            createShader(GL_FRAGMENT_SHADER, readFile("Shaders/fragment-shader.glsl").c_str())
    };
    int shaderCount = sizeof(shaders);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = createProgram(shaders, shaderCount, "outColor");

    // Specify the layout of the vertex data
    enableVertexAttributeArray(shaderProgram, "position", 2, 7 * sizeof(float), 0);
    enableVertexAttributeArray(shaderProgram, "color", 3, 7 * sizeof(float), 2 * sizeof(float));
    enableVertexAttributeArray(shaderProgram, "texcoord", 2, 7 * sizeof(float), 5 * sizeof(float));

    // Load textures
    GLuint textures[1];
    glGenTextures(1, textures);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    image = SOIL_load_image("Images/sample.png", &width, &height, nullptr, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    bool running = true;
    sf::Event windowEvent{};
    
    while (running) {
        while (window.pollEvent(windowEvent)) {
            running &= dispatchEvent(windowEvent);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_INT, nullptr);

        window.display();
    }

    glDeleteTextures(2, textures);
    disposeProgram(shaderProgram);
    disposeShaders(shaders, shaderCount);
    disposeBuffers(buffers, bufferCount);
    glDeleteVertexArrays(1, &vao);
    return 0;
}

int main() {
    sf::ContextSettings settings = buildSettings(BITDEPTH_24BPP, STENCILDEPTH_8BPP, ANTIALIASING_2);
    sf::Window window(
            sf::VideoMode(800, 600, BITDEPTH_32BPP),
            "Test Application",
            sf::Style::Close | sf::Style::Titlebar,
            settings);
    glewExperimental = GL_TRUE;
    glewInit();
    return mainPump(window);
}
