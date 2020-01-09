#ifndef _BMPPLAY_H_
#define _BMPPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************Header file *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/***********************************Macro***********************************/
//LCD height
#define Height 480
//LCD width
#define Width 800
//LCD size，一个像素四个字节
#define LCD_SIZE (480*800*4)
//BMP header size
#define BMP_INFO_SIZE 54
//LCD文件路径
#define LCD_PATH "/dev/fb0"

/**********************************Data*************************************/
//文件描述符,内存映射指针
typedef struct fileinfo{
    int bmp_fd;
    int lcd_fd;
    int *mmap_ptr;
}FileInfo;

//BMP图片设置显示方式的结构体
typedef struct show_bmp_struct{
    /*LCDx轴显示位置起点*/
    int offset_x;
    int offset_y;
    //显示下一张BMP图片的时候是否刷掉上一张
    //=1,刷新
    //=0,不刷新
    int refresh_flag;
}show_struct;

//BMP图片相关信息
//BMP文件头信息
typedef struct tagBITMAPFILEHEADER
{
    /*位图文件的类型，必须为BM(1-2字节）*/
    short int bfType;
    /*位图文件的大小，以字节为单位（3-6字节，低位在前）*/
    unsigned int bfSize;
    /*位图文件保留字，必须为0(7-8字节）*/
    short int bfReserved1;
    /*位图文件保留字，必须为0(9-10字节）*/
    short int bfReserved2;
    /*位图数据的起始位置，以相对于位图（11-14字节，低位在前）
    文件头的偏移量表示，以字节为单位*/
    unsigned int bfOffBits;
}__attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    /*本结构所占用字节数（15-18字节）*/
    unsigned int biSize;
    /*位图的宽度，以像素为单位（19-22字节）*/
    long int biWidth;
    /*位图的高度，以像素为单位（23-26字节）*/
    long int biHeight;
    /*目标设备的级别，必须为1(27-28字节）*/
    short int biPlanes;
    /*每个像素所需的位数，必须是1（双色),  4(16色），8(256色 ）
    16(高彩色)或24（真彩色）之一（29-30字节）*/
    short int biBitCount;
    /*位图压缩类型，必须是0（不压缩），
    1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一,（31-34字节）*/
    unsigned int biCompression;
    /*位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，
    以字节为单位（35-38字节）*/
    unsigned int biSizeImage;
    /*位图水平分辨率，每米像素数（39-42字节）*/
    long int biXPelsPerMeter;
    /*位图垂直分辨率，每米像素数（43-46字节)*/
    long int biYPelsPerMeter;
    /*位图实际使用的颜色表中的颜色数（47-50字节）*/
    unsigned int biClrUsed;
    /*位图显示过程中重要的颜色数（51-54字节）*/
    unsigned int biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER;

/************************************Function*************************************/
int LcdInit (FileInfo *fd, int refresh_flag);

int BmpInit (FileInfo *fd, const char *bmp_path);

//读取bmp图片头部信息
int ReadBmpInfo (int fd, BITMAPFILEHEADER *fileptr, BITMAPINFOHEADER *infoptr);

//读取bmp图片像素点数据
char *ReadBmpData (FileInfo fd, BITMAPFILEHEADER *fileptr,BITMAPINFOHEADER *infoptr);

//在LCD上显示BMP图片
int LcdDisplay (FileInfo fd, char *bmp_buf, int offset_x, int offset_y);

//总的BMP图片显示接口
void BmpPlay (const char *bmp_path, FileInfo *fd,show_struct show_struction,\
              BITMAPFILEHEADER *fileptr, BITMAPINFOHEADER *infoptr);

#ifdef __cplusplus
}
#endif
#endif
