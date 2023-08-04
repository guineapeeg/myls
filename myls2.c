#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <string.h>

char *options;
char *fileList;

void *printIndexNumber(char *locationOf);
void *printFilesLongFormat(char *locationOf, int index);
void *noArgumentsls();
void *checkFlag(char *argv);
void *emptyls();

int flags[] = {0, 0, 0}; // flags will be like : l i R

int main(int argc, char *argv[])
{

    while (1)
    {

        printFilesLongFormat(argv[2], 0);

        exit(0);
    }

    int i = 2;
    int lineArgumentN = 0;

    if (argc < 2) // no arguments
    {
        emptyls(".");
    }
    else
    { // more arguments supplied

        while (lineArgumentN == 0 && i <= argc) // checking if every argument is a flag
        {
            if (argv[i - 1][0] == '-')
            {
                checkFlag(argv[i - 1]);
                printf("i : %d", i);
                i++;
            }
            else
            {
                lineArgumentN = 1;
            }
        }

        // after all flags have been processed
        i = i - 1;
        printf("\n i: %d \n", i);
        printf("arguments: %d \n", argc);

        // need to process path arguments
        if (i < argc)
        {
            while (i < argc)
            {

                printf("fat \n");
                if (flags[0] == 1 && flags[1] == 1)
                {

                    printf("my argument: %s \n", argv[i]);
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

                    if (zeroFlags != 1)
                    { // no flags at all provided

                        emptyls(argv[i]);
                    }
                }

                i++;
            }
        }
        else
        {
            int zeroFlags = 1;

            if (flags[0] == 1 && flags[1] == 1)
            {
                printFilesLongFormat(".", 1);
                printf("are we here");
            }
            else
            {

                if (flags[0] == 1)
                {
                    // l
                    printFilesLongFormat(".", 0);
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

                if (zeroFlags != 1)
                { // no flags at all provided

                    emptyls(argv[i]);
                }
            }
        }

        // combined i and l

        //
    }

    printf("\n");
}
void *emptyls(char *locationOf)
{

    struct dirent *d;
    DIR *dp = opendir(locationOf);
    struct stat myStat;

    if (dp)
    {

        while ((d = readdir(dp)) != NULL)
        {
            if (d->d_name[0] != '.')
            {
                stat(d->d_name, &myStat);
                printf("%s ", d->d_name);
            }
        }
        closedir(dp);
    }

    return NULL;
}

void *checkFlag(char *argv)
{
    printf("%s \n", argv);

    int c = strlen(argv);
    for (int i = 1; i < c; i++)
    {
        if (argv[i] == 'l')
        {
            flags[0] = 1;
            printf("l detected \n");
        }
        else if (argv[i] == 'i')
        {
            flags[1] = 1;
            printf("i detected \n");
        }
        else if (argv[i] == 'R')
        {
            flags[2] = 1;
            printf("R detected \n");
        }

        // printf("here \n");

        printf("integers i %d c %d", i, c);
    }

    return NULL;
}

void *printIndexNumber(char *locationOf)
{

    printf("In index print function, %s", locationOf);

    struct dirent *d;
    DIR *dp = opendir(locationOf);
    struct stat myStat;

    if (dp)
    {

        while ((d = readdir(dp)) != NULL)
        {
            if (d->d_name[0] != '.')
            {
                stat(d->d_name, &myStat);
                printf("%s ", d->d_name);
                printf("%ld\n", myStat.st_ino);
            }
        }
        closedir(dp);
    }

    return NULL;
}

void *printFilesLongFormat(char *locationOf, int index)
{

    printf("hello from long format: %s", locationOf);

    struct dirent *d;
    DIR *dp = opendir(locationOf);
    struct stat myStat;

    if (dp)
    {

        while ((d = readdir(dp)) != NULL)

        //for every file here
        {
            printf("\n %s", d->d_name);

            if (d->d_name[0] != '.')
            {

                stat("\\foo\\secretheader.h", &myStat);
                int gid = myStat.st_gid;
                struct group *grp;
                grp = getgrgid(gid);
                printf(" %s", grp->gr_name);
            }
        }
    }

    // struct dirent *d;
    // DIR *dp = opendir(locationOf);
    // struct stat myStat;

    // if (dp)
    // {

    //     while ((d = readdir(dp)) != NULL)
    //     {

    //         printf("%s", d->d_name);
    //         if (d->d_name[0] != '.')
    //         {
    //             stat(d->d_name, &myStat);

    //             if (index == 1)
    //             {
    //                 printf("%ld ", myStat.st_ino);
    //             }

    //             // printf("%d", myStat.st_mode);

    //             if ((S_ISDIR(myStat.st_mode)))
    //             {
    //                 printf("d");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }
    //             // owner permission

    //             if (myStat.st_mode & S_IRUSR)
    //             {
    //                 printf("r");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IWUSR)
    //             {
    //                 printf("w");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IXUSR)
    //             {
    //                 printf("x");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             // putchar('\n');

    //             // group permission

    //             if (myStat.st_mode & S_IRGRP)
    //             {
    //                 printf("r");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IWGRP)
    //             {
    //                 printf("w");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IXGRP)
    //             {
    //                 printf("x");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             // putchar('\n');

    //             // others permission

    //             if (myStat.st_mode & S_IROTH)
    //             {
    //                 printf("r");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IWOTH)
    //             {
    //                 printf("w");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             if (myStat.st_mode & S_IXOTH)
    //             {
    //                 printf("x");
    //             }
    //             else
    //             {
    //                 printf("-");
    //             }

    //             printf(" %ld", myStat.st_nlink);

    //             int uid = myStat.st_uid;
    //             struct passwd *pwd;
    //             pwd = getpwuid(uid);
    //             printf(" %s", pwd->pw_name);

    //             int gid = myStat.st_gid;
    //             struct group *grp;
    //             grp = getgrgid(gid);
    //             printf(" %s", grp->gr_name);

    //             printf(" %ld", myStat.st_size);

    //             // size_t dateOfLastMod;
    //             char date[50];
    //             // dateOfLastMod =
    //             strftime(date, 20, " %b %d %H:%M", localtime(&(myStat.st_mtime)));
    //             printf(" %s", date);

    //             printf(" %s", d->d_name);

    //             putchar('\n');
    //         }
    //     }
    //     closedir(dp);
    // }
    // else
    // {
    //     printf("couldnt open directory");
    // }

    return NULL;
}

void *recursiveListing(char *locationOf)
{

    return NULL;
}