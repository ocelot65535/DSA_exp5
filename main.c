#include "decoder.h"
int main() {
    int is_linux = 0;
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

    int n = 27;
    int m ;
    m = 2*n -1;
    SqList list;
    HTNode ht[m+1];
    hfmCode HC; // 存放编码结果

    init_deleteCache(is_linux);

    // 存放待编码字符与权重
    init_SqList(&list, character);

    init_initTree(ht, n, weight, character);
    init_get_hfmcode(ht, &HC, n);


    //为什么第一个还是从1开始。。。。
    for (int i = 1; i <= n; i++)
    {
        init_save_codefile(ht[i].character, HC[i], is_linux);
    }
    encoder_encode(ht, HC, n, is_linux);

    decoder_decode(is_linux);
    return 0;
}