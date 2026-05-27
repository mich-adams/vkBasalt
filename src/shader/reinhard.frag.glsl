#version 450
// Vulkan GLSL port of Reshade port of Reinhard tonemap, lol
// Based on code from John Hable's and Tom Madams' blogs at http://filmicworlds.com/blog/filmic-tonemapping-operators/ and https://imdoingitwrong.wordpress.com/2010/08/19/why-reinhard-desaturates-my-blacks-3/ respectively
// by Jace Regenbrecht

layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float reinhardExposure = 1.0;
layout(constant_id = 1) const float reinhardGamma = 2.2;
layout(constant_id = 2) const float reinhardUseLuminance = 1.0;
layout(constant_id = 3) const float reinhardUseSimple = 0.0;
layout(constant_id = 4) const float reinhardWhitePoint = 5.0;

vec3 ReinhardSimple(vec3 x)
{
    return x / (1.0 + x);
}

vec3 ReinhardComplex(vec3 x, float white)
{
    return (x * (1.0 + (x / (white * white)))) / (1.0 + x);
}

void main() {
    vec4 texColor_alpha = texture(inputTexture, texcoord).rgba;
    vec3 texColor = texColor_alpha.rgb;
    texColor *= reinhardExposure;

    if (int(reinhardGamma) > 1) {
        texColor = pow(texColor, vec3(reinhardGamma));
    }

    texColor *= reinhardExposure; // Exposure adjustment

    vec3 processColor;
    float lum;

    // Determine if using lum or rgb
    if (int(reinhardUseLuminance) != 0) {
        lum = 0.2126f * texColor[0] + 0.7152 * texColor[1] + 0.0722 * texColor[2];
        processColor = vec3(lum, 0, 0);
    } else {
        processColor = texColor;
    }

    // Run tonemap equations
    if (int(reinhardUseSimple) != 0) {
        processColor = ReinhardSimple(processColor);
    } else {
        processColor = ReinhardComplex(processColor, reinhardWhitePoint);
    }

    // Do luminance adjustments
    if (int(reinhardUseLuminance) != 0) {
        float lumScale = float(processColor) / lum;
        processColor = texColor * lumScale;
    }

    // Post-tonemap gamma correction
    if (reinhardGamma > 1.00) {
        texColor = pow(processColor, vec3(1 / reinhardGamma));
    } else {
        texColor = processColor;
    }

    fragColor = vec4(texColor, texColor_alpha);
}
