#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Hàm xử lý signal SIGUSR1
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received SIGUSR1 signal. Waking up...\n");
        // Thực hiện các công việc cần thiết khi nhận được signal để "wake up"
    }
}

int main() {
    // Đăng ký hàm xử lý signal
    signal(SIGUSR1, signal_handler);

    printf("Sleeping indefinitely. Send SIGUSR1 signal to wake up.\n");
    
    // Vòng lặp vô hạn để giữ chương trình sleep
    while(1) {
        sleep(3600); // sleep 1 tiếng
    }

    return 0;
}

