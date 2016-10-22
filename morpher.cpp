#include "morpher.hpp"



Morpher::Morpher(Figure* fromFig_, Figure* toFig_, int iterations_) {


    this->iterations = iterations_;
    this->fromFig = fromFig_;
    this->toFig = toFig_;

    std::vector<glm::vec3>& vertxs1 = *fromFig->getVertexes();
    std::vector<glm::vec3>& vertxs2 = *toFig->getVertexes();

    if (vertxs1.size() != vertxs2.size())  {
        std::cerr << "Figures must be isomorphic and have same vertex amount" << std::endl;
        return;
    }

    for (auto i = 0; i < vertxs1.size(); i++) {
        shifts.push_back((vertxs1[i] - vertxs2[i]) / (float)iterations);
    }

}


bool Morpher::morph() {

    if (currIter == iterations) reverse = true;
    if (currIter == 0) reverse = false;

    if (!reverse) {
        currIter++;
    } else {
        currIter--;
    }

    std::vector<glm::vec3>& vertxs = *fromFig->getVertexes();
    for (auto i = 0; i < vertxs.size(); i++) {
        if (!reverse) {
            vertxs[i] -= shifts[i];
        } else {
            vertxs[i] += shifts[i];
        }
    }
    std::cout << "\n";
}