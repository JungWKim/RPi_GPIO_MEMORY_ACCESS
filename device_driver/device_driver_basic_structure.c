#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>

int device_open()
{

}

int device_release()
{

}

//과거 int가 16비트였다가 현재 32비트로 증가했을때처럼, 나중에 primitive자료형의 바이트크기가 변할때 시스템의 소스코드변경없이 헤더파일들을 재사용할 수 있게 ssize_t와 같이 재정의한 것이다.
//
// size_t : unsigned int
// ssize_t : signed int
// pid_t : process id
//
ssize_t device_read()
{

}

ssize_t device_write()
{

}

static struct file_operations device_fops = {
    .open=device_open,
    .release=device_release,
    .read=device_read,
    .write=device_write
}

//void 생략하면 안됨
static int init_func(void)
{
    return 0;
}

static void exit_func(void)
{

}

module_init(init_func);
module_exit(exit_func);
