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
    strcat(newnode->code, code);
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

    regex_t regex;
    regmatch_t match[3];
    int reti = regcomp(&regex, "(^[A-Z]:| :)[01]+$",REG_EXTENDED);

    if (reti){
        fprintf(stderr, "正则表达式编译不成功");
        exit(-1);
    }

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
        if (regexec(&regex, line_buffer, 1, match, 0)){
            char ch =line_buffer[match[1].rm_so];

            int size = 0;
            for (int i=0;i < strlen(line_buffer);i++){
                char code_01 = line_buffer[i];
                if (code_01 == '0' || code_01 == '1')
                    size++;
                if (code_01 == '\n')
                    break;
            }
            char code[size + 1];

            strncpy(code, line_buffer + 2, size);
            code[size] = '\0';

            decoder_addnode(head,ch,code, (int)size);
        }
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
    char line_buffer[2048];

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
        strncpy(text,line_buffer,size);

        found_character = decoder_sreach_code(head,text, strlen(text));
        if (found_character != 'N'){
            fputc(found_character,textfile);
            start = end + 1;
            end ++;
        } else{
            continue;
        }
    }
    fclose(codefile);
    fclose(textfile);
}

char decoder_sreach_code(char2code * head, char * string, int length){
    char2code * ptr = head;
    while (ptr->next != NULL){
        ptr = ptr->next;
        if (strcmp(string, ptr->code))
            return ptr->character;
    }
    return 'N';
}