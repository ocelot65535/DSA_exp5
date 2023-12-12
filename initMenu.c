#include "initMenu.h"
#define CLEAR_BUF \
    {\
    int ch; \
while ((ch = getchar()) != EOF && ch != '\n')\
        {\
        ; \
        }\
    }
#include "initMenu.h"

struct C_W function(int n){
    struct C_W array;
    for (int i = 0; i < n; ++i) {
        printf("请输入代编码字母:");
        scanf("%c", &array.c[i]);
        CLEAR_BUF
        printf("请输入权重:");
        scanf("%d", &array.w[i]);
        CLEAR_BUF
    }
    return array;
}
