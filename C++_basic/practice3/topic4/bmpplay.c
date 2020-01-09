#include "bmpplay.h"

//图片调整后的宽度和长度
static unsigned int bmp_width;
static unsigned int bmp_height;

//refresh_flag:0,不刷新
//1,刷新LCD
int LcdInit (FileInfo *fd, int refresh_flag)
{
    int x = 0;
    int y = 0;
    int black = 0x00000000;

    fd->lcd_fd = open (LCD_PATH, O_RDWR);

    if  (-1 == fd->lcd_fd)
    {
        perror ("LcdInit() open lcd error");
        return -1;
    }
    
    fd->mmap_ptr = (int *)mmap (NULL, LCD_SIZE, PROT_READ
            | PROT_WRITE, MAP_SHARED, fd->lcd_fd, 0);

    if (MAP_FAILED == fd->mmap_ptr)
    {
        perror ("LcdInit() (mmap() ) error");
        return -2;
    }

    //初始化lcd为黑色,图片切换时候,刷屏
    if (refresh_flag)
    {
        for (y = 0; y < Height; y++)
        {
            for (x = 0; x < Width; x++)
            {
                *(fd->mmap_ptr + y*800 + x) = black;
            }
        }
    }
    
    return 0;
}

//初始化bmp
int BmpInit (FileInfo *fd, const char *bmp_path)
{
    fd->bmp_fd = open (bmp_path, O_RDWR);

    if  (-1 == fd->bmp_fd)
    {
        perror ("BmpInit() open bmp error");
        return -1;
    }

    return 0;
}

int ReadBmpInfo (int fd, BITMAPFILEHEADER *fileptr, BITMAPINFOHEADER *infoptr)
{
    int readRet = 0;
    int ret = -1;
    int bmp_fd = fd;
    //注意:这里一定要用unsigned char, 用char会报错
    //怀疑是他们范围不一样的影响
    unsigned char bmp_info[BMP_INFO_SIZE];

    readRet = read (bmp_fd, bmp_info, BMP_INFO_SIZE);
    if (-1 == readRet)
    {
        perror ("ReadBmpInfo() (read() ) error");
        return ret;
    }

    infoptr->biWidth = bmp_info[18] << 0 | bmp_info[19] << 8 | bmp_info[20] << 16
                | bmp_info[21] << 24;
    infoptr->biHeight = bmp_info[22] << 0 | bmp_info[23] << 8 | bmp_info[24] << 16
                | bmp_info[25] << 24;
    
    //调整图片信息，让图片能正确显示在LCD上
    if (infoptr->biWidth < Width && infoptr->biHeight < Height)
    {
        bmp_width = infoptr->biWidth;
        bmp_height = infoptr->biHeight;
        ret = 0;
    }
    else if (infoptr->biWidth < Width && infoptr->biHeight >= Height)
    {
        bmp_width = infoptr->biWidth;
        bmp_height = Height;
        ret = 0;
    }
    else if (infoptr->biWidth >= Width && infoptr->biHeight < Height)
    {
        bmp_width = Width;
        bmp_height = infoptr->biHeight;
        ret = 1;
    }
    else
    {
        bmp_width = Width;
        bmp_height = Height;
        ret = 1;
    }

    //图片真实大小(不含补充的空字节)
    fileptr->bfSize = infoptr->biWidth * infoptr->biHeight * 3;
    
    return ret;
}

char *ReadBmpData (FileInfo fd, BITMAPFILEHEADER *fileptr,BITMAPINFOHEADER *infoptr)
{
    unsigned int y = 0;
    int ret = 0;
    int readRet = 0;
    int readLine = 0;
    int bmp_fd = fd.bmp_fd;
    char * bmp_buf = NULL;
    char * bmp_ptr = NULL;
    unsigned int bmp_size = 0;
    //bmp图片的空字节数
    int space_char;

    //读取图片信息
    ret = ReadBmpInfo (bmp_fd, fileptr, infoptr);
    if (ret < 0)
    {
        printf ("Function ReadBmpData() error!\n");
        exit (-1);
    }

    //bmp图片每一行进行了四字节对齐，在读图片的时候要跳过
    //因为补充的空字节没计算在图片信息（长×宽×3）内
    if (0 != (infoptr->biWidth * 3 % 4))
    {
        space_char = 4 - infoptr->biWidth * 3 % 4;
    }
    else
    {
        space_char = 0;
    }

    //要显示图片的大小, 有可能不是图片的实际大小
    //所以用调整后的图片长宽, 丢掉空字节
    bmp_size = bmp_width * bmp_height * 3;
    bmp_buf = (char *)malloc (bmp_size);
    memset (bmp_buf, 0, bmp_size);
    bmp_ptr = bmp_buf;

    //跳过两个bmp结构体，共54个字节
    //ReadBmpInfo()已经跳过了，所以这里不需要跳过54字节
    //lseek (bmp_fd, BMP_INFO_SIZE, SEEK_SET);

    //每行读取图片的像素数据
    for (y = 0; y < bmp_height; y++)
    {
        readLine = read (bmp_fd, bmp_ptr, bmp_width * 3);
        bmp_ptr += bmp_width * 3;
        if (-1 == readLine)
        {
            perror ("ReadBmpData() (read() ) error");
            return NULL;
        }
        readRet += readLine;
        //图片实际宽度大于LCD width时: 跳过图片每行超出LCD宽度的字节和每行的空字节
        //图片实际宽度小于LCD width时: 跳过图片每行的空字节
        lseek (bmp_fd, (infoptr->biWidth - bmp_width) * 3 + space_char, SEEK_CUR);
    }

    printf ("Read :%d byte\n", readRet);

    return bmp_buf;
}

int  LcdDisplay (FileInfo fd, char *bmp_buf, int offset_x, int offset_y)
{
    unsigned int x = 0;
    unsigned int y = 0;

    for (y = 0; y < bmp_height; y++)
    {
        for (x = 0; x < bmp_width; x++)
        {
            //BGR-->RGB
            *(fd.mmap_ptr + (bmp_height - 1 - y + offset_y)*800 + x + offset_x) =
                                            (bmp_buf[(y * bmp_width + x)*3 + 0] << 0)
                                          | (bmp_buf[(y * bmp_width + x)*3 + 1] << 8)
                                          | (bmp_buf[(y * bmp_width + x)*3 + 2] << 16);
        }
    }
    
    return 0;
}

/*
//random play
void random_play (FileInfo fd, unsigned char * bmp_buf)
{
    int offset_x = 
}
*/

void BmpPlay (const char *bmp_path, FileInfo *fd, show_struct show_struction,\
              BITMAPFILEHEADER *fileptr, BITMAPINFOHEADER *infoptr)
{
    int ret = 0;
    char *bmp_buf = NULL;
    
    //1.初始化lcd
    ret = LcdInit (fd, show_struction.refresh_flag);
    if (-1 == ret)
    {   
        printf ("LcdInit() fault!\n");
        return;
    }

    //2.初始化bmp
    ret = BmpInit(fd, bmp_path);
    if (-1 == ret)
    {
        printf ("BmpInit() fault!\n");
        return;
    }

    //3.读取bmp图片数据,bmp_buf:分配的堆内存首地址
    bmp_buf = ReadBmpData (*fd, fileptr, infoptr);
     
    //4.显示图片
    LcdDisplay (*fd, bmp_buf, show_struction.offset_x, show_struction.offset_y);

    munmap (fd->mmap_ptr, LCD_SIZE);
    close (fd->bmp_fd);
    close (fd->lcd_fd);
}
