#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define FILENAME "data.txt"

volatile sig_atomic_t ready = 0;

// Hàm xử lý signal SIGUSR1
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        ready = 1;
    }
}

int main() {
    // Đăng ký signal handler
    signal(SIGUSR1, signal_handler);

    // Fork ra tiến trình B
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Tiến trình con (B)
        execl("./program_B", "program_B", NULL);
        perror("execl() failed");
        exit(EXIT_FAILURE);
    } else { // Tiến trình cha (A)
        // Chờ tiến trình con sẵn sàng
        while (!ready);
        
        // Mở file để ghi
        FILE *file = fopen(FILENAME, "a");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        
        // Đọc dòng counter cuối cùng từ file
        int counter;
        fscanf(file, "%d", &counter);
        
        // Tăng counter lên 1
        counter++;
        
        // Ghi dòng mới vào file chứa process ID của tiến trình và counter mới
        fprintf(file, "Process ID: %d, Counter: %d\n", getpid(), counter);
        
        // Đóng file
        fclose(file);
        
        // Gửi signal để báo cho tiến trình con (B) biết là đã ghi xong
        kill(pid, SIGUSR1);
    }

    return 0;
}

