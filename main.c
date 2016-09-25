#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LineNode{
    char *str;
    struct LineNode* next;
}LineNode;

typedef struct LineStack{
   struct LineNode* top;
    struct LineNode* bottom;
}LineStack;

//LineNode buildNode(char* str){
//    LineNode one;
//    if(str!=NULL||strlen(str)){
//        if(one.str=(char*)malloc((strlen(str)+1)*sizeof(char))){
//            strcpy(one.str,str);
//            one.next=NULL;
//        } else{
//            printf("内存不足");
//            exit(0);
//        }
//    }
//    return one;
//}

LineNode* buildNode(char* str){
    LineNode* one;
    if((one=(LineNode*)malloc(sizeof(LineNode)))==NULL){
        printf("内存不足");
        exit(0);
    }
    if(str!=NULL){
        if(one->str=(char*)malloc((strlen(str)+1)*sizeof(char))){
            strcpy(one->str,str);
            one->next=NULL;
        } else{
            printf("内存不足");
            exit(0);
        }
    }
    return one;
}




LineStack* InitLineStack(void){
    LineStack* s=NULL;
    if((s=(LineStack*)malloc(sizeof(LineStack)))==NULL){
        printf("内存不足");
    }
    s->bottom=NULL;
    s->top=NULL;
    return s;
}

int pushIntoLineStack(LineStack* s,LineNode *n){
    if(s==NULL||n==NULL){
        printf("请初始化LineStack和LIneNode");
    }
    if(s->bottom==NULL||s->top==NULL){
    //  若是空栈
        s->bottom=n;
        s->top=n;
        n->next=NULL;
    } else{
    //  不是空栈则压入
        n->next=s->top;
        s->top=n;
    }
}


void PrnintLineStack(LineStack* s){
    int i=0;
    if(s==NULL||s->bottom==NULL){
        printf("空的LineStack无法打印");

    }
    LineNode* pointer;
    pointer=s->top;
    do{
        printf("[%d]%s\n",i,pointer->str);
        pointer=pointer->next;
        i++;
    }while (pointer!=NULL);

    printf("-打印完成\n");
}

int readFileToLineStack(LineStack* s,char* filename){
    FILE* fp;
    if((fp=fopen(filename,"r"))){

        if(s==NULL){
            printf("请先初始化LineStack");
        } else{

            char tmp[10240];
            char ch;
            int i=0;
            ch =fgetc(fp);

            while (ch!=EOF){
                tmp[i]=ch;
                if(ch=='\n'){
                    tmp[i]='\0';
                    if(strlen(tmp)>0){
                        LineNode* one = buildNode(tmp);
                        pushIntoLineStack(s,one);
                    }
                    i=0;
                } else{
                    i++;
                }
                ch=fgetc(fp);
            }
        }


    } else{
        printf("文件打开失败，请检查文件是否存在");
    }
}





int main(){
    LineStack* s;
    s=InitLineStack();
    readFileToLineStack(s,"/home/chaos/TestText.txt");
    PrnintLineStack(s);

}