#include <vector>
#include <cstring>
#include "../log.h"
#include "vkInstance.h"
#include "vkSurface.h"
#include "vkFunctions.h"

std::vector<const char*> requiredDeviceExtensions = {
	"VK_KHR_swapchain"
};

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
VkSurfaceCapabilitiesKHR surfaceCapabilities;
std::vector<VkSurfaceFormatKHR> surfaceFormats;
std::vector<VkPresentModeKHR> surfacePresentModes;
int32_t mainQueueFamily = -1;
VkPhysicalDeviceProperties2 deviceProps;
VkPhysicalDeviceFeatures deviceFeatures;
VkPhysicalDeviceRayTracingPipelinePropertiesKHR rayTracingProps = {};

VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
			return format;
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			return format;
	}

	log_fatal(std::runtime_error("failed to find supported format"));
	return candidates[0];
}

void findPhysicalDevice() {
	uint32_t deviceCount;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	std::vector<VkPhysicalDevice> availableDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, availableDevices.data());

	for (const VkPhysicalDevice& availableDevice : availableDevices) {
		uint32_t extCount;
		vkEnumerateDeviceExtensionProperties(availableDevice, nullptr, &extCount, nullptr);
		std::vector<VkExtensionProperties> extProps(extCount);
		vkEnumerateDeviceExtensionProperties(availableDevice, nullptr, &extCount, extProps.data());

		bool supportsExts{true};
		for (const char* const& ext : requiredDeviceExtensions) {
			bool found{false};

			for (const VkExtensionProperties& extProp : extProps) {
				if (!strcmp(ext, extProp.extensionName)) {
					found = true;
					break;
				}
			}

			if (!found) {
				supportsExts = false;
				break;
			}
		}

		uint32_t queueFamiliesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(availableDevice, &queueFamiliesCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamiliesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(availableDevice, &queueFamiliesCount, queueFamilyProps.data());

		for (uint32_t i{0}; i < queueFamilyProps.size(); i++) {
			if (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && queueFamilyProps[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
				VkBool32 presentSupported = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(availableDevice, i, surface, &presentSupported);
				
				if (presentSupported) {
					mainQueueFamily = i;
					break;
				}
			}
		}

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(availableDevice, surface, &surfaceCapabilities);

		uint32_t formatsCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(availableDevice, surface, &formatsCount, nullptr);
		surfaceFormats.resize(formatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(availableDevice, surface, &formatsCount, surfaceFormats.data());

		uint32_t presentModesCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(availableDevice, surface, &presentModesCount, nullptr);
		surfacePresentModes.resize(presentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(availableDevice, surface, &presentModesCount, surfacePresentModes.data());

		rayTracingProps.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
		deviceProps.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		deviceProps.pNext = &rayTracingProps;

		vkGetPhysicalDeviceProperties2(availableDevice, &deviceProps);
		vkGetPhysicalDeviceFeatures(availableDevice, &deviceFeatures);

		if (supportsExts && mainQueueFamily != -1 && !surfaceFormats.empty() && !surfacePresentModes.empty()
		&& deviceFeatures.fillModeNonSolid) {
			physicalDevice = availableDevice;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
		log_fatal(std::runtime_error("failed to find suitable gpu"));
}
