#include "initTree.h"

void init_SqList(SqList *list, char c[]){
    for(int i = 0; i <= MAXSIZE_LIST;i++){
        (*list)[i].data = 0;
        (*list)[i].name = c[i];
    }
}

void init_select(HTree HT, int end, int *m1, int *m2){
    int i = 1;
    // 定义两个最小值的区间范围
    int min1 = 0;
    int min2 = 0;
    /*遍历哈夫曼数组，将没双亲的取出来*/
    while (HT[i].parent != 0&&i<=end){
        i++;
    }
    min1 = HT[i].weight;
    *m1 = i;
    i++;
    while (HT[i].parent != 0&&i<=end){
        i++;
    }
    min2 = HT[i].weight;
    *m2 = i;
    /*规定m1始终为最小的，m2始终比m1大*/
    if(min1>HT[i].weight){
        *m2 = *m1;
        *m1 = i;
        min2 = min1;
        min1 = HT[i].weight;
    }
    /*遍历剩下的节点*/
    for(int j = i+1;j <= end; j++){
        // 如果有遍历节点有双亲则跳过这个节点遍历下一个
        if(HT[j].parent != 0){
            continue;
        }
        /*三种情况，落到区间左侧，落到区间右侧，落到区间内*/
        if(HT[j].weight <= min1){
            min2 = min1;
            min1 = HT[j].weight;
            *m2 = *m1;
            *m1 = j;
        } else if(HT[j].weight > min1 && HT[j].weight < min2){
            min2 = HT[j].weight;
            *m2 = j;
        } else if(HT[j].weight > min2){
            continue;
        }
    }
}

// 根据叶子节点个数初始化哈夫曼树
void init_initTree(HTNode *ht, int n, int w[], char c[]){
    int m ;
    m = 2*n -1;

    // 初始化叶子节点，并且赋予其权重
    for(int i = 1; i<= n; i++){
        ht[i].weight = w[i - 1];
        ht[i].character = c[i - 1];
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }

    //初始化非叶子节点
    for(int i = n+1; i<=m; i++) {
        ht[i].weight = 0;
        ht[i].character = 0;
        ht[i].parent = 0;
        ht[i].LChild = 0;
        ht[i].RChild = 0;
    }
    for(int i = n+1; i<=m; i++){
        int min1 = 0, min2 = 0;
        init_select(ht, i - 1, &min1, &min2);
        ht[min1].parent = i;
        ht[min2].parent = i;
        ht[i].LChild = min1;
        ht[i].RChild = min2;
        ht[i].weight = ht[min1].weight + ht[min2].weight;
    }

    printf("哈夫曼树构造完成");

}

void init_get_hfmcode(HTNode *Ht, hfmCode **HC, int n) {
    *HC = (hfmCode*) malloc(sizeof(hfmCode) * (n + 1));

    char *cd = (char*) malloc(sizeof(char) * n);
    int start = 0;
    int c = 0;
    int f = 0; // 存放双亲
    cd[n-1] = '\0';

    for (int i = 1; i <= n; i++) {
        c = i;
        start = n - 1;
        f = Ht[i].parent; // 判断双亲，找根节
        while (f != 0) {
            start--;
            if (Ht[f].LChild == c) {
                cd[start] = '0';
            } else {
                cd[start] = '1';
            }
            c = f;
            f = Ht[c].parent;
        }

        (*HC)[i] = (char*)malloc(sizeof(char) * (n - start));
        strcpy((*HC)[i], &cd[start]);
    }
    free(cd);
}

void init_save_codefile(char ch, char* code, int is_linux){
    FILE *fp;
    char * filepath = ".\\hfmtree";
    if (is_linux)
        filepath = "../hfmtree";

    fp = fopen(filepath, "a+");
    if (fp == NULL){
        printf("打开文件失败");
        exit(0);
    }

    fprintf(fp, "%c:%s\n", ch, code);

    fclose(fp);
}

void init_deleteCache(int is_linux){
    FILE * hfmtree;
    FILE * codefile;
    FILE * textfile;

    char * hfmtree_path = ".\\hfmtree";
    char * codefile_path = "..\\codefile";
    char * textfile_path = "..\\textfile";

    if (is_linux){
        hfmtree_path = "../hfmtree";
        codefile_path = "../codefile";
        textfile_path = "../textfile";
    }

    hfmtree = fopen(hfmtree_path, "w");
    codefile = fopen(codefile_path,"w");
    textfile = fopen(textfile_path, "w");

    fclose(hfmtree);
    fclose(codefile);
    fclose(textfile);
}