#include "thread_pool.h"

static thread_pool *pool = NULL;
struct file_path {
    char src_path[1024];
    char des_path[1024];
};

void *file_copy (void *arg)
{
    int src_fd;
    int des_fd;
    int ret = 0;
    char buf[1024];
    int readRet = 0;
    int writeRet = 0;
    char *tmp = NULL;
    struct file_path *path = (struct file_path *)arg;
    
    printf ("%s %s\n", path->src_path, path->des_path);
    
    src_fd = open (path->src_path, O_RDONLY);
    des_fd = open (path->des_path, O_CREAT | O_TRUNC | O_WRONLY, 00777);
    if (-1 == src_fd || -1 == des_fd)
    {
        ret = -1;
        printf ("Function file_copy() (open() ) error: %d\n", ret);
        return NULL;
    }

    while (1)
    {   
        while (-1 == (readRet = read (src_fd, buf, sizeof(buf))) && 
                EINTR == errno)
        {
            continue;
        }

        if (-1 == readRet)
        {   
            ret = -2;
            printf ("Function file_copy() (read() ) error: %d\n", ret);
            break;
        }
        
        if (0 == readRet)
        {
            puts ("Complete reading.");
            break;
        }
        
        tmp = buf;

        while (readRet > 0)
        {
            while (-1 == (writeRet = write (des_fd, buf, readRet)) &&
                    EINTR == errno)
            {
                continue;
            }
            
            if (-1 == writeRet)
            {
                ret = -3;
                printf ("Function file_copy() (write() ) error: %d\n", ret);
                break;
            }

            readRet = readRet - writeRet;
            tmp = tmp + writeRet;
        }

        if (-1 == writeRet)
        {
            break;
        }
    }
  
    free (path);
    path = NULL;
    close (src_fd);
    close (des_fd);
}

//查找文件
int dir_test (char * dirname, char * desdirname)
{
    int ret = 0;
    DIR * dir = NULL;
    struct dirent * dirs;
    char dirname1[1024];
    char desdirname1[1024];

    sprintf (dirname1, "%s" , dirname);
    sprintf (desdirname1, "%s" , desdirname);

    dir = opendir (dirname1);
    if (NULL == dir)
    {
        ret = -1;
        printf ("Function dir_test() (opendir() ) error: %d\n", ret);
        return ret;
    }

    while (1)
    {
        dirs = readdir (dir);
        if (NULL == dirs)
        {
            //perror ("read error");
            break;
        }

        if (DT_DIR == dirs->d_type)
        {
            if (0 == strcmp (".", dirs->d_name) || 0 == strcmp ("..", dirs->d_name))
            {
                continue;
            }

            sprintf (dirname1, "%s/%s", dirname,dirs->d_name);
            sprintf (desdirname1, "%s/%s", desdirname,dirs->d_name);
            mkdir (desdirname1 ,0777);
            dir_test (dirname1, desdirname1);
        }
        else if (DT_REG == dirs->d_type)
        {
            struct file_path * path = (struct file_path *)malloc (sizeof(struct file_path));
            
            sprintf (path->src_path, "%s/%s", dirname, dirs->d_name); 
            sprintf (path->des_path, "%s/%s", desdirname, dirs->d_name);
            
	        // 2, throw tasks
            add_task(pool, file_copy, (void *)path);
        }
    }

    return ret;
}

void *find (void *arg)
{
    char *dirname = "/home/linux/bmp";
    char *desdirname = "/home/linux/test"; 
    //mkdir (desdirname ,0777);

    dir_test (dirname, desdirname);
}

int main(void)
{
	pthread_t a;

	// 1, initialize the pool
	pool = malloc(sizeof(thread_pool));
	init_pool(pool, 2);

	pthread_create(&a, NULL, find, NULL);

	// 3, check active threads number
	printf("current thread number: %d\n",
			remove_thread(pool, 0));

	// 5, add threads
	add_thread(pool, 10);

	// 6, remove threads
	//printf("remove 3 threads from the pool, "
	//       "current thread number: %d\n",
	//		remove_thread(pool, 3));

	// 7, destroy the pool
	destroy_pool(pool);
	
    //return 0;
}

