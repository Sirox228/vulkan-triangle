#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include <vulkan/vulkan.h>
#include <vector>

extern VkSwapchainKHR swapchain;
extern VkFormat swapchainImageFormat;
extern VkExtent2D swapchainExtent;
extern std::vector<VkImage> swapchainImages;
extern std::vector<VkImageView> swapchainImageViews;
extern std::vector<VkFramebuffer> swapchainFramebuffers;

void createSwapchain();
void createSwapchainImageViews();
void createSwapchainFramebuffers();
void destroySwapchain();
void destroySwapchainImageViews();
void destroySwapchainFramebuffers();

#endif
