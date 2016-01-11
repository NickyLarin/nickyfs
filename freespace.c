#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "freespace.h"

#include "disk.h"
#include "superblock.h"
#include "fs_block.h"

static struct SuperBlock *superBlock;

static int *currentFreeBlocks;

int initFreeSpace() {
    superBlock = getSuperBlock();
    currentFreeBlocks = (int *)malloc(getMaxDataAmount());
    return 0;
}

int readFreeBlocksPortion() {
    int next;
    if (readFsBlock(getFreeListPointer(), &next, currentFreeBlocks, getMaxDataAmount()) != 0)
        return -1;
}

int createFreeSpaceList() {
    int dataSize = getMaxDataAmount();

    // Считаем количество блоков, которое требуется чтобы хранить весь список
    int numberBlocksRequired = getTotalBlocksAmount() / (dataSize/sizeof(int));
    if (getTotalBlocksAmount() % (dataSize/sizeof(int)) != 0)
        numberBlocksRequired++;

    int data[dataSize/sizeof(int)];
    int dataIndex = 0;
    int position = 1;

    // Перебираем каждый блок в файловой системе по номеру и записываем порциями
    // которые помещаются в один блок
    for (int i = 1; i <= getTotalBlocksAmount(); i++) {
        data[dataIndex] = i;
        dataIndex++;
        if (dataIndex == dataSize/sizeof(int)) {
            writeFsBlock(position, position+1, data, sizeof(data));
            position++;
            dataIndex = 0;
            memset(data, -1, sizeof(data));
        } else if (i == getTotalBlocksAmount()) {
            writeFsBlock(position, -1, data, sizeof(data));
        }
    }
    setFreeListPointer(1);
    setFreeBlocksAmount(getTotalBlocksAmount());
    readFreeBlocksPortion();
    // Помечаем занятыми блоки, которые заняты самым списком
    for (int i = 0; i < numberBlocksRequired; i++) {
        currentFreeBlocks[i] = -1;
        decreaseFreeBlocksAmount();
    }
    printf("Total: %d Free: %d\n", getTotalBlocksAmount(), getFreeBlocksAmount());
}

int getFreeBlock() {
    int result = -1;
    for (int i = 0; i < getBlockDataSize()/sizeof(int); i++) {
        if (currentFreeBlocks[i] != -1) {
            result = currentFreeBlocks;
            currentFreeBlocks[i] = -1;
        }
    }
    if (result == -1) {
        readFreeBlocksPortion();
    }
    return result;
}

/*
int setBlockFree() {
}
*/

int disposeFreeSpace() {
    free(currentFreeBlocks);
    return 0;
}
