#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H
struct SuperBlock {
    int maxDataAmount;  // Максимальное количество данных, которое может вместить один блок (байт)
    int totalBlocksAmount;  // Общее количество блоков в системе (не считая суперблок)
    int freeBlocksAmount;  // Количество свободных блоков в системе
    int freeListPointer;  // Указатель на первый блок списка пустых блоков
    int rootDirPointer;  // Указатель на первый блок корневого каталога
};

// Создать супер блок (размер диска(раздела), размер блока)
struct SuperBlock *getSuperBlock();
int createSuperBlock(int diskSize, int blockSize);
int getTotalBlocksAmount();
int getFreeBlocksAmount();
int setFreeBlocksAmount(int newAmount);
int increaseFreeBlocksAmount();
int decreaseFreeBlocksAmount();
int getFreeListPointer();
int setFreeListPointer(int pointer);
int getMaxDataAmount();
#endif
