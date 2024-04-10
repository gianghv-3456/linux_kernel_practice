#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pid_of_sleep_program>\n", argv[0]);
        return 1;
    }

    // Lấy PID của chương trình sleep từ đối số dòng lệnh
    pid_t pid = atoi(argv[1]);

    // Gửi signal SIGUSR1 đến chương trình sleep
    if (kill(pid, SIGUSR1) == 0) {
        printf("Signal SIGUSR1 sent to process with PID %d.\n", pid);
    } else {
        perror("kill");
        return 1;
    }

    return 0;
}
