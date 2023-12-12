#include "decoder.h"
#include "initMenu.h"

int main() {
    int is_linux = 1;
    if (!is_linux){
        system("chcp 65001");
    }
    /* 测试数据*/
    /* char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     * 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}*/
    /* int weight[] = {'186', '64', '13', '22', '32', '103', '21', '15', '47', '57', '1', '5',
     * '32', '20', '57', '63', '15', '1', '48', '51', '80', '23', '8', '18', '1', '16', '1'}*/

    char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                        'I', 'J', 'K', 'L', 'M','N', 'O', 'P',
                        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                        'Y', 'Z'};
    int weight[] = {186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5,
                    32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1};

    int n ;
    printf("请输入待编码字母个数");
    scanf("%d", &n);
    getchar();
    struct C_W array;
    array = function(n);// 从终端读取字母与权重
    int m ;
    m = 2*n -1;
    SqList list[n];
    HTNode ht[m+1];
    hfmCode HC; // 存放编码结果

    init_deleteCache(is_linux);

    // 存放待编码字符与权重
    init_SqList(&list, array.c, n);

    init_initTree(ht, n, array.w, array.c);
    init_get_hfmcode(ht, &HC, n);


    //为什么第一个还是从1开始。。。。
    // 星答：舍弃了第1位数组元素，下标从1开始
    for (int i = 1; i <= n; i++)
    {
        init_save_codefile(ht[i].character, HC[i], is_linux);
    }
    encoder_encode(ht, HC, n, is_linux);

    decoder_decode(is_linux);
    return 0;
}