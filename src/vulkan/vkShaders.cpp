#include "vkFunctions.h"
#include "vkLogicalDevice.h"
#include <vector>
#include "../log.h"
#include <fstream>

std::vector<char> readShader(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
		log_fatal(std::runtime_error("failed to open shader"));
	size_t size = file.tellg();
	std::vector<char> buffer(size);
	file.seekg(0);
	file.read(buffer.data(), size);
	file.close();
	return buffer;
}

void createShaderModule(std::vector<char> code, VkShaderModule& shaderModule) {
	VkShaderModuleCreateInfo shaderModuleInfo = {};
	shaderModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleInfo.codeSize = code.size();
	shaderModuleInfo.pCode = reinterpret_cast<uint32_t*>(code.data());

	if (vkCreateShaderModule(device, &shaderModuleInfo, nullptr, &shaderModule) != VK_SUCCESS)
		log_error(std::runtime_error("failed to create shader module"));
}
