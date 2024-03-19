#include <SDL2/SDL.h>
#include <memory>
#include "config.h"
#include "vulkan/vkChain.h"
#include "timer.h"
#include <random>
#include <vector>
#include "vulkan/vkLogicalDevice.h"
#include "vulkan/vkFunctions.h"
#include "vulkan/vkVertex.h"
#include "vulkan/vkRenderPresent.h"

SDL_Window* window;
bool active = true;
/*std::shared_ptr<image> renderImage;
uint32_t* imageData;*/
float elapsedTime = 0.0f;
bool shouldRender = true;

std::vector<vertex> vertices = {
	{{0.0f, -0.5f, 0.0f}},
	{{0.5f, 0.5f, 0.0f}},
	{{-0.5f, 0.5f, 0.0f}},
};

std::vector<uint32_t> vertexIndices = {
	0, 1, 2
};

std::mt19937 randomEngine;
std::uniform_int_distribution<std::mt19937::result_type> distribution;


int main() {
	randomEngine.seed(std::random_device()());
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	window = SDL_CreateWindow("vulkan rtx", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI);

	vkChainInit();

	SDL_Event event;
	while (active) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				active = false;
				break;
			}
		}

		render();
		frame = (frame + 1) % MAX_FRAMES_FLIGHT;
	}

	vkDeviceWaitIdle(device);

	vkChainDestroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}
