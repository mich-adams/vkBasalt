#version 450
#extension GL_GOOGLE_include_directive : require

layout(set = 0, binding = 6) uniform sampler2D linearDepthImg;

layout(location = 0) out vec2 fragColor;
layout(location = 0) in vec2 textureCoord;
layout(location = 1) in vec4[3] offsets;

#include "smaa_settings.h"

vec2 SMAAScreenSpaceNormalsPS_EdgeAware(sampler2D linearDepthSampler, vec2 tc)
{
    vec3 offset = vec3(SMAA_RT_METRICS.xy, 0.0);
    vec2 posCenter = tc;
    
    vec2 posNorth = posCenter - offset.zy;
    vec2 posSouth = posCenter + offset.zy;
    vec2 posWest  = posCenter - offset.xz;
    vec2 posEast  = posCenter + offset.xz;
    
    float depthCenter = texture(linearDepthSampler, posCenter).r;
    float depthNorth  = texture(linearDepthSampler, posNorth).r;
    float depthSouth  = texture(linearDepthSampler, posSouth).r;
    float depthWest   = texture(linearDepthSampler, posWest).r;
    float depthEast   = texture(linearDepthSampler, posEast).r;
    
    // Edge detection threshold
    float edgeThreshold = 0.001;

    // For a bit of smoothing
    // Allows some blending in the slope detection to mask banding in the depth buffer
    float depthEpsilon = 0.0005;
    
    // Vertical edge detection (North-South)
    float slopeNorth = abs(depthCenter - depthNorth) > depthEpsilon ? 
                   (depthCenter - depthNorth) : 0.0;
    float slopeSouth = abs(depthSouth - depthCenter) > depthEpsilon ? 
                    (depthSouth - depthCenter) : 0.0;
    
    // Check if slopes match (continuous surface) or mismatch (edge)
    bool verticalEdge = (sign(slopeNorth) != sign(slopeSouth)) || 
                        (abs(abs(slopeNorth) - abs(slopeSouth)) > edgeThreshold);
    
    // Choose which samples to use for vertical gradient
    float depthTop, depthBottom;
    if (verticalEdge)
    {
        // We're on an edge - only use the sample on our side
        if (abs(slopeNorth) < abs(slopeSouth))
        {
            // North is on our surface, South is across the edge
            depthTop = depthNorth;
            depthBottom = depthCenter;
        }
        else
        {
            // South is on our surface, North is across the edge
            depthTop = depthCenter;
            depthBottom = depthSouth;
        }
    }
    else
    {
        // Continuous surface - use centered difference
        depthTop = depthNorth;
        depthBottom = depthSouth;
    }
    
    // Horizontal edge detection (West-East)
    float slopeWest = abs(depthCenter - depthWest) > depthEpsilon ? 
                  (depthCenter - depthWest) : 0.0;
    float slopeEast = abs(depthEast - depthCenter) > depthEpsilon ? 
                    (depthEast - depthCenter) : 0.0;
    
    bool horizontalEdge = (sign(slopeWest) != sign(slopeEast)) || 
                          (abs(abs(slopeWest) - abs(slopeEast)) > edgeThreshold);
    
    float depthLeft, depthRight;
    if (horizontalEdge)
    {
        if (abs(slopeWest) < abs(slopeEast))
        {
            depthLeft = depthWest;
            depthRight = depthCenter;
        }
        else
        {
            depthLeft = depthCenter;
            depthRight = depthEast;
        }
    }
    else
    {
        depthLeft = depthWest;
        depthRight = depthEast;
    }
    
    // Calculate normals with the selected pixels
    vec2 posTop = verticalEdge ? (abs(slopeNorth) < abs(slopeSouth) ? posNorth : posCenter) : posNorth;
    vec2 posBottom = verticalEdge ? (abs(slopeNorth) < abs(slopeSouth) ? posCenter : posSouth) : posSouth;
    vec2 posLeft = horizontalEdge ? (abs(slopeWest) < abs(slopeEast) ? posWest : posCenter) : posWest;
    vec2 posRight = horizontalEdge ? (abs(slopeWest) < abs(slopeEast) ? posCenter : posEast) : posEast;
    
    vec3 vertTop = vec3(posTop - 0.5, 1) * depthTop;
    vec3 vertBottom = vec3(posBottom - 0.5, 1) * depthBottom;
    vec3 vertLeft = vec3(posLeft - 0.5, 1) * depthLeft;
    vec3 vertRight = vec3(posRight - 0.5, 1) * depthRight;
    
    vec3 dx = vertRight - vertLeft;
    vec3 dy = vertBottom - vertTop;

    vec3 normal = normalize(cross(dx, dy));
    
    return normal.xy;
}

void main()
{
    fragColor = SMAAScreenSpaceNormalsPS_EdgeAware(linearDepthImg, textureCoord);
}