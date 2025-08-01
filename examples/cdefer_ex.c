//
// Created by Jessica Bruce on 8/1/25.
//

#include "../cdefer.h"

#include <stdio.h>
#include <stdlib.h>

// Cleanup function to close a FILE* when the variable goes out of scope
void close_file(FILE **fp) {
    if (fp && *fp) {
        printf("Closing file automatically.\n");
        fclose(*fp);
    }
}

void use_defer() {
    // Declare a FILE* with the defer attribute.
    // close_file will be called automatically when `fp` goes out of scope.
    defer(close_file) FILE *fp = fopen("example.txt", "w");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Hello, defer!\n");

    // No need to explicitly call fclose(fp).
    // It will be called automatically when this function returns,
    // thanks to the defer macro and cleanup attribute.
}