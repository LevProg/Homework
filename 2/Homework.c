#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1000

int main(void)
{
    setlocale(LC_ALL, "Russian");
    FILE* file;
    FILE* newFile;
    char filename[50];
    int newLineLenght;
    printf("Введите имя файла:\n");
    scanf("%49s", &filename);
    printf("Введите длину строки:\n");
    scanf("%d", &newLineLenght);
    char s[LEN];
    int lineLen = 0;
    int curPos = 0;
    int isThereSpaces = 0;
    char ch[2];
    file = fopen(filename, "r");
    newFile = fopen("newData.txt", "w");
    newLineLenght--;
    while (fgets(s, sizeof(s), file) != NULL) {
        printf("%s", s);
        for (int i = 0; s[i] != '\0'; i++) {
            lineLen = i;
            if (s[i] == ' '){
                isThereSpaces = 1;
            }
        }
        if (isThereSpaces) {
            if (lineLen > newLineLenght) {
                curPos = 0;
                for (int i = 0; i <= lineLen; i++) {
                    if (i >= newLineLenght + curPos) {
                        for (int k = i; k > 0; k--) {
                            if (s[k] == ' ') {
                                s[k] = '\n';
                                i = k + newLineLenght;
                                curPos = k;
                                break;
                            }
                        }
                    }
                }
            }
        }
        else{
            if (lineLen > newLineLenght) {
                for (int k = 1; k <= lineLen / newLineLenght;k++) {
                    ch[0] = s[newLineLenght*k];
                    s[newLineLenght *k] = '\n';
                    for (int i = newLineLenght * k; i < lineLen-1; i++) {
                        ch[1] = s[i + 1];
                        s[i + 1]=ch[0];
                        ch[0] = ch[1];
                    }
                }
            }
        }
        fputs(s, newFile);
    }
    return 0;
}