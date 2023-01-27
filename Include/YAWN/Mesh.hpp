#pragma once 

#include "GraphicsResource.hpp"

namespace YAWN {
    class Mesh : public GraphicsResource {
    public:
        Mesh();

        virtual ~Mesh() override;

        virtual void Load(const String& path) override;

    private:

    };
}
