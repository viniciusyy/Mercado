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
void visualizarCarrinho();
Produto pegarProdutoPorCodigo();
int * temNoCarrinho();
void fecharProduto();

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
    
}

// ----------------- Cadastrar os produtos --------------------------
void cadastrarProduto(){

}

// ----------------- Listar os produtos --------------------------
void listarProdutos(){

}

// ----------------- Visualizar o carrinho --------------------------
void visualizarCarrinho(){

}

// ----------------- Pegar o produto pelo código --------------------------
Produto pegarProdutoPorCodigo(){

}

// ----------------- Verificar se o produto está no carrinho --------------------------
int * temNoCarrinho(){

}

// ----------------- Fechar o produto --------------------------
void fecharProduto(){

}