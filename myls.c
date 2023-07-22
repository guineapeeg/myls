#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char* options;
char* fileList;

int main(int argc, char* argv[]){

    if(argc > 1){

    }

struct dirent *d;
DIR *dp = opendir(".");

    options = "-i"; //print the index numberof each file
}