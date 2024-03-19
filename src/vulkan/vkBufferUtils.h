#ifndef VK_BUFFER_UTILS_H
#define VK_BUFFER_UTILS_H

#include <vulkan/vulkan.h>

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
void copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);

#endif
