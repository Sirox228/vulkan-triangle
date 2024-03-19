#ifndef VK_CMD_BUFFER_H
#define VK_CMD_BUFFER_H

#include <vulkan/vulkan.h>
#include <vector>

extern std::vector<VkCommandBuffer> commandBuffers;

void createCommandBuffers();
VkCommandBuffer getSingleTimeCmdBuffer();
void submitSingleTimeCmdBuffer(VkCommandBuffer& cmdBuffer);

#endif
