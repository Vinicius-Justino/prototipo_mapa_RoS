#include </home/cardoos/codigos/C/prototipo_mapa_RoS/linked_lists/linked_lists.c>
#include <math.h>
#define QUANTIDADE_FILEIRAS 25

struct fileira {
    int indice;
    struct node *itens;
    struct fileira *proxima;
};

struct fileira* cria_table();
void apaga_table(struct fileira *table);

int algoritmo_hash(int coordenadas[2]);

void coloca_rua(struct fileira *table, int coordenadas[2], char restricao[4]);
struct rua acessa_rua(struct fileira *table, int coordenadas[2]);

const struct rua RUA_NAO_EXISTE = {
    {0, 0},
    {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}
};

/* int main(void) {
    struct fileira *inicio_table = cria_table();

    for (int x = -14; x < 15; x++) {
        for (int y = -14; y < 15; y++) {
            int coordenadas[2] = {x, y};
            char saidas_determinadas[4] = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO};
            coloca_rua(inicio_table, coordenadas, saidas_determinadas);
        }
    }

    struct fileira *fileira_atual = inicio_table;
    while (fileira_atual != NULL) {
        printf("%d: ", (*fileira_atual).indice);

        int cont_ruas = 0;
        struct node *rua_atual = (*fileira_atual).itens;
        while (rua_atual != NULL) {
            cont_ruas++;
            //printf("(%d, %d) -> ", (*rua_atual).conteudo.coordenadas[0], (*rua_atual).conteudo.coordenadas[1]);
            
            rua_atual = (*rua_atual).proximo;
        }

        printf("%d \n", cont_ruas);
        //printf("NULL \n");
        fileira_atual = (*fileira_atual).proxima;
    }

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
    int x = coordenadas[0], y = coordenadas[1];

    x = (x < 0) ? ((QUANTIDADE_FILEIRAS + (x % -QUANTIDADE_FILEIRAS)) - 1) : (x % QUANTIDADE_FILEIRAS);
    y = (y < 0) ? ((QUANTIDADE_FILEIRAS + (y % -QUANTIDADE_FILEIRAS)) - 1) : (y % QUANTIDADE_FILEIRAS);
    
    return x / (int)(sqrt(QUANTIDADE_FILEIRAS)) + y / (int)(sqrt(QUANTIDADE_FILEIRAS)) * (int)(sqrt(QUANTIDADE_FILEIRAS));
}

void coloca_rua(struct fileira *table, int coordenadas[2], char restricao[4]) {
    int fileira_rua = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_rua) {
        fileira_certa = (*fileira_certa).proxima;
    }

    coloca_node(&((*fileira_certa).itens), cria_node(coordenadas, restricao));
}

struct rua acessa_rua(struct fileira *table, int coordenadas[2]) {
    int fileira_rua = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_rua) {
        fileira_certa = (*fileira_certa).proxima;
    }

    struct node *node_atual = (*fileira_certa).itens;
    while (node_atual != NULL) {
        if ((*node_atual).conteudo.coordenadas[0] == coordenadas[0] && (*node_atual).conteudo.coordenadas[1] == coordenadas[1]) {
            return (*node_atual).conteudo;
        }

        node_atual = (*node_atual).proximo;
    }

    return RUA_NAO_EXISTE;
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