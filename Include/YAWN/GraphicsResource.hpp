#pragma once 

#include "Resource.hpp"

namespace YAWN {
    class GraphicsResource : public Resource {
    public:
        GraphicsResource(Id id);

        virtual ~GraphicsResource() override = default;

        Id Id() const noexcept;

    protected:
        const YAWN::Id _id;
    };
}