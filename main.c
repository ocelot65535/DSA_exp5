#include "hfmtree.h"
int main() {
    /* 测试数据*/
    /* char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     * 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}*/
    /* int weight[] = {'186', '64', '13', '22', '32', '103', '21', '15', '47', '57', '1', '5',
     * '32', '20', '57', '63', '15', '1', '48', '51', '80', '23', '8', '18', '1', '16', '1'}*/
    char character[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                        'I', 'J', 'K', 'L', 'M','N', 'O', 'P',
                        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                        'Y', 'Z'};
    struct SeqList list[MAXSIZE_LIST];
    initSqList(list, character);
    //这里没分配内存，可能空指针了

}
