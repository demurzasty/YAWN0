#include <YAWN/GraphicsResource.hpp>

using namespace YAWN;

GraphicsResource::GraphicsResource(YAWN::Id id)
    : _id(id) {
}

Id GraphicsResource::Id() const noexcept {
    return _id;
}
