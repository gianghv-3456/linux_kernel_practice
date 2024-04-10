#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    // Mở một file trước khi fork
    int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

    // Kiểm tra lỗi khi mở file
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Fork để tạo ra process con
    pid_t pid = fork();

    // Kiểm tra lỗi fork
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Process cha
    if (pid > 0) {
        // In ra PID của cha
        printf("PID của cha: %d\n", getpid());
        // In ra thông báo
        printf("I am parent\n");
        // Ghi thông tin vào file
        dprintf(fd, "PID của cha: %d\nI am parent\n", getpid());
        // Chờ process con kết thúc
        sleep(2);
    }
    // Process con
    else if (pid == 0) {
        // In ra PID của con
        printf("PID của con: %d\n", getpid());
        // In ra thông báo
        printf("I am child\n");
        // Ghi thông tin vào file
        dprintf(fd, "PID của con: %d\nI am child\n", getpid());
        sleep(2);
    } else {
        printf("Error when fork\n");
        exit(EXIT_FAILURE);
    }

    // Đóng file
    close(fd);

    // Kiểm tra PID sử dụng lệnh PS
    printf("Sử dụng lệnh PS để kiểm tra PID\n");

    // Dùng biến thông thường để kiểm tra
    int variable = 42;
    printf("Biến thông thường: %d\n", variable);

    // // Sử dụng lệnh kill để giết process con
    // if (pid > 0) {
    //     printf("Process cha sẽ giết process con\n");
    //     kill(pid, SIGKILL);
    //     wait(NULL); // Chờ process con kết thúc
    // } else {
    //     sleep(20);
    //     printf("Process con qua sleep va chay tiep\n");
    // }

    // Sử dụng lệnh kill để giết process cha
    if (pid > 0) {
        sleep(20);
        printf("Process cha qua sleep va chay tiep\n");
        
    } else {
        printf("Process con sẽ giết process cha\n");
        kill(getpid()-1, SIGKILL);
        wait(NULL); // Chờ process con kết thúc
    }

    // Kiểm tra xem process còn lại có bị giết không
    if (pid > 0) {
        printf("Process cha chuan bi ketthuc\n");
    } else {
        printf("Process con chuan bi ket thuc\n");
    }

    return 0;
}

