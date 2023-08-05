#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <string.h>
#include <sys/dir.h>

char *options;
char *fileList;

void *printIndexNumber(char *locationOf);
void *printFilesLongFormat(char *locationOf, int index);
void *noArgumentsls();
void *checkFlag(char *argv);
void *emptyls();
void *emptylsAlpha(char *locationOf);

int flags[] = {0, 0, 0}; // flags will be like : l i R

int main(int argc, char *argv[])
{

    if (argc < 2) // no arguments
    {
        emptyls(".");
    }
    else
    { // more arguments supplied
        int i = 1;
        int lineArgumentN = 0;

        while (lineArgumentN == 0 && i < argc) // checking if every argument is a flag
        {
            if (argv[i][0] == '-')
            {
                checkFlag(argv[i]);
                i++;
            }
            else
            {
                lineArgumentN = 1;
            }
        } // checking if every argument is a flag

        if (i < argc) // if we have additional path arguments
        {
            while (i < argc)
            {
                if (flags[0] == 1 && flags[1] == 1)
                {
                    printFilesLongFormat(argv[i], 1);
                }
                else
                {
                    int zeroFlags = 1;

                    if (flags[0] == 1)
                    {
                        // l
                        printFilesLongFormat(argv[i], 0);
                        zeroFlags = 0;
                    }
                    else if (flags[1] == 1)
                    {
                        // i
                        printIndexNumber(argv[i]);
                        zeroFlags = 0;
                    }

                    if (flags[2] == 1)
                    {
                        // R
                        zeroFlags = 0;
                    }

                    if (zeroFlags != 0)
                    { // no flags at all provided

                        emptyls(argv[i]);
                    }
                }

                i++;
            } // while there are some arguments left
        }
        else // if we only have flags with no path specified
        {

            if (flags[0] == 1 && flags[1] == 1)
            {
                printFilesLongFormat(".", 1);
            }
            else
            {
                int zeroFlags = 1;

                if (flags[0] == 1)
                {
                    // l
                    printFilesLongFormat(".", 0);
                    zeroFlags = 0;
                }
                else if (flags[1] == 1)
                {
                    // i
                    printIndexNumber(".");
                    zeroFlags = 0;
                }

                if (flags[2] == 1)
                {
                    // R
                    zeroFlags = 0;
                }

                if (zeroFlags != 0)
                { // no flags at all provided

                    emptyls(".");
                }
            }
        }
    }
}

void *checkFlag(char *argv)
{

    int c = strlen(argv);
    for (int i = 1; i < c; i++)
    {
        if (argv[i] == 'l')
        {
            flags[0] = 1;
        }
        else if (argv[i] == 'i')
        {
            flags[1] = 1;
        }
        else if (argv[i] == 'R')
        {
            flags[2] = 1;
        }
    }

    return NULL;
}

void *printFilesLongFormat(char *locationOf, int index)
{

    struct dirent **namelist;
    int n;
    int i = 0;

    n = scandir(locationOf, &namelist, NULL, alphasort);
    if (n < 0)
    {
        printf("No such file or directory");
    }
    else
    {
        while (i < n)
        {
            if (namelist[i]->d_name[0] != '.')
            {

                struct dirent *dir;
                struct stat myStatInside;

                char path[100];
                strcpy(path, locationOf);
                strcat(path, "/");
                strcat(path, namelist[i]->d_name);

                stat(path, &myStatInside);

                if (index == 1)
                {
                    printf("%ld ", myStatInside.st_ino);
                }

                if ((S_ISDIR(myStatInside.st_mode)))
                {
                    printf("d");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IRUSR)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IWUSR)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IXUSR)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IRGRP)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IWGRP)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IXGRP)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IROTH)
                {
                    printf("r");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IWOTH)
                {
                    printf("w");
                }
                else
                {
                    printf("-");
                }

                if (myStatInside.st_mode & S_IXOTH)
                {
                    printf("x");
                }
                else
                {
                    printf("-");
                }

                printf(" %ld", myStatInside.st_nlink);

                int uid = myStatInside.st_uid;
                struct passwd *pwd;
                pwd = getpwuid(uid);
                printf(" %s", pwd->pw_name);

                int gid = myStatInside.st_gid;
                struct group *grp;
                grp = getgrgid(gid);
                printf(" %s", grp->gr_name);

                printf(" %ld", myStatInside.st_size);

                // size_t dateOfLastMod;
                char date[50];
                // dateOfLastMod =
                strftime(date, 20, " %b %d %H:%M", localtime(&(myStatInside.st_mtime)));
                printf(" %s", date);

                printf(" %s", namelist[i]->d_name);

                putchar('\n');

            }

            free(namelist[i]);
            i++;
        }
        free(namelist);
    }

    return NULL;
}

void *emptyls(char *locationOf)
{

    struct dirent **namelist;
    int n;
    int i = 0;

    n = scandir(locationOf, &namelist, NULL, alphasort);
    if (n < 0)
    {
        printf("No such file or directory");
    }
    else
    {
        while (i < n)
        {
            if (namelist[i]->d_name[0] != '.')
            {

                printf("%s\n", namelist[i]->d_name);
            }

            free(namelist[i]);
            i++;
        }
        free(namelist);
    }

    return NULL;
}

void *printIndexNumber(char *locationOf)
{

    struct dirent **namelist;
    int n;
    int i = 0;

    n = scandir(locationOf, &namelist, NULL, alphasort);
    if (n < 0)
    {
        printf("No such file or directory");
    }
    else
    {
        while (i < n)
        {
            if (namelist[i]->d_name[0] != '.')
            {

                struct dirent *dir;
                // DIR *dpInside = opendir(namelist[i]->d_name);
                struct stat myStatInside;

                char path[100];
                strcpy(path, locationOf);
                strcat(path, "/");
                strcat(path, namelist[i]->d_name);

                stat(path, &myStatInside);

                printf("%ld ", myStatInside.st_ino);
            }

            free(namelist[i]);
            i++;
        }
        free(namelist);
    }

    return NULL;
}
