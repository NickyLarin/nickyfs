#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DISK_BLOCK_SIZE 4096

FILE *disk = NULL;

int diskOpen(char *path) {
    disk = fopen(path, "rb+");
    if (disk == NULL) {
        fprintf(stderr, "Error: opening \"disk\" file\n");
        return -1;
    }
    return 0;
}

int diskSeek(int pos) {
    if (fseek(disk, pos*DISK_BLOCK_SIZE, SEEK_SET) != 0) {
        perror("Error: changing \"disk\" file position");
        return -1;
    }
    return 0;
}

int diskWriteBlock(int pos, void *buf) {
    if (diskSeek(pos) != 0)
        return -1;
    if (fwrite(buf, DISK_BLOCK_SIZE, 1, disk) < 1) {
        fprintf(stderr, "Error: writing data to \"disk\" file\n");
        return -1;
    }
    return 0;
}

int diskReadBlock(int pos, void *buf) {
    if (diskSeek(pos) != 0)
        return -1;
    if (fread(buf, DISK_BLOCK_SIZE, 1, disk) < 1) {
        fprintf(stderr, "Error: reading data from \"disk\" file\n");
        return -1;
    }
    return 0;
}

int diskClose() {
    if (fclose(disk) != 0) {
        perror("Error: closing \"disk\" file");
        return -1;
    }
    return 0;
}
