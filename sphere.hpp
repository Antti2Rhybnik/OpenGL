#ifndef OPENGL1_SPHERE_HPP
#define OPENGL1_SPHERE_HPP


#include "figure.hpp"

class Sphere : public Figure {

private:
    float radius;
    int vertSegms;
    int horizSegms;

public:
    Sphere(float radius_, int vertSegms_, int horizSegms_);
    Sphere(float radius_, int vertSegms_, int horizSegms_, glm::vec3 pos);

private:

    inline int layer(int, int) const;

};


#endif //OPENGL1_SPHERE_HPP
