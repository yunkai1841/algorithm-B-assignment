#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FOPEN_ERROR -1
#define SUCCESS 1

#define DP_ARRAY_MAX 20010
int dp[DP_ARRAY_MAX][DP_ARRAY_MAX];

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

int not_equals(int a, int b){
    return a != b;
}

int min(int a, int b){
    return a < b ? a : b;
}

/* 
文字列a, bの編集距離を求める
a: char配列
b: char配列
na: aの長さ
nb: bの長さ
*/
int editdis(char a[], int na, char b[], int nb){
    int i, j;

    for(i = 0; i <= na; i++){
        dp[i][0] = i;
    }
    for(i = 0; i <= nb; i++){
        dp[0][i] = i;
    }

    //dp
    for(i = 1; i <= na; i++){
        for(j = 1; j <= nb; j++){
            dp[i][j] = min(dp[i-1][j-1] + not_equals(a[i-1], b[j-1]),
                min(dp[i-1][j]+1, dp[i][j-1]+1));
            
        }
    }
    return dp[na][nb];
}

int main(){
    char x[51000], y[51000]; //observed data
    char s[51000], l[51000]; //correct data

    //idata is correct data
    //odata is observed data
    read_data("all2/Model1/dat0/idata", x, y);
    read_data("all2/Model1/dat0/odata", s, l);

    int d = editdis(x, 20000, s, 20000);
    printf("%d\n", d);
    return 0;

}