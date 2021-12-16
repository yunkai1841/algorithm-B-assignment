#include<stdio.h>

#define FOPEN_ERROR -1
#define SUCCESS 1

int read_data(char filename[], char dat1[], char dat2[]){
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL) return FOPEN_ERROR;

    fscanf(fp, "%s%s", dat1, dat2);

    fclose(fp);
    return SUCCESS;
}

int read_answer(char filename[], int *dat1, int *dat2){
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL) return FOPEN_ERROR;

    fscanf(fp, "%d%d", dat1, dat2);

    fclose(fp);
    return SUCCESS;
}

int main(){
    char x[51000], y[51000];
    read_data("all2/Model1/dat0/idata", x, y);
    printf("%s\n%s\n", x, y);
    return 0;
}