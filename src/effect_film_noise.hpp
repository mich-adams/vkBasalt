#ifndef EFFECT_FILM_NOISE_HPP_INCLUDED
#define EFFECT_FILM_NOISE_HPP_INCLUDED
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
    class FilmNoiseEffect : public SimpleEffect
    {
    public:
        FilmNoiseEffect(LogicalDevice*       pLogicalDevice,
                  VkFormat             format,
                  VkExtent2D           imageExtent,
                  std::vector<VkImage> inputImages,
                  std::vector<VkImage> outputImages,
                  Config*              pConfig);
        ~FilmNoiseEffect();
    };
} // namespace vkBasalt

#endif // EFFECT_FILM_NOISE_HPP_INCLUDED
