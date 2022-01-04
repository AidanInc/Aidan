#pragma once
#include <string>
#include <memory>
#include "DataTypes.h"
namespace Scene {
    class ILight {
    public:
        virtual ~ILight() {};

        virtual std::string getName() const =0;

        virtual void        setPosition(const Vector3&) =0;
        virtual Vector3     getPosition() const =0;

        virtual void        setColor(const Color&) =0;
        virtual Color       getColor() const =0;

        virtual void        setIntensity(int candelas) =0;
        virtual int         getIntensity() const =0;
    };

    typedef std::shared_ptr<ILight> LightPtr;
}