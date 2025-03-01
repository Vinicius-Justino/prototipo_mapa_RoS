#include </home/cardoos/codigos/C/prototipo_mapa_RoS/ruas/ruas.c>

struct node {
    struct rua conteudo;
    struct node *proximo;
};

struct node* cria_node(int coordenadas[2], char restricao[4]);
void coloca_node(struct node **lista, struct node *endereco_node_novo);
void apaga_lista(struct node *lista);

/* int main(void) {
    struct node *inicio_lista = NULL;

    for (int i = 0; i <= 9; i++) {
        int coordenadas[2] = {i, i};
        char saidas_determinadas[4] = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO};
        coloca_node(&inicio_lista, cria_node(coordenadas, saidas_determinadas));
    }

    struct node *rua_atual = inicio_lista;
    while (rua_atual != NULL) {
        printf("(%d, %d) -> ", (*rua_atual).conteudo.coordenadas[0], (*rua_atual).conteudo.coordenadas[1]);
        rua_atual = (*rua_atual).proximo;
    }

    printf("NULL \n");
    apaga_lista(inicio_lista);
    return 0;
} */

struct node* cria_node(int coordenadas[2], char restricao[4]) {
    struct node node_novo;
    node_novo.conteudo = cria_rua(coordenadas, restricao);
    node_novo.proximo = NULL;
    
    struct node *endereco_node = malloc(sizeof(struct node));
    *endereco_node = node_novo;

    return endereco_node;
}

void coloca_node(struct node **lista, struct node *endereco_node_novo) {
    (*endereco_node_novo).proximo = *lista;
    *lista = endereco_node_novo;

    return;
}

void apaga_lista(struct node *lista) {
    if ((*lista).proximo != NULL) {
        apaga_lista((*lista).proximo);
    }

    free(lista);
}