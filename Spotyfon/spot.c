#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // para strcasecmp
#include "spotyfon.h"

// ------- funções gerais ---------------------

int carregarMusicas(const char *nomeArquivo, Musica lista[], int max) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0;
    }
    char linha[512];
    int qtd = 0;
    while (fgets(linha, sizeof(linha), arquivo) && qtd < max) {
        linha[strcspn(linha, "\n")] = 0;
        char *token = strtok(linha, ";");
        if (!token) continue;
        strncpy(lista[qtd].artista, token, sizeof(lista[qtd].artista));
        token = strtok(NULL, ";");
        if (!token) continue;
        lista[qtd].codigo = atoi(token);
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(lista[qtd].titulo, token, sizeof(lista[qtd].titulo));
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(lista[qtd].letra, token, sizeof(lista[qtd].letra));
        token = strtok(NULL, ";");
        if (!token) continue;
        lista[qtd].execucoes = atoi(token);
        qtd++;
    }
    fclose(arquivo);
    return qtd;
}

void imprimirMusica(Musica *m) {
    if (!m) return;
    printf("Título: %s\n", m->titulo);
    printf("Artista: %s\n", m->artista);
    printf("Código: %d\n", m->codigo);
    printf("Letra: %s\n", m->letra);
    printf("Execuções: %d\n", m->execucoes);
}

// ------- PILHA ---------------------

DescPilha *criaDescPilha(void) {
    DescPilha *pilha = malloc(sizeof(DescPilha));
    if (!pilha) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

NodoPilha *criaNodoPilha(Musica *m) {
    NodoPilha *novo = malloc(sizeof(NodoPilha));
    if (!novo) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->musica = m;
    novo->prox = NULL;
    return novo;
}

void inserirPilha(DescPilha *pilha, NodoPilha *novoElemento) {
    if (!pilha || !novoElemento) return;
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

int existePilha(DescPilha *pilha) {
    return pilha && pilha->topo != NULL;
}

int tamanhoPilha(DescPilha *pilha) {
    return pilha ? pilha->tamanho : 0;
}

void imprimirPilha(DescPilha *pilha) {
    if (!pilha) {
        printf("Pilha não existe!\n");
        return;
    }
    NodoPilha *atual = pilha->topo;
    printf("Pilha (topo -> base):\n");
    while (atual) {
        imprimirMusica(atual->musica);
        printf("-----\n");
        atual = atual->prox;
    }
}

void salvarPilhaSimples(DescPilha *pilha, const char *nomeArquivo) {
    if (!pilha) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo %s para salvar!\n", nomeArquivo);
        return;
    }
    NodoPilha *atual = pilha->topo;
    while (atual) {
        fprintf(f, "%s;%s\n", atual->musica->artista, atual->musica->titulo);
        atual = atual->prox;
    }
    fclose(f);
}

void exportarPilhaCompleta(DescPilha *pilha, const char *nomeArquivo) {
    if (!pilha) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo %s para exportar!\n", nomeArquivo);
        return;
    }
    NodoPilha *atual = pilha->topo;
    while (atual) {
        Musica *m = atual->musica;
        fprintf(f, "%s;%d;%s;%s;%d\n",
            m->artista, m->codigo, m->titulo, m->letra, m->execucoes);
        atual = atual->prox;
    }
    fclose(f);
}

void freePilha(DescPilha *pilha) {
    if (!pilha) return;
    NodoPilha *atual = pilha->topo;
    while (atual) {
        NodoPilha *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(pilha);
}

// --------- FILA -------------

DescFila *createFila(void) {
    DescFila *fila = malloc(sizeof(DescFila));
    if (!fila) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void inserirFila(DescFila *fila, Musica *m) {
    if (!fila || !m) return;
    NodoFila *novo = malloc(sizeof(NodoFila));
    if (!novo) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->musica = m;
    novo->prox = NULL;

    if (!fila->fim) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

int existeFila(DescFila *fila) {
    return fila && fila->inicio != NULL;
}

int tamanhoFila(DescFila *fila) {
    return fila ? fila->tamanho : 0;
}

void imprimirFila(DescFila *fila) {
    if (!fila) {
        printf("Fila não existe!\n");
        return;
    }
    NodoFila *atual = fila->inicio;
    printf("Fila (início -> fim):\n");
    while (atual) {
        imprimirMusica(atual->musica);
        printf("-----\n");
        atual = atual->prox;
    }
}

void salvarFilaSimples(DescFila *fila, const char *nomeArquivo) {
    if (!fila) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo %s para salvar!\n", nomeArquivo);
        return;
    }
    NodoFila *atual = fila->inicio;
    while (atual) {
        fprintf(f, "%s;%s\n", atual->musica->artista, atual->musica->titulo);
        atual = atual->prox;
    }
    fclose(f);
}

void exportarFilaCompleta(DescFila *fila, const char *nomeArquivo) {
    if (!fila) return;
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao abrir arquivo %s para exportar!\n", nomeArquivo);
        return;
    }
    NodoFila *atual = fila->inicio;
    while (atual) {
        Musica *m = atual->musica;
        fprintf(f, "%s;%d;%s;%s;%d\n",
            m->artista, m->codigo, m->titulo, m->letra, m->execucoes);
        atual = atual->prox;
    }
    fclose(f);
}

void freeFila(DescFila *fila) {
    if (!fila) return;
    NodoFila *atual = fila->inicio;
    while (atual) {
        NodoFila *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(fila);
}

// ------- BUSCAS ------------

int buscarMusicaArquivo(const char *nomeArquivo, Musica *resultado, int criterio, const char *valorStr, int valorInt) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    char linha[512];
    Musica temp;

    while (fgets(linha, sizeof(linha), fp)) {
        if (sscanf(linha, "%255[^;];%d;%255[^;];%255[^;];%d",
            temp.artista, &temp.codigo, temp.titulo, temp.letra, &temp.execucoes) == 5) {
            
            int encontrou = 0;
            switch (criterio) {
                case 1: // código
                    if (temp.codigo == valorInt) encontrou = 1;
                    break;
                case 2: // artista
                    if (strcasecmp(temp.artista, valorStr) == 0) encontrou = 1;
                    break;
                case 3: // título
                    if (strcasecmp(temp.titulo, valorStr) == 0) encontrou = 1;
                    break;
            }
            if (encontrou) {
                *resultado = temp;
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}

int buscarMusicaPlaylistPorCodigo(DescFila *fila, int codigo, Musica *resultado) {
    if (!fila || !resultado) return 0;
    NodoFila *atual = fila->inicio;
    while (atual) {
        if (atual->musica->codigo == codigo) {
            *resultado = *(atual->musica);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int buscarMusicaPlaylistPorArtista(DescFila *fila, const char *artista, Musica *resultado) {
    if (!fila || !resultado || !artista) return 0;
    NodoFila *atual = fila->inicio;
    while (atual) {
        if (strcasecmp(atual->musica->artista, artista) == 0) {
            *resultado = *(atual->musica);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int buscarMusicaPlaylistPorTitulo(DescFila *fila, const char *titulo, Musica *resultado) {
    if (!fila || !resultado || !titulo) return 0;
    NodoFila *atual = fila->inicio;
    while (atual) {
        if (strcasecmp(atual->musica->titulo, titulo) == 0) {
            *resultado = *(atual->musica);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void buscarMusica(const char *nomeArquivo, Musica *resultado, DescFila *fila, DescPilha *pilha) {
    int bus, criterio;
    char valorStr[256];
    int valorInt;

    printf("\n=== BUSCA DE MÚSICAS ===\n");

    if (fila == NULL || fila->tamanho == 0) {
        printf("Playlist vazia ou não inicializada.\n");
    } else {
        printf("Playlist atual tem %d músicas.\n", fila->tamanho);
    }

    printf("Escolha o critério de busca:\n");
    printf("1 - Código\n2 - Artista\n3 - Título\n");
    scanf("%d", &criterio);
    getchar(); // consumir \n

    if (criterio == 1) {
        printf("Digite o código: ");
        scanf("%d", &valorInt);
        getchar();
        bus = buscarMusicaArquivo(nomeArquivo, resultado, criterio, NULL, valorInt);
    } else {
        printf("Digite o texto para busca (ex: nome artista ou título): ");
        fgets(valorStr, sizeof(valorStr), stdin);
        valorStr[strcspn(valorStr, "\n")] = 0;
        bus = buscarMusicaArquivo(nomeArquivo, resultado, criterio, valorStr, 0);
    }

    if (bus) {
        printf("Música encontrada no arquivo:\n");
        imprimirMusica(resultado);
    } else {
        printf("Música não encontrada no arquivo.\n");
    }
}

