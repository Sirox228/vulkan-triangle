#include "vkFunctions.h"
#include "vkLogicalDevice.h"
#include "vkQueue.h"
#include "vkCommandPools.h"
#include "../log.h"
#include "../config.h"
#include <vector>

std::vector<VkCommandBuffer> commandBuffers;

void createCommandBuffers() {
	commandBuffers.resize(MAX_FRAMES_FLIGHT);

	VkCommandBufferAllocateInfo cmdBufAllocInfo = {};
	cmdBufAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdBufAllocInfo.commandPool = mainCommandPool;
	cmdBufAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmdBufAllocInfo.commandBufferCount = MAX_FRAMES_FLIGHT;

	if (vkAllocateCommandBuffers(device, &cmdBufAllocInfo, commandBuffers.data()) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to create command buffers"));
}

VkCommandBuffer getSingleTimeCmdBuffer() {
	VkCommandBufferAllocateInfo cmdBufInfo = {};
	cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdBufInfo.commandPool = shortCommandPool;
	cmdBufInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmdBufInfo.commandBufferCount = 1;

	VkCommandBuffer cmdBuffer;
	vkAllocateCommandBuffers(device, &cmdBufInfo, &cmdBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	if (vkBeginCommandBuffer(cmdBuffer, &beginInfo) != VK_SUCCESS)
		log_error(std::runtime_error("failed to begin recording command buffer"));

	return cmdBuffer;
}

void submitSingleTimeCmdBuffer(VkCommandBuffer& cmdBuffer) {
	vkEndCommandBuffer(cmdBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffer;

	vkQueueSubmit(mainQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(mainQueue);

	vkFreeCommandBuffers(device, shortCommandPool, 1, &cmdBuffer);
}
