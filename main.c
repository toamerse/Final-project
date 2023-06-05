#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "head.h"
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// Window dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DEBUG 0
#define Radom_MAX 8
#define Radom_MIN 1
// create surface, create texture with surface -> create renderer -> render to window

// create surface, create texture with surface -> create renderer -> render to window
// this program is the program to deal with Battle_System()
// go on certain x,y -> battle system
//battle system functions : 1) button to press 2) functions to use skill 3) show out player's pokemon ,enemies pokemon and anmations while using skill.
//                             4) short music when using skill 5) change BGM(specific) 6) count the exp,hp...ect. 

typedef struct{
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect DestRect;
}SDL_need;

void initialize_battle(SDL_Renderer* renderer, SDL_need battle_needs,SDL_need enemy_needs, SDL_need player_needs){   
    SDL_RenderCopy(renderer, battle_needs.Texture, NULL, NULL); //要在(645,192) 放上敵人,(274,414)放上自己出戰的
    SDL_RenderCopy(renderer, enemy_needs.Texture, NULL, &enemy_needs.DestRect); //敵人
    SDL_RenderCopy(renderer, player_needs.Texture, NULL, &player_needs.DestRect); //player
}
//-------------------------------------------------------------------------------------------------//
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

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int duration) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_Delay(duration);
}
//-------------------------------------------------------------------------------------------------//


int rand_enemy(){
    int x = rand() % (Radom_MAX - Radom_MIN + 1) + Radom_MIN;
    return x;
}

SDL_Rect set_DestRect(SDL_Rect xy, int x, int y, int w, int h){ //設定座標的大小
    xy.x = x;
    xy.y = y;
    xy.w = w;
    xy.h = h;
    return xy;
}





void check_ballnumber(int *ball_number, SDL_need ball_needs, SDL_Renderer* renderer, SDL_need battle_needs, SDL_need enemy_needs, SDL_need player_needs, int *catched) {
    if ((*ball_number) >= 1){
        int frequent_1 = 60, frequent_2 = 20;

        while (frequent_1--) {
            initialize_battle(renderer, battle_needs, enemy_needs, player_needs);
            SDL_RenderCopy(renderer, ball_needs.Texture, NULL, &ball_needs.DestRect);
            SDL_RenderPresent(renderer);
            ball_needs.DestRect.x += 6.18; // 定義好球移動軌跡
            ball_needs.DestRect.y -= 3.7;
            SDL_Delay(5); // ball hits after flying 
        }
        (*ball_number)--;

        int angle = 30; // 傾斜角度

        while (frequent_2--){
            initialize_battle(renderer, battle_needs, enemy_needs, player_needs);
            SDL_RenderCopyEx(renderer, ball_needs.Texture, NULL, &ball_needs.DestRect, angle, NULL, SDL_FLIP_NONE); // 將球傾斜指定角度
            SDL_RenderPresent(renderer);
            angle = -angle; // 改變傾斜角度方向
            SDL_Delay(60); // ball hits after flying 
        }

        if (rand_enemy() % 2 == 0) { // 這邊要接到data 1.有抓到 2. 沒抓到
            (*catched) = 1;
        }
    }
    else {
        printf("no ball\n");
    }
}

void paper_scissor_stone(char gamer, SDL_need battle_needs, SDL_need enemy_needs, SDL_need player_needs,SDL_Renderer* renderer){
    //char gamer; // 玩家出拳
    int computer; // 電腦出拳
    int result; // 比賽結果.

    // 初始化 SDL_ttf
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
    }

    TTF_Font* font = TTF_OpenFont("8bitOperatorPlus8-Regular.ttf", 28);
    if (font == NULL) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
    }
    
    switch (gamer){
        case 65: //A
        case 97: //a
            gamer=4;
            break;
        case 66: //B
        case 98: //b
            gamer=7;
            break;
        case 67: //C
        case 99: //c
            gamer=10;
            break;
        default:
            break;
    }
    
    srand((unsigned)time(NULL)); // 隨機數種子
    computer=rand()%3; // 產生隨機數並取餘，得到電腦出拳
    result=(int)gamer+computer; // gamer 為 char 型別，數學運算時要強制轉換型別
    printf("computer use");
    SDL_Color color = {255, 0, 0, 255};
    renderText(renderer, font, "Computer Use", color, 100, 100, 1000);
    // 刷新渲染器并等待退出事件
    SDL_RenderPresent(renderer);
    switch (computer){
        case 0:
            printf(" scissor\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Scissor!", color, 100, 150, 1000);
            SDL_RenderPresent(renderer);
            break; //4  1
        case 1:
            printf(" stone\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Stone!", color, 100, 150, 1000);
            SDL_RenderPresent(renderer);
            break; //7 2
        case 2:
            printf(" paper\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Paper!", color, 100, 150, 1000);
            SDL_RenderPresent(renderer);
            break;  //10 3
    }
    printf("your use");
    //SDL_Color color = {255, 255, 255, 255};
    renderText(renderer, font, "You Use!", color, 100, 200, 1000);
    SDL_RenderPresent(renderer);
    switch (gamer){
        case 4:
            printf(" scissor\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Scissor!", color, 100, 250, 1000);
            SDL_RenderPresent(renderer);
            break;
        case 7:
            printf(" stone\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Stone!", color, 100, 250, 1000);
            SDL_RenderPresent(renderer);
            break;
        case 10:
            printf(" paper\n");
            //SDL_Color color = {255, 255, 255, 255};
            renderText(renderer, font, "Paper!", color, 100, 250, 1000);
            SDL_RenderPresent(renderer);
            break;
    }
    if(result==6||result==7||result==11){
        //敵人扣血
        //deduction();
        printf("you win!\n");
        //SDL_Color color = {255, 255, 255, 255};
        renderText(renderer, font, "You win!", color, 100, 300, 1000);
        SDL_RenderPresent(renderer);
    }else if(result==5||result==9||result==10){
        //我方扣血
        //deduction();
        printf("computer win!\n");
        //SDL_Color color = {255, 255, 255, 255};
        renderText(renderer, font, "Computer Win!", color, 100, 300, 1000);
        SDL_RenderPresent(renderer);
    }else{
        printf("draw\n");
        renderText(renderer, font, "Draw!", color, 100, 300, 1000);
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(1000);
    SDL_RenderClear(renderer);
    initialize_battle(renderer, battle_needs,enemy_needs, player_needs);
    SDL_RenderPresent(renderer);
}

void checkBattle(SDL_Renderer* renderer, SDL_need battle_needs, SDL_need enemy_needs, SDL_need player_needs, SDL_need ball_needs, int *ball_number){
    int enemy_num=0,running=1,catched=0;
    SDL_Event event;
        //換場景先暫時當作battke system 的地方
        SDL_RenderClear(renderer);
        initialize_battle(renderer, battle_needs,enemy_needs, player_needs);
        SDL_RenderPresent(renderer);
        
        enemy_num = rand_enemy();
        #if DEBUG
            printf("enemy_num:%d\n",enemy_num);
            printf("enemyDestRect:%d %d\n", enemy_needs.DestRect.x, enemy_needs.DestRect.y);
        #endif
    
    while(running){

        while (SDL_PollEvent(&event)){

            if(event.type == SDL_QUIT){
                // Handle quit event
                running = 0;
                break;
            }
            if(catched == 1){
                // Handle quit event
                running = 0;
                break;
            }

            if(event.type == SDL_KEYDOWN){
                // Check which key was pressed 
                    switch(event.key.keysym.sym){
                    case SDLK_q:
                        paper_scissor_stone('A',battle_needs,  enemy_needs,  player_needs, renderer);
                        break;
                    case SDLK_w:
                        paper_scissor_stone('B',battle_needs,  enemy_needs,  player_needs, renderer);
                        break;
                    case SDLK_e:
                        paper_scissor_stone('C',battle_needs,  enemy_needs,  player_needs, renderer); //決定勝負
                        break;
                    case SDLK_b: //丟球動畫
                        check_ballnumber(ball_number, ball_needs, renderer, battle_needs, enemy_needs, player_needs, &catched);
                        initialize_battle(renderer, battle_needs,enemy_needs, player_needs);
                        SDL_RenderPresent(renderer);
                        break;   
                    default:
                        break; 
                    }
                
            }
        }
        SDL_Delay(50);
    }
}
/*void deduction(char result, int* playerHP, int* enemyHP) {
    if (result == 'W'){
        *enemyHP -= 1;  // Deduct 1 HP from the enemy
    }else if (result == 'L'){
        *playerHP -= 1;  // Deduct 1 HP from the player
    } 
}*/





int main(int argc, char *argv[]){
    srand(time(NULL));
    
    initialize_hash_table();
    pokemon_stats_init();

    hash_table_insert(&flower);
    hash_table_insert(&dragan);
    hash_table_insert(&turtle);
    hash_table_insert(&pikachu);
    hash_table_insert(&nine_tails);
    hash_table_insert(&fat);
    hash_table_insert(&strange);
    hash_table_insert(&stupid);
    hash_table_insert(&ibu); // data

    initialize_bag_data();

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create a SDL_Window and a SDL_Renderer
    SDL_Window *window = SDL_CreateWindow("Image Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    } 
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Load the image using SDL_Image
    SDL_Surface *mapSurface = IMG_Load("./image/map.jpg");
    if (mapSurface == NULL){
        printf("Unable to load image! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }
    
    // Create a SDL_Texture from the loaded image
    SDL_Texture *mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    if(mapTexture == NULL){
        printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create a SDL_Texture from the loaded image
    SDL_need battle_needs = {battle_needs.Surface = IMG_Load("./image/battleBackground.png"), battle_needs.Texture = SDL_CreateTextureFromSurface(renderer, battle_needs.Surface)};
    SDL_need enemy_needs = {enemy_needs.Surface = IMG_Load("./image/ball.png"),enemy_needs.Texture = SDL_CreateTextureFromSurface(renderer, enemy_needs.Surface),enemy_needs.DestRect = set_DestRect(enemy_needs.DestRect, 645, 192, 85, 65)};
    SDL_need player_needs = {player_needs.Surface = IMG_Load("./image/ball.png"),player_needs.Texture = SDL_CreateTextureFromSurface(renderer, player_needs.Surface),player_needs.DestRect = set_DestRect(player_needs.DestRect, 274, 414, 85, 65)};
    SDL_need ball_needs = {ball_needs.Surface = IMG_Load("./image/ball.png"),ball_needs.Texture = SDL_CreateTextureFromSurface(renderer, ball_needs.Surface),ball_needs.DestRect = set_DestRect(ball_needs.DestRect, 274, 414, 85, 65)};


    // 初始化 SDL_ttf
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 1;
    }

    // 加载字体文件
    TTF_Font* font = TTF_OpenFont("8bitOperatorPlus8-Regular.ttf", 28);
    if (font == NULL) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        return 1;
    }
    // create texture for player.


    SDL_Surface *playerSurface = IMG_Load("./image/player.jpg");
    SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

    // Set up destination rectangle for player character
    SDL_Rect playerDestRect, enemyDestRect, ourDestRect; 
    
    playerDestRect = set_DestRect(playerDestRect, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 3, 45, 35);
    enemyDestRect = set_DestRect(enemyDestRect, 645, 192, 45, 35);
    ourDestRect = set_DestRect(ourDestRect, 274, 414, 45, 35); //設定座標


    // Clear the renderer and render the image texture as the background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerDestRect);
    SDL_RenderPresent(renderer);
    // Handle events

    SDL_Event event;
    int running = 1, battle=0;
    while(running){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerDestRect);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                // Handle quit event
                running = 0;
                break;
            }
            /*if(event.type == SDL_MOUSEBUTTONDOWN){
                printf("toughed\n");
            }*/
            if(event.type == SDL_KEYDOWN){
                #if DEBUG
                    printf("playerDestRect.x:%d\n", playerDestRect.x);
                    printf("playerDestRect.y:%d\n", playerDestRect.y);
                #endif
                
                // Check which key was pressed
                switch(event.key.keysym.sym){
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


                }
                int ball_number = 10; // 道具系統做好之後可以改，這是預設值
                int x = rand() % (Radom_MAX - Radom_MIN + 1) + Radom_MAX; //random to meet pokemon, need more handling 
                if((x%4) == 0) checkBattle(renderer, battle_needs, enemy_needs, player_needs, ball_needs, &ball_number);
    
            }
        }

        SDL_Delay(50);
    }
    

    // Clean up and exit
    SDL_DestroyTexture(mapTexture);
    SDL_FreeSurface(mapSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}