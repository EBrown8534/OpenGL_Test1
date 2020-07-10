//
// Created by ebrown on 03/01/2019.
//

#ifndef OPENGL_TEST1_SETTINGS_H
#define OPENGL_TEST1_SETTINGS_H

#include <SFML/Graphics.hpp>

using uint = unsigned int;
sf::ContextSettings buildSettings(uint depth, uint stencil, uint antialiasing, uint major = 3, uint minor = 2) {
    return sf::ContextSettings(depth, stencil, antialiasing, major, minor, sf::ContextSettings::Core, true);
}

enum BitDepth {
    BITDEPTH_32BPP = 32,
    BITDEPTH_24BPP = 24
};

enum StencilDepth {
    STENCILDEPTH_8BPP = 8
};

enum AntiAliasing {
    ANTIALIASING_2 = 2
};

#endif //OPENGL_TEST1_SETTINGS_H
