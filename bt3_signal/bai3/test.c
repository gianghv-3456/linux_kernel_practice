#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char line[100]; // Assuming max line length is 100 characters, adjust as needed
    int lastNumber;

    // Open the file in read mode
    file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // Read lines until end of file, storing the last line
    while (fgets(line, sizeof(line), file) != NULL) {
        // do nothing, we are interested in the last line
        puts(line);
    }

    // Convert the last line to an integer
    lastNumber = atoi(line);

    // Close the file
    fclose(file);

    // Output the last number
    printf("Last number in the file is: %d\n", lastNumber);

    return 0;
}
