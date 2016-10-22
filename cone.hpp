#ifndef OPENGL1_CONE_HPP
#define OPENGL1_CONE_HPP

#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.hpp"
#include "figure.hpp"

class Cone : public Figure {

private:
    float radius = 1.0f;
    float height = 1.0f;
    int vertSegms = 1;
    int radSegms = 4;

public:

    Cone(float radius_, float height_, int vertSegms_, int radSegms_);
    Cone(float radius_, float height_, int vertSegms_, int radSegms_, glm::vec3 pos);

    float getRadius() const;
    float getHeight() const;

private:
    inline int layer(int numLay, int shift) const;

};

#endif //OPENGL1_CONE_HPP
