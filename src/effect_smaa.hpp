#ifndef EFFECT_SMAA_HPP_INCLUDED
#define EFFECT_SMAA_HPP_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "vulkan_include.hpp"

#include "effect.hpp"
#include "config.hpp"

#include "logical_device.hpp"

namespace vkBasalt
{
    class SmaaEffect : public Effect
    {
    public:
        SmaaEffect(LogicalDevice*       pLogicalDevice,
                   VkFormat             format,
                   VkExtent2D           imageExtent,
                   std::vector<VkImage> inputImages,
                   std::vector<VkImage> outputImages,
                   Config*              pConfig);
        void applyEffect(uint32_t imageIndex, VkCommandBuffer commandBuffer) override;
        void useDepthImage(VkImage depthImage, VkImageView depthImageView);
        void useDepthImage(VkImageView depthImageView) override;
        ~SmaaEffect();

    private:
        LogicalDevice*               pLogicalDevice;
        std::vector<VkImage>         inputImages;
        std::vector<VkImage>         linearDepthImages;
        std::vector<VkImage>         normalImages;
        std::vector<VkImage>         edgeImages;
        std::vector<VkImage>         blendImages;
        std::vector<VkImage>         outputImages;
        std::vector<VkImageView>     inputImageViews;
        std::vector<VkImageView>     linearDepthImageViews;
        std::vector<VkImageView>     normalImageViews;
        std::vector<VkImageView>     edgeImageViews;
        std::vector<VkImageView>     blendImageViews;
        std::vector<VkImageView>     outputImageViews;
        std::vector<VkDescriptorSet> imageDescriptorSets;
        std::vector<VkFramebuffer>   linearDepthFramebuffers;
        std::vector<VkFramebuffer>   normalFramebuffers;
        std::vector<VkFramebuffer>   edgeFramebuffers;
        std::vector<VkFramebuffer>   blendFramebuffers;
        std::vector<VkFramebuffer>   neighborFramebuffers;
        VkImage                      depthImage;
        VkImage                      areaImage;
        VkImage                      searchImage;
        VkImageView                  depthImageView;
        VkImageView                  areaImageView;
        VkImageView                  searchImageView;
        VkDescriptorSetLayout        imageSamplerDescriptorSetLayout;
        VkDescriptorPool             descriptorPool;
        VkShaderModule               depthVertexModule;
        VkShaderModule               depthFragmentModule;
        VkShaderModule               normalVertexModule;
        VkShaderModule               normalFragmentModule;
        VkShaderModule               edgeVertexModule;
        VkShaderModule               edgeFragmentModule;
        VkShaderModule               blendVertexModule;
        VkShaderModule               blendFragmentModule;
        VkShaderModule               neighborVertexModule;
        VkShaderModule               neighborFragmentModule;
        VkRenderPass                 depthRenderPass;
        VkRenderPass                 normalRenderPass;
        VkRenderPass                 renderPass;
        VkRenderPass                 unormRenderPass;
        VkPipelineLayout             pipelineLayout;
        VkPipeline                   linearDepthPipeline;
        VkPipeline                   normalPipeline;
        VkPipeline                   edgePipeline;
        VkPipeline                   blendPipeline;
        VkPipeline                   neighborPipeline;
        VkExtent2D                   imageExtent;
        VkFormat                     format;
        VkDeviceMemory               dummyDepthMemory;
        VkDeviceMemory               imageMemory;
        VkDeviceMemory               linearDepthMemory;
        VkDeviceMemory               normalMemory;
        VkDeviceMemory               areaMemory;
        VkDeviceMemory               searchMemory;
        VkSampler                    sampler;
        VkSampler                    depthSampler;

        Config* pConfig;
    };
} // namespace vkBasalt

#endif // EFFECT_SMAA_HPP_INCLUDED
