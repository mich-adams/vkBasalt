#include "effect_reinhard.hpp"

#include <cstring>

#include "image_view.hpp"
#include "descriptor_set.hpp"
#include "buffer.hpp"
#include "renderpass.hpp"
#include "graphics_pipeline.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"
#include "sampler.hpp"

#include "shader_sources.hpp"

namespace vkBasalt
{
    ReinhardEffect::ReinhardEffect(LogicalDevice*       pLogicalDevice,
                                   VkFormat             format,
                                   VkExtent2D           imageExtent,
                                   std::vector<VkImage> inputImages,
                                   std::vector<VkImage> outputImages,
                                   Config*              pConfig)
    {
        float reinhardExposure     = pConfig->getOption<float>("reinhardExposure", 1.0);
        float reinhardGamma        = pConfig->getOption<float>("reinhardGamma", 2.2);
        float reinhardUseLuminance = pConfig->getOption<float>("reinhardUseLuminance", 1);
        float reinhardUseSimple    = pConfig->getOption<float>("reinhardUseSimple", 0);
        float reinhardWhitePoint   = pConfig->getOption<float>("reinhardWhitePoint", 5.0);

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = reinhard_frag;

        std::vector<VkSpecializationMapEntry> specMapEntrys(5);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {reinhardExposure, reinhardGamma, reinhardUseLuminance, reinhardUseSimple, reinhardWhitePoint};

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = reinhard_frag;

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    ReinhardEffect::~ReinhardEffect()
    {
    }
} // namespace vkBasalt
