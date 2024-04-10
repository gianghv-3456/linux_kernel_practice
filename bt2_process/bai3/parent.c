#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        //  con
        execl("./child", "child", argv[1], NULL);
        perror("execl");
       
    } else {
        // cha
        int status;
        waitpid(pid, &status, 0);
            printf("Child process status: %s\n", (status == 0) ? "success" : "fail" );
       
    }

    return 0;
}



