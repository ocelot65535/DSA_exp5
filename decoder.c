#include "decoder.h"

char2code * decoder_initList(){
    char2code * head = malloc(sizeof (char2code));

    head->character = '?';
    head->code = malloc(sizeof("NaN"));
    head->code = "NaN";
    head->length =0;
    head->next = NULL;

    return head;
}

void decoder_addnode(char2code * head, char ch, char * code, int length){
    char2code * newnode = malloc(sizeof (char2code));

    newnode->length = length;
    newnode->character = ch;

    newnode->code = malloc(sizeof(code));
    strcpy(newnode->code, code);
    newnode->next = NULL;

    char2code * ptr = head;
    while (ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = newnode;
    head->length++;
}

char2code * decoder_parsing_file(int is_linux){
    FILE * hfmtree;
    char line_buffer[64];
    char2code * head = decoder_initList();

    char * filepath = "..\\hfmtree";
    if (is_linux){
        filepath = "../hfmtree";
    }

    hfmtree = fopen(filepath, "r");
    if (hfmtree == NULL){
        printf("哈夫曼树打开失败");
        exit(-1);
    }

    while (fgets(line_buffer, sizeof (line_buffer), hfmtree)){
        char ch =line_buffer[0];

        int size = 0;
        for (int i=0;i < strlen(line_buffer);i++){
            char code_01 = line_buffer[i];
            if (code_01 == '0' || code_01 == '1')
                size++;
            if (code_01 == ';')
                break;
        }
        char code[size + 1];

        strncpy(code, line_buffer + 2, size);
        code[size] = '\0';

        decoder_addnode(head,ch,code, (int)size);
    }
    return head;
}

void decoder_decode(int is_linux){
    FILE * codefile;
    FILE * textfile;

    char found_character;
    char buffer[20];
    memset(buffer, 0, sizeof (buffer));
    char2code * head = decoder_parsing_file(is_linux);
    printf("成功读入哈夫曼树\n");
    char line_buffer[1024];

    char * filepath = "..\\codefile";
    char * textpath = "..\\textfile";
    if (is_linux)
        filepath = "../codefile";
    if (is_linux)
        textpath = "../textfile";

    codefile = fopen(filepath, "r");
    textfile = fopen(textpath, "w");
    if (codefile == NULL){
        printf("codefile打开失败");
        exit(-1);
    }
    if (textfile == NULL){
        printf("textfile打开失败");
        exit(-1);
    }

    int start = 0;
    int last;
    fgets(line_buffer,sizeof(line_buffer), codefile);
    char chara;
    for (last = 0;last < sizeof (line_buffer); last++){
        chara = line_buffer[last];
        if (chara == ';')
            break;
    }
    int end=0;
    while (end <= last){
        end++;
        int size = end - start;
        char text[size];
        text[size] = '\0';
        strncpy(text,line_buffer + start, size);

        found_character = decoder_sreach_code(head,text);
        if (found_character != '@'){
            fputc(found_character,textfile);
            printf("向文件中输出了一个%c\n", found_character);
            start = end;
            end ++;
        } else{
            continue;
        }
    }
    fclose(codefile);
    fclose(textfile);
}

char decoder_sreach_code(char2code * head, char * string){
    printf("正在搜索%s\n", string);
    char2code * ptr = head;
    while (ptr->next != NULL){
        ptr = ptr->next;
        if (!strcmp(string, ptr->code))
            return ptr->character;
    }
    return '@';
}