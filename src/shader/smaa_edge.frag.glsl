#version 450
#extension GL_GOOGLE_include_directive : require

layout(set = 0, binding = 0) uniform sampler2D colorImg;
layout(set = 0, binding = 5) uniform sampler2D rawDepthImg;
layout(set = 0, binding = 6) uniform sampler2D linearDepthImg;
layout(set = 0, binding = 7) uniform sampler2D normalImg;

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec2 textureCoord;
layout(location = 1) in vec4[3] offsets;

#include "smaa_settings.h"
#define SMAA_INCLUDE_VS 0
#define SMAA_INCLUDE_PS 1
#include "smaa.h"

void main()
{
    if (detectionType == 1) {
        fragColor = vec4(SMAAColorEdgeDetectionPS(textureCoord, offsets, colorImg), 0.0, 0.0);
    }

    else if (detectionType == 2) {
        fragColor = vec4(SMAADepthEdgeDetectionPS(textureCoord, offsets, linearDepthImg), 0.0, 0.0);
    }

    else {
        fragColor = vec4(SMAALumaEdgeDetectionPS(textureCoord, offsets, colorImg), 0.0, 0.0);
    }
}