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

produto* criarProduto(int codigo, const char* descricao, float preco);
void inserirProduto(produto** lista, produto* novo);
void imprimirProdutos(produto* lista);
void desalocarProdutos(produto** lista);

itemEstoque* criarItemEstoque(int codigo_produto, int quantidade);
void inserirItemEstoque(itemEstoque** lista, itemEstoque* novo);
void imprimirEstoque(itemEstoque* lista);
void desalocarEstoque(itemEstoque** lista);

itemCarrinho* criarItemCarrinho(int codigo, int qtd, float preco_unit);
void inserirItemCarrinho(carrinho* c, itemCarrinho* novo);
void removerItemCarrinho(carrinho* c, int codigo);
void imprimirCarrinho(carrinho* c);
void desalocarCarrinho(carrinho* c);

void desalocarPonteiro(void **p);

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
                //imprimirCarrinho(//carrinho//);
                int subopcao=-1;
                printf("Gostaria de:\nAdicionar item ao carrinho-1\nRemover item do carrinho-2\nVoltar ao menu principal-3\n");
                scanf("%d",&subopcao);
                switch(subopcao){
                    case 1:
                    //adicionar//
                    break;
                    case 2:
                    //remover//
                    break;
                    case 3:
                    //voltar//
                    break;
                }

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

produto* criarProduto(int codigo, const char* descricao, float preco){
    produto* novo=(produto*)malloc(sizeof(produto));
    novo->codigo=codigo;
    strncpy(novo->descricao, descricao, 64);
    novo->preco=preco;
    novo->prox=NULL;
    return novo;
}

void inserirProduto(produto** lista, produto* novo){
    novo->prox=*lista;
    *lista=novo;
}

void imprimirProdutos(produto* lista){
    produto* atual=lista;
    while(atual!=NULL){
        printf("Codigo: %d\nDescricao: %s\nPreco: %.2f\n\n", atual->codigo, atual->descricao, atual->preco);
        atual=atual->prox;
    }
}

void desalocarProdutos(produto** lista){
    produto* atual=*lista;
    produto* temp;
    while(atual!=NULL){
        temp=atual;
        atual=atual->prox;
        free(temp);
    }
    *lista=NULL;
}

void desalocarPonteiro(void **p){
    free(*p);
    *p=NULL;
}