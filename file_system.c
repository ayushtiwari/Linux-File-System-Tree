//
//  file_system.c
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 26/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "file_system.h"

/// Get a new regular file type node
NODE* newRegNode(char name[]) {
    NODE *reg_node = (NODE*)malloc(sizeof(NODE));
    strcpy(reg_node->name, name);
    reg_node->type = REG;
    reg_node->childPtr = reg_node->siblingPtr = reg_node->parentPtr = NULL;
    
    return reg_node;
}

/// Get a new directory type node
NODE* newDirNode(char name[]) {
    NODE *dir_node = (NODE*)malloc(sizeof(NODE));
    strcpy(dir_node->name, name);
    dir_node->type = DIR;
    dir_node->childPtr = dir_node->siblingPtr = dir_node->parentPtr = NULL;
    
    return dir_node;
}
