//
//  goto_link store.h
//  a
//
//  Created by Tyler on 2016/10/18.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//

#ifndef goto_link_store_h
#define goto_link_store_h

#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "goto_link_store.h"

typedef struct{
    uint32_t instr_num;
    int par:2;
} req_location;

typedef struct link_set link_set;

struct link_set{
    char name[128];//start with $ are reserved by programs.
    int used;//if the location have put in
    uint32_t loc;//location in byte
    link_set *next;
    int length_req;
    req_location *reqls;
};

int get_h(char *name);

void init_store();

link_set *get_link_set(char *name);

link_set *new_link_set(char *name);

void free_link_sets();

void put_link_loc(char *name, uint32_t loc);

void put_link_req(char *name, uint32_t instr_num, int par);

void print_link(char *name);

#endif /* goto_link_store_h */
