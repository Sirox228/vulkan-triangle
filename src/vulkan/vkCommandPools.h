#ifndef VK_COMMAND_POOLS_H
#define VK_COMMAND_POOLS_H

#include <vulkan/vulkan.h>

extern VkCommandPool mainCommandPool;
extern VkCommandPool shortCommandPool;

void createCommandPool(VkCommandPool& pool, VkCommandPoolCreateFlagBits flags);
void destroyCommandPool(VkCommandPool& pool);

#endif
