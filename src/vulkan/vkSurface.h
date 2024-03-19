#ifndef VK_SURFACE_H
#define VK_SURFACE_H

#include <vulkan/vulkan.h>

extern VkSurfaceKHR surface;

void createVulkanSDLSurface();
void destroyVulkanSDLSurface();

#endif
