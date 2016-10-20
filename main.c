//
//  main.c
//  a
//
//  Created by Tyler on 2016/10/09.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//

#include <stdio.h>
#include "goto_link_store.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    init_store();
    put_link_loc("lollollol", 100);
    put_link_req("lollollol", 23, 1);
    //put_link_req("test", 23, 1);
    print_link("lollollol");
    return 0;
}
