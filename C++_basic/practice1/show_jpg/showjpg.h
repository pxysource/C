#ifndef _SHOWJPG_H_
#define _SHOWJPG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "jpeglib.h"

/*********************************Macro**********************************/
#define LCD_DEV 		"/dev/fb0"
#define LCD_H  			480
#define LCD_W   		800
#define LCD_SIZE_BIT 	(480*800*4)
#define MIN(x,y)		((x) <= (y) ? (x) : (y))

/************************************************************************/
typedef struct _tag_show_jpg{
    int lcd_fd;
    int jpg_fd;
    int jpg_size;
    int offset_x;
    int offset_y;
    int *mmap_ptr;
    const char *jpg_path;
}show_jpg_struct;

/*********************************Function*******************************/
/*
 * @brief:	show jpg on LCD(800*480)
 * @param:	jpg_path, jpg图片的完整路径
 * 			refresh, 显示多张图片的方式，1，刷掉前一张；0，不刷掉前一张图片
 * 			offset_x, 显示在LCD的哪个位置
 * 			offset_y, 显示在LCD的哪个位置
 * @rtv:	int, 返回一些可能遇到的错误号
 **/
int Play_Jpg (const char *jpg_path, int refresh, int offset_x, int offset_y);

#ifdef __cplusplus
}
#endif

#endif
