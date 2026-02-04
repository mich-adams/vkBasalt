#version 450

layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float dpxContrast = 0.1;
layout(constant_id = 1) const float dpxSaturation = 3.0;
layout(constant_id = 2) const float dpxStrength = 0.02;

void main() {
    vec4 color = texture(inputTexture, texcoord).rgba;
    vec3 dpxRGBC = vec3(0.36, 0.38, 0.34);
    vec3 dpxRGBCurve = vec3(8.0, 8.0, 8.0);
    vec3 dpxColorfulness = vec3(2.5, 2.5, 2.5);

    mat3x3 dpxRGB = mat3x3(
            2.6714711726599600, -1.2672360578624100, -0.4109956021722270,
            -1.0251070293466400, 1.9840911624108900, 0.0439502493584124,
            0.0610009456429445, -0.2236707508128630, 1.1590210416706100
        );
    mat3x3 dpxXYZ = mat3x3(
            0.5003033835433160, 0.3380975732227390, 0.1645897795458570,
            0.2579688942747580, 0.6761952591447060, 0.0658358459823868,
            0.0234517888692628, 0.1126992737203000, 0.8668396731242010
        );
    vec3 dpxB = color.rgb * (1.0 - dpxContrast) + (0.5 * dpxContrast);
    vec3 dpxB2 = (1.0 / (1.0 + exp(dpxRGBCurve / 2.0)));
    dpxB = ((1.0 / (1.0 + exp(-dpxRGBCurve * (dpxB - dpxRGBC)))) / (-2.0 * dpxB2 + 1.0)) + (-dpxB2 / (-2.0 * dpxB2 + 1.0));

    float dpxVal = max(max(dpxB.r, dpxB.g), dpxB.b);
    vec3 dpxC0 = dpxXYZ * (pow(abs(dpxB / dpxVal), 1.0 / dpxColorfulness) * dpxVal);
    color.rgb = mix(color.rgb, (dpxRGB * ((1.0 - dpxSaturation) * dot(dpxC0, vec3(0.30, 0.59, 0.11)) + dpxSaturation * dpxC0)), dpxStrength);
    
    fragColor = color;
}
