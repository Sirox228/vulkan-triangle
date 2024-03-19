#include "vkFunctions.h"
#include "vkPhysicalDevice.h"
#include "vkInstance.h"
#include "../log.h"

VkDevice device;

void makeLogicalDevice() {
	float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo queueInfo;
	queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueInfo.queueFamilyIndex = mainQueueFamily;
	queueInfo.queueCount = 1;
	queueInfo.pQueuePriorities = &queuePriority;
	queueInfo.pNext = nullptr;
	queueInfo.flags = 0;

	VkDeviceCreateInfo deviceInfo;
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pQueueCreateInfos = &queueInfo;
	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pEnabledFeatures = &deviceFeatures;
	deviceInfo.enabledExtensionCount = requiredDeviceExtensions.size();
	deviceInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();
	deviceInfo.pNext = nullptr;
	deviceInfo.flags = 0;
	
	#ifdef VALID_LAYERS
	deviceInfo.enabledLayerCount = layers.size();
	deviceInfo.ppEnabledLayerNames = layers.data();
	#else
	deviceInfo.enabledLayerCount = 0;
	#endif

	if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to create logical device"));
}

void destroyLogicalDevice() {
	vkDestroyDevice(device, nullptr);
}
