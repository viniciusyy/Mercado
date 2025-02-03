#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;    
    int quantidade;    
} Carrinho;

void infoPruduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0; //Para saber quantos o produto foi cadastrado
static int contador_carrinho = 0; //Para saber quantos produto tem no carrinho
static Carrinho carrinho[50];  //Para adicionar itens no carrinho
static Produto produtos[50]; //Para cadastrar os produtos no array
    


int main() {

    menu();
    return 0;
}

// -----------------Imprimir as informasções do produto --------------------------
void infoPruduto(Produto prod){
    printf("Código: %d \n Nome: %s \n Preço: %.2f\n", prod.codigo), strtok(prod.nome, "\n"), prod.preco;
}

//----------------- Menu --------------------------
void menu(){
    printf("========================================\n");
    printf("================ Bem vindo ==============\n");
    printf("================= Mercado ==============\n");
    printf("========================================\n");

    printf("Escolha uma opção:\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Comprar produto\n");
    printf("4 - Visualizar carrinho\n");
    printf("5 - Fechar pedido\n");
    printf("6 - Sair\n");

    int opcao;
    scanf("%d", &opcao);
    getchar(); //Pra resolver aquele bug de pular linha

    switch(opcao){
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            visualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("Volte sempre");
            sleep(2);
            exit(0);
        default:
            printf("Opção inválida!\n");
            sleep(2);
            menu();
            break;
    }
}


// ----------------- Cadastrar os produtos --------------------------
void cadastrarProduto(){
    printf("Cadastro de produto\n");
    printf("===================\n");

    printf("Digite o nome do produto: ");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Digite o preço do produto: ");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O produto %s foi cadastrado com sucesso!\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = contador_produto + 1;
    contador_produto++;

    sleep(2);
    menu();
}

// ----------------- Listar os produtos --------------------------
void listarProdutos(){
    if(contador_produto > 0){            //Para verificar se tem algum produto cadastrado
        printf("Listagem de produtos\n");
        printf("=====================\n");
        for(int i = 0; i < contador_produto; i++){
            infoPruduto(produtos[i]);
            printf("-------------------\n");
            sleep(1);
        }
        sleep(2);
        menu();
    }
    else{
        printf("Nenhum produto cadastrado!\n");
        sleep(2);
        menu();
    }
}

// ----------------- Comprar o produto --------------------------
void comprarProduto(){  //Para verificar se tem algum produto cadastrado
    if(contador_produto > 0){ 
        printf("Informe o codigo do produto que deseja adicionar ao carrinho. \n");

        printf("============= Produtos disponíveis =============\n");
        for(int i = 0; i < contador_produto; i++){
            infoPruduto(produtos[i]);
            printf("-------------------\n");
            sleep(1);
        }

        int codigo;
        scanf("%d", &codigo);
        getchar(); 

        int tem_mercado = 0; //Para verificar se tem o produto no mercado
        
        for(int i = 0; i < contador_produto; i++){
            if(produtos[i].codigo == codigo){
                tem_mercado = 1;
                
                if(contador_carrinho > 0){
                    int * retorno = temNoCarrinho(codigo);

                    if(retorno[0] == 1){
                        carrinho[retorno[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s\n", strtok(carrinho[retorno[1]].produto.nome, "\n"));
                        sleep(2);
                        menu();
                    }
                    else{
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("Produto adicionado ao carrinho\n", strtok(p.nome, "\n"));
                        sleep(2);
                        menu();
                    }
                }
                else{
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("Produto adicionado ao carrinho\n", strtok(p.nome, "\n"));
                    sleep(2);
                    menu();
                }                   
            }
        }

        if(tem_mercado < 1){
            printf("Nao foi encontrado o produto com o codigo %d\n", codigo);
            sleep(2);
            menu();
        }
    }
    else{
        printf("Nenhum produto cadastrado!\n");
        sleep(2);
        menu();
    }
   
}

// ----------------- Visualizar o carrinho --------------------------
void visualizarCarrinho(){
    if(contador_carrinho > 0){      //Para verificar se tem algum produto no carrinho
        printf("Produtos no carrinho\n");
        printf("=====================\n");
        for(int i = 0; i < contador_carrinho; i++){
            infoPruduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("-------------------\n");
            sleep(1);
        }
        sleep(2);
        menu();
    }
    else{
        printf("Nao tem produto no carrinho");
        sleep(2);
        menu();
    }

}

// ----------------- Pegar o produto pelo código --------------------------
Produto pegarProdutoPorCodigo(int codigo){
    Produto p;
    for(int i = 0; i < contador_produto; i++){
        if(produtos[i].codigo == codigo){
            p = produtos[i];
        }
    }
    return p;

}

// ----------------- Verificar se o produto está no carrinho --------------------------
int * temNoCarrinho(int codigo){
    int static retorno [] = {0, 0}; //Indica que nao achou nada no carrinho
    for(int i = 0; i < contador_carrinho; i++){
        if(carrinho[i].produto.codigo == codigo){
            retorno[0] = 1; //Indica que tem o codigo no carrinho
            retorno[1] = i; //Indica o indice do produto no carrinho
        }
    }
    return retorno;
}

// ----------------- Fechar o produto --------------------------
void fecharPedido(){

    if(contador_carrinho > 0){
        float valorTotal = 0;
        printf("Produtos no carrinho\n");
        printf("=====================\n");
        for(int i = 0; i < contador_carrinho; i++){
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade; 
            infoPruduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("-------------------\n");
            sleep(1);
        }
        printf("O valor total do pedido foi de: %.2f\n", valorTotal);
        contador_carrinho = 0;    //Limpa o carrinho
        printf("Obrigado por comprar conosco!\n");
        sleep(5);
        menu();
    }
    else{
        printf("O carrinho esta vazio!\n");
        sleep(2);
        menu();
    }
}
