#include </home/cardoos/codigos/C/prototipo_mapa_RoS/ruas/ruas.c>

struct node {
    struct rua conteudo;
    struct node *proximo;
};

struct node* cria_node(int coordenadas[2], char restricao[4]);
void coloca_node(struct node **lista, struct node *endereco_node_novo);
struct rua conteudo_node(struct node *lista, int indice);
void apaga_lista(struct node *lista);

/* int main(void) {
    struct node *inicio_lista = NULL;

    for (int i = 0; i <= 9; i++) {
        int coordenadas[2] = {i, i};
        char saidas_determinadas[4] = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO};
        coloca_node(&inicio_lista, cria_node(coordenadas, saidas_determinadas));
    }

    struct rua node5 = conteudo_node(inicio_lista, 5);
    printf("(%d, %d)\n", node5.coordenadas[0], node5.coordenadas[1]);

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

struct rua conteudo_node(struct node *lista, int indice) {
    struct node *node_atual = lista;
    for (int i = 0; i < indice; i++) {
        node_atual = (*node_atual).proximo;
    }

    return (*node_atual).conteudo;
}

void apaga_lista(struct node *lista) {
    if ((*lista).proximo != NULL) {
        apaga_lista((*lista).proximo);
    }

    free(lista);
}