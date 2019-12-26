//
//  main.c
//  file_system_tree_sim
//
//  Created by Ayush Tiwari on 24/12/19.
//  Copyright © 2019 Ayush Tiwari. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_system.h"
#include "utilities.h"
#include "commands.h"

int simCommandLine(fileSystem *fs) {
    
    char line[128]="";                     // user input command line
    char command[16]="", pathName[64]="";     // command and pathname strings
    char error[128]="";
    
    int quit_flag = 1;
    
    while(quit_flag) {
        strcpy(command, "");
        strcpy(pathName, "");
        
        printf("user@machine ");
        pwd_(fs);
        printf(" %% ");
        fgets(line, 128, stdin);
        line[strlen(line)-1] = 0;
        sscanf(line, "%s %s", command, pathName);
        
        int commandIndex = findCmd(command);
        
        switch (commandIndex) {
            case 0:
                mkdir_(fs, pathName);
                break;
            case 1:
                rmdir_(fs, pathName);
                break;
            case 2:
                ls_(fs, pathName);
                break;
            case 3:
                cd_(fs, pathName);
                break;
            case 4:
                pwd_(fs);
                printf("\n");
                break;
            case 5:
                creat_(fs, pathName);
                break;
            case 6:
                rm_(fs, pathName);
                break;
            case 7:
                reload_(fs, pathName);
                break;
            case 8:
                save_(fs, pathName);
                break;
            case 9:
                menu_();
                break;
            case 10:
                quit_(fs);
                quit_flag = 0;
                printf("Logged Out!\n");
                break;
                
            default:
                sprintf(error, "Command not found - %s", command);
                logError(error);
                break;
        }
        
    }
        
    return 1;
}

int main(int argc, const char * argv[]) {
    
    fileSystem fs;
    initialize(&fs);
    simCommandLine(&fs);
    
    return 0;
}
