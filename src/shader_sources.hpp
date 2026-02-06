#pragma once

#include <vector>
#include <cstdint>

namespace vkBasalt
{
    const std::vector<uint32_t> cas_frag = {
#include "cas.frag.h"
    };

    const std::vector<uint32_t> deband_frag = {
#include "deband.frag.h"
    };

    const std::vector<uint32_t> dls_frag = {
#include "dls.frag.h"
    };

    const std::vector<uint32_t> dpx_frag = {
#include "dpx.frag.h"
    };

    const std::vector<uint32_t> film_noise_frag = {
#include "film_noise.frag.h"
    };

    const std::vector<uint32_t> full_screen_triangle_vert = {
#include "full_screen_triangle.vert.h"
    };

    const std::vector<uint32_t> fxaa_frag = {
#include "fxaa.frag.h"
    };

    const std::vector<uint32_t> lut_frag = {
#include "lut.frag.h"
    };

    const std::vector<uint32_t> smaa_blend_frag = {
#include "smaa_blend.frag.h"
    };

    const std::vector<uint32_t> smaa_blend_vert = {
#include "smaa_blend.vert.h"
    };

    const std::vector<uint32_t> smaa_edge_frag = {
#include "smaa_edge.frag.h"
    };

    const std::vector<uint32_t> smaa_edge_vert = {
#include "smaa_edge.vert.h"
    };

    const std::vector<uint32_t> smaa_neighbor_frag = {
#include "smaa_neighbor.frag.h"
    };

    const std::vector<uint32_t> smaa_neighbor_vert = {
#include "smaa_neighbor.vert.h"
    };

    const std::vector<uint32_t> linear_depth_frag = {
#include "linear_depth.frag.h"
    };

    const std::vector<uint32_t> screen_space_normal_frag = {
#include "screen_space_normal.frag.h"
    };

    const std::vector<uint32_t> vibrance_frag = {
#include "vibrance.frag.h"
    };
} // namespace vkBasalt
