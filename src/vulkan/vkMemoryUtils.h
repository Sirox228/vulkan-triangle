#ifndef VK_MEMORY_UTILS_H
#define VK_MEMORY_UTILS_H

#include <vulkan/vulkan.h>

extern uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

#endif
