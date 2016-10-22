//
// Created by antti on 05.10.16.
//

#ifndef OPENGL1_MORPHER_HPP
#define OPENGL1_MORPHER_HPP


#include <iostream>
#include <vector>
#include <glm/vec3.hpp>

#include "figure.hpp"

class Morpher {

private:

    Figure* fromFig;
    Figure* toFig;

    std::vector<glm::vec3> shifts;
    int iterations;
    int currIter = 0;
    bool reverse = false;

public:
    Morpher(Figure* fromFig_, Figure* toFig_, int iterations_);
    bool morph();


};


#endif //OPENGL1_MORPHER_HPP
