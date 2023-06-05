#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"head.h"

Pokemon *hash_table[TABLE_SIZE];  //to deal with that two data store in the same table

unsigned int hash(char *name){
    int length=strnlen(name,MAX_NAME);
    int hash_value=0;
    for(int i=0;i<length;i++){
        hash_value+=name[i];   //to sum up every characters' ASCII
        hash_value=(hash_value+=name[i] % TABLE_SIZE);  //to calculate which table should put in
    }
    return hash_value;    //which location is store
}

//make sure every table is empty
void initialize_hash_table(){
    for(int i=0;i<TABLE_SIZE;i++){
        hash_table[i]=NULL;
    }
}

bool hash_table_insert(Pokemon *p){
    if(p==NULL){      //the table is empty
        return false;
    }
    int index=hash(p->name);
    p->next=hash_table[index];
    hash_table[index]=p;
    //printf("*******%d %s\n",index,p->attributes1);
    //printf("******%s\n",hash_table[index]);
    return true;
}

//find a person in the table by their name
Pokemon *hash_table_lookup(char *name){
    int index=hash(name);
    Pokemon *temp=hash_table[index];
    //temp->next=hash_table[index];
    //hash_table[index]=temp;
    //printf("&&&&&&&%d %s\n",index,temp->attributes1);
    //printf("***%s\n",temp->name);
    while(temp!=NULL && strcmp(temp->name,name)!=0){
        temp=temp->next;
    }
    return temp;
}

Pokemon *hash_table_delete(char *name){
    int index=hash(name);
    Pokemon *temp=hash_table[index];
    Pokemon *prev=NULL;
    while(temp!=NULL && strcmp(temp->name,name)!=0){
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        return NULL;
    }
    if(prev==NULL){
        //deleting the head
        hash_table[index]=temp->next;
    }
    else{
        prev->next=temp->next;
    }
    return temp;
}

void pokemon_stats_init(){

    strcpy(flower.name, "flower");
    strcpy(flower.attributes1, "grass");
    strcpy(flower.attributes2, "poison");
    flower.blood = 3;
    flower.attack = 3;
    flower.defense = 3;
    flower.special_attack = 4;
    flower.special_defense = 4;
    flower.speed = 3;

    strcpy(dragan.name, "dragan");
    strcpy(dragan.attributes1, "fire");
    strcpy(dragan.attributes2, "---");
    dragan.blood = 3;
    dragan.attack = 4;
    dragan.defense = 3;
    dragan.special_attack = 4;
    dragan.special_defense = 3;
    dragan.speed = 4;

    strcpy(turtle.name, "turtle");
    strcpy(turtle.attributes1, "water");
    strcpy(turtle.attributes2, "---");
    turtle.blood = 3;
    turtle.attack = 3;
    turtle.defense = 4;
    turtle.special_attack = 3;
    turtle.special_defense = 4;
    turtle.speed = 3;

    strcpy(pikachu.name, "pikachu");
    strcpy(pikachu.attributes1, "electric");
    strcpy(pikachu.attributes2, "---");
    pikachu.blood = 3;
    pikachu.attack = 4;
    pikachu.defense = 3;
    pikachu.special_attack = 3;
    pikachu.special_defense = 3;
    pikachu.speed = 6;

    strcpy(nine_tails.name, "nine_tails");
    strcpy(nine_tails.attributes1, "fire");
    strcpy(nine_tails.attributes2, "---");
    nine_tails.blood = 5;
    nine_tails.attack = 5;
    nine_tails.defense = 5;
    nine_tails.special_attack = 5;
    nine_tails.special_defense = 6;
    nine_tails.speed = 6;

    strcpy(fat.name, "fat");
    strcpy(fat.attributes1, "normal");
    strcpy(fat.attributes2, "fairy");
    fat.blood = 5;
    fat.attack = 4;
    fat.defense = 2;
    fat.special_attack = 4;
    fat.special_defense = 2;
    fat.speed = 3;

    strcpy(strange.name, "strange");
    strcpy(strange.attributes1, "fighting");
    strcpy(strange.attributes2, "---");
    strange.blood = 6;
    strange.attack = 8;
    strange.defense = 5;
    strange.special_attack = 4;
    strange.special_defense = 5;
    strange.speed = 4;

    strcpy(ibu.name, "ibu");
    strcpy(ibu.attributes1, "normal");
    strcpy(ibu.attributes2, "---");
    ibu.blood = 4;
    ibu.attack = 4;
    ibu.defense = 3;
    ibu.special_attack = 3;
    ibu.special_defense = 4;
    ibu.speed = 4;

    strcpy(stupid.name, "stupid");
    strcpy(stupid.attributes1, "water");
    strcpy(stupid.attributes2, "psychic");
    stupid.blood = 4;
    stupid.attack = 4;
    stupid.defense = 5;
    stupid.special_attack = 5;
    stupid.special_defense = 3;
    stupid.speed = 2;
}



/*-------------------------------------------*/
//player data



Player *bag_data[BAG_SIZE];

unsigned int bag(char *name){
    int length=strlen(name);
    int bag_value=0;
    for(int i=0;i<length;i++){
        bag_value=name[i];   //to sum up every characters' ASCII
    }
    return bag_value;    //which location is store
}

//make sure every table is empty
void initialize_bag_data(){
    for(int i=0;i<BAG_SIZE;i++){
        bag_data[i]=NULL;
    }
}

bool bag_data_insert(Player *p){
    if(p==NULL){      //the table is empty
        return false;
    }
    int index=bag(p->name);
    p->next=bag_data[index];
    bag_data[index]=p;
    //printf("*******%d %s\n",index,p->attributes1);
    //printf("******%s\n",hash_table[index]);
    return true;
}

//find a person in the table by their name
Player *bag_data_lookup(char *name){
    int index=bag(name);
    Player *temp=bag_data[index];
    //temp->next=hash_table[index];
    //hash_table[index]=temp;
    //printf("&&&&&&&%d %s\n",index,temp->attributes1);
    //printf("***%s\n",temp->name);
    while(temp!=NULL && strcmp(temp->name,name)!=0){
        temp=temp->next;
    }
    return temp;
}

Player *bag_data_delete(char *name){
    int index=bag(name);
    Player *temp=bag_data[index];
    Player *prev=NULL;
    while(temp!=NULL && strcmp(temp->name,name)!=0){
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        return NULL;
    }
    if(prev==NULL){
        //deleting the head
        bag_data[index]=temp->next;
    }
    else{
        prev->next=temp->next;
    }
    return temp;
}

