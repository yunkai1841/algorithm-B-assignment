#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DP_ARRAY_MAX 200
int dp[DP_ARRAY_MAX][DP_ARRAY_MAX];

int not_equals(int a, int b){
    return a != b;
}

int min(int a, int b){
    return a < b ? a : b;
}

void printstring(char s[], int n){
    int i;
    for(i = 0; i < n; i++){
        putchar(s[i]);
    }
    puts("");
}

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

/* 
文字列a, bの編集距離を求める2
bの長さを可変として0~nbとしたときの編集距離
a: char配列
b: char配列
na: aの長さ
nb: bの長さ
*/
int editdis_min(char a[], int na, char b[], int nb){
    int result = editdis(a, na, b, nb);
    int i;
    for(i = 0; i < nb; i++) result = min(dp[na][i], result);
    return result;
}

/* 
小さな配列が大きな配列のどの部分にあるか探索する
source右端の動作は保証しない
target: 小さいchar配列
source: 大きいchar配列
*/
int matching(char target[], int ntarget, char source[], int nsource){
    int i, j;
    const int margin = ntarget/2;
    int *d;
    d = (int *)calloc(nsource+1, sizeof(int));
    int min_element = 0;
    for(i = 0; i < nsource; i++){
        d[i] = editdis_min(target, ntarget, source+i, ntarget+margin);
        if(d[i] < d[min_element]) min_element = i;
    }
    return min_element;
}

int main(){
    
}