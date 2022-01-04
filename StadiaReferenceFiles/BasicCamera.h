#pragma once
#include "ICamera.h"
namespace Scene {
    class BasicCamera : public ICamera {
    public:
        BasicCamera();
        void        setName(std::string);
        std::string getName() const;

        void        setPosition(const Vector3&);
        Vector3     getPosition() const;

        void        setUpDirection(const Vector3&);
        Vector3     getUpDirection() const;

        void        setForwardDirection(const Vector3&);
        Vector3     getForwardDirection() const;

        void        notify(const InputEvent&);
        void        update(float deltaMS);
    private:
        std::string name;
        Vector3     position;
        Vector3     up;
        Vector3     forward;

        bool        isMovingForward;
        bool        isMovingBackward;
        bool        isMovingDown;
        bool        isMovingUp;
        bool        isMovingRight;
        bool        isMovingLeft;
        bool        isLooking;
        float       mouseSensitivity; // radians/pixel

        const float moveSpeed = 40.0; // meters/second
    };
}