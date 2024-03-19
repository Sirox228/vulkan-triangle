#include "../vertices.h"
#include "vkBufferUtils.h"
#include "vkLogicalDevice.h"
#include "vkFunctions.h"

VkBuffer indexBuffer;
VkDeviceMemory indexBufferMemory;

void makeIndexBuffer() {
	VkDeviceSize size = sizeof(vertexIndices[0]) * vertexIndices.size();
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	void* data;

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	vkMapMemory(device, stagingBufferMemory, 0, size, 0, &data);
	memcpy(data, vertexIndices.data(), size);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(stagingBuffer, indexBuffer, size);

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void destroyIndexBuffer() {
	vkDestroyBuffer(device, indexBuffer, nullptr);
	vkFreeMemory(device, indexBufferMemory, nullptr);
}
