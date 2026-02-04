#include "effect_dpx.hpp"

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
    DpxEffect::DpxEffect(LogicalDevice*       pLogicalDevice,
                         VkFormat             format,
                         VkExtent2D           imageExtent,
                         std::vector<VkImage> inputImages,
                         std::vector<VkImage> outputImages,
                         Config*              pConfig)
    {

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = dpx_frag;

        float dpxContrast   = pConfig->getOption<float>("dpxContrast", 0.1);
        float dpxSaturation = pConfig->getOption<float>("dpxSaturation", 3.0);
        float dpxStrength   = pConfig->getOption<float>("dpxStrength", 0.02);

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = dpx_frag;

        std::vector<VkSpecializationMapEntry> specMapEntrys(3);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {dpxContrast, dpxSaturation, dpxStrength};

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    DpxEffect::~DpxEffect()
    {
    }
} // namespace vkBasalt
