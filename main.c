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
    struct carrinho *prox;
}carrinho;

//--------------------------------------------------------------------------------//
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
void removerItemCarrinho(carrinho* c, int codigo, int quantidade_remover);//

filial* criarFilial(int id, const char* nome);//
void inserirFilial(filial** lista, filial* nova);//
void imprimirFiliais(filial* lista);//
void desalocarFiliais(filial** lista);//

carrinho *criarCarrinho(itemCarrinho *itens);//
void inserirCarrinho(carrinho **lista, carrinho *novo);//
void imprimirCarrinhos(carrinho *lista);//
void imprimirCarrinho(carrinho* c);//
void desalocarCarrinho(carrinho* c);//
void imprimirListaCarrinhos(carrinho* lista);//

int verificarDisponibilidade(carrinho* c, filial* f);//

void desalocarPonteiro(void **p);//

void carregarDados(produto** lista_produtos, filial** lista_filiais, carrinho **carrinho_cliente);//

void buscarItemEstoquePorCodigo(filial* lista_filiais, int codigo_produto, int quantidade_desejada);//
void buscarItemEstoquePorDescricao(filial* lista_filiais, produto* lista_produtos, const char* descricao, int quantidade_desejada);//

int main(){
    carrinho* carrinhos_clientes=NULL;

    filial* filiais=NULL;

    produto* produtos=NULL;

    int opcao=-1;
    while (opcao!=0){
        printf("O que gostaria de fazer?\nCarregar dados-1\nPesquisar por codigo ou descricao-2\nListar itens no carrinho/Remover/Adicionar-3\nVerificar disponibilidade-4\nEscolher filial para finalizar a compra-5\nGerar relatorios-6\nSair do programa gerando relatorio e desalocando memoria-0\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                carregarDados(&produtos, &filiais, &carrinhos_clientes);
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
                if (carrinhos_clientes==NULL || produtos==NULL || carrinhos_clientes->itens==NULL){
                    printf("Carrinho vazio ou produtos nao carregados. Tente novamente.\n");
                    break;
                }
                imprimirCarrinho(carrinhos_clientes);
                int subopcao2=-1;
                printf("\nGostaria de:\nAdicionar item ao carrinho-1\nRemover item do carrinho-2\nVoltar ao menu principal-3\n");
                scanf("%d",&subopcao2);
                switch(subopcao2){
                    case 1:
                        int codigo_add=0, quantidade_add=0, achou=0;
                        float preco_add=0.0;
                        produto *paux=produtos;
                        printf("Qual item gostaria de adicionar?(codigo)\n");
                        scanf("%d",&codigo_add);
                        while (paux!=NULL){
                            if(paux->codigo==codigo_add){
                                preco_add=paux->preco;
                                achou=1;
                                break;
                            }
                            paux=paux->prox;
                        }
                        if(achou==0){
                            printf("Produto nao encontrado. Tente novamente.\n");
                                break;
                        }
                        printf("Qual a quantidade desejada?\n");
                        scanf("%d",&quantidade_add);
                        inserirItemCarrinho(carrinhos_clientes, criarItemCarrinho(codigo_add, quantidade_add, preco_add));
                    break;
                    case 2:
                        int codigo_rem=0, quantidade_rem=0, achou1=0;
                        printf("Qual item gostaria de remover?(codigo)\n");
                        scanf("%d",&codigo_rem);
                        produto *paux1=produtos;
                        while (paux1!=NULL){
                            if(paux1->codigo==codigo_rem){
                                achou1=1;
                                break;
                            }
                            paux1=paux1->prox;
                        }
                        if(achou1==0){
                            printf("Produto nao encontrado. Tente novamente.\n");
                            break;
                        }
                        printf("Qual a quantidade desejada?\n");
                        scanf("%d",&quantidade_rem);
                        removerItemCarrinho(carrinhos_clientes, codigo_rem, quantidade_rem);
                    break;
                }
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
    imprimirFiliais(filiais);
    imprimirCarrinho(carrinhos_clientes);
    imprimirProdutos(produtos);
    imprimirListaCarrinhos(carrinhos_clientes);
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

void removerItemCarrinho(carrinho* c, int codigo, int quantidade_remover) {
    if (!c || !c->itens || quantidade_remover <= 0) return;

    itemCarrinho *atual = c->itens, *anterior = NULL;
    while (atual) {
        if (atual->codigo_produto == codigo) {
            if (quantidade_remover >= atual->qtd) {
                // Remove o item inteiro
                if (anterior) {
                    anterior->prox = atual->prox;
                } else {
                    c->itens = atual->prox;
                }
                c->total -= atual->qtd * atual->preco_unit;
                free(atual);
            } else {
                // Remove apenas parte da quantidade
                atual->qtd -= quantidade_remover;
                c->total -= quantidade_remover * atual->preco_unit;
            }
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

carrinho* criarCarrinho(itemCarrinho* itens) {
    carrinho* novo = (carrinho*)malloc(sizeof(carrinho));
    if (!novo) {
        printf("Erro na alocacao da lista de carrinhos\n");
        return NULL;
    }

    novo->itens = itens;
    novo->total = 0.0;
    novo->prox = NULL;

    itemCarrinho* atual = itens;
    while (atual) {
        novo->total += atual->qtd * atual->preco_unit;
        atual = atual->prox;
    }

    return novo;
}

void inserirCarrinho(carrinho **lista, carrinho *novo){
    if (*lista == NULL) {
        // Primeiro carrinho: aponta para si mesmo
        novo->prox = novo;
        *lista = novo;
    }
    else{
    novo->prox = (*lista)->prox;
    (*lista)->prox = novo;
    *lista = novo;
    }
}


void imprimirListaCarrinhos(carrinho* lista) {
    if (!lista) {
        printf("Nenhum carrinho registrado.\n");
        return;
    }

    int contador = 1;
    carrinho* atual = lista->prox; // começa pelo primeiro carrinho

    do {
        printf("\nCarrinho %d:\n", contador++);
        printf("Total: R$ %.2f\n", atual->total);

        itemCarrinho* item = atual->itens;
        if (!item) {
            printf("  (Carrinho vazio)\n");
        } else {
            while (item) {
                printf("  Produto: %d | Quantidade: %d | Preço unitário: R$ %.2f\n",
                       item->codigo_produto, item->qtd, item->preco_unit);
                item = item->prox;
            }
        }

        atual = atual->prox;
    } while (atual != lista->prox); // volta ao primeiro carrinho
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



void carregarDados(produto** lista_produtos, filial** lista_filiais, carrinho **carrinho_cliente) {
    FILE *PRODUTOS = fopen("produtos_v2.txt", "r");
    FILE *FILIAIS = fopen("filiais_v2.txt", "r");
    FILE *ESTOQUES = fopen("estoques_v2.txt", "r");
    FILE *CARRINHO = fopen("carrinhos_clientes_v2.txt", "r");

    if (!PRODUTOS || !FILIAIS || !ESTOQUES || !CARRINHO) {
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

    // Carregar carrinho
    char linha_c[128];
    int id_carrinho = -1;
    carrinho* atual = NULL;

    while (fgets(linha_c, sizeof(linha_c), CARRINHO) != NULL) {
        if (linha_c[0] == '#' || strlen(linha_c) < 2) continue;

        char comando[32];
        int cod_produto, qtd;
        sscanf(linha_c, "%s", comando);

        if (strcmp(comando, "NOVO_CARRINHO") == 0) {
            sscanf(linha_c, "%*s %d", &id_carrinho);
            atual = criarCarrinho(NULL); // cria novo carrinho
            if (*carrinho_cliente == NULL){
                atual->prox = atual;
                *carrinho_cliente = atual;
            }
            else{
            atual->prox = (*carrinho_cliente)->prox;
            (*carrinho_cliente)->prox = atual; // insere no final da lista
            *carrinho_cliente = atual;
            }

        } else if (strcmp(comando, "ADD") == 0) {
            sscanf(linha_c, "%*s %d %d", &cod_produto, &qtd);
            produto* p = *lista_produtos;
            while (p && p->codigo != cod_produto) p = p->prox;
            if (p) {
                itemCarrinho* novo = criarItemCarrinho(cod_produto, qtd, p->preco);
                inserirItemCarrinho(atual, novo);
            }
        } else if (strcmp(comando, "FIM") == 0) {
            atual = NULL;
            id_carrinho = -1;
        }
    }

    fclose(PRODUTOS);
    fclose(FILIAIS);
    fclose(ESTOQUES);
    fclose(CARRINHO);

    printf("Dados carregados com sucesso!\n");
}

