#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_LEN 100
#define MAX_STUDENTS 10

// Struct định nghĩa sinh viên
struct Student {
    char id[MAX_LEN];
    char name[MAX_LEN];
    char class[MAX_LEN];
};

// Hàm xử lý tín hiệu Ctrl+V
void signal_handler(int signal_num) {
    if (signal_num == SIGQUIT) {
        printf("\nCtrl+V được nhận. Kết thúc chương trình 2...\n");
        exit(0);
    }
}

int main() {
    signal(SIGQUIT, signal_handler);

    int choice;
    printf("Chuong trinh 2\n");
    while (1) {
        printf("1. Nhan Ctrl+V de doc du lieu tu vung nho chia se\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Ket thuc\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); // Đọc kí tự newline từ bộ đệm

        switch (choice) {
            case 1: {
                key_t key = ftok(".", 'S'); // Tạo key
                int shmid = shmget(key, MAX_STUDENTS * sizeof(struct Student), IPC_CREAT | 0666); // Tạo bộ nhớ dùng chung
                struct Student *shared_data = (struct Student *)shmat(shmid, NULL, 0); // Liên kết vùng nhớ chia sẻ

                printf("Da nhan Ctrl+V. Dang doc du lieu tu vung nho chia se...\n");
                sleep(2); // Giả sử thời gian để đọc là 2 giây
                printf("Doc xong!\n");

                shmdt(shared_data); // Ngắt kết nối vùng nhớ chia sẻ
                break;
            }
            case 2: {
                key_t key = ftok(".", 'S'); // Tạo key
                int shmid = shmget(key, MAX_STUDENTS * sizeof(struct Student), IPC_CREAT | 0666); // Tạo bộ nhớ dùng chung
                struct Student *shared_data = (struct Student *)shmat(shmid, NULL, 0); // Liên kết vùng nhớ chia sẻ

                printf("Danh sach sinh vien:\n");
                for (int i = 0; i < MAX_STUDENTS; ++i) {
                    if (shared_data[i].id[0] != '\0') {
                        printf("Ma SV: %s\n", shared_data[i].id);
                        printf("Ten: %s\n", shared_data[i].name);
                        printf("Lop: %s\n", shared_data[i].class);
                        printf("\n");
                    }
                }

                shmdt(shared_data); // Ngắt kết nối vùng nhớ chia sẻ
                break;
            }
            case 3:
                printf("Ket thuc chuong trinh 2...\n");
                exit(0);
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    }

    return 0;
}
