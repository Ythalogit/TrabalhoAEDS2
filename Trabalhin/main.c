#include "intercalacao.h"
#include "funcionarios.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void intercalacao_basico(char *nome_arquivo_saida, int num_p, Lista *nome_particoes) {
    int fim = 0;
    FILE *out;

    if ((out = fopen(nome_arquivo_saida, "wb")) == NULL) {
        printf("Erro ao abrir arquivo de saída\n");
        return;
    }

    TVet v[num_p];

    for (int i = 0; i < num_p; i++) {
        v[i].f = fopen(nome_particoes->nome, "rb");
        v[i].aux_p = 0;
        
        if (v[i].f != NULL) {
            fseek(v[i].f, v[i].aux_p * tamanho_registro(), SEEK_SET);
            TFunc *f = le_funcionario(v[i].f);
            
            if (f == NULL) {
                v[i].func = funcionario(INT_MAX, "", "", "", 0.0);
            } else {
                v[i].func = f;
            }
        } else {
            fim = 1;
        }
        nome_particoes = nome_particoes->prox;
    }

    int aux = 0;
    while (!fim) {
        int menor = INT_MAX;
        int pos_menor = -1;

        for (int i = 0; i < num_p; i++) {
            if (v[i].func->cod < menor) {
                menor = v[i].func->cod;
                pos_menor = i;
            }
        }

        if (menor == INT_MAX) {
            fim = 1;
        } else {
            fseek(out, aux * tamanho_registro(), SEEK_SET);
            salva_funcionario(v[pos_menor].func, out);
            
            v[pos_menor].aux_p++;
            fseek(v[pos_menor].f, v[pos_menor].aux_p * tamanho_registro(), SEEK_SET);
            TFunc *f = le_funcionario(v[pos_menor].f);
            aux++;

            if (f == NULL) {
                v[pos_menor].func = funcionario(INT_MAX, "", "", "", 0.0);
            } else {
                v[pos_menor].func = f;
            }
        }
    }

    for (int i = 0; i < num_p; i++) {
        if (v[i].f != NULL) {
            fclose(v[i].f);
        }
    }
    
    fclose(out);
}

void intercalacao_arvore_de_vencedores(TPilha **pilha, int *vetTop, char *nome_arquivo_saida, int num_p) {
    // Implementar primeira parte do trabalho
}