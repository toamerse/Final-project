#ifndef POKEMON_STATS_H
#define POKEMON_STATS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_NAME 256
#define TABLE_SIZE 10  //to define how much table

//pokemon's data
struct pokemon{
    char name[100];
    char attributes1[100];
    char attributes2[100];
    int blood;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
    struct pokemon *next;
};

typedef struct pokemon Pokemon;

Pokemon flower;
Pokemon dragan;
Pokemon turtle;
Pokemon pikachu;
Pokemon nine_tails;
Pokemon fat;
Pokemon strange;
Pokemon stupid;
Pokemon ibu;

void pokemon_stats_init();

unsigned int hash(char *name);

//make sure every table is empty
void initialize_hash_table();

bool hash_table_insert(Pokemon *p);

//find a person in the table by their name
Pokemon *hash_table_lookup(char *name);

Pokemon *hash_table_delete(char *name);

#endif // STATS


//player data
#define BAG_SIZE 10

struct player{
    char name[100];
    int blood;
    int coin;
    int potion;
    struct player *next;
};

typedef struct player Player;


unsigned int bag(char *name);

//make sure every location is empty
void initialize_bag_data();

bool bag_data_insert(Player *p);

//find a person in the location by their name
Player *bag_data_lookup(char *name);

Player *bag_data_delete(char *name);
