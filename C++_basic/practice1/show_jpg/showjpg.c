#include "showjpg.h"

static int Lcd_Init (show_jpg_struct *ptr, const char *jpg_path, int refresh)
{
    int x = 0;
    int y = 0;
    int black = 0x00000000;

    ptr->lcd_fd = open (LCD_DEV, O_RDWR);
    ptr->jpg_fd = open (jpg_path, O_RDONLY);

    if (-1 == ptr->lcd_fd || -1 == ptr->jpg_fd)
    {
        puts ("Function Lcd_Init() (open() ) error!");
        return -1;
    }
    
    //注意:映射的时候指针指向的是一个像素, 一个像素是四个字节, 
    //所以mmap_ptr指向的是int类型, 而不是char或则其他类型。
    ptr->mmap_ptr = (int *)mmap (NULL, LCD_SIZE_BIT, PROT_READ | PROT_WRITE,
            MAP_SHARED, ptr->lcd_fd, 0);
    if (MAP_FAILED == ptr->mmap_ptr)
    {
        puts ("Function Lcd_Init() (mmap() ) error!");
        return -2;
    }

    //刷新
    if (refresh)
    {
        for (y = 0; y < LCD_H; y++)
        {
            for (x = 0; x < LCD_W; x++)
            {
                *(ptr->mmap_ptr + y * LCD_W + x) = black;
            }
        }
    }

    //jpg图片的路径正确, 放入show_jpg的结构体中
    ptr->jpg_path = jpg_path;

    return 0;
}

//获取jpg文件的大小
static long Get_JpgSize (const char *jpg_path)
{
    long jpg_size = 0;
    struct stat statbuf;
    int statRet = 0;

    statRet = stat (jpg_path, &statbuf);
    if (-1 == statRet)
    {
        puts ("Function Get_JpgSize() (stat() ) error!");
        return -1;
    }
    else if (0 == statRet)
    {
        jpg_size = statbuf.st_size;
    }

    if (jpg_size < 3000)
    {
        puts ("Function Get_JpgSize() error: jpg size error!");
        return -2;
    }
    
    return jpg_size;
}

//显示jpg图片
static int Show_Jpg (show_jpg_struct show_jpg)
{
    int x = 0;
    int y = 0;
    unsigned int realWidth = 0;
    unsigned int realHeight = 0;
    unsigned int i = 0;
    int color = 0;
    //定义解码结构体,出错处理结构体
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr         jerr;
    unsigned char *jpg_ptr = NULL;
    
    jpg_ptr = (unsigned char *)malloc (show_jpg.jpg_size);
    read (show_jpg.jpg_fd, jpg_ptr, show_jpg.jpg_size);

    //注册出错处理
    cinfo.err = jpeg_std_error (&jerr);
    //创建解码
    jpeg_create_decompress (&cinfo);
    //直接解码内存数据
    jpeg_mem_src (&cinfo, jpg_ptr, show_jpg.jpg_size);
    //读文件头
    jpeg_read_header (&cinfo, TRUE);
    //开始解码
    jpeg_start_decompress (&cinfo);

    unsigned char color_buf[cinfo.output_width];
    unsigned char *ptr = NULL;
    x = show_jpg.offset_x;
    y = show_jpg.offset_y;
    realWidth = MIN(cinfo.output_height,LCD_W) - x;
    realHeight = MIN(cinfo.output_height,LCD_H) - y;

    //读取解码数据，图片有可能大于LCD，也可能小于LCD，大于部分不显示
    while (cinfo.output_scanline < realHeight)
    {
        bzero(color_buf, sizeof(color_buf));
        ptr = color_buf;

        //读取jpg一行的rgb值
        jpeg_read_scanlines (&cinfo, &ptr, 1);

        for (i = 0; i < realWidth; i++)
        {
            color  = *(ptr + 2);
            color |= *(ptr + 1) << 8;
            color |= *ptr << 16;

            //显示像素点
            *(show_jpg.mmap_ptr + LCD_W * y + x) = color;
            ptr += 3;

            x++;
        }

        //换行
        y++;
        x = show_jpg.offset_x;
    }

    //解码完成
    jpeg_finish_decompress (&cinfo);
    jpeg_destroy_decompress (&cinfo);

    if (NULL != jpg_ptr)
    {
        free (jpg_ptr);
        jpg_ptr = NULL;
    }
    
    return 0;
}

int Play_Jpg (const char *jpg_path, int refresh, int offset_x, int offset_y)
{
    int ret = 0;
    show_jpg_struct show_jpg;
    bzero (&show_jpg, sizeof(show_jpg_struct));

    if ((offset_x >= 0 && offset_x < 800) &&
        (offset_y >= 0 && offset_y < 480))
    {
        show_jpg.offset_x = offset_x;
        show_jpg.offset_y = offset_y;
    }
    else
    {
        puts ("offset error!");
        return -1;
    }

    //1.初始化lcd
    ret = Lcd_Init (&show_jpg, jpg_path, refresh);
    if (ret < 0)
    {
        ret = -2;
        puts ("Lcd_Init() error!");
        goto exit;
    }

    //2.获取jpg图片的大小
    ret = Get_JpgSize (jpg_path);
    if (ret < 0)
    {
        ret = -3;
        puts ("Get_JpgSize() error!");
        goto exit;
    }
    show_jpg.jpg_size = ret;

    //3.显示图片
    Show_Jpg (show_jpg);

exit:
    //关闭打开的文件,释放映射的内存
    close (show_jpg.lcd_fd);
    close (show_jpg.jpg_fd);
    munmap (show_jpg.mmap_ptr, LCD_SIZE_BIT);

    return ret;
}
