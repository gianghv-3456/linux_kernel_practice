#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Kiểm tra xem có đủ tham số hay không
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    // Mở file để ghi
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    // Ghi "hello world" vào file
    if (fprintf(file, "hello world\n") < 0) {
        perror("fprintf");
        fclose(file);
        return -1;
    }

    // Đóng file và trả về trạng thái kết quả
    fclose(file);
    return 0;
}


