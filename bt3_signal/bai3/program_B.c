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
        printf("B received Signal\n");
        ready = 1;
    }
}

void readLastNumber(FILE *file, int *number)
{
    char line[100];
    int lastNumber;
    // Read lines until end of file, storing the last line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // do nothing, we are interested in the last line
    }

    // Convert the last line to an integer
    lastNumber = atoi(line);

    // Close the file
    fclose(file);

    // Output the last number
    printf("Last number in the file is: %d\n", lastNumber);
    *number = lastNumber;
}

int main() {
    // Đăng ký signal handler
    signal(SIGUSR1, signal_handler);
    printf("Fork! Hello from B!\tpid: %d\n", getpid());

    WAIT_SIG:
    printf("ready of B: %d\n", ready);
    // Chờ signal từ tiến trình cha (A)
    while (!ready);
    
    // Mở file để ghi
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    //read the last number
    int counter = 0;
    readLastNumber(file, &counter);
    fclose(file);

    printf("B read counter: %d\n", counter);
    
    // Tăng counter lên 1
    counter++;
    
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("B printf file\n********************\n");
    // Ghi dòng mới vào file chứa process ID của tiến trình và counter mới
    fprintf(file, "B write pid: %d\n%d\n", getpid(), counter);
    
    // Đóng file
    fclose(file);

    //send signal to A
    kill(getppid(), SIGUSR1);

    //Đổi cờ, chờ lần gửi tiếp
    ready = 0;
    goto WAIT_SIG;
    
    return 0;
}
