#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>;

using namespace std;

using uint = unsigned int;

void firstTest()
{

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My first test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		SDL_Texture* texture;
		std::string filename = "../images/background1.png";

		SDL_Surface* surface = IMG_Load(filename.c_str());

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		SDL_RenderCopy(renderer, texture, nullptr, nullptr);

		SDL_Rect destRect;
		destRect.w = destRect.h = 100;
		destRect.x = 0; destRect.y = 400;

		SDL_Texture* dogSprite;

		std::string dogFilename = "../images/dog.png";
		SDL_Surface* dogSurface = IMG_Load(dogFilename.c_str());
		
		
		dogSprite=	SDL_CreateTextureFromSurface(renderer, dogSurface);
		SDL_FreeSurface(dogSurface);
		
		int textFrameW = 768 / 6;
		int textFrameH = 82 / 1;
		SDL_Rect srcRect;
		srcRect.x = srcRect.y = 0;
		srcRect.w = textFrameW;
		srcRect.h = textFrameH;
		SDL_RenderCopy(renderer, texture, &srcRect, nullptr);

		bool exit = false;
		while (SDL_QUIT) {
			srcRect.x = textFrameW * int(((SDL_GetTicks() / 2) % 6));
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
			SDL_RenderCopy(renderer, dogSprite, &srcRect, &destRect);
			

			destRect.x += 100;
			if (destRect.x > winWidth) {
				destRect.x = 0;
			}
			SDL_RenderPresent(renderer);
			SDL_Delay(500);
		}
		
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
