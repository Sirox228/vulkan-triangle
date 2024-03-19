#include "vkInstance.h"
#include "vkSurface.h"
#include "vkPhysicalDevice.h"
#include "vkLogicalDevice.h"
#include "vkQueue.h"
#include "vkVertexBuffer.h"
#include "vkIndexBuffer.h"
#include "vkFunctions.h"
#include "vkSwapchain.h"
#include "vkRenderPass.h"
#include "vkGraphicsPipeline.h"
#include "vkCommandPools.h"
#include "vkDepthImage.h"
#include "vkSyncObjects.h"
#include "vkCmdBuffer.h"

void vkChainInit() {
	#ifdef VK_NO_PROTOTYPES
	initPreInstanceFunctions();
	#endif
	createVulkanInstance();
	#ifdef VK_NO_PROTOTYPES
	initInstanceFunctions();
	#endif
	createVulkanSDLSurface();
	findPhysicalDevice();
	makeLogicalDevice();
	#ifdef VK_NO_PROTOTYPES
	initDeviceFunctions();
	#endif
	getMainQueue();
	createSwapchain();
	createSwapchainImageViews();
	createRenderPass();
	createGraphicsPipeline();
	createCommandPool(mainCommandPool, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	createCommandPool(shortCommandPool, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT);
	createDepthImage();
	makeVertexBuffer();
	makeIndexBuffer();
	createSwapchainFramebuffers();
	createCommandBuffers();
	createSyncObjects();
}

void vkChainDestroy() {
	destroySyncObjects();
	destroySwapchainFramebuffers();
	destroyIndexBuffer();
	destroyVertexBuffer();
	destroyDepthImage();
	destroyCommandPool(shortCommandPool);
	destroyCommandPool(mainCommandPool);
	destroyGraphicsPipeline();
	destroyRenderPass();
	destroySwapchainImageViews();
	destroySwapchain();
	destroyLogicalDevice();
	destroyVulkanSDLSurface();
	destroyVulkanInstance();
}
