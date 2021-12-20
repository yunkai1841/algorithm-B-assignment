// edata generator do not guarantee the correct answer
#include <stdio.h>
#include <string.h>
#include "lib.h"

#define TARGET_PER_STEP 10

/* 
文字列a, bのedataを求める
正解が連続しているときに精度が良い
a: 正解のchar配列
b: 観測値char配列
na: aの長さ
nb: bの長さ
result: 結果格納配列
*/
int edata(char a[], int na, char b[], int nb, char result[]){
    int i, j;
    int flag = 0;
    for(i = 0; i < na; i++){
        int correct =editdis(a+i, TARGET_PER_STEP, b+flag, TARGET_PER_STEP);
        int yokei = editdis(a+i, TARGET_PER_STEP, b+flag+1, TARGET_PER_STEP);
        int sobire = editdis(a+i+1, TARGET_PER_STEP, b+flag, TARGET_PER_STEP);
        // int miss = editdis(s+i+1, TARGET_PER_STEP, b+flag+1, TARGET_PER_STEP);

        // 判別
        if(yokei < correct && yokei <= sobire){
            // yokei
            result[i] = 'i'; flag+=2;
        } else if(sobire < correct && sobire <= yokei){
            // sobire
            result[i] = 'd';
        } else{
            // correct or miss
            if (a[i] == b[flag]){
                result[i] = '.'; flag++;
            } else {
                result[i] = 's'; flag++;
            }            
        }

        // printf("answer>%c, my>%c\n", edata_correct[i], result[i]);
    }
}