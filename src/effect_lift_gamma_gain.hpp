#ifndef EFFECT_LIFT_GAMMA_GAIN_HPP_INCLUDED
#define EFFECT_LIFT_GAMMA_GAIN_HPP_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "vulkan_include.hpp"

#include "effect_simple.hpp"
#include "config.hpp"

namespace vkBasalt
{
    class LiftGammaGainEffect : public SimpleEffect
    {
    public:
        LiftGammaGainEffect(LogicalDevice*       pLogicalDevice,
                  VkFormat             format,
                  VkExtent2D           imageExtent,
                  std::vector<VkImage> inputImages,
                  std::vector<VkImage> outputImages,
                  Config*              pConfig);
        ~LiftGammaGainEffect();
    };
} // namespace vkBasalt

#endif // EFFECT_LIFT_GAMMA_GAIN_HPP_INCLUDED
