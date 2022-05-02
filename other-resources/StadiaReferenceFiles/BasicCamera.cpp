#include "BasicCamera.h"
using namespace Scene;

BasicCamera::BasicCamera() :
    isMovingForward(false),
    isMovingBackward(false),
    isMovingLeft(false),
    isMovingRight(false),
    isMovingUp(false),
    isMovingDown(false),
    isLooking(false),
    mouseSensitivity(.0021f),
    position{ 0,0,0 },
    up{ 0,0,1 },
    forward{ 1,0,0 } {};

void BasicCamera::setName(std::string n) {
    name = n;
}

std::string BasicCamera::getName() const {
    return name;
}

void BasicCamera::setPosition(const Vector3& p) {
    position = p;
}

Vector3 BasicCamera::getPosition() const {
    return position;
}

void BasicCamera::setUpDirection(const Vector3& u) {
    up = u;
}

Vector3 BasicCamera::getUpDirection() const {
    return up;
}

void BasicCamera::setForwardDirection(const Vector3& f) {
    forward = f;
}

Vector3 BasicCamera::getForwardDirection() const {
    return forward;
}

void BasicCamera::notify(const InputEvent& e) {
    if(e.eventType == EventType::KEY_DOWN) {
        if(e.key == Key::W) isMovingForward = true;
        if(e.key == Key::S) isMovingBackward = true;
        if(e.key == Key::A) isMovingLeft = true;
        if(e.key == Key::D) isMovingRight = true;
        if(e.key == Key::E) isMovingUp = true;
        if(e.key == Key::Q) isMovingDown = true;
    }
    if(e.eventType == EventType::KEY_UP) {
        if(e.key == Key::W) isMovingForward = false;
        if(e.key == Key::S) isMovingBackward = false;
        if(e.key == Key::A) isMovingLeft = false;
        if(e.key == Key::D) isMovingRight = false;
        if(e.key == Key::E) isMovingUp = false;
        if(e.key == Key::Q) isMovingDown = false;
    }
    // rotate camera
    if(e.eventType == EventType::MOUSE_CLICK) {
        isLooking = true;
    }
    if(e.eventType == EventType::MOUSE_RELEASE) {
        isLooking = false;
    }
    if(e.eventType == EventType::MOUSE_MOVE) {
        if(isLooking) {
            // look left and right (about z axis) with mouse x movement
            float rotateZRadians = -e.moveX * mouseSensitivity;
            forward = forward * rotateZ(rotateZRadians);
            
            // look up and down with y mouse movement
            float rotateRadians = -e.moveY * mouseSensitivity;
            Vector3 right = up.cross(forward);
            forward = forward * rotateAboutAxis(right, rotateRadians);

            // keep forward vector a unit vector (only points)
            forward.normalize();
        }
    }
}

void BasicCamera::update(float deltaMs) {
    if(isMovingForward) {
        float moveDistance = moveSpeed / 1000.0f * deltaMs; // meters/second / miliseconds/second * miliseconds = meters
        position += moveDistance * forward;
    }
    if(isMovingBackward) {
        float moveDistance = moveSpeed / 1000.0f * deltaMs;
        position -= moveDistance * forward;
    }
    if(isMovingLeft) {
        float moveDistance = moveSpeed / 1000.0f * deltaMs;
        Vector3 left = -forward.cross(up).normalize();
        position += moveDistance * left;
    }
    if(isMovingRight) {
        float moveDistance = moveSpeed / 1000.0f * deltaMs;
        Vector3 right = forward.cross(up).normalize();
        position += moveDistance * right;
    }
    if(isMovingUp) {
        position.z += moveSpeed / 1000.0f * deltaMs;
    }
    if(isMovingDown) {
        position.z -= moveSpeed / 1000.0f * deltaMs;
    }
}