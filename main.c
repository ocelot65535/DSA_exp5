#include "decoder.h"

typedef struct inited_tree{
    HTNode * ht;
    hfmCode * HC;
}inited_tree;

void set_inited_tree(inited_tree * tree, HTNode * ht, hfmCode * HC){
    tree->ht = ht;
    tree->HC = HC;
}

HTNode * get_ht(inited_tree * tree){
    return tree->ht;
}

hfmCode * get_HC(inited_tree * tree){
    return tree->HC;
}

inited_tree tree;

void init(int is_linux);
void encode(int is_linux, inited_tree * tree, int n);
void decode(int is_linux);


int main() {
    int is_linux = 0;
    int is_inited = 0;

    int n = 27;

    if (!is_linux){
        system("chcp 65001");
    }

    printf("请输入操作：\n");
    printf("I:初始化\n");
    printf("C:编码\n");
    printf("D:解码\n");
    printf("E:退出\n");

    char ch;
    ch = getchar();

    while (ch != 'E'){
        if (ch == 'I'){
            init(is_linux);
            is_inited = 1;
            printf("初始化完成\n");
        }
        if (ch == 'C'){
            if (is_inited){
                encode(is_linux, &tree, n);
                printf("编码完成\n");
            }
            printf("请先初始化\n");
        }
        if (ch == 'D'){
            decode(is_linux);
            printf("解码完成\n");
        }


        printf("请输入操作：\n");
        printf("I:初始化\n");
        printf("C:编码\n");
        printf("D:解码\n");
        printf("E:退出\n");

        fflush(stdin);
        ch = getchar();
    }
    printf("感谢使用，再见\n");
    return 0;
}

void init(int is_linux){
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

    set_inited_tree(&tree, ht, HC);
}


void encode(int is_linux, inited_tree * tree, int n){
    HTNode * ht;
    hfmCode HC;

    ht = get_ht(tree);
    HC = get_HC(tree);

    encoder_encode(ht, HC, n, is_linux);
}

void decode(int is_linux){
    decoder_decode(is_linux);
}