#include <vulkan/vulkan.h>
#include <SDL2/SDL_vulkan.h>
#include "vkInstance.h"
#include "../window.h"
#include "../log.h"
#include "vkFunctions.h"

VkSurfaceKHR surface;

void createVulkanSDLSurface() {
	if (SDL_Vulkan_CreateSurface(window, instance, &surface) != SDL_TRUE)
		log_fatal(std::runtime_error("failed to create SDL vulkan surface"));
}

void destroyVulkanSDLSurface() {
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
