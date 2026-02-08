#version 450
/**
 * Lift Gamma Gain version 1.1, by 3an and CeeJay.dk
 * Ported to glsl by kevinlekiller 2022
 * The MIT License (MIT)
**/

layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float liftR = 1.0;
layout(constant_id = 1) const float liftG = 1.0;
layout(constant_id = 2) const float liftB = 1.0;
layout(constant_id = 3) const float gammaR = 1.0;
layout(constant_id = 4) const float gammaG = 1.0;
layout(constant_id = 5) const float gammaB = 1.0;
layout(constant_id = 6) const float gainR = 1.0;
layout(constant_id = 7) const float gainG = 1.0;
layout(constant_id = 8) const float gainB = 1.0;

void main() {
    vec4 color = texture(inputTexture, texcoord).rgba;
    vec3 liftRGB = vec3 (liftR, liftG, liftB);
    vec3 gammaRGB = vec3 (gammaR, gammaG, gammaB);
    vec3 gainRGB = vec3 (gainR, gainG, gainB);

    // -- Lift --
    color.rgb = color.rgb * (1.5 - 0.5 * liftRGB) + 0.5 * liftRGB - 0.5;
    // Is not strictly necessary, but does not cost performance
    color.rgb = clamp(color.rgb, 0.0, 1.0);

    // -- Gain --
    color.rgb *= gainRGB;

    // -- Gamma --
    color.rgb = pow(abs(color.rgb), 1.0 / gammaRGB);

    color.rgb = clamp(color.rgb, 0.0, 1.0);
    
    fragColor = color;
}
