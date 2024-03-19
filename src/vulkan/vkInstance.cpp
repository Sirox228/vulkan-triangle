#include "vkFunctions.h"
#include "../window.h"
#include "../log.h"
#include <SDL2/SDL_vulkan.h>
#include <vector>
#include <cstring>

VkInstance instance;

std::vector<const char*> layers = {
    "VK_LAYER_KHRONOS_validation"
};

bool checkValidationLayersSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* const& layer : layers) {
		bool found{false};

		for (const VkLayerProperties& available : availableLayers) {
			if (!strcmp(layer, available.layerName)) {
				found = true;
				break;
			}
		}
		if (!found) return false;
	}

	return true;
}

void createVulkanInstance() {
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "vulkan rtx";
	appInfo.applicationVersion =  VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pNext = nullptr;

	uint32_t extCount;
	SDL_Vulkan_GetInstanceExtensions(window, &extCount, nullptr);
	std::vector<const char*> extensions(extCount);
	SDL_Vulkan_GetInstanceExtensions(window, &extCount, extensions.data());

	VkInstanceCreateInfo instanceInfo = {};
	
	#ifdef VALID_LAYERS
	if (!checkValidationLayersSupport())
		log_fatal(std::runtime_error("validation layers were requested, but are not supported"));

	instanceInfo.enabledLayerCount = layers.size();
	instanceInfo.ppEnabledLayerNames = layers.data();
	#else
	instanceInfo.enabledLayerCount = 0;
	#endif

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = extCount;
	instanceInfo.ppEnabledExtensionNames = extensions.data();

	if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to create vulkan instance"));
}

void destroyVulkanInstance() {
	vkDestroyInstance(instance, nullptr);
}
