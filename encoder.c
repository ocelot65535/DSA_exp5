#include "encoder.h"


void encoder_readTree(){
    //读取建立好的哈夫曼树
}

int encoder_search(char ch, HTNode * charlist, int n){
    for (int i = 1;i <= n;i++){
        if (ch == charlist[i].character){
            return i;
        }
    }
    return -1;
}

void encoder_encode(HTNode * charlist, hfmCode code, int n, int is_linux){
    //读取需要编码的文件
    char ch;
    char * string;
    FILE * source;
    FILE * target;
    char * sourcepath = "..\\tobetrans";
    char * targetpath = "..\\codefile";

    if (is_linux){
        sourcepath = "../tobetrans";
        targetpath = "../codefile";

    }

    source = fopen(sourcepath, "r");
    target = fopen(targetpath, "a");

    if (source == NULL){
        printf("tobetrans打开文件失败");
        exit(0);
    }
    if (target == NULL){
        printf("codefile打开文件失败");
        exit(0);
    }

    while ((ch = fgetc(source)) != EOF){
        //查找字幕在表中的位置
        int index = encoder_search(ch, charlist, n);
        //将编码写入到文件中
        if (index != -1){
            string = code[index];
            fprintf(target, "%s", string);
        }
    }
    fprintf(target, ";");
    printf("\n编码完成\n");
    fclose(source);
    fclose(target);
}