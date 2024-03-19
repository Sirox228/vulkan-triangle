#ifndef VK_GRAPHICS_PIPELINE_H
#define VK_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.h>

extern VkPipelineLayout graphicsPipelineLayout;
extern VkPipeline graphicsPipeline;

void createGraphicsPipeline();
void destroyGraphicsPipeline();

#endif
