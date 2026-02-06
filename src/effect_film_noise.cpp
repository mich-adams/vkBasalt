#include "effect_film_noise.hpp"

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
    FilmNoiseEffect::FilmNoiseEffect(LogicalDevice*       pLogicalDevice,
                                     VkFormat             format,
                                     VkExtent2D           imageExtent,
                                     std::vector<VkImage> inputImages,
                                     std::vector<VkImage> outputImages,
                                     Config*              pConfig)
    {

        float strength = pConfig->getOption<float>("filmNoiseStrength", 2.0);

        vertexCode   = full_screen_triangle_vert;
        fragmentCode = film_noise_frag;

        VkSpecializationMapEntry strengthMapEntry;
        strengthMapEntry.constantID = 0;
        strengthMapEntry.offset     = 0;
        strengthMapEntry.size       = sizeof(float);

        VkSpecializationInfo fragmentSpecializationInfo;
        fragmentSpecializationInfo.mapEntryCount = 1;
        fragmentSpecializationInfo.pMapEntries   = &strengthMapEntry;
        fragmentSpecializationInfo.dataSize      = sizeof(float);
        fragmentSpecializationInfo.pData         = &strength;

        pVertexSpecInfo   = nullptr;
        pFragmentSpecInfo = &fragmentSpecializationInfo;

        init(pLogicalDevice, format, imageExtent, inputImages, outputImages, pConfig);
    }
    FilmNoiseEffect::~FilmNoiseEffect()
    {
    }
} // namespace vkBasalt
