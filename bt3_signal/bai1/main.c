#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Hàm xử lý tín hiệu SIGINT (Ctrl + C)
void sigint_handler(int signum) {
    printf("hello world\n");
}

int main() {
    // Thiết lập xử lý tín hiệu SIGINT
    signal(SIGINT, sigint_handler);

    // Vòng lặp vô hạn để chờ tín hiệu SIGINT
    while (1) {
        sleep(1);  
    }

    return 0;
}

