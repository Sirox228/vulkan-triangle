#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include <vulkan/vulkan.h>
#include <vector>

extern std::vector<const char*> requiredDeviceExtensions;

extern VkPhysicalDevice physicalDevice;
extern VkSurfaceCapabilitiesKHR surfaceCapabilities;
extern std::vector<VkSurfaceFormatKHR> surfaceFormats;
extern std::vector<VkPresentModeKHR> surfacePresentModes;
extern int32_t mainQueueFamily;
extern VkPhysicalDeviceProperties2 deviceProps;
extern VkPhysicalDeviceFeatures deviceFeatures;
extern VkPhysicalDeviceRayTracingPipelinePropertiesKHR rayTracingProps;

VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
void findPhysicalDevice();

#endif
