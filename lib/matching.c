#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

#define DP_ARRAY_MAX 200
int dp[DP_ARRAY_MAX][DP_ARRAY_MAX];

int not_equals(int a, int b) { return a != b; }

int min(int a, int b) { return a < b ? a : b; }

/*
文字列a, bの編集距離を求める
a: char配列
b: char配列
na: aの長さ
nb: bの長さ
*/
int editdis(char a[], int na, char b[], int nb) {
    int i, j;

    for (i = 0; i <= na; i++) {
        dp[i][0] = i;
    }
    for (i = 0; i <= nb; i++) {
        dp[0][i] = i;
    }

    // dp
    for (i = 1; i <= na; i++) {
        for (j = 1; j <= nb; j++) {
            dp[i][j] = min(dp[i - 1][j - 1] + not_equals(a[i - 1], b[j - 1]),
                           min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
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
int editdis_min(char a[], int na, char b[], int nb) {
    int result = editdis(a, na, b, nb);
    int i;
    for (i = 0; i < nb; i++) result = min(dp[na][i], result);
    return result;
}

/*
小さな配列が大きな配列のどの部分にあるか探索する
source右端の動作は保証しない
target: 小さいchar配列
source: 大きいchar配列
*/
int matching(char target[], int ntarget, char source[], int nsource) {
    int i, j;
    const int margin = ntarget / 2;
    int *d;
    d = (int *)calloc(nsource + 1, sizeof(int));
    int min_element = 0;
    for (i = 0; i < nsource; i++) {
        d[i] = editdis_min(target, ntarget, source + i, ntarget + margin);
        if (d[i] < d[min_element]) min_element = i;
    }
    return min_element;
}

typedef struct {
    int first;
    int second;
} pair;
/*
改良版小さな配列が2つの大きな配列のどの部分にあるか探索する
source右端の動作は保証しない
target: 小さいchar配列
source1: 大きいchar配列
source2: 大きいchar配列
*/
pair matching2(char target[], int ntarget, char source1[], char source2[],
               int nsource) {
    int i, j;
    const int margin = ntarget / 10;
    int *d[2];
    d[0] = (int *)calloc(nsource + 1, sizeof(int));
    d[1] = (int *)calloc(nsource + 1, sizeof(int));
    pair min_element = {0, 0};
    for (i = 0; i < nsource; i++) {
        d[0][i] = editdis_min(target, ntarget, source1 + i, ntarget + margin);
        d[1][i] = editdis_min(target, ntarget, source2 + i, ntarget + margin);
        if (d[0][i] < d[min_element.first][min_element.second]) {
            min_element.first = 0;
            min_element.second = i;
        }
        if (d[1][i] < d[min_element.first][min_element.second]) {
            min_element.first = 1;
            min_element.second = i;
        }
    }
    return min_element;
}

void printstring(char s[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        putchar(s[i]);
    }
    puts("");
}

int main() {
    // just for test
    char target[200], source[2][50100];
    scanf("%s%s%s", target, source[0], source[1]);
    pair a = matching2(target, 20, source[0], source[1], 50);
    printf("%d %d\n", a.first, a.second);
    printstring(source[a.first]+a.second, 20);
    printstring(target, 20);
}