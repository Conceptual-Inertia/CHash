//
//  goto_link store.c
//  a
//
//  Created by Tyler on 2016/10/18.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "goto_link_store.h"

int num_sets = 256;
int used_sets;
link_set *link_sets;

link_set *hash[256];//point to the first pointer of the set;

int get_h(char *name){
    if (strlen(name) == 1) return name[0];
    if (strlen(name) == 2) return ((name[0] & 15) << 4) + (name[1] & 15);
    if (strlen(name) == 3) return ((name[0] & 7) << 5) + ((name[1] & 7) << 2) +(name[2] & 3);
    return ((name[0] & 3) << 6) + ((name[1] & 3) << 4) +((name[2] & 3) << 2) + (name[3] & 3);
}

void init_store(){
    link_sets = (link_set *) malloc(num_sets * sizeof(link_set));
    if (!link_sets){
        printf("Failed to allocate");
        exit(1);
    }
    
}

link_set *get_link_set(char *name){
    if (!hash[get_h(name)]) {
        hash[get_h(name)] = new_link_set(name);
        return hash[get_h(name)];
    }
    link_set *temp = hash[get_h(name)];
    while(strcmp((temp->name), name)){
        if (!temp->next){
            temp->next = new_link_set(name);
        }
        temp = temp->next;
    }
    return temp;
    //printf("Error: Failed to set up link");
    //return NULL;
}

link_set *new_link_set(char *name){
    if (used_sets == num_sets){
        num_sets *= 2;
        link_sets = (link_set *) realloc(link_sets, num_sets * sizeof(link_set));
    }
    strcpy(link_sets[num_sets].name, name);
    num_sets ++;
    return &link_sets[num_sets - 1];
}

void free_link_sets(){
    free(link_sets);
}

void put_link_loc(char *name, uint32_t loc){
    if (get_link_set(name)->used){
        printf("repeating on link setup.");
        return;
    }
    get_link_set(name)->loc = loc;
    get_link_set(name)->used = 1;
}

void put_link_req(char *name, uint32_t instr_num, int par){
    link_set * temp = get_link_set(name);
    temp->length_req ++;
    if (temp->length_req == 1){
        temp->reqls = (req_location *)malloc(sizeof(req_location));
    }else{
        temp->reqls = (req_location *) realloc(temp->reqls, temp->length_req * sizeof(req_location));
    }
    if (!temp->reqls){
        printf("Failed to allocate");
        exit(1);
    }
    temp->reqls[temp->length_req -1].instr_num = instr_num;
    temp->reqls[temp->length_req -1].par = par;
}

void print_link(char *name){
    
    link_set *temp =get_link_set(name);
    puts(temp->name);
    printf("name: %s\n", temp->name);
    printf("location: %u\n", temp->loc);
    for (int i = 0; i < temp->length_req; i ++){
        printf("%d %d\n", temp->reqls[i].instr_num, temp->reqls[i].par);
    }
}
