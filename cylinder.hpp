#ifndef OPENGL1_CYLINDER_HPP
#define OPENGL1_CYLINDER_HPP

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "figure.hpp"

class Cylinder : public Figure {

private:
    float radius = 1.0f;
    float height = 1.0f;
    int vertSegms = 1;
    int radSegms = 4;

public:

    Cylinder(float radius_, float height_, int vertSegms_, int radSegms_);
    Cylinder(float radius_, float height_, int vertSegms_, int radSegms_, glm::vec3 pos_);

    float getRadius() const;
    float getHeight() const;

private:
    inline int layer(int numLay_, int shift_) const;
};


#endif //OPENGL1_CYLINDER_HPP
