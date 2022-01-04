#pragma once
#include <string>
#include <memory>
#include "DataTypes.h"

namespace Scene {
    class IMaterial {
    public:
        virtual ~IMaterial() {};

        virtual void          setName(std::string) =0;
        virtual std::string   getName() const =0;

        virtual void          setTransparency(unsigned char transparency) =0;
        virtual unsigned char getTransparency() const =0;

        virtual void          setColor(const Color&) =0;
        virtual Color         getColor() const =0;
    };

    typedef std::shared_ptr<IMaterial> MaterialHandle;
}