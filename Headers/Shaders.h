//
// Created by ebrown on 03/01/2019.
//

#ifndef OPENGL_TEST1_SHADERS_H
#define OPENGL_TEST1_SHADERS_H

class ShaderCreateException: public std::exception {
private:
    GLint _error;

public:
    explicit ShaderCreateException(GLint error);
    virtual const char* what() const noexcept override;
};

GLuint createShader(GLenum type, const GLchar* source);
void attachShaders(GLuint program, const GLuint* shaders, int shaderCount);
void disposeShaders(const GLuint* shaders, int shaderCount);
GLuint createProgram(const GLuint* shaders, int shaderCount, const char* output);
void disposeProgram(GLuint program);
GLint enableVertexAttributeArray(const GLuint& shaderProgram, const GLchar* name, const GLuint size, const GLuint stride, const int offset);
GLuint createBindArrayBuffer(GLenum target, const void* data, const int dataSize, const GLenum drawType);
GLuint createVertexArray();
void disposeBuffers(const GLuint* buffers, GLsizei count);

#endif //OPENGL_TEST1_SHADERS_H
