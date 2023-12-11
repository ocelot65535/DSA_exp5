//
// Created by 30544 on 2023/12/5.
//
#ifndef ITEM_5_HUFFMAN_HFMTREE_H
#define ITEM_5_HUFFMAN_HFMTREE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE_LIST 27
// 节点类型定义
typedef struct HTNode{
    // 存放权值以及左右孩子指向双亲的指针
    int weight;
    char character;
    int parent, LChild, RChild;
}HTNode, *HTree;

// 定义静态顺序表来存放每个字符对应的
typedef struct SeqList{
    int data;
    char name;
}SqList[MAXSIZE_LIST];

// 指向指针的指针
typedef char **hfmCode;
//--------------------------------------------------------------------------------//

// 初始化顺序表操作
void init_SqList(SqList *list, char c[]);

// 定义select函数来寻找最小值
/*向select函数传入哈夫曼数组， 传入待遍历叶子节点的个数，定义*m1, *m2传入实参地址 */
void init_select(HTree HT, int end, int *m1, int *m2);

// 初始化哈夫曼树，根据定义：一颗有n个叶子的哈夫曼树共有2n-1个节点
void init_initTree(HTNode *ht, int n, int w[], char c[]);

// 使用已经构造好的哈夫曼树来求编码
void init_get_hfmcode(HTNode *Ht, hfmCode **HC, int n);

// 储存编码结果
void init_save_codefile(char ch, char* code, int is_linux);

void init_deleteCache(int is_linux);


#endif //ITEM_5_HUFFMAN_HFMTREE_H

