#include "effect_sepia.hpp"

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
    SepiaEffect::SepiaEffect(LogicalDevice*       pLogicalDevice,
                             VkFormat             format,
                             VkExtent2D           imageExtent,
                             std::vector<VkImage> inputImages,
                             std::vector<VkImage> outputImages,
                             Config*              pConfig)
    {

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = sepia_frag;

        float sepiaStrength = pConfig->getOption<float>("sepiaStrength", 0.58);
        float sepiaR        = pConfig->getOption<float>("sepiaR", 0.55);
        float sepiaG        = pConfig->getOption<float>("sepiaG", 0.43);
        float sepiaB        = pConfig->getOption<float>("sepiaB", 0.42);
        ;

        std::vector<VkSpecializationMapEntry> specMapEntrys(4);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {sepiaStrength, sepiaR, sepiaG, sepiaB};

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    SepiaEffect::~SepiaEffect()
    {
    }
} // namespace vkBasalt
