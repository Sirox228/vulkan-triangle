#include "vkFunctions.h"
#include "vkPhysicalDevice.h"
#include "vkLogicalDevice.h"

VkQueue mainQueue;

void getMainQueue() {
	vkGetDeviceQueue(device, mainQueueFamily, 0, &mainQueue);
}
