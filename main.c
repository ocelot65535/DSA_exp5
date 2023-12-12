#include "initMenu.h"

typedef struct inited_tree{
    HTNode * ht;
    hfmCode HC;
}inited_tree;

HTNode * get_ht(inited_tree * tree){
    return tree->ht;
}

hfmCode get_HC(inited_tree * tree){
    return tree->HC;
}

void init(int is_linux, inited_tree * tree, int is_testing);

void encode(int is_linux, inited_tree * tree, int n);

void decode(int is_linux);

void print_codefile(int is_linux);

void printHTree(HTNode *ht, int index, int depth);


int main() {
    int is_linux = 0;
    int is_inited = 0;
    int is_testing = 1;

    int n = 27;

    inited_tree * tree;
    tree = malloc(sizeof (inited_tree));

    if (!is_linux){
        system("chcp 65001");
    }


    init_deleteCache(is_linux);

    printf("请输入操作：\n");
    printf("I:初始化\n");
    printf("C:编码\n");
    printf("D:解码\n");
    printf("P:打印编码文件\n");
    printf("T:打印哈夫曼树\n");
    printf("E:退出\n");

    char ch;
    ch = getchar();
//    ch = 'I';
    while (ch != 'E'){
        if (ch == 'I'){
            init(is_linux, tree, is_testing);
            is_inited = 1;
            printf("初始化完成\n");
        }
        if (ch == 'C'){
            if (is_inited){
                encode(is_linux, tree, n);
                printf("编码完成\n");
            }
            else{
                init(is_linux, tree, is_testing);
                is_inited = 1;
                encode(is_linux, tree, n);
                printf("编码完成\n");
            }
        }
        if (ch == 'D'){
            decode(is_linux);
            printf("解码完成\n");
        }
        if (ch == 'P'){
            print_codefile(is_linux);
        }
        if (ch == 'T'){
            if (is_inited){
                printHTree(tree->ht,1,0);
            } else{
                printf("请先初始化\n");
            }
        }


        printf("请输入操作：\n");
        printf("I:初始化\n");
        printf("C:编码\n");
        printf("D:解码\n");
        printf("P:打印编码文件\n");
        printf("T:打印哈夫曼树\n");
        printf("E:退出\n");


        fflush(stdin);
        ch = getchar();
//        ch = 'T';
    }
    printf("感谢使用，再见\n");
    return 0;
}

void init(int is_linux, inited_tree * tree, int is_testing){
    /* 测试数据*/
    /* char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     * 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}*/
    /* int weight[] = {'186', '64', '13', '22', '32', '103', '21', '15', '47', '57', '1', '5',
     * '32', '20', '57', '63', '15', '1', '48', '51', '80', '23', '8', '18', '1', '16', '1'}*/

    if (is_testing){
        char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                            'I', 'J', 'K', 'L', 'M','N', 'O', 'P',
                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z'};
        int weight[] = {186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5,
                        32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1};
        int n = 27;
        int m ;
        m = 2*n -1;
        SqList list[n];
        HTNode ht[m+1];
        hfmCode HC; // 存放编码结果


        init_deleteCache(is_linux);
        // 存放待编码字符与权重
        init_SqList(&list, character);

        init_initTree(ht, n, weight, character);
        init_get_hfmcode(ht, &HC, n);


        for (int i = 1; i <= n; i++)
        {
            init_save_codefile(ht[i].character, HC[i], is_linux);
        }
        tree->ht = malloc(sizeof (HTNode) * (m+1));
        tree->ht = ht;
        tree->HC = malloc(sizeof (hfmCode) * (n + 1));
        tree->HC = HC;
    }else{
        int n ;
        printf("请输入待编码字母个数");
        scanf("%d", &n);
        getchar();
        struct C_W array;
        // 从终端读取字母与权重
        array = function(n);
        int m ;
        m = 2*n -1;
        SqList list[n];
        HTNode ht[m+1];
        hfmCode HC; // 存放编码结果


        init_deleteCache(is_linux);
        // 存放待编码字符与权重
        init_SqList(&list, array.c);

        init_initTree(ht, n, array.w, array.c);
        init_get_hfmcode(ht, &HC, n);


        for (int i = 1; i <= n; i++)
        {
            init_save_codefile(ht[i].character, HC[i], is_linux);
        }
        tree->ht = malloc(sizeof (HTNode) * (m+1));
        tree->ht = ht;
        tree->HC = malloc(sizeof (hfmCode) * (n + 1));
        tree->HC = HC;
    }
}

void encode(int is_linux, inited_tree * tree, int n){
    encoder_encode(tree->ht, tree->HC, n, is_linux);
}

void decode(int is_linux){
    decoder_decode(is_linux);
}

void print_codefile(int is_linux){
    FILE * codefile;
    char line_buffer[1024];
    char * filepath = "..\\codefile";
    if (is_linux){
        filepath = "../codefile";
    }
    codefile = fopen(filepath, "r");
    if (codefile == NULL){
        printf("codefile打开失败");
        exit(-1);
    }
    int index = 0;
    char ch;
    while ((ch = fgetc(codefile)) != ';'){
        if (index == 50){
            printf("\n");
            index = 0;
        }
        printf("%c", ch);
        index++;
    }
    printf("\n");
}

void printHTree(HTNode *ht, int index, int depth) {
    if (index == 0) {
        return;
    }
    printHTree(ht, ht[index].RChild, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (ht[index].LChild == 0 && ht[index].RChild == 0) {
        printf("%c (%d)\n", ht[index].character, ht[index].weight);
    } else {
        printf("* (%d)\n", ht[index].weight);
    }
    printHTree(ht, ht[index].LChild, depth + 1);
}
