#version 450
/**
  Vibrance
  by Christian Cann Schuldt Jensen ~ CeeJay.dk

  Vibrance intelligently boosts the saturation of pixels so pixels that had little color get a larger boost than pixels that had a lot.
  This avoids oversaturation of pixels that were already very saturated.
  Ported to glsl by kevinlekiller - 2022
 */
/*
    The MIT License (MIT)

    Copyright (c) 2014 CeeJayDK

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
layout(location = 0) in vec2 texcoord;
layout(location = 0) out vec4 fragColor;
layout(set = 0, binding = 0) uniform sampler2D inputTexture;

layout(constant_id = 0) const float vibranceVibrance = 0.15;
layout(constant_id = 1) const float vibranceRBalance = 1.0;
layout(constant_id = 2) const float vibranceGBalance = 1.0;
layout(constant_id = 3) const float vibranceBBalance = 1.0;
layout(constant_id = 4) const float vibranceLumaType = 0;

vec3 vibranceRGBBalance = vec3(vibranceRBalance, vibranceGBalance, vibranceBBalance);
vec3 vibranceCoefLuma = vec3(0.333333, 0.333334, 0.333333);
vec3 vibranceCoeffVibrance = vec3(vibranceRGBBalance * -vibranceVibrance);

void main() {
    if(vibranceLumaType != 1)
    {
        vibranceCoefLuma = vec3(0.333333, 0.333334, 0.333333);
    }
    else
    {
	vibranceCoefLuma = vec3(0.212656, 0.715158, 0.072186);
    }
    vec4 color = texture(inputTexture, texcoord).rgba;
    float luma = dot(vibranceCoefLuma, color.rgb);
    float max_color = max(color.r, max(color.g, color.b));
    float min_color = min(color.r, min(color.g, color.b));
    float color_saturation = max_color - min_color;
    vec3 p_col = vec3(vec3(vec3(vec3(sign(vibranceCoeffVibrance) * color_saturation) - 1.0) * vibranceCoeffVibrance) + 1.0);
    color.r = mix(luma, color.r, p_col.r);
    color.g = mix(luma, color.g, p_col.g);
    color.b = mix(luma, color.b, p_col.b);

    fragColor = color;
}
