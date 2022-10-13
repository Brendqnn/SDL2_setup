#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Utils.hpp"

#include "RenderWindow.hpp"
#include "Entity.hpp"


int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
    
    RenderWindow window("GAME v1.0", 1280, 720);

    SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");

    // Entity entities[3] = {
    //     Entity(0, 0, grassTexture),
    //     Entity(30, 0, grassTexture),
    //     Entity(30, 30, grassTexture)
    // };

    std::vector<Entity> entitiees = {
        Entity(Vector2f(0, 0), grassTexture),
        Entity(Vector2f(30, 0), grassTexture),
        Entity(Vector2f(30, 30), grassTexture),
        Entity(Vector2f(30, 60), grassTexture)

    };

    {
        Entity wilson(Vector2f(100, 50), grassTexture);
        entitiees.push_back(wilson);
    }

    bool gameRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }

                accumulator -= timeStep;
            }

            const float alpha = accumulator / timeStep;
        
            window.clear();

            for (Entity& e : entitiees)
            {
                window.render(e);
            }

            window.display();

            int frameTicks = SDL_GetTicks() - startTicks;
            if (frameTicks < 1000 / window.getRefreshRate())
            {
                SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
            }

        }
    }

    window.cleanUp();

    SDL_Quit();

    return 0;
    
}