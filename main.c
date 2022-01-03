#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DP_ARRAY_MAX 11000
int dp[DP_ARRAY_MAX][DP_ARRAY_MAX];

typedef struct item {
    int key;
    int value;
} item;

int not_equals(int a, int b) { return a != b; }

int min(int a, int b) { return a < b ? a : b; }

// just for debug
void printstring(char s[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        putchar(s[i]);
    }
    puts("");
}

// just for debug
void fileout_array2(int *a[], int n, int m){
    FILE *fp = fopen("array.csv", "w");
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            fprintf(fp, "%d, ", dp[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void strreverse(char *dest, char *src){
    int i;
    int n = strlen(src);
    for(i = 0; i < n; i++){
        dest[i] = src[n-i-1];
    }
}

#define FOPEN_ERROR -1
#define SUCCESS 1

int read_data(char filename[], char dat1[], char dat2[]) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) return FOPEN_ERROR;

    fscanf(fp, "%s%s", dat1, dat2);

    fclose(fp);
    return SUCCESS;
}

int read_answer(char filename[], int *dat1, int *dat2) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) return FOPEN_ERROR;

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
int editdis(char a[], int na, char b[], int nb) {
    int i, j;
    //debug
    // printf("editdis debug >>\n");
    // printstring(a, na);
    // printstring(b, nb);

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
    // printf("%c %c\n\n", a[0], a[na-1]);
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

item *editdis_min_all(char a[], int na, char b[], int nb) {
    int i, j;
    item *result;
    result = (item *)malloc(sizeof(item) * na);

    // initialize result
    // value max is around 50000
    for (i = 0; i <= na; i++) {
        result[i].key = -1;
        result[i].value = 100000;
    }
    editdis(a, na, b, nb);
    for (i = 1; i <= na; i++) {
        for (j = 0; j <= nb; j++){
            if(dp[i][j] < result[i].value) {
                result[i].key = j;
                result[i].value = dp[i][j];
            }
        } 
    }
    return result;
}

/*
小さな配列が大きな配列のどの部分にあるか探索する
! source右端の動作は保証しない
target: 小さいchar配列
source: 大きいchar配列
*/
int matching(char target[], int ntarget, char source[], int nsource) {
    int i, j;
    const int margin = ntarget / 10;
    int *d;
    d = (int *)calloc(nsource + 1, sizeof(int));
    int min_element = 0;
    for (i = 0; i < nsource; i++) {
        d[i] = editdis_min(target, ntarget, source + i, ntarget + margin);
        if (d[i] < d[min_element]) min_element = i;
    }
    return min_element;
}

int main(int argc, char *argv[]) {
    char x[51000], y[51000], rx[51000], ry[51000];  // correct data
    char s[51000], l[51000], rs[51000], rl[51000];  // observed data

    read_data(argv[1], x, y);  // arg[1]
    read_data(argv[2], s, l);  // arg[2]

    strreverse(rx, x);
    strreverse(ry, y);
    strreverse(rs, s);
    strreverse(rl, l);

    int i, j;
    item * result[5];
    int dx, ds, previous;
    int forward_xs[50001], backward_xl[50001], forward_yl[50001], backward_ys[50001];

    // * compare x and s forward
    dx = 0; ds = 0;
    for(i = 0; i < 5; i++){
        if(i == 4){
            result[i] = editdis_min_all(x+dx, 10000, s+ds, strlen(s)-ds);
            break;
        }
        result[i] = editdis_min_all(x+dx, 10000, s+ds, 10050);
        dx += 10000;
        ds += result[i][10000].key;
    }
    previous = 0;
    for(i = 0; i < 5; i++){
        for(j = 1; j <= 10000; j++){
            // printf("%d, %d, %d\n", j, result[i][j].key, result[i][j].value);
            forward_xs[i*10000+j] = result[i][j].value + previous;
        }
        previous = forward_xs[(i+1)*10000];
    }

    // * compare x and l backward
    dx = 0; ds = 0;
    for(i = 0; i < 5; i++){
        if(i == 4){
            result[i] = editdis_min_all(rx+dx, 10000, rl+ds, strlen(rl)-ds);
            break;
        }
        result[i] = editdis_min_all(rx+dx, 10000, rl+ds, 10050);
        dx += 10000;
        ds += result[i][10000].key;
    }
    previous = 0;
    for(i = 0; i < 5; i++){
        for(j = 1; j <= 10000; j++){
            // printf("%d, %d, %d\n", j, result[i][j].key, result[i][j].value);
            backward_xl[i*10000+j] = result[i][j].value + previous;
        }
        previous = backward_xl[(i+1)*10000];
    }

    // * compare y and l forward
    dx = 0; ds = 0;
    for(i = 0; i < 5; i++){
        if(i == 4){
            result[i] = editdis_min_all(y+dx, 10000, l+ds, strlen(l)-ds);
            break;
        }
        result[i] = editdis_min_all(y+dx, 10000, l+ds, 10050);
        dx += 10000;
        ds += result[i][10000].key;
    }
    previous = 0;
    for(i = 0; i < 5; i++){
        for(j = 1; j <= 10000; j++){
            // printf("%d, %d, %d\n", j, result[i][j].key, result[i][j].value);
            forward_yl[i*10000+j] = result[i][j].value + previous;
        }
        previous = forward_yl[(i+1)*10000];
    }

    // * compare y and s backward
    dx = 0; ds = 0;
    for(i = 0; i < 5; i++){
        if(i == 4){
            result[i] = editdis_min_all(ry+dx, 10000, rs+ds, strlen(rs)-ds);
            break;
        }
        result[i] = editdis_min_all(ry+dx, 10000, rs+ds, 10050);
        dx += 10000;
        ds += result[i][10000].key;
    }
    previous = 0;
    for(i = 0; i < 5; i++){
        for(j = 1; j <= 10000; j++){
            // printf("%d, %d, %d\n", j, result[i][j].key, result[i][j].value);
            backward_ys[i*10000+j] = result[i][j].value + previous;
        }
        previous = backward_ys[(i+1)*10000];
    }

    item min_element = {1, 100000};
    for(i = 1; i <= 50000; i++){
        // printf("%d, %d\n", forward_xs[i], backward_xl[i]);
        int tmp = forward_xs[i] + backward_xl[50001-i] + forward_yl[i] + backward_ys[50001-i];
        if(tmp < min_element.value) {
            min_element.key = i;
            min_element.value = tmp;
        }
    }
    printf("%d, %d\n", min_element.key, min_element.value);
}