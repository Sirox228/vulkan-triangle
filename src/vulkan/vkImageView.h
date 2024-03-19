#ifndef VK_IMAGE_VIEW_H
#define VK_IMAGE_VIEW_H

#include <vulkan/vulkan.h>

void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect, VkImageView& view);

#endif
