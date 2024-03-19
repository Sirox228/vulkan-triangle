#ifndef VK_DEPTH_IMAGE_H
#define VK_DEPTH_IMAGE_H

#include <vulkan/vulkan.h>

extern VkImage depthImage;
extern VkDeviceMemory depthImageMemory;
extern VkImageView depthImageView;

VkFormat findDepthFormat();
bool hasStencil(VkFormat format);
void createDepthImage();
void destroyDepthImage();

#endif
