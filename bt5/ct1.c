#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Hàm xử lý tín hiệu Ctrl+C
void signal_handler(int signal_num) {
    if (signal_num == SIGINT) {
        printf("\nCtrl+C được nhận. Kết thúc chương trình 1...\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, signal_handler);

    struct Student students[MAX_STUDENTS]; // Mảng chứa danh sách sinh viên
    int num_students = 0; // Số lượng sinh viên hiện tại

    int choice;
    printf("Chuong trinh 1\n");
    while (1) {
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Nhan Ctrl+C de copy danh sach sinh vien vao vung nho chia se\n");
        printf("3. Ket thuc\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); // Đọc kí tự newline từ bộ đệm

        switch (choice) {
            case 1:
                printf("Nhap so luong sinh vien: ");
                scanf("%d", &num_students);
                getchar(); // Đọc kí tự newline từ bộ đệm
                if (num_students > MAX_STUDENTS) {
                    printf("So luong sinh vien vuot qua gioi han. Vui long nhap lai!\n");
                    break;
                }
                printf("Nhap danh sach sinh vien:\n");
                for (int i = 0; i < num_students; ++i) {
                    printf("Nhap vao ma sv cua sinh vien %d: ", i + 1);
                    fgets(students[i].id, MAX_LEN, stdin);
                    students[i].id[strcspn(students[i].id, "\n")] = 0; // Xóa kí tự newline
                    printf("Nhap vao ten cua sinh vien %d: ", i + 1);
                    fgets(students[i].name, MAX_LEN, stdin);
                    students[i].name[strcspn(students[i].name, "\n")] = 0;
                    printf("Nhap vao lop cua sinh vien %d: ", i + 1);
                    fgets(students[i].class, MAX_LEN, stdin);
                    students[i].class[strcspn(students[i].class, "\n")] = 0;
                }
                printf("Da nhap xong!\n");
                break;
            case 2: {
                key_t key = ftok(".", 'S'); // Tạo key
                int shmid = shmget(key, MAX_STUDENTS * sizeof(struct Student), IPC_CREAT | 0666); // Tạo bộ nhớ dùng chung
                struct Student *shared_data = (struct Student *)shmat(shmid, NULL, 0); // Liên kết vùng nhớ chia sẻ

                printf("Da nhan Ctrl+C. Dang copy danh sach sinh vien vao vung nho chia se...\n");
                for (int i = 0; i < num_students; ++i) {
                    strcpy(shared_data[i].id, students[i].id);
                    strcpy(shared_data[i].name, students[i].name);
                    strcpy(shared_data[i].class, students[i].class);
                }
                sleep(2); // Giả sử thời gian để copy là 2 giây
                printf("Copy xong!\n");

                shmdt(shared_data); // Ngắt kết nối vùng nhớ chia sẻ
                //shmctl(shmid, IPC_RMID, NULL); // Xóa bộ nhớ chia sẻ
                break;
            }
            case 3:
                printf("Ket thuc chuong trinh 1...\n");
                exit(0);
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    }

    return 0;
}
