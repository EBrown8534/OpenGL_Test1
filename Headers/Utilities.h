//
// Created by ebrown on 03/02/2019.
//

#ifndef OPENGL_TEST1_UTILITIES_H
#define OPENGL_TEST1_UTILITIES_H

#include <string>
#include <fstream>

std::string readFile(const char* filename) {
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());
    return str;
}

#endif //OPENGL_TEST1_UTILITIES_H
