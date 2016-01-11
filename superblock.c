#include <string.h>
#include <stdio.h> //

#include "superblock.h"

#include "common.h"
#include "disk.h"

static struct SuperBlock superBlock;

int writeSuperBlock() {
    byte tmp[4096];
    memset(tmp, 0, sizeof(tmp));
    memcpy(tmp, &superBlock, sizeof(struct SuperBlock));
    if (diskWriteBlock(0, tmp) != 0)
        return -1;
    return 0;
}

int readSuperBlock() {
    byte tmp[4096];
    if (diskReadBlock(0, tmp) != 0)
        return -1;
    memcpy(&superBlock, tmp, sizeof(struct SuperBlock));
    return 0;
}

struct SuperBlock *getSuperBlock() {
    return &superBlock;
}

int createSuperBlock(int diskSize, int blockSize) {
    memset(&superBlock, 0, sizeof(superBlock));
    // Устанавливаем указанный размер блока, минус место под указатель в каждом блоке
    superBlock.maxDataAmount = blockSize-sizeof(int);
    // Общее количество блоков, минус суперблок
    superBlock.totalBlocksAmount = diskSize/blockSize-1;
    if (writeSuperBlock() != 0)
        return -1;
    return 0;
}

int getTotalBlocksAmount() {
    return superBlock.totalBlocksAmount;
}

int getFreeBlocksAmount() {
    return superBlock.freeBlocksAmount;
}

int setFreeBlocksAmount(int newAmount) {
    superBlock.freeBlocksAmount = newAmount;
    if (writeSuperBlock() != 0)
        return -1;
    return 0;
}

int increaseFreeBlocksAmount() {
    superBlock.freeBlocksAmount++;
    return 0;
}

int decreaseFreeBlocksAmount() {
    superBlock.freeBlocksAmount--;
    return 0;
}

int getFreeListPointer() {
    return superBlock.freeListPointer;
}

int setFreeListPointer(int pointer) {
    superBlock.freeListPointer = pointer;
    if (writeSuperBlock() != 0)
        return -1;
    return 0;
}

int getMaxDataAmount() {
    return superBlock.maxDataAmount;
}
