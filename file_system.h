//
//  file_system.h
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 26/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#ifndef file_system_h
#define file_system_h

typedef struct node {
    char name[64];                  // Name of file
    enum {DIR, REG} type;           // File type : Regular or Directory
    struct node *childPtr,          // Pointer to oldest child file
                *siblingPtr,        // Pointer to oldest sibling file
                *parentPtr;         // Pointer to parent directory
} NODE;

/// FileSystem Structure
typedef struct {
    NODE *root, *cwd;
} fileSystem;

NODE* newRegNode(char name[]);
NODE* newDirNode(char name[]);

#endif /* file_system_h */
