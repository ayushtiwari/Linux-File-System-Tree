//
//  commands.h
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 26/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#ifndef commands_h
#define commands_h

int findCmd(char command[]);
int mkdir_(fileSystem *fs, char *pathName);
int rmdir_(fileSystem *fs, char pathName[]);
int cd_(fileSystem *fs, char pathName[]);
void pwdHelper(NODE *curr);
int pwd_(fileSystem *fs);
int ls_(fileSystem *fs, char pathName[]);
int creat_(fileSystem *fs, char *pathName);
int rm_(fileSystem *fs, char pathName[]);
void saveHelper(NODE *node, char prefix[], FILE *fPtr);
int save_(fileSystem *fs, char fileName[]);
int reload_(fileSystem *fs, char filename[]);
int menu_(void);
int quit_(fileSystem *fs);

#endif /* commands_h */
