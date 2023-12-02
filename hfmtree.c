#include "hfmtree.h"

void initSqList(SqList *list, char c[]){
    for(int i = 0; i <= MAXSIZE_LIST;i++){
        (*list[i]).data = 0;
        (*list[i]).name = c[i];
    }
}

/* 项目数据*/
/* char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}*/
/* int weight[] = {'186', '64', '13', '22', '32', '103', '21', '15', '47', '57', '1', '5', '32', '20', '57', '63', '15', '1', '48', '51', '80', '23', '8', '18', '1', '16', '1'}*/
void select(HTree HT, int end, int *m1, int *m2){
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
        if(HT[j].parent == 0){
            continue;
        }
        /*三种情况，落到区间左侧，落到区间右侧，落到区间内*/
        if(HT[j].weight < min1){
            min1 = HT[j].weight;
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
void initTree(HTree *ht, int n, int w[], char c[]){
    int m ;
    m = 2*n -1;
    // 创建节点
    *ht = (HTree)malloc((m+1)* sizeof (HTNode));

    // 初始化叶子节点，并且赋予其权重
    for(int i = 1; i<= n; i++){
        (*ht)[i].weight = w[i - 1];
        (*ht)[i].character = c[i - 1];
        (*ht)[i].parent = 0;
        (*ht)[i].LChild = 0;
        (*ht)[i].RChild = 0;
    }

    //初始化非叶子节点
    for(int i = n+1; i<=m; i++) {
        (*ht)[i].weight = 0;
        (*ht)[i].character = 0;
        (*ht)[i].parent = 0;
        (*ht)[i].LChild = 0;
        (*ht)[i].RChild = 0;
    }
    for(int i = n+1; i<=m; i++){
        int *min1 = NULL, *min2 = NULL;
        select(ht, i-1, min1, min2);
        (*ht)[*min1].parent = i;
        (*ht)[*min2].parent = i;
        (*ht)[i].LChild = *min1;
        (*ht)[i].RChild = *min2;
        (*ht)[i].weight = (*ht)[*min1].weight + (*ht)[*min2].weight;
    }
    printf("哈夫曼树构造完成");

}

void get_code(SqList *list, HTree *ht, char c[]){
    // 遍历待编码字符
    for(int i = 0; i<=25;i++){
        if((*list[i]).name == (*ht)->character){
            // 如果作为左子树，则置为0
            // 如果作为右子树，则置为1
            // 因为是从叶子节点逆序寻找根节点，使用临时静态栈对其进行存储
            // 待最后寻找到根节点，将临时静态栈数据依次弹出，并将其保存到顺序表中的data
        }
    }

}