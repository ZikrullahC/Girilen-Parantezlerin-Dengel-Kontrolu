#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node* link;
} node;

typedef struct head {
    int count;
    node* top;
} head;

head* stack_olustur() {
    head* stack = (head*)malloc(sizeof(head));

    if (stack) {
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}

void eleman_ekle(head* stack, char karakter) {
    node* yeni = (node*)malloc(sizeof(node));

    if (yeni) {
        yeni->link = stack->top;
        stack->top = yeni;
        yeni->data = karakter;
        (stack->count)++;
    }
}

char eleman_cek(head* stack) {
    node* temp = stack->top;
    char dataoutPtr;

    if (stack->count == 0)
        return NULL;
    else {
        temp = stack->top;
        dataoutPtr = stack->top->data;
        stack->top = stack->top->link;
        free(temp);
        (stack->count)--;
    }
    return dataoutPtr;
}

int karsilastir(head* stack, char dizi[]) {
    int i = 0, j, kontrol = 0;

    for (j = 0; j < strlen(dizi) / 2; j++) {
        char karakter = eleman_cek(stack);

        switch (karakter) {
        case '{':
            if (dizi[i] == '}')
                kontrol++;
            i++;
            break;

        case '(':
            if (dizi[i] == ')')
                kontrol++;
            i++;
            break;

        default:
            break;
        }
    }

    if (kontrol == strlen(dizi) / 2)
        return 1;
    else
        return 0;
}

int main() {
    int i, j = 0, boyut;
    char karakter;
    printf("Kaç karakter gireceğinizi giriniz: ");
    scanf("%d", &boyut);
    char dizi[boyut];
    head* stack = stack_olustur();

    for (i = 0; i < boyut; i++) {
        scanf(" %c", &karakter);

        if (karakter == '(' || karakter == '{') {
            eleman_ekle(stack, karakter);
        } else {
            dizi[j] = karakter;
            j++;
        }
    }

    if (karsilastir(stack, dizi))
        printf("DENGELI\n");
    else
        printf("DENGESIZ\n");

    return 0;
}
