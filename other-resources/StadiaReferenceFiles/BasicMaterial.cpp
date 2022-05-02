#include "BasicMaterial.h"
using namespace Scene;

void BasicMaterial::setName(std::string n) {
    name = n;
}
std::string BasicMaterial::getName() const {
    return name;
}

void BasicMaterial::setTransparency(unsigned char t) {
    transparency = t;
}

unsigned char BasicMaterial::getTransparency() const {
    return transparency;
}

void BasicMaterial::setColor(const Color& c) {
    color = c;
}

Color BasicMaterial::getColor() const {
    return color;
}