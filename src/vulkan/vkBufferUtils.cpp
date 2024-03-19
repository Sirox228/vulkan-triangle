#include "../log.h"
#include "vkLogicalDevice.h"
#include "vkPhysicalDevice.h"
#include "vkCmdBuffer.h"
#include "vkFunctions.h"
#include "vkMemoryUtils.h"

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.flags = 0;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	
	if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
	    log_fatal(std::runtime_error("failed to create buffer"));
	
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
	
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, properties);
	
	if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	    log_fatal(std::runtime_error("failed to allocate buffer"));
	
	vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size) {
	VkCommandBuffer cmdbuffer = getSingleTimeCmdBuffer();

	VkBufferCopy copyArea = {};
	copyArea.srcOffset = 0;
	copyArea.dstOffset = 0;
	copyArea.size = size;

	vkCmdCopyBuffer(cmdbuffer, src, dst, 1, &copyArea);

	submitSingleTimeCmdBuffer(cmdbuffer);
}
