#pragma once
#include <string>
#include "IMaterial.h"
namespace Scene {
    class BasicMaterial : public IMaterial {
    public:
        BasicMaterial() : transparency(0) {}

        void          setName(std::string name);
        std::string   getName() const;

        void          setTransparency(unsigned char transparency);
        unsigned char getTransparency() const;

        void          setColor(const Color&);
        Color         getColor() const;
    private:
        std::string   name;
        unsigned char transparency;
        Color         color;
    };
}