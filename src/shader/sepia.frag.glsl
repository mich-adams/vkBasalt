#version 450
/* Ported to glsl by kevinlekiller 2022
 * The MIT License (MIT) */

layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float sepiaStrength = 0.58;
layout(constant_id = 1) const float sepiaR = 0.55;
layout(constant_id = 2) const float sepiaG = 0.43;
layout(constant_id = 3) const float sepiaB = 0.42;

void main() {
    vec3 sepiaTint = vec3(sepiaR, sepiaG, sepiaB);
    vec4 texColor = texture(inputTexture,texcoord).rgba;

    fragColor.rgb = mix(texColor.rgb, texColor.rgb * sepiaTint * 2.55, sepiaStrength);
}
