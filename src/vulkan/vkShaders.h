#ifndef VK_SHADERS_H
#define VK_SHADERS_H

#include <vector>
#include <vulkan/vulkan.h>

std::vector<char> readShader(const std::string& filename);
void createShaderModule(std::vector<char> code, VkShaderModule& shaderModule);

#endif
