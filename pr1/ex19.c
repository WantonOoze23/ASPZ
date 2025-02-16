#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

typedef struct {
    char character;
    int frequency;
} CharFreq;

int compare(const void* a, const void* b) {
    CharFreq* cf1 = (CharFreq*)a;
    CharFreq* cf2 = (CharFreq*)b;
    
    if (cf1->frequency != cf2->frequency)
        return cf2->frequency - cf1->frequency;
    
    return cf1->character - cf2->character;
}


int isWhitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int main() {
    FILE* file;
    CharFreq charFreq[MAX_CHARS];

    for (int i = 0; i < MAX_CHARS; i++) {
        charFreq[i].character = (char)i;
        charFreq[i].frequency = 0;
    }
    
    file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Помилка відкриття файлу!\n");
        return 1;
    }
    
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isWhitespace(ch) && ch < MAX_CHARS) {
            charFreq[ch].frequency++;
        }
    }
    
    fclose(file);
    
    qsort(charFreq, MAX_CHARS, sizeof(CharFreq), compare);
    
    printf("Символ\tЧастота\t\n");
    printf("---------------\n");
    
    for (int i = 0; i < MAX_CHARS; i++) {
        if (charFreq[i].frequency > 0) {
            printf("%c\t%d\n", charFreq[i].character, charFreq[i].frequency);
        }
    }
    
    return 0;
}