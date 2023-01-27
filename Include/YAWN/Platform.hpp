#pragma once 

#include "Managed.hpp"

namespace YAWN {
    class Platform : public Reference {
    public:
        static Managed<Platform> Instance();

    public:
        virtual ~Platform() = default;

        virtual bool IsWindowOpen() const = 0;

        virtual void PollEvents() = 0;

        virtual double CurrentTime() const = 0;

        virtual void* WindowHandle() const = 0;
    };
}
