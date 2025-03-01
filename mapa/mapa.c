#include </home/cardoos/codigos/C/prototipo_mapa_RoS/hash_tables/hash_tables.c>

struct rua troca_rua(struct fileira *table, int coords_novas[2]);

int main(void) {
    srand((unsigned)time(NULL));

    struct fileira *mapa = cria_table();
    int coords_player[2] = {0, 0};
    char rua_inicial[4] = {ABERTA, ABERTA, ABERTA, ABERTA};
    coloca_rua(mapa, coords_player, rua_inicial);

    char acao, descarte;
    do {
        struct rua rua_atual = troca_rua(mapa, coords_player);
        printf("\n\n\nCoordenadas: (%d, %d)\n",
            rua_atual.coordenadas[0],
            rua_atual.coordenadas[1]
        );

        printf("Layout: %c, %c, %c, %c\n\n",
            rua_atual.saidas[0],
            rua_atual.saidas[1],
            rua_atual.saidas[2],
            rua_atual.saidas[3]
        );

        printf("Seu movimento: ");
        scanf("%c%c", &acao, &descarte);

        switch (acao) {
            case 'w':
                coords_player[1] += (rua_atual.saidas[0] == ABERTA) ? 1 : 0;
                break;
            case 'a':
                coords_player[0] -= (rua_atual.saidas[3] == ABERTA) ? 1 : 0;
                break;
            case 's':
                coords_player[1] -= (rua_atual.saidas[2] == ABERTA) ? 1 : 0;
                break;
            case 'd':
                coords_player[0] += (rua_atual.saidas[1] == ABERTA) ? 1 : 0;
                break;
            default:
                break;
        }
    } while (acao != 'q');

    apaga_table(mapa);
    return 0;
}

struct rua troca_rua(struct fileira *table, int coords_novas[2]) {
    struct rua rua_nova = acessa_rua(table, coords_novas);
    if (rua_nova.saidas[0] != RUA_NAO_EXISTE.saidas[0]) {
        return rua_nova;
    }

    int x = coords_novas[0], y = coords_novas[1];
    int coords_vizinhas[4][2] = {{x, y+1}, {x+1, y}, {x, y-1}, {x-1, y}};

    char restricao[4] = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO};
    for (char i = 0; i < 4; i++) {
        restricao[i] = acessa_rua(table, coords_vizinhas[i]).saidas[(i + 2) % 4];
    }

    coloca_rua(table, coords_novas, restricao);
    return acessa_rua(table, coords_novas);
}