#include <stdio.h>
#include <string.h>

int dp[10000][10000];

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
    char a[] = "";
    char b[] = "";
    int d = editdis(a, strlen(a), b, strlen(b));
    printf("%d\n", d);
}