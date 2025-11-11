#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

produto* criarProduto(int codigo, const char* descricao, float preco);//
void inserirProduto(produto** lista, produto* novo);//
void imprimirProdutos(produto* lista);//
void desalocarProdutos(produto** lista);//

itemEstoque* criarItemEstoque(int codigo_produto, int quantidade);//
void inserirItemEstoque(itemEstoque** lista, itemEstoque* novo);//
void imprimirEstoque(itemEstoque* lista);//
void desalocarEstoque(itemEstoque** lista);//

itemCarrinho* criarItemCarrinho(int codigo, int qtd, float preco_unit);//
void inserirItemCarrinho(carrinho* c, itemCarrinho* novo);//
void removerItemCarrinho(carrinho* c, int codigo);//
void imprimirCarrinho(carrinho* c);//
void desalocarCarrinho(carrinho* c);//

filial* criarFilial(int id, const char* nome);//
void inserirFilial(filial** lista, filial* nova);//
void imprimirFiliais(filial* lista);//
void desalocarFiliais(filial** lista);//

void desalocarPonteiro(void **p);//

void carregarDados(produto** lista_produtos, filial** lista_filiais);//

void buscarItemEstoquePorCodigo(filial* lista_filiais, int codigo_produto, int quantidade_desejada);//
void buscarItemEstoquePorDescricao(filial* lista_filiais, produto* lista_produtos, const char* descricao, int quantidade_desejada);//

int main(){
    carrinho* carrinho_cliente=(carrinho*)malloc(sizeof(carrinho));
    carrinho_cliente->itens=NULL;
    carrinho_cliente->total=0.0;

    filial* filiais=NULL;

    produto* produtos=NULL;

    int opcao=-1;
    while (opcao!=0){
        printf("O que gostaria de fazer?\nCarregar dados-1\nPesquisar por codigo ou descricao-2\nListar itens no carrinho/Remover/Adicionar-3\nVerificar disponibilidade-4\nEscolher filial para finalizar a compra-5\nGerar relatorios-6\nSair do programa gerando relatorio e desalocando memoria-0\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                carregarDados(&produtos, &filiais);
            break;
            case 2:
                int subopcao=-1;
                printf("Gostaria de buscar por codigo-1 ou descricao-2?\n");
                scanf("%d",&subopcao);
                switch(subopcao){
                    case 1:
                        int codigo_produto;
                        printf("Digite o codigo do produto:\n");
                        scanf("%d",&codigo_produto);
                        int quantidade_desejada;
                        printf("Digite a quantidade desejada:\n");
                        scanf("%d",&quantidade_desejada);
                        buscarItemEstoquePorCodigo(filiais, codigo_produto, quantidade_desejada);
                    break;
                    case 2:
                        char descricao_produto[64];
                        printf("Digite a descricao do produto:\n");
                        scanf("%s",descricao_produto);
                        int quantidade_desejada2;
                        printf("Digite a quantidade desejada:\n");
                        scanf("%d",&quantidade_desejada2);
                        buscarItemEstoquePorDescricao(filiais, produtos, descricao_produto, quantidade_desejada2);
                    break;
                }
            break;
            case 3:
                imprimirCarrinho(carrinho_cliente);
                int subopcao2=-1;
                printf("\nGostaria de:\nAdicionar item ao carrinho-1\nRemover item do carrinho-2\nVoltar ao menu principal-3\n");
                scanf("%d",&subopcao2);
                switch(subopcao2){
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
        //desalocar carrinho//
    }
    //desalocar tudo e gerar relatorio final//
    printf("saindo...\n");
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

itemEstoque* criarItemEstoque(int codigo_produto, int quantidade) {
    itemEstoque* novo = (itemEstoque*)malloc(sizeof(itemEstoque));
    if (!novo) return NULL;

    novo->codigo_produto = codigo_produto;
    novo->quantidade = quantidade;
    novo->prox = NULL;

    return novo;
}

void inserirItemEstoque(itemEstoque** lista, itemEstoque* novo) {
    if (!lista || !novo) return;

    // Verifica se o produto já existe no estoque
    itemEstoque* atual = *lista;
    while (atual) {
        if (atual->codigo_produto == novo->codigo_produto) {
            atual->quantidade += novo->quantidade;
            free(novo); // já existe, só atualiza a quantidade
            return;
        }
        atual = atual->prox;
    }

    // Insere no início da lista
    novo->prox = *lista;
    *lista = novo;
}

void imprimirEstoque(itemEstoque* lista) {
    itemEstoque* atual = lista;
    printf("Estoque:\n");
    while (atual) {
        printf("Produto %d - Quantidade: %d\n", atual->codigo_produto, atual->quantidade);
        atual = atual->prox;
    }
}

void desalocarEstoque(itemEstoque** lista) {
    itemEstoque* atual = *lista;
    while (atual) {
        itemEstoque* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *lista = NULL;
}

itemCarrinho* criarItemCarrinho(int codigo, int qtd, float preco_unit) {
    itemCarrinho* novo = (itemCarrinho*)malloc(sizeof(itemCarrinho));
    if (!novo) return NULL;

    novo->codigo_produto = codigo;
    novo->qtd = qtd;
    novo->preco_unit = preco_unit;
    novo->prox = NULL;

    return novo;
}

void inserirItemCarrinho(carrinho* c, itemCarrinho* novo) {
    if (!c || !novo) return;
    itemCarrinho* atual = c->itens;
    while (atual) {
        if (atual->codigo_produto == novo->codigo_produto) {
            atual->qtd += novo->qtd;
            c->total += novo->qtd * atual->preco_unit;
            free(novo);
            return;
        }
        atual = atual->prox;
    }
    novo->prox = c->itens;
    c->itens = novo;
    c->total += novo->qtd * novo->preco_unit;
}

void removerItemCarrinho(carrinho* c, int codigo) {
    if (!c || !c->itens) return;
    itemCarrinho *atual = c->itens, *anterior = NULL;
    while (atual) {
        if (atual->codigo_produto == codigo) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                c->itens = atual->prox;
            }
            c->total -= atual->qtd * atual->preco_unit;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void desalocarCarrinho(carrinho* c) {
    if (!c) return;
    itemCarrinho* atual = c->itens;
    while (atual) {
        itemCarrinho* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    c->itens = NULL;
    c->total = 0.0;
}

void imprimirCarrinho(carrinho* c){
    itemCarrinho* atual=c->itens;
    printf("Itens no carrinho:\n");
    while(atual!=NULL){
        printf("Codigo do produto: %d\nQuantidade: %d\nPreco unitario: %.2f\n\n", atual->codigo_produto, atual->qtd, atual->preco_unit);
        atual=atual->prox;
    }
    printf("Total do carrinho: %.2f\n", c->total);
}

filial* criarFilial(int id, const char* nome){
    filial* nova=(filial*)malloc(sizeof(filial));
    nova->id_filial=id;
    strncpy(nova->nome, nome, 40);
    nova->estoque=NULL;
    nova->prox=NULL;
    return nova;

}

void inserirFilial(filial** lista, filial* nova){
    nova->prox=*lista;
    *lista=nova;
}

void imprimirFiliais(filial* lista){
    filial* atual=lista;
    while(atual!=NULL){
        printf("ID da filial: %d\nNome: %s\n", atual->id_filial, atual->nome);
        imprimirEstoque(atual->estoque);
        atual=atual->prox;
    }
}

void desalocarFiliais(filial** lista){
    filial* atual=*lista;
    filial* temp;
    while(atual!=NULL){
        temp=atual;
        atual=atual->prox;
        desalocarEstoque(&temp->estoque);
        free(temp);
    }
    *lista=NULL;
}

void desalocarPonteiro(void **p){
    free(*p);
    *p=NULL;
}

void buscarItemEstoquePorCodigo(filial* lista_filiais, int codigo_produto, int quantidade_desejada) {
    int encontrado = 0;
    filial* atual = lista_filiais;

    while (atual != NULL) {
        itemEstoque* item = atual->estoque;
        while (item != NULL) {
            if (item->codigo_produto == codigo_produto && item->quantidade >= quantidade_desejada) {
                printf("Produto disponivel na filial %s:\n", atual->nome);
                printf("Codigo: %d | Quantidade: %d\n", item->codigo_produto, item->quantidade);
                encontrado =1;
            }
            item = item->prox;
        }
        atual = atual->prox;
    }

    if (encontrado==0) {
        printf("Produto nao disponivel na quantidade desejada em nenhuma filial.\n");
    }
}

void buscarItemEstoquePorDescricao(filial* lista_filiais, produto* lista_produtos, const char* descricao, int quantidade_desejada) {
    int codigo_produto = -1;
    float preco = 0.0;

    // 1. Buscar o código do produto pela descrição
    produto* p = lista_produtos;
    while (p != NULL) {
        if (strcmp(p->descricao, descricao) == 0) {
            codigo_produto = p->codigo;
            preco = p->preco;
            break;
        }
        p = p->prox;
    }

    if (codigo_produto == -1) {
        printf("Produto com descricao '%s' nao encontrado.\n", descricao);
        return;
    }

    // 2. Procurar o produto nas filiais
    int encontrado = 0;
    filial* f = lista_filiais;
    while (f != NULL) {
        itemEstoque* item = f->estoque;
        while (item != NULL) {
            if (item->codigo_produto == codigo_produto && item->quantidade >= quantidade_desejada) {
                printf("Produto disponivel na filial %s:\n", f->nome);
                printf("Codigo: %d | Descricao: %s | Preco: %.2f | Quantidade: %d\n",
                       codigo_produto, descricao, preco, item->quantidade);
                encontrado = 1;
            }
            item = item->prox;
        }
        f = f->prox;
    }

    if (!encontrado) {
        printf("Produto '%s' nao disponivel na quantidade desejada em nenhuma filial.\n", descricao);
    }
}



void carregarDados(produto** lista_produtos, filial** lista_filiais) {
    FILE *PRODUTOS = fopen("produtos_v2.txt", "r");
    FILE *FILIAIS = fopen("filiais_v2.txt", "r");
    FILE *ESTOQUES = fopen("estoques_v2.txt", "r");

    if (!PRODUTOS || !FILIAIS || !ESTOQUES) {
        printf("Erro ao abrir um ou mais arquivos.\n");
        return;
    }

    // Carregar produtos
    int codigo;
    char descricao[64];
    float preco;
    while (fscanf(PRODUTOS, "%d %s %f", &codigo, descricao, &preco) == 3) {
        produto* novo = criarProduto(codigo, descricao, preco);
        inserirProduto(lista_produtos, novo);
    }

    // Carregar filiais
    char linha[100];
    int id_filial;
    char nome[40];

    while (fgets(linha, sizeof(linha), FILIAIS) != NULL) {
        if (sscanf(linha, "%d %[^\n]", &id_filial, nome) == 2) {
            filial* nova = criarFilial(id_filial, nome);
            inserirFilial(lista_filiais, nova);
        }
    }

    // Carregar estoques
    int filial_id, produto_id, quantidade;
    while (fscanf(ESTOQUES, "%d %d %d", &filial_id, &produto_id, &quantidade) == 3) {
        filial* f = *lista_filiais;
        while (f && f->id_filial != filial_id) {
            f = f->prox;
        }
        if (f) {
            itemEstoque* novo_item = criarItemEstoque(produto_id, quantidade);
            inserirItemEstoque(&(f->estoque), novo_item);
        }
    }

    fclose(PRODUTOS);
    fclose(FILIAIS);
    fclose(ESTOQUES);

    printf("Dados carregados com sucesso!\n");
}