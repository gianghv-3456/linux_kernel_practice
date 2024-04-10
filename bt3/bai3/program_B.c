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
    
    // Chờ signal từ tiến trình cha (A)
    while (!ready);
    
    // Mở file để ghi
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    // Đọc dòng counter cuối cùng từ file
    int counter;
    fseek(file, -sizeof(int), SEEK_END);
    fscanf(file, "%d", &counter);
    
    // Tăng counter lên 1
    counter++;
    
    // Ghi dòng mới vào file chứa process ID của tiến trình và counter mới
    fprintf(file, "Process ID: %d, Counter: %d\n", getpid(), counter);
    
    // Đóng file
    fclose(file);
    
    return 0;
}
