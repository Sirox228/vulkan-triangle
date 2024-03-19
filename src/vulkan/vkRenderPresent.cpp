#include "vkFunctions.h"
#include "vkCmdBuffer.h"
#include "vkSyncObjects.h"
#include "vkLogicalDevice.h"
#include "vkSwapchain.h"
#include "vkQueue.h"
#include "vkRenderPass.h"
#include "vkGraphicsPipeline.h"
#include "vkVertexBuffer.h"
#include "vkIndexBuffer.h"
#include "../vertices.h"
#include "../log.h"
#include "../config.h"
#include <limits>
#include <array>

uint16_t frame = 0;


void recordCommands(VkCommandBuffer& cmdBuffer, uint32_t& index) {
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	if (vkBeginCommandBuffer(cmdBuffer, &beginInfo) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to begin recording draw command buffer"));

	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.renderPass = renderPass;
	renderPassBeginInfo.framebuffer = swapchainFramebuffers[index];
	renderPassBeginInfo.renderArea.offset = {0, 0};
	renderPassBeginInfo.renderArea.extent = swapchainExtent;

	std::array<VkClearValue, 2> clearValues = {
		VkClearValue{
			.color = {{0.0f, 0.0f, 0.0f, 1.0f}}
		},
		VkClearValue{
			.depthStencil = {1.0f, 0}
		},
	};

	renderPassBeginInfo.clearValueCount = clearValues.size();
	renderPassBeginInfo.pClearValues = clearValues.data();


	vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

	std::array<VkBuffer, 1> vertexBuffers = {vertexBuffer};
	std::array<VkDeviceSize, 1> vertexBufferOffsets = {0};
	vkCmdBindVertexBuffers(cmdBuffer, 0, vertexBuffers.size(), vertexBuffers.data(), vertexBufferOffsets.data());

	vkCmdBindIndexBuffer(cmdBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	vkCmdDrawIndexed(cmdBuffer, vertexIndices.size(), 1, 0, 0, 0);

	vkCmdEndRenderPass(cmdBuffer);

	if (vkEndCommandBuffer(cmdBuffer) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to finish recording draw command buffer"));
}


void render() {
	vkWaitForFences(device, 1, &inFlightFences[frame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t index;
	vkAcquireNextImageKHR(device, swapchain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphores[frame], nullptr, &index);

	vkResetFences(device, 1, &inFlightFences[frame]);

	vkResetCommandBuffer(commandBuffers[frame], 0);

	recordCommands(commandBuffers[frame], index);

	std::array<VkSemaphore, 1> wait = {imageAvailableSemaphores[frame]};
	std::array<VkSemaphore, 1> signal = {renderFinishedSemaphores[frame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = wait.size();
	submitInfo.pWaitSemaphores = wait.data();
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[frame];
	submitInfo.signalSemaphoreCount = signal.size();
	submitInfo.pSignalSemaphores = signal.data();

	if (vkQueueSubmit(mainQueue, 1, &submitInfo, inFlightFences[frame]) != VK_SUCCESS)
		log_fatal(std::runtime_error("failed to submit draw command buffer"));


	std::array<VkSwapchainKHR, 1> swapchains = {swapchain};

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = signal.size();
	presentInfo.pWaitSemaphores = signal.data();
	presentInfo.swapchainCount = swapchains.size();
	presentInfo.pSwapchains = swapchains.data();
	presentInfo.pImageIndices = &index;

	vkQueuePresentKHR(mainQueue, &presentInfo);
}
