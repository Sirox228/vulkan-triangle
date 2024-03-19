#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <vulkan/vulkan.h>
#include <vector>

extern std::vector<const char*> layers;

extern VkInstance instance;

void createVulkanInstance();
void destroyVulkanInstance();

#endif
