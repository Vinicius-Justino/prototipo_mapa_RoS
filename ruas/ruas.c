#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABERTA 'a'
#define FECHADA 'f'
#define INDEFINIDO '?'

#define CHANCES_RETA 40
#define CHANCES_ESQUINA 30
#define CHANCES_BIFURCACAO 20
#define CHANCES_ENCRUZILHADA 9
#define CHANCES_SEM_SAIDA 1

struct rua {
    int coordenadas[2];

    char saidas[4];
};

int potencia_simples(int base, int expoente);
struct rua cria_rua(int coordenadas[2], char restricao[4]);

char retas[3] = {5, 10, 0};
char esquinas[5] = {3, 6, 9, 12, 0};
char bifurcacoes[5] = {7, 11, 13, 14, 0};
char encruzilhada[2] = {15, 0};
char sem_saida [5] = {1, 2, 4, 8, 0};
char *tipos_ruas[5] = {retas, esquinas, bifurcacoes, encruzilhada, sem_saida};

/* int main(void) {
    srand((unsigned)time(NULL));

    int coords[2] = {0, 0};
    char saidas_determinadas[4] = {ABERTA, INDEFINIDO, ABERTA, INDEFINIDO};

    for (int i = 0; i < 10; i++) {
        struct rua teste = cria_rua(coords, saidas_determinadas);
        printf("%c, %c, %c, %c\n", teste.saidas[0], teste.saidas[1], teste.saidas[2], teste.saidas[3]);
    }
    
    return 0;
} */

struct rua cria_rua(int coordenadas[2], char restricao[4]) {
    struct rua rua_nova;
    rua_nova.coordenadas[0] = coordenadas[0];
    rua_nova.coordenadas[1] = coordenadas[1];

    char mascara = 0, modelo = 0;
    for (char i = 0; i < 4; i++) {
        mascara += potencia_simples(2, (3 - i)) * (restricao[i] != INDEFINIDO);
        modelo += potencia_simples(2, (3 - i)) * (restricao[i] == ABERTA);
    }

    char chances_tipos_ruas[5] = {CHANCES_RETA, CHANCES_ESQUINA, CHANCES_BIFURCACAO, CHANCES_ENCRUZILHADA, CHANCES_SEM_SAIDA};
    char ultimo_tipo_possivel = 0, chances_valendo = 0;
    for (char tipo = 0; tipo < 5; tipo++) {
        for (char variante = 0; tipos_ruas[tipo][variante] != 0; variante++) {
            char rua = tipos_ruas[tipo][variante];

            if ((rua & mascara) == modelo) {  
                ultimo_tipo_possivel = tipo;
                break;
            }
        }

        if (ultimo_tipo_possivel == tipo) {
            chances_valendo += chances_tipos_ruas[tipo];
        } else {
            chances_tipos_ruas[tipo] = 0;
        }
    }

    for (char tipo = 0; tipo < 5; tipo++) {
        if (chances_tipos_ruas[tipo] == 0) {
            continue;
        }

        chances_tipos_ruas[tipo] = chances_tipos_ruas[tipo] * 100 / chances_valendo;
    }

    float probabilidades[5];
    for (char tipo = 0; tipo < 5; tipo++) {
        if (tipo == ultimo_tipo_possivel) {
            probabilidades[tipo] = 100.0f;
            break;
        }
        
        probabilidades[tipo] = chances_tipos_ruas[tipo] / 100.0f;
        for (char antecessor = 0; antecessor < tipo; antecessor++) {
            probabilidades[tipo] /= 1.0f - probabilidades[antecessor];
        }
    }

    char rua_escolhida = 0;
    for (char tipo = 0; tipo < 5; tipo++) {
        char ruas_possiveis[4];
        char cont_ruas_possiveis = 0;

        for (char variante = 0; tipos_ruas[tipo][variante] != 0; variante++) {
            char rua = tipos_ruas[tipo][variante];

            if ((rua & mascara) == modelo) {  
                ruas_possiveis[cont_ruas_possiveis] = rua;
                cont_ruas_possiveis++;
            }
        }

        if (cont_ruas_possiveis == 0) {
            continue;
        }
        
        if (rand() % 100 < (int)(probabilidades[tipo] * 100)) {
            rua_escolhida = ruas_possiveis[rand() % cont_ruas_possiveis];
            break;
        }
    }
    

    char estados[2] = {FECHADA, ABERTA};
    for (char i = 3; i >= 0; i--) {
        rua_nova.saidas[3 - i] = estados[(rua_escolhida >= potencia_simples(2, i))];
        rua_escolhida -= potencia_simples(2, i) * (rua_escolhida >= potencia_simples(2, i));
    }

    return rua_nova;
}

int potencia_simples(int base, int expoente) {
    int resultado = 1;
    while (expoente > 0) {
        resultado *= base;
        expoente--;
    }

    return resultado;
}