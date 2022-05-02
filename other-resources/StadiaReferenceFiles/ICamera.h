#pragma once
#include <string>
#include <memory>
#include "DataTypes.h"
#include "InputEvent.h"

namespace Scene {
    class ICamera {
    public:
        virtual ~ICamera() {};

        virtual void        setName(std::string) =0;
        virtual std::string getName() const =0;

        virtual void        setPosition(const Vector3&) =0;
        virtual Vector3     getPosition() const =0;

        virtual void        setUpDirection(const Vector3&) =0;
        virtual Vector3     getUpDirection() const =0;

        virtual void        setForwardDirection(const Vector3&) =0;
        virtual Vector3     getForwardDirection() const =0;

        virtual void        notify(const InputEvent& e) =0;
        virtual void        update(float deltaMs) =0;
    };

    typedef std::shared_ptr<ICamera> CameraHandle;
}