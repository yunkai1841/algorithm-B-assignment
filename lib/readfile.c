#include<stdio.h>

int read_data(char filename[], char dat1[], char dat2[]){
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL) return -1;

    fscanf(fp, "%s%s", dat1, dat2);

    fclose(fp);
    return 1;    
}

int main(){
    char x[51000], y[51000];
    read_data("all2/Model1/dat0/idata", x, y);
    printf("%s\n%s\n", x, y);
    return 0;
}