#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include <vulkan/vulkan.h>

void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

#endif
