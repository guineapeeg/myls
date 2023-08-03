#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

char* options;
char* fileList;

void* printIndexNumber(char* locationOf);
void* printFilesLongFormat(char* locationOf);

int main(int argc, char* argv[]){

    if(argc > 1){

    }

    options = "-i"; //print the index numberof each file
    //printIndexNumber(".");
    printFilesLongFormat(".");
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

void* printFilesLongFormat(char* locationOf){

    struct dirent *d;
    DIR *dp = opendir(locationOf);
    struct stat myStat;


    if(dp){

        
        while ((d = readdir(dp)) != NULL)
        {
            if(d->d_name[0] != '.'){
            stat(d->d_name, &myStat);
            //printf("%d", myStat.st_mode);
            
            if((S_ISDIR(myStat.st_mode))){
                printf("d");
            }else{
                printf("-");
            }
            //owner permission

            if(myStat.st_mode & S_IRUSR){
                printf("r");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IWUSR){
                printf("w");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IXUSR){
                printf("x");
            }else{
                printf("-");
            }

            //putchar('\n');

            //group permission

            if(myStat.st_mode & S_IRGRP){
                printf("r");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IWGRP){
                printf("w");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IXGRP){
                printf("x");
            }else{
                printf("-");
            }

            //putchar('\n');

            //others permission

            if(myStat.st_mode & S_IROTH){
                printf("r");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IWOTH){
                printf("w");
            }else{
                printf("-");
            }

            if(myStat.st_mode & S_IXOTH){
                printf("x");
            }else{
                printf("-");
            }

            printf(" %ld", myStat.st_nlink);

            int uid = myStat.st_uid;
            struct passwd* pwd;
            pwd = getpwuid(uid);
            printf(" %s", pwd->pw_name);


            int gid = myStat.st_gid;
            struct group *grp;
            grp = getgrgid(gid);
            printf(" %s", grp->gr_name);

            printf(" %ld", myStat.st_size);

            size_t dateOfLastMod;
            char date[50];
            dateOfLastMod = strftime(date, 20, " %b %d %H:%M", localtime(&(myStat.st_mtime)));
            printf(" %s", date);

            printf(" %s", d->d_name);

            putchar('\n');

            }
        }
        closedir(dp);

    }


    return NULL;
}