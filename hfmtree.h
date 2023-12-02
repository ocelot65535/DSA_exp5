#ifndef ITEM_5_HUFFMAN_HFMTREE_H
#define ITEM_5_HUFFMAN_HFMTREE_H
#include <malloc.h>
#include <stdio.h>

#define MAXSIZE_LIST 25
// 节点类型定义
typedef struct HTNode{
    // 存放权值以及左右孩子指向双亲的指针
    int weight;
    char character;
    int parent, LChild, RChild;
}HTNode, *HTree;

// 定义静态栈来存储每个字符的哈夫曼编码


// 定义静态顺序表来存放每个字符对应的
typedef struct SeqList{
    int data;
    char name;
}SqList[MAXSIZE_LIST];

// 初始化顺序表操作
void initSqList(SqList *list,  char c[]);

// 定义select函数来寻找最小值
/*向select函数传入哈夫曼数组， 传入待遍历叶子节点的个数，定义*m1, *m2传入实参地址 */
void select(HTree HT, int end, int *m1, int *m2);

// 初始化哈夫曼树，根据定义：一颗有n个叶子的哈夫曼树共有2n-1个节点
void initTree(HTree *ht, int n, int w[], char c[]);

// 使用已经构造好的哈夫曼树来求编码
void get_code(SqList *list, HTree *ht, char c[]);


#endif //ITEM_5_HUFFMAN_HFMTREE_H


