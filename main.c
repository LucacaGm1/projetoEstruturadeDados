#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
    int chave;
    struct no *prox;
}no;

typedef struct produto{
    int codigo;
    char descricao[64];
    float preco;
    struct produto *prox;
}produto;

typedef struct itemEstoque{
    int codigo_produto;
    int quantidade;
    struct itemEstoque *prox;
}itemEstoque;

typedef struct filial{
    int id_filial;
    char nome[40];
    itemEstoque *estoque;
    struct filial *prox;
}filial;

typedef struct itemCarrinho{
    int codigo_produto;
    int qtd;
    float preco_unit;
    struct itemCarrinho *prox;
}itemCarrinho;

typedef struct carrinho{
    itemCarrinho *itens;
    float total;
}carrinho;

no *alocano(int k);
void insereInicio(int k, no **lista);
void imprimirLista(no *lista);
void desalocar(void **p);

int main(){
    FILE *CARRINHOS, *ESTOQUES, *PRODUTOS, *FILIAIS;
    int opcao=-1;
    while (opcao!=0){
        printf("O que gostaria de fazer?\nCarregar dados-1\nPesquisar por codigo ou descricao-2\nListar itens no carrinho/Remover/Adicionar-3\nVerificar disponibilidade-4\nEscolher filial para finalizar a compra-5\nGerar relatorios-6\nSair do programa gerando relatorio e desalocando memoria-0\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
            //arquivos//
            break;
            case 2:
            //receber um codigo ou descrição/nome e buscar nas listas estoque//
            break;
            case 3:
            //imprimir lista carrinho//
            //buscar e reduzir a quantidade desejada de um produto ou buscar e aumentar/se nao encontrar adicionar à lista carrinho//
            break;
            case 4:
            //buscar cada item do carrinho em cada uma das filiais e dizer quais têm disponibilidade de todos e quais não têm e o que falta, caso não tenha algum item//
            break;
            case 5:
            //abater do estoque da filial escolhida//
            break;
            case 6:
            //arquivos//
            break;
        }
        //desalocar, arquivos(relatórios)//
    }
    return 0;
}

//--------------------------------------------------------------------------------//

no *alocano(int k){
    no *novono=malloc(sizeof(no));
    novono->chave=k;
    if(novono)
        return novono;
    printf("Erro na alocação");
    return NULL;
}
void insereInicio(int k, no **lista){
    no *noinicio=alocano(k);
    noinicio->prox=*lista;
    *lista=noinicio;
}
void imprimirLista(no *lista){
    if(lista){
        while(lista){
        printf("%d", lista->chave);
        lista=lista->prox;
        }
    }
    else
        printf("Lista vazia!");
}

void desalocar(void **p){
    free(*p);
    *p=NULL;
}

void desalocarLista(no **lista) {
    no *atual = *lista;
    while (atual != NULL) {
        no *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista = NULL; //sim ou nao
}