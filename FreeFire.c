// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {ORD_NOME, ORD_TIPO, ORD_PRIORIDADE} Criterio;

// --- Funções ---
void listarItens(Item mochila[], int qtd) {
    printf("\n=== Inventário ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               i+1, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

void adicionarItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome: ");
    fgets(mochila[*qtd].nome, MAX_NOME, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*qtd].tipo, MAX_TIPO, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    getchar();

    printf("Prioridade (1-5): ");
    scanf("%d", &mochila[*qtd].prioridade);
    getchar();

    (*qtd)++;
}

void removerItem(Item mochila[], int *qtd) {
    char nomeRemover[MAX_NOME];
    printf("Digite o nome do item para remover: ");
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int j = encontrado; j < *qtd-1; j++) {
            mochila[j] = mochila[j+1];
        }
        (*qtd)--;
        printf("Item removido!\n");
    } else {
        printf("Item não encontrado.\n");
    }
}

void ordenarItens(Item mochila[], int qtd, Criterio crit) {
    int comparacoes = 0;
    for (int i = 1; i < qtd; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            int cmp = 0;
            if (crit == ORD_NOME) cmp = strcmp(chave.nome, mochila[j].nome);
            else if (crit == ORD_TIPO) cmp = strcmp(chave.tipo, mochila[j].tipo);
            else cmp = chave.prioridade - mochila[j].prioridade;

            comparacoes++;
            if (cmp < 0) {
                mochila[j+1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j+1] = chave;
    }
    printf("Ordenação concluída com %d comparações.\n", comparacoes);
}

int buscaBinaria(Item mochila[], int qtd, char *nome) {
    int esq = 0, dir = qtd - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) dir = meio - 1;
        else esq = meio + 1;
    }
    return -1;
}

// --- Programa Principal ---
int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\nMenu:\n");
        printf("1 - Adicionar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Ordenar Itens\n");
        printf("5 - Buscar Item (Binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: adicionarItem(mochila, &qtd); ordenadoPorNome=false; break;
            case 2: removerItem(mochila, &qtd); ordenadoPorNome=false; break;
            case 3: listarItens(mochila, qtd); break;
            case 4: {
                int crit;
                printf("Ordenar por: 1-Nome, 2-Tipo, 3-Prioridade: ");
                scanf("%d", &crit);
                getchar();
                ordenarItens(mochila, qtd, crit-1);
                ordenadoPorNome = (crit==1);
                break;
            }
            case 5: {
                if (!ordenadoPorNome) {
                    printf("A lista deve estar ordenada por nome!\n");
                    break;
                }
                char nomeBusca[MAX_NOME];
                printf("Digite o nome do item: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                int pos = buscaBinaria(mochila, qtd, nomeBusca);
                if (pos != -1) {
                    printf("Item encontrado: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo,
                           mochila[pos].quantidade, mochila[pos].prioridade);
                } else {
                    printf("Item não encontrado.\n");
                }
                break;
            }
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while(opcao != 0);

    return 0;
}

