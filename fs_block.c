#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fs_block.h"

#include "disk.h"
#include "superblock.h"

int writeFsBlock(int position, int next, void *data, int _size) {
    struct {
        int next;
        char data[getMaxDataAmount()];
    } block;
    block.next = next;
    memset(block.data, 0, sizeof(block.data));
    int size = sizeof(block.data);
    if (_size < size)
        size = _size;
    memcpy(block.data, data, size);
    if (diskWriteBlock(position, &block) != 0)
        return -1;
    return 0;
}

int readFsBlock(int position, int *next, void *data, int _size) {
    struct {
        int next;
        char data[getMaxDataAmount()];
    } block;
    if (diskReadBlock(position, &block) != 0)
        return -1;
    *next = block.next;
    int size = sizeof(block.data);
    if (_size < size)
        size = _size;
    memcpy(data, block.data, size);
    return 0;
}
