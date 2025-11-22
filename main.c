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
    int id_filial_finalizada;
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
void desalocarListaCarrinhos(carrinho** lista);//
void imprimirListaCarrinhos(carrinho* lista);//

void verificarDisponibilidade(carrinho* c, filial* f);//
void abaterEstoque(carrinho* c, filial* f, int id_filial_destino, int modo_automatico);//
void carregarDados(produto** lista_produtos, filial** lista_filiais, carrinho **carrinho_cliente);//

void buscarItemEstoquePorCodigo(filial* lista_filiais, int codigo_produto, int quantidade_desejada);//
void buscarItemEstoquePorDescricao(filial* lista_filiais, produto* lista_produtos, const char* descricao, int quantidade_desejada);//

void gerarRelatorioGeral(carrinho* lista_carrinhos, filial* lista_filiais, produto* lista_produtos);//
void desalocarPonteiro(void **p);//

//--------------------------------------------------------------------------------//

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
                if (carrinhos_clientes==NULL || filiais==NULL || produtos==NULL){
                        printf("Dados nao foram carregados, tente novamente.\n");
                        break;
                }

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
                if (produtos==NULL || filiais==NULL){
                    printf("Produtos ou filiais nao carregados. Tente novamente.\n");
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
                verificarDisponibilidade(carrinhos_clientes, filiais);
            break;
            case 5:
            if(carrinhos_clientes==NULL || filiais==NULL){
                printf("Carrinho vazio ou filiais nao carregadas. Tente novamente.\n");
                break;
            }
                int opcao_finalizar=-1;
                printf("Escolha a filial para finalizar a compra:\n");
                scanf("%d",&opcao_finalizar);
                abaterEstoque(carrinhos_clientes, filiais, opcao_finalizar, 0);
            break;
// ...
            case 6:
                gerarRelatorioGeral(carrinhos_clientes, filiais, produtos);
            break;
        }
    }
    printf("\nGerando relatorio final antes de sair...\n");
    gerarRelatorioGeral(carrinhos_clientes, filiais, produtos);
    imprimirFiliais(filiais);
    imprimirCarrinho(carrinhos_clientes);
    imprimirProdutos(produtos);
    imprimirListaCarrinhos(carrinhos_clientes);

    printf("\n--- Desalocando Memoria ---\n");
    desalocarProdutos(&produtos);
    desalocarFiliais(&filiais);
    desalocarListaCarrinhos(&carrinhos_clientes);

    // verifica se tudo foi desalocado
    if (produtos == NULL && filiais == NULL && carrinhos_clientes == NULL) {
        printf("Toda a memoria alocada foi desalocada com sucesso.\n");
    } else {
        printf("AVISO: Algumas listas nao foram completamente desalocadas.\n");
    }

    printf("saindo...\n");
    return 0;
}

//--------------------------------------------------------------------------------//

produto* criarProduto(int codigo, const char* descricao, float preco){
    produto* novo=(produto*)malloc(sizeof(produto));
    if(!novo){
    printf("Falha na alocacao de memoria para novo produto.\n");
    return NULL;
    }
    novo->codigo=codigo;
    strncpy(novo->descricao, descricao, 64);
    novo->preco=preco;
    novo->prox=NULL;
    return novo;
}

void inserirProduto(produto** lista, produto* novo){
    if(novo==NULL || lista==NULL) return;
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
    if(c==NULL){
        printf("Carrinho vazio.\n");
        return;
    }
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
    if(lista==NULL){
        printf("Nenhuma filial registrada.\n");
        return;
    }
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
    novo->id_filial_finalizada = -1;

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
                printf("  Produto: %d | Quantidade: %d | Preco unitario: R$ %.2f\n",
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
        printf("Produto nao existe ou nao este disponivel na quantidade desejada em nenhuma filial.\n");
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
        if (PRODUTOS) fclose(PRODUTOS);
        if (FILIAIS) fclose(FILIAIS);
        if (ESTOQUES) fclose(ESTOQUES);
        if (CARRINHO) fclose(CARRINHO);
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
        } else if (strcmp(comando, "REMOVE") == 0) {
            sscanf(linha_c, "%*s %d %d", &cod_produto, &qtd);
            if (atual != NULL) {
                removerItemCarrinho(atual, cod_produto, qtd);
            }
        } else if (strcmp(comando, "VERIFICAR_ATENDIMENTO") == 0) { // <-- Modificação aqui
            if (atual != NULL) {
                verificarDisponibilidade(atual, *lista_filiais);
            }
        } else if (strcmp(comando, "FINALIZAR") == 0) {
            int id_filial_destino;
            sscanf(linha_c, "%*s %d", &id_filial_destino);
            if (atual != NULL) {
                abaterEstoque(atual, *lista_filiais, id_filial_destino, 1); 
            }
        } else if (strcmp(comando, "FIM") == 0) {
            if (atual != NULL) {
                if (atual->id_filial_finalizada == -1) {
                    atual->id_filial_finalizada = -2; // Código para CANCELADO
                }
            }

            atual = NULL;
            id_carrinho = -1;
        }
    }

    // Fechar arquivos
    fclose(PRODUTOS);
    fclose(FILIAIS);
    fclose(ESTOQUES);
    fclose(CARRINHO);
}


void verificarDisponibilidade(carrinho* c, filial* f) {
    if (c == NULL || c->itens == NULL) { //verifição
        printf("O carrinho esta vazio ou nao esta registrado.\n");
        return;
    }
    if (f == NULL) { //verificação
        printf("Nenhuma filial registrada.\n");
        return;
    }

    printf("\nDisponibilidade\n");

    filial* filial_atual = f;
    int qualquer_filial_ok = 0;

    while (filial_atual != NULL) { //primeiro loop que percorre as filiais
        printf("Verificando Filial: %s (ID: %d)...\n", filial_atual->nome, filial_atual->id_filial);
        int itens_faltantes = 0;
        int itens_totais = 0;
        itemCarrinho* itemC = c->itens;

        while (itemC != NULL) { //loop que percorre os itens do carrinho
            itemEstoque* itemEstoque = filial_atual->estoque;
            int estoque = 0;
            int achou = 0;

            while (itemEstoque != NULL) { //loop que percorre estoque das fliais
                if (itemEstoque->codigo_produto == itemC->codigo_produto) {
                    estoque = itemEstoque->quantidade;
                    achou = 1; //se encontrou, da um break e volta para o loop dos itens dos carrinhos, se não, continua procurando no estoque
                    break;
                }
                itemEstoque = itemEstoque->prox;
            }
            if (!achou || estoque < itemC->qtd) { //se saiu do loop do estoque e não encontrou o item ou a quantidade em estoque é menor que o item escolhido, mostra o
                                                  //item que fala, a quantidade e soma no contador de itens faltantes
                printf("Indisponivel: Produto %d.(Precisa: %d, Tem: %d)\n", itemC->codigo_produto, itemC->qtd, estoque);
                itens_faltantes++;
            }
            itens_totais++;
            itemC = itemC->prox;
        }
        if (itens_faltantes == 0) {
            printf("A filial possui todos os produtos\n");
            qualquer_filial_ok = 1; // encontrou uma filial que atende ao carrinho
        } else if (itens_faltantes == itens_totais) {
            printf("Esta filial nao possui nenhum dos itens desejados.\n");
        } else {
            printf("Falta(m) %d item(ns).\n", itens_faltantes);
        }
        printf("\n");

        filial_atual = filial_atual->prox; //vai para a próxima filial
    }
    // se nenhuma filial atendeu completamente ao pedido
    if (!qualquer_filial_ok) {
        printf("Nenhuma filial esta apta para realizar a compra.\n");
    }

    return;
}

void abaterEstoque(carrinho* c, filial* f, int id_filial_destino, int modo_automatico) {

    if (c == NULL || c->itens == NULL) { //verificação
        printf("O carrinho esta vazio ou nao existe.\n");
        return;
    }
    if (f == NULL) { //verificação
        printf("Nenhuma filial registrada.\n");
        return;
    }

    filial* f_escolhida = f;
    while (f_escolhida != NULL && f_escolhida->id_filial != id_filial_destino) { // Usando o novo parâmetro
        f_escolhida = f_escolhida->prox; //se não é a primeira filial percorre
    }

    if (f_escolhida == NULL) { //se não encontra a filial retorna
        printf("Filial com ID %d nao encontrada. A compra nao pode ser finalizada.\n", id_filial_destino);
        return;
    }

    printf("\nProcessando compra na filial: %s\n", f_escolhida->nome);

    itemCarrinho* atual = c->itens;
    itemCarrinho* anterior = NULL;
    int houve_ajuste = 0; //conta quantos itens foram ajustados

    // --- Parte 1: Ajuste do Carrinho (Verificação de Estoque) ---
    while (atual != NULL) {
        itemEstoque* est = f_escolhida->estoque; //ponteiro para o estoque da filial escolhida
        int qtd_estoque = 0; //guarda a quantidade dos itens se existirem no estoque

        while (est != NULL) {
            if (est->codigo_produto == atual->codigo_produto) { //se o item existir no estoque
                qtd_estoque = est->quantidade; //guarda a quantidade em estoque
                break; //sai do while
            }
            est = est->prox;
        }

        if (qtd_estoque < atual->qtd) { //se a quantidade do estoque for menor
            houve_ajuste = 1;
            printf("Ajuste no produto %d: Pedido %d -> Disponivel %d\n", atual->codigo_produto, atual->qtd, qtd_estoque);
            atual->qtd = qtd_estoque; //ajusta o carrinho para ter aquantidade disponivel na filial
        }

        if (atual->qtd == 0) { //se a quantidade é 0 remove o item do carrinho
            printf("Produto %d removido do carrinho (Sem estoque).\n", atual->codigo_produto);

            itemCarrinho* temp = atual;

            if (anterior == NULL) {
                c->itens = atual->prox; // era o primeiro da lista
                atual = c->itens;
            }
            else {
                anterior->prox = atual->prox; // era um item do meio/fim
                atual = anterior->prox;
            }
            free(temp); // libera memória do item removido
        }
        else { //se for maior ou igual continua percorrendo
            anterior = atual;
            atual = atual->prox;
        }
    }

    // --- Parte 2: Finalização da Compra e Abate ---
    if (c->itens == NULL) { //se a filial não tiver nenhum dos itens
        c->total = 0.0;
        printf("\nCOMPRA CANCELADA\n");
        printf("A filial escolhida nao possui nenhum dos itens desejados.\n");
        return;
    }

    float novo_total = 0.0;
    itemCarrinho* aux = c->itens;
    while (aux != NULL) { //se tiver pelo menos um altera o valor do carrinho principal
        novo_total += aux->qtd * aux->preco_unit;
        aux = aux->prox;
    }
    c->total = novo_total;

    if (houve_ajuste) {
        printf("\nO carrinho foi ajustado automaticamente conforme o estoque.\n");
        printf("Novo Total: %.2f\n", c->total);

        if (modo_automatico) {
            printf("Compra automatica: CONFIRMADA APÓS AJUSTE.\n");
        } else {
            // case 5: pergunta ao usuário
            printf("Deseja confirmar a compra com esses itens? (1-Sim / 0-Nao): ");
            int confirma;
            scanf("%d", &confirma);
            if (confirma != 1) {
                printf("Compra cancelada pelo usuario.\n");
                return;
            }
        }
    }

    atual = c->itens;
    while (atual != NULL) {
        itemEstoque* est = f_escolhida->estoque;
        while (est != NULL) {
            if (est->codigo_produto == atual->codigo_produto) {
                est->quantidade -= atual->qtd;
                break;
            }
            est = est->prox;
        }
        atual = atual->prox;
    }
    c->id_filial_finalizada = id_filial_destino;

    printf("\nVENDA CONCLUÍDA COM SUCESSO!\n");
    printf("Estoque da filial %s atualizado.\n", f_escolhida->nome);
}

void desalocarListaCarrinhos(carrinho** lista) {
    if (*lista == NULL) {
        return;
    }

    carrinho* cabeca = (*lista)->prox;
    carrinho* atual = cabeca;
    carrinho* temp;

    // quebra a ligação circular
    (*lista)->prox = NULL;

    // percorre a lista
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        desalocarCarrinho(temp);
        free(temp);
    }

    *lista = NULL;
}

void gerarRelatorioGeral(carrinho* lista_carrinhos, filial* lista_filiais, produto* lista_produtos) {
    FILE *arq = fopen("relatorio_final.txt", "w"); // "w" para limpar o arquivo antigo e criar um novo
    if (!arq) {
        printf("Erro ao abrir arquivo de relatorio.\n");
        return;
    }

    // ==========================================
    // PARTE 1: RELATORIO DE CARRINHOS
    // ==========================================
    fprintf(arq, "=====================================================\n");
    fprintf(arq, "RELATORIO GERAL DE CARRINHOS E DIAGNOSTICO\n");
    fprintf(arq, "=====================================================\n");

    if (lista_carrinhos == NULL) {
        fprintf(arq, "Nenhum carrinho na memoria.\n");
    } else {
        carrinho *primeiro = lista_carrinhos->prox;
        if (primeiro == NULL) primeiro = lista_carrinhos;

        carrinho *atual = primeiro;
        int contador = 1;

        do {
            fprintf(arq, ">>> CARRINHO %d ", contador++);

            if (atual->id_filial_finalizada > 0) {
                fprintf(arq, "[STATUS: FINALIZADO na Filial ID %d]\n", atual->id_filial_finalizada);
            }
            else if (atual->id_filial_finalizada == -2) {
                fprintf(arq, "[STATUS: CANCELADO / ABANDONADO]\n");
            }
            else {
                fprintf(arq, "[STATUS: EM ABERTO]\n");
            }

            itemCarrinho *ic = atual->itens;
            if (!ic) fprintf(arq, "    (Sem itens no momento)\n");

            float total_carrinho = 0;
            while (ic != NULL) {
                fprintf(arq, "    - Prod: %d | Qtd: %d | R$ %.2f\n", ic->codigo_produto, ic->qtd, ic->preco_unit);
                total_carrinho += (ic->qtd * ic->preco_unit);
                ic = ic->prox;
            }
            fprintf(arq, "    TOTAL: R$ %.2f\n", total_carrinho);


            if (atual->id_filial_finalizada == -1 && lista_filiais != NULL) {
                fprintf(arq, "    --- Analise de Disponibilidade ---\n");
                filial *f = lista_filiais;
                int alguma_atende = 0;

                while (f != NULL) {
                    itemCarrinho *check = atual->itens;
                    int faltas = 0;
                    while (check != NULL) {
                        itemEstoque *est = f->estoque;
                        int tem = 0;
                        while (est) {
                            if (est->codigo_produto == check->codigo_produto) {
                                tem = est->quantidade; break;
                            }
                            est = est->prox;
                        }
                        if (tem < check->qtd) faltas++;
                        check = check->prox;
                    }

                    if (faltas == 0) {
                        fprintf(arq, "    [V] Filial %s (ID %d): ATENDE COMPLETO\n", f->nome, f->id_filial);
                        alguma_atende = 1;
                    } else {
                        fprintf(arq, "    [X] Filial %s (ID %d): Faltam itens\n", f->nome, f->id_filial);
                    }
                    f = f->prox;
                }
                if(!alguma_atende) fprintf(arq, "    >> Nenhuma filial atende o pedido completo.\n");
            }

            fprintf(arq, "-----------------------------------------------------\n");
            atual = atual->prox;
        } while (atual != NULL && atual != primeiro);
    }
    fprintf(arq, "\n\n");

    // ==========================================
    // PARTE 2: RELATORIO DE ESTOQUE
    // ==========================================
    fprintf(arq, "=====================================================\n");
    fprintf(arq, "RELATORIO DE ESTOQUE POR FILIAL\n");
    fprintf(arq, "=====================================================\n");

    filial *f = lista_filiais;
    if (f == NULL) {
        fprintf(arq, "Nenhuma filial cadastrada.\n");
    }

    while (f != NULL) {
        fprintf(arq, "FILIAL: %s (ID: %d)\n", f->nome, f->id_filial);

        itemEstoque *ie = f->estoque;
        if (ie == NULL) {
            fprintf(arq, "  (Estoque Vazio)\n");
        } else {
            fprintf(arq, "  CODIGO | DESCRICAO                     | QTD | PRECO UNIT\n");
            while (ie != NULL) {
                char descricao[64] = "Produto nao cadastrado";
                float preco = 0.0;

                produto *p = lista_produtos;
                while(p != NULL){
                    if(p->codigo == ie->codigo_produto){
                        strncpy(descricao, p->descricao, 64);
                        preco = p->preco;
                        break;
                    }
                    p = p->prox;
                }

                fprintf(arq, "  %-6d | %-29s | %-3d | R$ %.2f\n",
                        ie->codigo_produto, descricao, ie->quantidade, preco);

                ie = ie->prox;
            }
        }
        fprintf(arq, "-----------------------------------------------------\n");
        f = f->prox;
    }

    fclose(arq);
    printf("Relatorio completo (Carrinhos + Estoque) gerado em 'relatorio_final.txt'.\n");
}
