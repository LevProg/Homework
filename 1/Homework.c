#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 1050

int main(void)
{
    FILE* fp;
    /*
    * гененрирование файла
    char s[STR_LEN];
    s[STR_LEN-1] = '\0';
    char* filename = "data.txt";
    char dic[] = {'q','w','e','a','1','3','4' ,'+' ,'-','*'};
    printf("%d \n", sizeof(dic));
    for (int i = 0; i < STR_LEN-1; i++) {
        s[i] = dic[0 + rand() % sizeof(dic)];
    }
    fopen_s(&fp,filename, "w");
    fputs(s, fp);
    */

    char filename[20];
    char group[100] = { "0" };
    char str[STR_LEN];
    char ch[2] = { '0','\0' };;
    int cntA = 0;
    int curCntAlpha = 0;
    printf("Enter file name:\n");
    scanf("%19s", filename);
    fp = fopen(filename, "r");
    if (fgets(str, sizeof(str), fp) != NULL) {
        printf("%s\n", str);
        for (int i = 0; i < sizeof(str) && str[i] != '\0'; i++) {
            ch[0] = str[i];
            if (isalpha(ch[0]) != 0) {
                curCntAlpha++;
                if (ch[0] == 'a') {
                    cntA++;
                }
                if (curCntAlpha == 1) {
                    group[0] = ch[0];
                }
                else if (curCntAlpha > 1) {
                    strcat(group, ch);
                }
            }
            else {
                if (cntA >= 2) {
                    printf("%s\n", group);
                }
                memset(group, 0, 100);
                curCntAlpha = cntA = 0;
            }
        }
    }
    return 0;
}