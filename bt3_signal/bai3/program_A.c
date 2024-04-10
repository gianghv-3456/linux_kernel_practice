#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define FILENAME "data.txt"

volatile sig_atomic_t ready = 1;

// Hàm xử lý signal SIGUSR1
void signal_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("A received Signal\n");
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

int main()
{
    // Đăng ký signal handler
    signal(SIGUSR1, signal_handler);

    // Fork ra tiến trình B
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    { // Tiến trình con (B)
        execl("./program_B", "program_B", NULL);
        perror("execl() failed");
        exit(EXIT_FAILURE);
    }
    else
    { // Tiến trình cha (A)
        sleep(2);
        printf("Fork! hello from A\tpid: %d\n", getpid());
        // Chờ tiến trình con sẵn sàng

    WAIT_SIG:
        while (!ready)
            ;
        // Mở file để ghi
        FILE *file = fopen(FILENAME, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error opening file.\n");
            exit(EXIT_FAILURE);
        }

        // Đọc dòng counter cuối cùng từ file
        int counter = 0;

        readLastNumber(file, &counter);
        // Close the file
        fclose(file);

        printf("A read counter: %d\n", counter);

        file = fopen(FILENAME, "a");
        if (file == NULL)
        {
            fprintf(stderr, "Error opening file.\n");
            exit(EXIT_FAILURE);
        }
        // Tăng counter lên 1
        counter++;

        // Ghi dòng mới vào file chứa process ID của tiến trình và counter mới
        fprintf(file, "A write pid: %d\n%d\n", getpid(), counter);

        // Đóng file
        fclose(file);

        // Gửi signal để báo cho tiến trình con (B) biết là đã ghi xong
        kill(pid, SIGUSR1);

        // Đổi cờ, chờ lần ghi tiếp theo
        ready = 0;

        // Về lại điểm chờ signal
        goto WAIT_SIG;
    }

    return 0;
}
