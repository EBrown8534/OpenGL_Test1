#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SOIL.h>
#include <sstream>
#include "../Headers/Shaders.h"

ShaderCreateException::ShaderCreateException(GLint error) {
    _error = error;
}
    
const char* ShaderCreateException::what() const noexcept {
    std::ostringstream s;
    s << "Error creating shader: " << _error;
    return s.str().c_str();
}

GLuint createShader(GLenum type, const GLchar* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        throw new ShaderCreateException(status); // NOLINT(cert-err09-cpp,cert-err61-cpp,misc-throw-by-value-catch-by-reference,hicpp-exception-baseclass)
    }

    return shader;
}

void attachShaders(GLuint program, const GLuint* shaders, const int shaderCount) {
    for (int i = 0; i < shaderCount; i++) {
        glAttachShader(program, shaders[i]);
    }
}

void disposeShaders(const GLuint* shaders, const int shaderCount) {
    for (int i = 0; i < shaderCount; i++) {
        glDeleteShader(shaders[i]);
    }
}

GLuint createProgram(const GLuint* shaders, const int shaderCount, const char* output) {
    GLuint shaderProgram = glCreateProgram();
    attachShaders(shaderProgram, shaders, shaderCount);
    glBindFragDataLocation(shaderProgram, 0, output);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return shaderProgram;
}

void disposeProgram(const GLuint program) {
    glDeleteProgram(program);
}

GLint enableVertexAttributeArray(const GLuint& shaderProgram, const GLchar* name, const GLuint size, const GLuint stride, const int offset) {
    GLint posAttrib = glGetAttribLocation(shaderProgram, name);
    glEnableVertexAttribArray((GLuint)posAttrib);
    glVertexAttribPointer((GLuint)posAttrib, size, GL_FLOAT, GL_FALSE, stride, (void *)offset);
    return posAttrib;
}

GLuint createBindArrayBuffer(GLenum target, const void* data, const int dataSize, const GLenum drawType) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(target, vbo);
    glBufferData(target, dataSize, data, drawType);
    return vbo;
}

GLuint createVertexArray() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

void disposeBuffers(const GLuint* buffers, GLsizei count) {
    glDeleteBuffers(count, buffers);
}
