#include <YAWN/Mesh.hpp>
#include <YAWN/GraphicsDevice.hpp>

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

using namespace YAWN;

Mesh::Mesh()
    : GraphicsResource(GraphicsDevice::Instance()->CreateMesh()) {
}

Mesh::~Mesh() {
    GraphicsDevice::Instance()->DestroyMesh(_id);
}

void Mesh::Load(const String& path) {
    cgltf_options options = {};
    cgltf_data* data = nullptr;
    cgltf_result result = cgltf_parse_file(&options, path.CString(), &data);
    if (result == cgltf_result_success) {
        /* TODO make awesome stuff */
        cgltf_free(data);
    }
}

