//
//  main.c
//  hw1_1
//
//  Created by Gabriel Barros on 2/3/18.
//  Copyright © 2018 Gabriel Barros. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char* read_file(char*, int);
void write_file(char*, char*);

// global variables
int numOfBytes;
char* data;

int main(int argc, char * argv[])
{
    
    int opt;
    while((opt = getopt(argc, argv, "n:i:o:")) != -1) {
        
        switch(opt) {
                
            case 'n':
                numOfBytes = atoi(optarg);
                
                break;
            case 'i':
                data = read_file(optarg, numOfBytes);
                
                break;
            case 'o':
                if(data != NULL) write_file(optarg, data);
                
                break;
            case ':':
                printf("option needs a value\n"); break;
            case '?':
                printf("unknown option: %c\n", optopt); break;
        }
    }
    
    return 0;
}


char* read_file(char* filename, int num_bytes)
{
    
    int fd;
    ssize_t nr;
    char* buf_rd;
    
    fd = open(filename, O_RDONLY);
    
    if(fd == -1)
    {
        perror("Error opening read file");
        return 0;
        
    }
    else
    {
        
        // allocationg memory
        buf_rd = calloc(num_bytes, sizeof(char));
        
        // reading the file up until the num of bytes
        nr = pread(fd, buf_rd, num_bytes, 0);
        printf("[file is opened]\n");
        
        if(nr == -1){
            perror("Error reading the file");
        } else{
            printf("Reading data from %s...\n", filename);
            printf("Data: [%s]\n", buf_rd);
        }
        
        free(buf_rd);
    }
    
    if(close(fd) == -1)
        perror("Error closing read file");
    
    return buf_rd;
    
}

void write_file(char *filename, char* buffer)
{
    
    int fd;
    ssize_t nw;
    
    if(access(filename, F_OK) == -1)
    {
        fd = open(filename, O_CREAT, O_WRONLY);
    }
    else
    {
        fd = open(filename, O_WRONLY);
        nw = pwrite(fd, buffer, strlen(buffer), 0);
        
        if(fd == -1)
        {
            perror("Error opening write file");
            return;
        }
        else if(nw == -1)
        {
            perror("Error writing to the file");
            return;
        }
    }
    
    if(close(fd) == -1)
        perror("Error closing write file");
}
