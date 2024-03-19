#ifndef VK_SYNC_OBJECTS_H
#define VK_SYNC_OBJECTS_H

#include <vulkan/vulkan.h>
#include <vector>

extern std::vector<VkSemaphore> imageAvailableSemaphores;
extern std::vector<VkSemaphore> renderFinishedSemaphores;
extern std::vector<VkFence> inFlightFences;

void createSyncObjects();
void destroySyncObjects();

#endif
