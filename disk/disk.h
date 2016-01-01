#ifndef DISK_H
#define DISK_H
// Открывает "файл-диск" на чтение-запись, но не создаёт его, если он не существует
int diskOpen(char *path);
// Записывает блок на диск, pos - номер блока от 0, размер блока 4096 байт
int diskWriteBlock(int pos, void *buf);
// Читает блок
int diskReadBlock(int pos, void *buf);
// Закрывает "файл-диск"
int diskClose();
#endif
