#ifndef VK_INDEX_BUFFER_H
#define VK_INDEX_BUFFER_H

#include <vulkan/vulkan.h>

extern VkBuffer indexBuffer;
extern VkDeviceMemory indexBufferMemory;

void makeIndexBuffer();
void destroyIndexBuffer();

#endif
