#include "vkFunctions.h"
#include "vkLogicalDevice.h"
#include "vkPhysicalDevice.h"
#include "../log.h"

VkCommandPool mainCommandPool;
VkCommandPool shortCommandPool;

void createCommandPool(VkCommandPool& pool, VkCommandPoolCreateFlagBits flags) {
	VkCommandPoolCreateInfo commandPoolInfo = {};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.flags = flags;
	commandPoolInfo.queueFamilyIndex = mainQueueFamily;

	if (vkCreateCommandPool(device, &commandPoolInfo, nullptr, &pool) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to create command pool"));
}

void destroyCommandPool(VkCommandPool& pool) {
	vkDestroyCommandPool(device, pool, nullptr);
}
