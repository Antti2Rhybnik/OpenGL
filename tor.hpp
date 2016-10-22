#ifndef OPENGL1_TOR_HPP
#define OPENGL1_TOR_HPP


#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.hpp"
#include "figure.hpp"

class Tor : public Figure {

private:
    float bigRadius = 1.0f;
    float smallRadius = 1.0f;
    int bigSegments = 4;
    int smallSegments = 4;

public:

    Tor(float bigRadius_, float smallRadius_, int bigSegments_, int smallSegments_);
    Tor(float bigRadius_, float smallRadius_, int bigSegments_, int smallSegments_, glm::vec3 pos);

private:

    inline int layer(int layNum, int shift) const;
};


#endif //OPENGL1_TOR_HPP
