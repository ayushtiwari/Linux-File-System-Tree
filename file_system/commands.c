////
////  commands.c
////  file_system_tree_sim
////
////  Created by Ayush Tiwari on 26/12/19.
////  Copyright © 2019 Ayush Tiwari. All rights reserved.
////
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_system.h"
#include "utilities.h"
#include "commands.h"

int findCmd(char command[]) {
    
    char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm", "reload", "save", "menu", "quit", NULL};
    
    int i=0;
    while(cmd[i]) {
        if(!strcmp(command, cmd[i]))
            return i;
        i++;
    }
    return -1;
}

int mkdir_(fileSystem *fs, char *pathName) {
    
    if(strlen(pathName)==0) {
        logError("Invalid pathname!");
        return 0;
    }
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *newDirectory = newDirNode(bname);

    NODE *parentDir = searchDir(fs, dname);

    if(!parentDir) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(parentDir->type != DIR) {
        logError("Not a directory!");
        return 0;
    }
    
    if(!parentDir->childPtr) {
        parentDir->childPtr = newDirectory;
        newDirectory->parentPtr = parentDir;
    }
    else {
        NODE *t = parentDir->childPtr;
        
        while(t->siblingPtr!=NULL && strcmp(t->name, bname)!=0) t = t->siblingPtr;
        if(strcmp(t->name, bname)==0) {
            logError("Directory already exists!");
            return 0;
        }
        t->siblingPtr = newDirectory;
        newDirectory->parentPtr = t;
    }

    return 1;
}

int rmdir_(fileSystem *fs, char pathName[]) {
    
    if(strlen(pathName)==0) {
        logError("Invalid pathname!");
        return 0;
    }
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *parentDir = searchDir(fs, dname);
    
    if(!parentDir) {
        logError("Invalid pathname");
        return 0;
    }

    NODE *t = parentDir->childPtr;
    
    while(t && strcmp(t->name, bname)!=0) t = t->siblingPtr;
    
    if(t==NULL) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(t->childPtr != NULL) {
        logError("Directory not empty!");
        return 0;
    }
    
    if(t->type == DIR) {
        
        if(t->parentPtr == parentDir) {
            t->parentPtr->childPtr = t->siblingPtr;
            if(t->siblingPtr)
                t->siblingPtr->parentPtr = t->parentPtr;
        }
        else {
            t->parentPtr->siblingPtr = t->siblingPtr;
            if(t->siblingPtr)
                t->siblingPtr->parentPtr = t->parentPtr;
        }
        free(t);
    } else {
        logError("File is not a directory!");
        return 0;
    }
    
    return 1;
}

int cd_(fileSystem *fs, char pathName[]) {
    
    if(strcmp(pathName, "")==0) {
        fs->cwd = fs->root;
        return 1;
    }
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *parentDir = searchDir(fs, dname);
    
    if(!parentDir) {
        logError("Invalid pathname");
        return 0;
    }
    
    NODE *t = parentDir;
    
    if(strcmp(bname, ".")!=0 && strcmp(bname, "/")!=0) {
        t = parentDir->childPtr;
        while(t && strcmp(t->name, bname)!=0) t = t->siblingPtr;
    }
    
    if(t==NULL) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(t->type == DIR) {
        fs->cwd = t;
    } else {
        logError("File is not a directory!");
        return 0;
    }
    
    return 1;
}

void pwdHelper(NODE *curr) {
    if(curr==NULL) return;
    pwdHelper(curr->parentPtr);
    if(curr->parentPtr && curr->parentPtr->childPtr==curr) {
        printf("%s", curr->parentPtr->name);
        printf("/");
    }
}

/**
    Present Working Directory
 */
int pwd_(fileSystem *fs) {
    pwdHelper(fs->cwd);
    printf("%s/", fs->cwd->name);
    return 1;
}

/**
    ls [pathname]
 */
int ls_(fileSystem *fs, char pathName[]) {
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *parentDir = searchDir(fs, dname);

    if(!parentDir) {
        logError("Invalid pathname!");
        return 0;
    }
    
    NODE *t = parentDir;
    
    if(strcmp(bname, ".")!=0 && strcmp(bname, "/")!=0) {
        t = parentDir->childPtr;
        while(t && strcmp(t->name, bname)!=0) t = t->siblingPtr;
    }
    

    if(t==NULL) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(t->type==DIR) {
        NODE *p = t->childPtr;
        if(p==NULL) return 1;
        while(p) {
            printf("%s\t", p->name);
            p = p->siblingPtr;
        }
        printf("\n");
    } else {
        printf("%s\n", t->name);
    }
    
    return 1;
}

int creat_(fileSystem *fs, char *pathName) {
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *newRegFile = newRegNode(bname);
    
    NODE *parentDir = searchDir(fs, dname);
    
    if(!parentDir) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(parentDir->type != DIR) {
        logError("Not a directory!");
        return 0;
    }
    
    if(!parentDir->childPtr) {
        parentDir->childPtr = newRegFile;
        newRegFile->parentPtr = parentDir;
    }
    else {
        NODE *t = parentDir->childPtr;
        
        while(t->siblingPtr!=NULL && strcmp(t->name, bname)!=0) t = t->siblingPtr;
        if(strcmp(t->name, bname)==0) {
            logError("File already exists!");
            return 0;
        }
        t->siblingPtr = newRegFile;
        newRegFile->parentPtr = t;
    }

    return 1;
}

int rm_(fileSystem *fs, char pathName[]) {
    
    char dname[64], bname[64];
    dbname(pathName, dname, bname);
    
    NODE *parentDir = searchDir(fs, dname);
    
    if(!parentDir) {
        logError("Invalid pathname");
        return 0;
    }

    NODE *t = parentDir->childPtr;
    while(t && strcmp(t->name, bname)!=0) t = t->siblingPtr;
    
    if(t==NULL) {
        logError("Invalid pathname!");
        return 0;
    }
    
    if(t->type == REG) {
        if(t->parentPtr == parentDir) {
            t->parentPtr->childPtr = t->siblingPtr;
            if(t->siblingPtr)
                t->siblingPtr->parentPtr = t->parentPtr;
        }
        else {
            t->parentPtr->siblingPtr = t->siblingPtr;
            if(t->siblingPtr)
                t->siblingPtr->parentPtr = t->parentPtr;
        }
    } else {
        logError("File is not a Regular File!");
        return 0;
    }
    
    return 1;
}

void saveHelper(NODE *node, char prefix[], FILE *fPtr) {
    
    if(node == NULL) return;
    
    char temp[128] = "";
    
    strcpy(temp, prefix);
    strcat(temp, "/");
    strcat(temp, node->name);
    
    fprintf(fPtr, "%s\t\t%s\n", node->type==DIR? "DIR":"REG", temp);
    
    saveHelper(node->childPtr, temp, fPtr);
    saveHelper(node->siblingPtr, prefix, fPtr);
    
}

int save_(fileSystem *fs, char fileName[]) {
    
    if(!fs->root)  {
        printf("Uninitalized Filesystem!");
        return 0;
    }
    
    FILE *fPtr = fopen(fileName, "w+");
    
    if(!fPtr) return 0;
    
    fprintf(fPtr, "%s\t\t%s\n", fs->root->type==DIR? "DIR":"REG", "/");
    saveHelper(fs->root->childPtr, "", fPtr);
    fclose(fPtr);
    
    return 1;
}

int reload_(fileSystem *fs, char filename[]) {
    
    FILE *fPtr = fopen(filename, "r");
    
    if(!fPtr) {
        printf("No saved filesystem!");
        return 0;
    }
    
    char type[64];
    char pathName[128];
    
    fscanf(fPtr, "%s\t\t%s", type, pathName);
    while(fscanf(fPtr, "%s\t\t%s", type, pathName)==2) {
        if(strcmp(type, "DIR")==0) {
            mkdir_(fs, pathName);
        } else {
            creat_(fs, pathName);
        }
    }
    
    fclose(fPtr);
    
    return 1;
}

int menu_() {
    
    printf("Command List\n");
    printf("------------\n");
    printf("mkdir pathname :make a new directory for a given pathname\n");
    printf("rmdir pathname :remove the directory, if it is empty\n");
    printf("cd [pathname]  :change CWD to pathname, or to / if no pathname\n");
    printf("ls [pathname]  :list the directory contents of pathname or CWD\n");
    printf("pwd            :print the (absolute) pathname of CWD\n");
    printf("creat pathname :create a FILE node\n");
    printf("rm pathname    :remove the FILE node\n");
    printf("save filename  :save the currentfile system tree as a file\n");
    printf("reload filename:construct afile system tree from a file\n");
    printf("menu           :show a menu of valid commands\n");
    printf("quit           :save thefile system tree, then terminate the program\n");
    
    return 1;
}

int quit_(fileSystem *fs) {
    save_(fs, "FileSystemDefault.txt");
    return 1;
}

