#include "vkFunctions.h"
#include "vkPhysicalDevice.h"
#include "vkLogicalDevice.h"
#include "vkImage.h"
#include "vkImageView.h"
#include "vkSwapchain.h"

VkImage depthImage;
VkDeviceMemory depthImageMemory;
VkImageView depthImageView;

VkFormat findDepthFormat() {
	return findSupportedFormat({VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

bool hasStencil(VkFormat format) {
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void createDepthImage() {
	VkFormat depthImageFormat = findDepthFormat();
	createImage(swapchainExtent.width, swapchainExtent.height, depthImageFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
	createImageView(depthImage, depthImageFormat, VK_IMAGE_ASPECT_DEPTH_BIT, depthImageView);
}

void destroyDepthImage() {
	vkDestroyImageView(device, depthImageView, nullptr);
	vkDestroyImage(device, depthImage, nullptr);
	vkFreeMemory(device, depthImageMemory, nullptr);
}
