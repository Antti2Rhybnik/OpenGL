#include "tor.hpp"

Tor::Tor(float bigRadius_, float smallRadius_, int bigSegments_, int smallSegments_) {

    if (bigSegments_ < 4) { bigSegments_ = 4; }
    if (smallSegments_ < 4) { smallSegments_ = 4; }
    if (bigRadius_ < smallRadius_) { std::swap(bigRadius_, smallRadius_); }

    bigRadius = bigRadius_;
    smallRadius = smallRadius_;
    bigSegments = bigSegments_;
    smallSegments = smallSegments_;


    float angleBig = (float) (2 * pi() / bigSegments);
    float angleSmall = (float) (2 * pi() / smallSegments);

    glm::vec3 Z_Normal = glm::vec3(0, 0, 1);

    vertexes = std::vector<glm::vec3>();
    glm::vec3 bigRotor = glm::vec3(x(bigRadius), y(0), z(0));
    glm::vec3 smallRotor = glm::vec3(x(smallRadius), y(0), z(0));
    glm::vec3 currVertex = glm::vec3(x(0), y(0), z(0));


    for (int i = 0; i < bigSegments; ++i) {

        /* вычисляем нормаль вращения для маленького "вращателя" */
        glm::vec3 rotatingNormal = glm::normalize(glm::cross(Z_Normal, smallRotor));
        /* строим сечение */
        for (int j = 0; j < smallSegments; ++j) {

            /* (снова) вычисляем вершину через сумму большого и маленького "вращателей" */
            currVertex = bigRotor + smallRotor;
            vertexes.push_back(currVertex);

            /* (снова) вращаем маленький вращатель по нормали вращения */
            smallRotor = glm::rotate(smallRotor, angleSmall, rotatingNormal);
        }

        /* поворачиваем маленький и большой "вращатели" на одинаковый угол по нормали Z */
        bigRotor = glm::rotate(bigRotor, angleBig, Z_Normal);
        smallRotor = glm::rotate(smallRotor, angleBig, Z_Normal);

    }

    Triangle tr = Triangle();
    for (int sR = 0; sR < smallSegments; ++sR) {
        for (int bR = 0; bR < bigSegments; ++bR) {
            tr.a = layer(bR, sR);
            tr.b = layer(bR, sR + 1);
            tr.c = layer(bR + 1, sR);
            triagIndexes.push_back(tr);
        }
    }

    for (int sR = 0; sR < smallSegments; ++sR) {
        for (int bR = 0; bR < bigSegments; ++bR) {
            tr.a = layer(bR + 1, sR);
            tr.b = layer(bR, sR + 1);
            tr.c = layer(bR + 1, sR + 1);
            triagIndexes.push_back(tr);
        }
    }

    for (Triangle tr_: triagIndexes) {
        std::cout << "a = " << tr_.a << ", b = " << tr_.b << ", c = " << tr_.c << std::endl;
    }
}

Tor::Tor(float bigRadius_, float smallRadius_, int bigSegments_, int smallSegments_, glm::vec3 pos) : Tor(bigRadius_, smallRadius_, bigSegments_, smallSegments_) {
    this->move(pos);
};


inline int Tor::layer(int layNum, int shift) const {
    return ((layNum >= bigSegments ? layNum % bigSegments : layNum) * smallSegments + ((shift >= smallSegments) ? shift % smallSegments: shift));
}