cmake_minimum_required(VERSION 3.20)
project(vulkan_triangle LANGUAGES CXX C VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(VALID_LAYERS "enabled validation layers" OFF)

if(VALID_LAYERS)
add_compile_definitions(VALID_LAYERS)
endif()

add_compile_definitions(GLM_FORCE_RADIANS GLM_FORCE_DEFAULT_ALIGNED_GENTYPES GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_FORCE_INTRINSICS)
add_compile_definitions(VK_NO_PROTOTYPES)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_library(LIBVULKAN vulkan)

set(SOURCES
	src/vulkan/vkFunctions.cpp
	src/vulkan/vkChain.cpp
	src/vulkan/vkInstance.cpp
	src/vulkan/vkPhysicalDevice.cpp
	src/vulkan/vkSurface.cpp
	src/vulkan/vkLogicalDevice.cpp
	src/vulkan/vkQueue.cpp
	src/vulkan/vkSwapchain.cpp
	src/vulkan/vkCmdBuffer.cpp
	src/vulkan/vkBufferUtils.cpp
	src/vulkan/vkVertexBuffer.cpp
	src/vulkan/vkIndexBuffer.cpp
	src/vulkan/vkImageView.cpp
	src/vulkan/vkMemoryUtils.cpp
	src/vulkan/vkImage.cpp
	src/vulkan/vkDepthImage.cpp
	src/vulkan/vkRenderPass.cpp
	src/vulkan/vkShaders.cpp
	src/vulkan/vkGraphicsPipeline.cpp
	src/vulkan/vkCommandPools.cpp
	src/vulkan/vkSyncObjects.cpp
	src/vulkan/vkRenderPresent.cpp
	src/log.cpp
	src/main.cpp
	src/stb_image.c
	src/timer.cpp
)

add_executable(vulkan_triangle ${SOURCES})
target_link_libraries(vulkan_triangle ${SDL2_LIBRARIES} ${LIBVULKAN})
