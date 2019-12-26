//
//  utilities.c
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 26/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

#include "file_system.h"
#include "utilities.h"

/// Print file system tree
void printFileSystemHelper(NODE *node, char prefix[]) {
    
    if(node == NULL) return;
    
    char temp[128] = "";
    
    strcpy(temp, prefix);
    strcat(temp, "/");
    strcat(temp, node->name);
    
    printf("%s\t\t%s\n", node->type==DIR? "DIR":"REG", temp);
    
    printFileSystemHelper(node->childPtr, temp);
    printFileSystemHelper(node->siblingPtr, prefix);
    
}

/// Print entire file system tree
void printEntireFileSystem(NODE *root) {
    if(!root) printf("Uninitialized Filesystem!\n");
    printf("type\tpathname\n");
    printf("----\t--------\n");
    
    printf("%s\t\t%s\n", root->type==DIR? "DIR":"REG", "/");
    printFileSystemHelper(root->childPtr, root->name);
}

/// Error Logging Function
void logError(char error[]) {
    printf("Error : ");
    printf("%s\n", error);
}

/// Delete a FileSystem from memory
void freeFileSystemTree(NODE *root) {
    if(!root) return;
    free(root->childPtr);
    free(root->siblingPtr);
    free(root);
}

/// Initialize root node of file system tree
void initialize(fileSystem *fs) {
    fs->root = newDirNode("");
    fs->cwd = fs->root;
}

void reInitializeFileSystem(fileSystem *fs) {
    freeFileSystemTree(fs->root);
    fs->cwd = NULL;
    initialize(fs);
}

/// directory and basename
void dbname(char *pathname, char *dname, char *bname) {
    char temp[128];
    strcpy(temp, pathname);
    strcpy(dname, dirname(temp));
    strcpy(temp, pathname);
    strcpy(bname, basename(temp));
}

/// Search for a node
NODE* searchDir(fileSystem *fs, char *dirPath) {
    
    if(!dirPath || strcmp(dirPath, ".")==0) return fs->cwd;
    if(strcmp(dirPath, "/")==0) return fs->root;
    
    char *s;
    char temp[64];
    strcpy(temp, dirPath);
    
    s = strtok(temp, "/");
    
    NODE *curr = fs->cwd;
    if(dirPath[0]=='/') curr = fs->root;

    while(s && curr) {
        
        if(curr->childPtr) curr = curr->childPtr;
        while(curr && strcmp(curr->name, s)!=0) curr=curr->siblingPtr;
        
        s = strtok(0, "/");
    }
    
    return curr;
}

/// Search for a file in a directory
NODE* searchInDir(NODE *dirNode, char fileName[]) {
    if(!dirNode) return NULL;
    
    NODE *t = dirNode->childPtr;
    while(t && strcmp(t->name, fileName)!=0) t = t->siblingPtr;
    return t;
}

