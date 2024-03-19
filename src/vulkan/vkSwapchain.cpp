#include "vkFunctions.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdint>
#include "vkPhysicalDevice.h"
#include "vkLogicalDevice.h"
#include "vkSurface.h"
#include "vkImageView.h"
#include "../window.h"
#include <SDL2/SDL_vulkan.h>
#include "../log.h"
#include "vkDepthImage.h"
#include <array>
#include "vkRenderPass.h"

VkSwapchainKHR swapchain;
VkFormat swapchainImageFormat;
VkExtent2D swapchainExtent;
std::vector<VkImage> swapchainImages;
std::vector<VkImageView> swapchainImageViews;
std::vector<VkFramebuffer> swapchainFramebuffers;

VkSurfaceFormatKHR chooseSwapchainSurfaceFormat() {
	for (const auto& availableFormat : surfaceFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return surfaceFormats[0];
}

VkPresentModeKHR chooseSwapchainSurfacePresentMode() {
	for (const auto& availablePresentMode : surfacePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

void createSwapchain() {
	VkSurfaceFormatKHR format = chooseSwapchainSurfaceFormat();
	VkPresentModeKHR presentMode = chooseSwapchainSurfacePresentMode();

	if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		swapchainExtent = surfaceCapabilities.currentExtent;
	} else {
		int32_t w, h;
		SDL_Vulkan_GetDrawableSize(window, &w, &h);

		swapchainExtent = {
			std::clamp(static_cast<uint32_t>(w), surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width),
			std::clamp(static_cast<uint32_t>(h), surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height)
		};
	}

	uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
	if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount)
		imageCount = surfaceCapabilities.maxImageCount;

	VkSwapchainCreateInfoKHR swapchainInfo = {};
	swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainInfo.pNext = nullptr;
	swapchainInfo.flags = 0;
	swapchainInfo.surface = surface;
	swapchainInfo.minImageCount = imageCount;
	swapchainInfo.imageFormat = format.format;
	swapchainInfo.imageColorSpace = format.colorSpace;
	swapchainInfo.imageExtent = swapchainExtent;
	swapchainInfo.imageArrayLayers = 1;
	swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainInfo.preTransform = surfaceCapabilities.currentTransform;
	swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainInfo.presentMode = presentMode;
	swapchainInfo.clipped = VK_TRUE;
	swapchainInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(device, &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to create swapchain"));

	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

	swapchainImageFormat = format.format;
}

void createSwapchainImageViews() {
	swapchainImageViews.resize(swapchainImages.size());

	for (size_t i{0}; i < swapchainImages.size(); i++)
		createImageView(swapchainImages[i], swapchainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, swapchainImageViews[i]);
}

void createSwapchainFramebuffers() {
	swapchainFramebuffers.resize(swapchainImageViews.size());

	for (size_t i{0}; i < swapchainFramebuffers.size(); i++) {
		std::array<VkImageView, 2> attachments = {
			swapchainImageViews[i],
			depthImageView
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = attachments.size();
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = swapchainExtent.width;
		framebufferInfo.height = swapchainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapchainFramebuffers[i]) != VK_SUCCESS)
			log_fatal(std::runtime_error("failed to create framebuffer"));
	}
}

void destroySwapchain() {
	vkDestroySwapchainKHR(device, swapchain, nullptr);
}

void destroySwapchainImageViews() {
	for (const auto& imageView : swapchainImageViews)
		vkDestroyImageView(device, imageView, nullptr);
}

void destroySwapchainFramebuffers() {
	for (const auto& framebuffer : swapchainFramebuffers)
		vkDestroyFramebuffer(device, framebuffer, nullptr);
}
