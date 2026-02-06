#version 450
// film noise
// by hunterk
// license: public domain
// Modified by kevinlekiller to only use the grain part.

layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float filmNoiseStrength = 2.0;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {

    vec4 color = texture(inputTexture, texcoord).rgba;
    float grain = (texcoord.x + 4.0) * (texcoord.y + 4.0) * ((mod(random(texcoord), 800.0) + 10.0) * 10.0);
    color += (mod((mod(grain, 13.0) + 1.0) * (mod(grain, 123.0) + 1.0), 0.01) - 0.005) * filmNoiseStrength;
    fragColor = color;
}
