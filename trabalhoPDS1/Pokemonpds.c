#include <stdio.h>
#include <string.h>

#define max_pokemon 100
#define max_name 50

// estrutura para representar um pokémon
typedef struct {
    char nome[max_name];
    int ataque;
    int defesa;
    int vida;
    char tipo[max_name];
} pokemon;


float calcular_modificador(char *tipo_atacante, char *tipo_defensor) {
    if ((strcmp(tipo_atacante, "eletrico") == 0 && strcmp(tipo_defensor, "agua") == 0) ||
        (strcmp(tipo_atacante, "agua") == 0 && strcmp(tipo_defensor, "fogo") == 0) ||
        (strcmp(tipo_atacante, "fogo") == 0 && strcmp(tipo_defensor, "gelo") == 0) ||
        (strcmp(tipo_atacante, "gelo") == 0 && strcmp(tipo_defensor, "pedra") == 0) ||
        (strcmp(tipo_atacante, "pedra") == 0 && strcmp(tipo_defensor, "eletrico") == 0)) {
        return 1.2;
    }
    if ((strcmp(tipo_atacante, "eletrico") == 0 && strcmp(tipo_defensor, "pedra") == 0) ||
        (strcmp(tipo_atacante, "agua") == 0 && strcmp(tipo_defensor, "eletrico") == 0) ||
        (strcmp(tipo_atacante, "fogo") == 0 && strcmp(tipo_defensor, "agua") == 0) ||
        (strcmp(tipo_atacante, "gelo") == 0 && strcmp(tipo_defensor, "fogo") == 0) ||
        (strcmp(tipo_atacante, "pedra") == 0 && strcmp(tipo_defensor, "gelo") == 0)) {
        return 0.8;
    }
    return 1.0;
}

void simular_batalha(pokemon *jogador1, int n1, pokemon *jogador2, int n2) {
    int i1 = 0, i2 = 0;
    while (i1 < n1 && i2 < n2) {
        pokemon *atk1 = &jogador1[i1];
        pokemon *def1 = &jogador2[i2];
        float modificador1 = calcular_modificador(atk1->tipo, def1->tipo);
        int dano1 = (int)(atk1->ataque * modificador1) - def1->defesa;
        if (dano1 <= 0) dano1 = 1;
        def1->vida -= dano1;
        printf("%s atacou %s causando %d de dano.\n", atk1->nome, def1->nome, dano1);

        if (def1->vida <= 0) {
            printf("%s venceu %s\n", atk1->nome, def1->nome);
            i2++;
            if (i2 >= n2) break;
        }

        pokemon *atk2 = &jogador2[i2];
        pokemon *def2 = &jogador1[i1];
        float modificador2 = calcular_modificador(atk2->tipo, def2->tipo);
        int dano2 = (int)(atk2->ataque * modificador2) - def2->defesa;
        if (dano2 <= 0) dano2 = 1;
        def2->vida -= dano2;
        printf("%s atacou %s causando %d de dano.\n", atk2->nome, def2->nome, dano2);

        if (def2->vida <= 0) {
            printf("%s venceu %s\n", atk2->nome, def2->nome);
            i1++;
            if (i1 >= n1) break;
        }
    }

    if (i1 < n1) {
        printf("jogador 1 venceu!\n");

        printf("pokemon sobreviventes do jogador 1:\n");
        for (int i = i1; i < n1; i++) {
            printf("%s\n", jogador1[i].nome);
        }
    } else {
        printf("jogador 2 venceu!\n");

        printf("pokemon sobreviventes do jogador 2:\n");
        for (int i = i2; i < n2; i++) {
            printf("%s\n", jogador2[i].nome);
        }
    }

    printf("\npokemon derrotados do jogador 1:\n");
    for (int i = 0; i < i1; i++) {
        printf("%s\n", jogador1[i].nome);
    }

    printf("\npokemon derrotados do jogador 2:\n");
    for (int i = 0; i < i2; i++) {
        printf("%s\n", jogador2[i].nome);
    }
}

int ler_dados(const char *dadospok, pokemon *jogador1, int *n1, pokemon *jogador2, int *n2) {
    FILE *file = fopen("dadospok.txt", "r");
    if (!file) {
        perror("erro ao abrir o arquivo");
        return 0;
    }

    fscanf(file, "%d %d", n1, n2);

    for (int i = 0; i < *n1; i++) {
        fscanf(file, "%s %d %d %d %s", jogador1[i].nome, &jogador1[i].ataque, &jogador1[i].defesa, &jogador1[i].vida, jogador1[i].tipo);
    }

    for (int i = 0; i < *n2; i++) {
        fscanf(file, "%s %d %d %d %s", jogador2[i].nome, &jogador2[i].ataque, &jogador2[i].defesa, &jogador2[i].vida, jogador2[i].tipo);
    }

    fclose(file);
    return 1;
}

int main() {
    pokemon jogador1[max_pokemon], jogador2[max_pokemon];
    int n1, n2;

    if (!ler_dados("dadospok", jogador1, &n1, jogador2, &n2)) {
        return 1;
    }

    printf("dados do jogador 1:\n");
    for (int i = 0; i < n1; i++) {
        printf("%s %d %d %d %s\n", jogador1[i].nome, jogador1[i].ataque, jogador1[i].defesa, jogador1[i].vida, jogador1[i].tipo);
    }

    printf("\ndados do jogador 2:\n");
    for (int i = 0; i < n2; i++) {
        printf("%s %d %d %d %s\n", jogador2[i].nome, jogador2[i].ataque, jogador2[i].defesa, jogador2[i].vida, jogador2[i].tipo);
    }

    printf("\niniciando a batalha:\n\n");
    simular_batalha(jogador1, n1, jogador2, n2);

    return 0;
}








