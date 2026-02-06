#ifndef EFFECT_VIBRANCE_HPP_INCLUDED
#define EFFECT_VIBRANCE_HPP_INCLUDED
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
    class VibranceEffect : public SimpleEffect
    {
    public:
        VibranceEffect(LogicalDevice*       pLogicalDevice,
                  VkFormat             format,
                  VkExtent2D           imageExtent,
                  std::vector<VkImage> inputImages,
                  std::vector<VkImage> outputImages,
                  Config*              pConfig);
        ~VibranceEffect();
    };
} // namespace vkBasalt

#endif // EFFECT_VIBRANCE_HPP_INCLUDED
