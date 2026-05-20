// john-chapman.github.io/2017/11/05/pseudo-lens-flare.html

#version 450
layout(set = 0, binding = 0) uniform sampler2D source;
layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 outColor;

layout(constant_id = 0) const float lensflareThreshold = 0.999;
layout(constant_id = 1) const float lensflareGhosts = 5.0;
layout(constant_id = 2) const float lensflareDispersal = 0.35;
layout(constant_id = 3) const float lensflareIntensity = 0.5;

void main() {
    vec4 baseColor = texture(source, texcoord);

    vec2 centerVec = vec2(0.5, 0.5) - texcoord;
    vec2 ghostVec = centerVec * lensflareDispersal;

    vec3 flareResult = vec3(0.0);

    // Colors of each lens flare ghost
    vec3 TINTS[5] = vec3[](
            vec3(1.5, 1.5, 1.5), // White
            vec3(1.2, 0.7, 0.3), // Orange
            vec3(0.5, 0.8, 1.5), // Blue
            vec3(1.0, 0.5, 0.5), // Red
            vec3(1.2, 1.0, 0.5) // Yellow
        );

    for (int i = 0; i < lensflareGhosts; ++i) {
        vec2 offset = texcoord + ghostVec * float(i + 1);
        vec3 sampleColor = texture(source, offset).rgb;

        float luma = dot(sampleColor, vec3(0.2126, 0.7152, 0.0722));
        float circleMask = smoothstep(lensflareThreshold, lensflareThreshold + 0.1, luma);

        if (circleMask > 0.0) {
            float weight = 1.0 - (float(i) / lensflareGhosts);

            vec3 currentTint = TINTS[i % 5];
            vec3 tintedColor = sampleColor * currentTint;

            flareResult += tintedColor * circleMask * weight;
        }
    }

    outColor = baseColor + vec4(flareResult * lensflareIntensity, 0.0);
}
