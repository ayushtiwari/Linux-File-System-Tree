//
//  utilities.h
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 26/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#ifndef utilities_h
#define utilities_h

void printFileSystemHelper(NODE *node, char prefix[]);
void printEntireFileSystem(NODE *root);
void logError(char error[]);
void freeFileSystemTree(NODE *root);
void initialize(fileSystem *fs);
void reInitializeFileSystem(fileSystem *fs);
void dbname(char *pathname, char *dname, char *bname);
NODE* searchDir(fileSystem *fs, char *dirPath);
NODE* searchInDir(NODE *dirNode, char fileName[]);

#endif /* utilities_h */
