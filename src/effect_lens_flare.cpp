#include "effect_lens_flare.hpp"

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
    LensFlareEffect::LensFlareEffect(LogicalDevice*       pLogicalDevice,
                                     VkFormat             format,
                                     VkExtent2D           imageExtent,
                                     std::vector<VkImage> inputImages,
                                     std::vector<VkImage> outputImages,
                                     Config*              pConfig)
    {

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = lens_flare_frag;

        float lensflareThreshold = pConfig->getOption<float>("lensflareThreshold", 0.98);
        float   lensflareGhosts    = pConfig->getOption<float>("lensflareGhosts", 5.0);
        float lensflareDispersal = pConfig->getOption<float>("lensflareDispersal", 0.35);
        float lensflareIntensity = pConfig->getOption<float>("lensflareIntensity", 0.5);

        std::vector<VkSpecializationMapEntry> specMapEntrys(4);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {lensflareThreshold, lensflareGhosts, lensflareDispersal, lensflareIntensity};

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    LensFlareEffect::~LensFlareEffect()
    {
    }
} // namespace vkBasalt
