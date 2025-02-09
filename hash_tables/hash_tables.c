#include </home/cardoos/codigos/C/prototipo_mapa_RoS/linked_lists/linked_lists.c>
#define QUANTIDADE_FILEIRAS 25

struct fileira {
    int indice;
    struct node *itens;
    struct fileira *proxima;
};

struct fileira* cria_table(int tamanho);
int algoritmo_hash(int coordenadas[]);
void coloca_par(struct fileira *table, int coordenadas[]);
void tira_par(struct fileira *table, int coordenadas[]);
int par_existe(struct fileira *table, int coordenadas[]);

void mostra_table(struct fileira *table);
void apaga_table(struct fileira *table);

/* int main(void) {
    struct fileira *inicio_table = cria_table(QUANTIDADE_FILEIRAS);

    for (int x = 0; x < 25; x++) {
        for (int y = 0; y < 25; y++) {
            int par[2] = {x, y};
            coloca_par(inicio_table, par);
        }
    }

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            int par[2] = {x, y};
            tira_par(inicio_table, par);
        }
    }

    int coordenadas_existentes[2] = {20, 20};
    int coordenadas_inexistentes[2] = {10, 10};
    printf("%d, %d\n",
        par_existe(inicio_table, coordenadas_existentes),
        par_existe(inicio_table, coordenadas_inexistentes)
    );

    mostra_table(inicio_table);
    apaga_table(inicio_table);
    return 0;
} */

struct fileira* cria_table(int tamanho) {
    struct fileira primeira_fileira = {0, NULL, NULL};

    struct fileira* table = malloc(sizeof(struct fileira));
    *table = primeira_fileira;

    struct fileira* final_table = table;
    for (int i = 1; i < tamanho; i++) {
        struct fileira fileira_nova = {i, NULL, NULL};

        struct fileira* endereco_fileira = malloc(sizeof(struct fileira));
        *endereco_fileira = fileira_nova;

        (*final_table).proxima = endereco_fileira;
        final_table = endereco_fileira;
    }

    return table;
}

int algoritmo_hash(int coordenadas[]) {
    return (coordenadas[0] + coordenadas[1]) % QUANTIDADE_FILEIRAS;
}

void coloca_par(struct fileira *table, int coordenadas[]) {
    int fileira_par = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_par) {
        fileira_certa = (*fileira_certa).proxima;
    }

    coloca_node(&((*fileira_certa).itens), cria_node(coordenadas), tamanho_lista((*fileira_certa).itens));
}

void tira_par(struct fileira *table, int coordenadas[]) {
    int fileira_par = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_par) {
        fileira_certa = (*fileira_certa).proxima;
    }

    int indice_par = 0;
    struct node *node_atual = (*fileira_certa).itens;
    while ((*node_atual).valor[0] != coordenadas[0] || (*node_atual).valor[1] != coordenadas[1]) {
        node_atual = (*node_atual).proximo;
        indice_par++;

        if (node_atual == NULL) {
            return;
        }
    }

    apaga_node(&((*fileira_certa).itens), indice_par);
}

int par_existe(struct fileira *table, int coordenadas[]) {
    int fileira_par = algoritmo_hash(coordenadas);

    struct fileira* fileira_certa = table;
    while ((*fileira_certa).indice != fileira_par) {
        fileira_certa = (*fileira_certa).proxima;
    }

    struct node *node_atual = (*fileira_certa).itens;
    while (node_atual != NULL) {
        if ((*node_atual).valor[0] == coordenadas[0] && (*node_atual).valor[1] == coordenadas[1]) {
            return 1;
        }

        node_atual = (*node_atual).proximo;
    }

    return 0;
}

void mostra_table(struct fileira *table) {
    struct fileira *fileira_atual = table;

    while (fileira_atual != NULL) {
        printf("%d: ", (*fileira_atual).indice);
        mostra_lista((*fileira_atual).itens);

        fileira_atual = (*fileira_atual).proxima;    
    }
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