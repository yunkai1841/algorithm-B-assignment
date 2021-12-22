#include <stdio.h>
#include <string.h>

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

int main() {
    char edata[2][50001];
    int p, error;
    char filedir[256], f2[256];
    scanf("%s", filedir);
    strcpy(f2, filedir);
    if (read_data(strcat(filedir, "/edata"), edata[0], edata[1]) == FOPEN_ERROR)
        return 1;
    if (read_answer(strcat(f2, "/answer"), &p, &error) == FOPEN_ERROR)
        return 1;
    int s_flag = 0, l_flag = 0;
    printf("correct, s, l\n");
    for (int i = 0; i < strlen(edata[0]); i++) {
        if(i == p){
            printf("\n-1, -1, -1\n\n");
            int tmp = s_flag; s_flag = l_flag; l_flag = tmp;
        }
        switch (edata[0][i]) {
            case 'i':
                s_flag += 2;
                break;
            case 'd':
                break;
            default:
                s_flag++;
                break;
        }
        switch (edata[1][i]) {
            case 'i':
                l_flag += 2;
                break;
            case 'd':
                break;
            default:
                l_flag++;
                break;
        }
        printf("%d, %d, %d\n", i, s_flag, l_flag);
    }
}