#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void write_file(char* content) {
    FILE* file;
    file = fopen("abc.txt", "a");
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return 1; // Thoát chương trình với mã lỗi
    }

    // Ghi nội dung vào tệp
    fprintf(file, content);

    // Đóng tệp
    fclose(file);

    printf("Nội dung đã được ghi vào tệp.\n");
}

int main() {
    
    pid_t pid = fork();

    if (pid == 0) {
        // Mã này được thực thi bởi tiến trình con
        printf("Hello from the child process!\tPID: %d\n", pid);
        printf("I am the child, my PID is %d\n", getpid());
        sleep(10);
        printf("Chill ended\n");
        
    } else if (pid > 0) {
        // Mã này được thực thi bởi tiến trình cha
        printf("Hello from the parent process!\tPID:%d\n", pid);

        
        printf("I am the parent, my PID is %d\n", getpid());
        sleep(10);

        printf("Parent ended\n");

    } else {
        // fork() thất bại, in ra lỗi
        perror("fork failed");
    }

    return 0;
}
