// 最長共通部分列
#include <stdio.h>

#define DP_ARRAY_MAX 20010
int dp[DP_ARRAY_MAX][DP_ARRAY_MAX];

int lcs(char a[], int na, char b[], int nb) {
    int i, j;

    // init
    for(i = 0; i < na; i++) dp[i][0] = 0;
    for(j = 0; j < nb; j++) dp[0][j] = 0;

    // dp
    for (i = 0; i < na; i++) {
        for (j = 0; j < nb; j++) {
        if (a[i] == b[j]) {
            dp[i + 1][j + 1] = dp[i][j] + 1;
        } else {
            dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        }
        }
    }
    return dp[na][nb];
}