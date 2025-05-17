#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rot13(char *frase) {
    for (int i = 0; frase[i] != '\0'; i++) {
        char c = frase[i];

        if (isalpha(c)) {
            int base = islower(c) ? 'a' : 'A';
            frase[i] = (c - base + 13) % 26 + base;
        } else {
            frase[i] = c;
        }
    }
}

int main() {
    char frase[100], lido[100];
    FILE *fp;

    printf("Digite a frase: ");
    fgets(frase, sizeof(frase), stdin);

    frase[strcspn(frase, "\n")] = '\0';

    rot13(frase);

    fp = fopen("mensagem.bin", "w+b");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
    }
    fwrite(frase, sizeof(char), strlen(frase), fp);

    fseek(fp, 0, SEEK_SET);

    fread(lido,sizeof(char), strlen(frase),fp);

    lido[strlen(frase)] = '\0';

    printf("Frase codificada: %s\n", lido);
    rot13(lido);

    printf("Frase descodificada: %s\n", lido);
    fclose(fp);
}
