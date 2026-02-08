#include "effect_lift_gamma_gain.hpp"

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
    LiftGammaGainEffect::LiftGammaGainEffect(LogicalDevice*       pLogicalDevice,
                         VkFormat             format,
                         VkExtent2D           imageExtent,
                         std::vector<VkImage> inputImages,
                         std::vector<VkImage> outputImages,
                         Config*              pConfig)
    {

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = lift_gamma_gain_frag;

        float liftR   = pConfig->getOption<float>("liftR", 1.0);
        float liftG = pConfig->getOption<float>("liftG", 1.0);
        float liftB   = pConfig->getOption<float>("liftB", 1.0);
        float gammaR   = pConfig->getOption<float>("gammaR", 1.0);
        float gammaG = pConfig->getOption<float>("gammaG", 1.0);
        float gammaB   = pConfig->getOption<float>("gammaB", 1.0);
        float gainR   = pConfig->getOption<float>("gainR", 1.0);
        float gainG = pConfig->getOption<float>("gainG", 1.0);
        float gainB   = pConfig->getOption<float>("gainB", 1.0);

        std::vector<VkSpecializationMapEntry> specMapEntrys(9);

        for (uint32_t i = 0; i < specMapEntrys.size(); i++)
        {
            specMapEntrys[i].constantID = i;
            specMapEntrys[i].offset     = sizeof(float) * i;
            specMapEntrys[i].size       = sizeof(float);
        }
        std::vector<float> specData = {liftR, liftG, liftB, gammaR, gammaG, gammaB, gainR, gainG, gainB};

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = specMapEntrys.size();
        fragmentSpecializationInfo.pMapEntries   = specMapEntrys.data();
        fragmentSpecializationInfo.dataSize      = sizeof(float) * specData.size();
        fragmentSpecializationInfo.pData         = specData.data();

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    LiftGammaGainEffect::~LiftGammaGainEffect()
    {
    }
} // namespace vkBasalt
