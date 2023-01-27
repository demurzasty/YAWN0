#version 450 core
#extension GL_ARB_bindless_texture : enable

layout (location = 0) out vec4 oColor;

layout (std430, binding = 0) buffer uSampler {
    sampler2D uSamplers[];
};

layout (location = 0) in vec4 iColor;
layout (location = 1) in vec2 iUV;

void main() {
    oColor = iColor * texture(uSamplers[0], iUV);
}
