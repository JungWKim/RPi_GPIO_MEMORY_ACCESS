#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BUTTER SHOWER");
MODULE_DESCRIPTION("module programming - hello module");

//__init or __initdata(used with data) : 함수나 변수가 운영체제 초기화 과정에만 사용된 후 바로 메모리에서 해제됨 >> 메모리 여유공간 증가
static int module_begin(void) {
    printk("hello, linux kernel module\n");
    return 0;
}

//드라이버 사용이 종료될때각가의종료함수를 부맂 않아도 알아서 메모리에서 제거시킴??
static void module_end(void) {
    printk("good bye!\n");
}

module_init(module_begin);
module_exit(module_end);

//1. 우선 모듈 컴파일하려면 커널 헤더파일이 필요
//2. 하지만 라즈비안엔 커널 헤더파일이 빌드인되지 않았으므로 직접 설치 >> sudo apt install raspberrypi-kernel-headers
//3. -C옵션은 커널헤더파일위치를 가리켜야하는데 위치는 /usr/src/linux-headers-$(uname -r)에 위치
