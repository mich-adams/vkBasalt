#include "effect_vibrance.hpp"

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
    VibranceEffect::VibranceEffect(LogicalDevice*       pLogicalDevice,
                                   VkFormat             format,
                                   VkExtent2D           imageExtent,
                                   std::vector<VkImage> inputImages,
                                   std::vector<VkImage> outputImages,
                                   Config*              pConfig)
    {

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = vibrance_frag;

        float vibranceVibrance = pConfig->getOption<float>("vibranceContrast", 0.15);
        float vibranceRBalance = pConfig->getOption<float>("vibranceRBalance", 1.0);
        float vibranceGBalance = pConfig->getOption<float>("vibranceGBalance", 1.0);
        float vibranceBBalance = pConfig->getOption<float>("vibranceBBalance", 1.0);
        float vibranceLumaType = pConfig->getOption<float>("vibranceLumaType", 0);

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = vibrance_frag;

        std::vector<VkSpecializationMapEntry> specMapEntrys(5);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {vibranceVibrance, vibranceRBalance, vibranceGBalance, vibranceBBalance, vibranceLumaType};

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    VibranceEffect::~VibranceEffect()
    {
    }
} // namespace vkBasalt
