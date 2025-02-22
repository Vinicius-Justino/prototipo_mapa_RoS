#include </home/cardoos/codigos/C/prototipo_mapa_RoS/linked_lists/linked_lists.c>
#include <math.h>
#define QUANTIDADE_FILEIRAS 25

struct fileira {
    int indice;
    struct node *itens;
    struct fileira *proxima;
};

struct fileira* cria_table();
int algoritmo_hash(int coordenadas[2]);
void coloca_rua(struct fileira *table, int coordenadas[2], char restricao[4]);
char rua_existe(struct fileira *table, int coordenadas[2]);

void apaga_table(struct fileira *table);

/* int main(void) {
    struct fileira *inicio_table = cria_table();

    for (int x = 0; x < 25; x++) {
        for (int y = 0; y < 25; y++) {
            int coordenadas[2] = {x, y};
            char saidas_determinadas[4] = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO};
            coloca_rua(inicio_table, coordenadas, saidas_determinadas);
        }
    }

    int coordenadas_existentes[2] = {20, 20};
    int coordenadas_inexistentes[2] = {30, 30};
    printf("%d, %d\n",
        rua_existe(inicio_table, coordenadas_existentes),
        rua_existe(inicio_table, coordenadas_inexistentes)
    );

    apaga_table(inicio_table);
    return 0;
} */

struct fileira* cria_table() {
    struct fileira primeira_fileira = {0, NULL, NULL};

    struct fileira* table = malloc(sizeof(struct fileira));
    *table = primeira_fileira;

    struct fileira* final_table = table;
    for (int i = 1; i < QUANTIDADE_FILEIRAS; i++) {
        struct fileira fileira_nova = {i, NULL, NULL};

        struct fileira* endereco_fileira = malloc(sizeof(struct fileira));
        *endereco_fileira = fileira_nova;

        (*final_table).proxima = endereco_fileira;
        final_table = endereco_fileira;
    }

    return table;
}

int algoritmo_hash(int coordenadas[2]) {
    int x = coordenadas[0] * (1 - 2 * (coordenadas[0] < 0)),
        y = coordenadas[1] * (1 - 2 * (coordenadas[1] < 0));
    
    return (x % QUANTIDADE_FILEIRAS) / (int)(sqrt(QUANTIDADE_FILEIRAS)) + (y % QUANTIDADE_FILEIRAS) / (int)(sqrt(QUANTIDADE_FILEIRAS)) * (int)(sqrt(QUANTIDADE_FILEIRAS));
}

void coloca_rua(struct fileira *table, int coordenadas[2], char restricao[4]) {
    int fileira_rua = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_rua) {
        fileira_certa = (*fileira_certa).proxima;
    }

    coloca_node(&((*fileira_certa).itens), cria_node(coordenadas, restricao));
}

char rua_existe(struct fileira *table, int coordenadas[2]) {
    int fileira_rua = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_rua) {
        fileira_certa = (*fileira_certa).proxima;
    }

    struct node *node_atual = (*fileira_certa).itens;
    while (node_atual != NULL) {
        if ((*node_atual).conteudo.coordenadas[0] == coordenadas[0] && (*node_atual).conteudo.coordenadas[1] == coordenadas[1]) {
            return 1;
        }

        node_atual = (*node_atual).proximo;
    }

    return 0;
}

void apaga_table(struct fileira *table) {
    if ((*table).proxima != NULL) {
        apaga_table((*table).proxima);
    }

    if ((*table).itens != NULL) {
        apaga_lista((*table).itens);
    }

    free(table);
}