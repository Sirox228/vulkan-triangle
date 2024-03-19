#ifndef VK_VERTEX_BUFFER_H
#define VK_VERTEX_BUFFER_H

#include <vulkan/vulkan.h>

extern VkBuffer vertexBuffer;
extern VkDeviceMemory vertexBufferMemory;

void makeVertexBuffer();
void destroyVertexBuffer();

#endif
