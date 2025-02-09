#include <stdio.h>
#include <stdlib.h>

struct node {
    int valor[2];
    struct node *proximo;
};

struct node* cria_node(int coordenadas[]);
void coloca_node(struct node **lista, struct node *endereco_node_novo, int indice);
void apaga_node(struct node **lista, int indice);
int* valor_node(struct node *lista, int indice);

int tamanho_lista(struct node *lista);
void mostra_lista(struct node *lista);
void apaga_lista(struct node *lista);

/* int main(void) {
    struct node *inicio_lista = NULL;

    for (int i = 0; i <= 9; i++) {
        int coordenadas[2] = {i, i};
        coloca_node(&inicio_lista, cria_node(coordenadas), tamanho_lista(inicio_lista));
    }

    int coordenadas[2] = {10, 10};
    coloca_node(&inicio_lista, cria_node(coordenadas), 5);
    apaga_node(&inicio_lista, 5);
    apaga_node(&inicio_lista, 0);
    apaga_node(&inicio_lista, tamanho_lista(inicio_lista) - 1);
    
    mostra_lista(inicio_lista);

    int *node5 = valor_node(inicio_lista, 5);
    printf("%d\n", node5[0]);

    apaga_lista(inicio_lista);
    return 0;
} */

struct node* cria_node(int coordenadas[]) {
    struct node node_novo;
    node_novo.valor[0] = coordenadas[0];
    node_novo.valor[1] = coordenadas[1];
    node_novo.proximo = NULL;
    
    struct node *endereco_node = malloc(sizeof(struct node));
    *endereco_node = node_novo;

    return endereco_node;
}

void coloca_node(struct node **lista, struct node *endereco_node_novo, int indice) {
    if (indice < 0 || indice > tamanho_lista(*lista)) {
        return;
    }

    (*endereco_node_novo).proximo = *lista;
    if (indice == 0) {
        *lista = endereco_node_novo;
        return;
    }

    for (int i = 1; i < indice; i++) {
        (*endereco_node_novo).proximo = (*(*endereco_node_novo).proximo).proximo;
    }

    struct node *node_anterior = (*endereco_node_novo).proximo;
    (*endereco_node_novo).proximo = (*(*endereco_node_novo).proximo).proximo;
    (*node_anterior).proximo = endereco_node_novo;
}

void apaga_node(struct node **lista, int indice) {
    if (indice < 0 || indice >= tamanho_lista(*lista)) {
        return;
    }

    struct node *anterior = *lista;
    if (indice == 0) {
        *lista = (*anterior).proximo;
        free(anterior);
        return;
    }

    for (int i = 1; i < indice; i++) {
        anterior = (*anterior).proximo;
    }

    struct node *excluido = (*anterior).proximo;
    (*anterior).proximo = (*excluido).proximo;
    free(excluido);
}

int* valor_node(struct node *lista, int indice) {
    if (indice < 0 || indice >= tamanho_lista(lista)) {
        return 0;
    }

    struct node *node_atual = lista;
    for (int i = 0; i < indice; i++) {
        node_atual = (*node_atual).proximo;
    }

    return (*node_atual).valor;
}

int tamanho_lista(struct node *lista) {
    struct node *node_atual = lista;
    int tamanho = 0;

    while (node_atual != NULL) {
        tamanho++;
        node_atual = (*node_atual).proximo;
    }

    return tamanho;
}

void mostra_lista(struct node *lista) {
    struct node *node_atual = lista;

    while (node_atual != NULL) {
        printf("(%d, %d) -> ", (*node_atual).valor[0], (*node_atual).valor[1]);
        node_atual = (*node_atual).proximo;
    }

    printf("NULL\n");
}

void apaga_lista(struct node *lista) {
    if ((*lista).proximo != NULL) {
        apaga_lista((*lista).proximo);
    }

    free(lista);
}