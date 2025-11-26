#version 450
#extension GL_GOOGLE_include_directive : require

layout(set = 0, binding = 5) uniform sampler2D rawDepthImg;

layout(location = 0) out float fragColor;
layout(location = 0) in vec2 textureCoord;

#include "smaa_settings.h"

// Based on ReShade code for compatibility
float linearizeDepth(sampler2D depthSampler, vec2 tc)
{
    if (depthInputIsUpsideDown != 0) {
        tc.y = 1.0 - tc.y;
    }
    
    float depth = texture(depthSampler, tc).x * depthMultiplier;
    
    if (depthInputIsLogarithmic != 0) {
        const float C = 0.01;
        depth = (exp(depth * log(C + 1.0)) - 1.0) / C;
    }
    
    if (depthInputIsReverse != 0) {
        depth = 1.0 - depth;
    }
    
    const float N = 1.0;
    depth /= depthLinearizationFarPlane - depth * (depthLinearizationFarPlane - N);
    
    return depth;
}

void main()
{
    fragColor = linearizeDepth(rawDepthImg, textureCoord);
}