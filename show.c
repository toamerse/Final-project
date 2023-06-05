#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void playMusic(const char* filename, int duration, int volume) {
    // 初始化 SDL2 和 SDL_mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
        return;
    }

    // 加载音乐文件
    Mix_Music *music = Mix_LoadMUS(filename);
    if (music == NULL) {
        printf("Mix_LoadMUS failed: %s\n", Mix_GetError());
        return;
    }

    // 设置音乐音量
    Mix_VolumeMusic(volume);

    // 播放音乐文件
    if (Mix_PlayMusic(music, 1) < 0) {
        printf("Mix_PlayMusic failed: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        return;
    }

    // 等待指定时长
    SDL_Delay(duration * 1000);

    // 停止音乐播放
    Mix_HaltMusic();

    // 释放音乐文件
    Mix_FreeMusic(music);

    // 关闭 SDL2 和 SDL_mixer
    Mix_CloseAudio();
    //SDL_Quit();
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


// create surface, create texture with surface -> create renderer -> render to window
int main(int argc, char *argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    //input the music file
    /*Mix_Music *music = Mix_LoadMUS("13.wav");
    if (music == NULL) {
        printf("Mix_LoadMUS failed: %s\n", Mix_GetError());
        //return 1;
    }*/

    //playMusic("08 Victory! (Wild Pokémon).wav", 5, 50);

    //play music
    /*    if (Mix_PlayMusic(music, 0) < 0) {
        printf("Mix_PlayMusic failed: %s\n", Mix_GetError());
        } */



    // Create a SDL_Window and a SDL_Renderer
    SDL_Window *window = SDL_CreateWindow("Image Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load the image using SDL_Image
    SDL_Surface *mapSurface = IMG_Load("./image/map.jpg");
    if (mapSurface == NULL) {
        printf("Unable to load image! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }

    // Create a SDL_Texture from the loaded image
    SDL_Texture *mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    if (mapTexture == NULL) {
        printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create texture for player.
    SDL_Surface *playerSurface = IMG_Load("./image/player.jpg");
    SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

    // Set up destination rectangle for player character
    SDL_Rect playerDestRect;
    playerDestRect.x = SCREEN_WIDTH / 2 - 20;
    playerDestRect.y = SCREEN_HEIGHT / 2 + 3;
    playerDestRect.w = 45; // Example width and height for player character
    playerDestRect.h = 35;

    // Clear the renderer and render the image texture as the background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerDestRect);
    SDL_RenderPresent(renderer);


        // 初始化 SDL_ttf
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("8bitOperatorPlus8-Regular.ttf", 28);
    if (font == NULL) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        return 1;
    }


    // Handle events
    SDL_Event event;
    int running = 1;
    while(running){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerDestRect);
        SDL_RenderPresent(renderer);

        // 渲染文本
    SDL_Color color = {255, 255, 255, 255};
    renderText(renderer, font, "Hello MotherFucker!", color, 100, 100);

  // 刷新渲染器并等待退出事件
    SDL_RenderPresent(renderer);
    /*bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }*/
    
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // Handle quit event
                running = 0;
                break;
            }else if (event.type == SDL_KEYDOWN){
                // Check which key was pressed
                switch (event.key.keysym.sym){
                    case SDLK_UP:
                        if(playerDestRect.y < 37){
                            
                        }else
                            playerDestRect.y -= 37;
                        break;
                    case SDLK_DOWN:
                        if (playerDestRect.y > SCREEN_HEIGHT - playerDestRect.h-37){
                            
                        }else
                            playerDestRect.y += 37;
                        break;
                    case SDLK_LEFT:
                        if (playerDestRect.x < 53){
                            
                        }else
                            playerDestRect.x -= 53;
                        break;
                    case SDLK_RIGHT:
                        if (playerDestRect.x > SCREEN_WIDTH - playerDestRect.w-53){
                        }else
                            playerDestRect.x += 53;
                        break;
                    // Add more cases for other keys as needed
                }
            }
        }

    SDL_Delay(50);
    }


    // Clean music
    //Mix_FreeMusic(music);
    //Mix_CloseAudio();

    //SDL_DestroyTexture(texture);
    //TTF_CloseFont(font);
    //TTF_Quit();

    // Clean up and exit
    SDL_DestroyTexture(mapTexture);
    SDL_FreeSurface(mapSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
