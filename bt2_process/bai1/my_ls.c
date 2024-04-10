#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void list_files(int show_hidden, int long_format) {
    DIR *dir;
    //dirent: D-entry {d_ino: inode_number, d_off: offset to next dir, rec_lent, d_name[] }
    struct dirent *entry;

    //struct stat: information about file
    struct stat file_stat;

    //open current dir, return DIR 
    dir = opendir(".");
    if (dir == NULL) {
        perror("Can't opening directory");
        exit(EXIT_FAILURE);
    }

    //readdir to traversal through dir, return a d-entry object
    while ((entry = readdir(dir)) != NULL) {
        
        //if this file is a hidden file (. before name), skip to next
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("Can't getting file stat");
            exit(EXIT_FAILURE);
        }

        // date
        if (long_format) {
            struct passwd *pwd;
            struct group *grp;
            char date[50];
            strftime(date, 50, "%b %d %H:%M", localtime(&(file_stat.st_mtime)));

            // check for permission
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" ");

            // so lien ket
            printf("%ld ", file_stat.st_nlink);

            // ten nguoi dung, nhom
            pwd = getpwuid(file_stat.st_uid);
            grp = getgrgid(file_stat.st_gid);
            printf("%s %s ", pwd->pw_name, grp->gr_name);

            // kich thuoc, thoi gian
            printf("%lld %s %s\n", (long long)file_stat.st_size, date, entry->d_name);
        } else {
            // ten file
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}


int main(int argc, char *argv[]) {
    int show_hidden = 0;
    int long_format = 0;
    int opt;

    // get the options
    while ((opt = getopt(argc, argv, "la")) != -1) {
        switch (opt) {
            case 'l':
                long_format = 1;
                break;
            case 'a':
                show_hidden = 1;
                break;
            default:
                fprintf(stderr, "Use: %s [-l] [-a]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    
    list_files(show_hidden, long_format);

    return 0;
}


