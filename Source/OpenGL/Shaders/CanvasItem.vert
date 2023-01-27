#version 450 core

layout (location = 0) in vec2 iPos;
layout (location = 1) in vec2 iUV;
layout (location = 2) in vec4 iColor;

uniform vec2 uScale;
uniform vec2 uTranslate;

out gl_PerVertex {
    vec4 gl_Position;
};

layout (location = 0) out vec4 oColor;
layout (location = 1) out vec2 oUV;

void main() {
    oColor = iColor;
    oUV = iUV;
   //  gl_Position = vec4(iPos * uScale + uTranslate, 0, 1);
    gl_Position = vec4((iPos / vec2(1280.0, 720.0)) * vec2(2.0, 2.0) - vec2(1.0), 0, 1);
    gl_Position.y *= -1.0;
}
