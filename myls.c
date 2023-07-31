#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

char* options;
char* fileList;

void* printIndexNumber();

int main(int argc, char* argv[]){

    if(argc > 1){

    }

    options = "-i"; //print the index numberof each file
    printIndexNumber(".");
}

void* printIndexNumber(char* locationOf){

    struct dirent *d;
    DIR *dp = opendir(locationOf);
    struct stat myStat;


    if(dp){

        while ((d = readdir(dp)) != NULL)
        {
            if(d->d_name[0] != '.'){
            stat(d->d_name, &myStat);
            printf("%s ", d->d_name);
            printf("%ld\n", myStat.st_ino);
            }
        }
        closedir(dp);

    }

    return NULL;

}