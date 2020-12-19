// Nome: Gustavo Henrique Coimbra Galo 		RA: 190667
// Nome: Juliana Mei Min Hua 				RA: 190824
// Nome: Vitor Joaquim de Carvalho Gois 	RA: 190810

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

#define MAX 100
#define PIN 102030
#define ARQUIVO "produtos.txt"

#define PRETO  		"\x1b[30m"
#define VERMELHO 	"\x1b[91m"
#define VERDE 		"\x1b[92m"
#define AZUL 		"\x1b[96m"
#define RESET		"\x1b[0m"
#define AMARELO 	"\x1b[93m"

FILE *file;

struct produto
{
	int id, quantidade; 
	double valor;
	char nome[10];	
};
int main()
{
	setlocale(LC_CTYPE, "");
	
	void desenharCabecalho();
	void desenharCabecalhoEstoque();
	void desenharCabecalhoNota();
	void desenharCabechalhoAdmin();
	
	void ListarProdutos();
	
	
	int loop, pin, tamanho, i, op, id, quantidade;
	double valorPagar, entrada, troco;
	struct produto Produto, ProdutosComprados[MAX];

	do
	{
		system("CLS");
		
		desenharCabecalho();
		
		printf("\n 	Olá, bem vindo! \n\n O que deseja realizar? \n\n\t [1] - Adicionar novos produtos.\n\t [2] - Consultar o estoque.\n\t [3] - Iniciar o sistema.\n\t [0] - Sair\n");
		printf("\n Informe a opção desejada > ");
		scanf("%d", &loop);
		
		
		switch(loop)
		{
			case 0:
				
				printf("\n Encerrando o sistema");
				Sleep(250);
				printf(".");
				Sleep(250);
				printf(".");
				Sleep(250);
				printf(".");
				
				sleep(1);
				
				exit(1);
				
				break;
				
			case 1: 
			
				sleep(1);
				system("CLS");
				
				desenharCabechalhoAdmin();
			
				printf("\n Informe PIN de acesso > " PRETO);
				scanf("%d", &pin);
				printf(RESET "");
				
				if (pin == PIN)
				{
					printf("\n Acessando o estoque");
					Sleep(300);
					printf(".");
					Sleep(300);
					printf(".");
					Sleep(300);
					printf(".");
					
					sleep(1);
					
					system("CLS");
					
					desenharCabecalhoEstoque();
					
					printf("\n Informe quantos produtos deseja adicionar > ");
					scanf("%d", &tamanho);
					
					for (i = 0; i < tamanho; i++)
					{
						
						printf("\n Nome do %iº produto > ", i + 1);
						fflush(stdin); 
						gets(Produto.nome);
						
						printf(" Valor unitário > R$", i + 1);
						scanf("%lf", &Produto.valor);

						
						if (WriteProduto(Produto)) printf("\n Produto adicionado com sucesso!\n");
					}
				}
				else printf("\n PIN NEGADO!");
				
				sleep(2);
				
				printf("\n Finalizando sessão");
				Sleep(250);
				printf(".");
				Sleep(250);
				printf(".");
				Sleep(250);
				printf(".");
				
				sleep(1);
			
				break;
			
			case 2: 
			
				sleep(1);
				
				system("CLS");
				
				desenharCabechalhoAdmin();
				
				printf("\n Informe PIN de acesso: " PRETO);
				scanf("%d", &pin);
				printf(RESET "");
				
				if (pin == PIN)
				{
			
					printf("\n Acessando estoque"); 
					Sleep(250);
					printf(".");
					Sleep(250);
					printf(".");
					Sleep(250);
					printf(".");
					
					sleep(1); 
					
					system("CLS"); 
					
					desenharCabecalhoEstoque();
					
					printf("\n Produtos: \n\n");
					
					ListarProdutos();

				}
				
				printf("\n\n Tecle ENTER para sair!\n");
				
				getch();
				
				break;
				
			case 3:
				
				printf("\n Abrindo o sistema");
				Sleep(300);
				printf(".");
				Sleep(300);
				printf(".");
				Sleep(300);
				printf(".");
				
				sleep(1);
				
				system("CLS");
		
				valorPagar = 0;
			
				file = fopen(ARQUIVO, "rb");
			
				if (file != NULL)
				{
					
					fclose(file);
					
					i = 0;
					
					do
					{
						
						if ( i >= MAX) 
						{
							system("CLS");
							desenharCabecalhoEstoque();
							printf("\n Você não pode comprar mais produtos, finalize a compra!");
						}
						else
						{
							
							system("CLS");
							
							desenharCabecalho();
							
							printf("\n Produtos: \n");
							
							ListarProdutos();
							
							do
							{
								printf("\n\n Informe o ID do produto desejado > ");
								scanf("%d", &id);
								
								if (id < 1 || id > GetQuantidade()) printf ("\n ID inválido!");
								
							}while(id < 1 || id > GetQuantidade());
							
							printf(" Quantidade desejada > ");
							scanf("%d", &quantidade);
							
							file = fopen(ARQUIVO, "rb");
							
							fseek(file, (id - 1)*(sizeof(struct produto)), SEEK_SET);
							
							if (fread(&Produto, sizeof(struct produto), 1, file) == 1) valorPagar += Produto.valor*quantidade;
							else printf("\n Erro no estoque.");
							
							fclose(file);
							
							Produto.quantidade = quantidade;
							
							ProdutosComprados[i] = Produto;
							
							i++;
						}
						
						do
						{
							
							printf("\n\t [1] - Continuar compra.\n\t [0] - Finalizar compra.\n\n Resposta > ");	
							scanf("%d", &op);
							
							if (op != 0 && op != 1) printf("\n Opção invalida.");
							
						}while(op != 0 && op != 1);
						
						if (op == 0)
						{
							sleep(1);
							
							system("CLS");
							
							desenharCabecalhoNota();
							
							printf("\n   \t\tNOME\tQUANTIDADE\tVALOR");
							
							for (tamanho = 0; tamanho < i; tamanho++)
							{
								printf("\n\t%10s\t%10d\t %4.2lf", ProdutosComprados[tamanho].nome, ProdutosComprados[tamanho].quantidade, ProdutosComprados[tamanho].valor);
							}
							printf("\n =======================================================\n");
							
							printf("\n TOTAL A PAGAR > R$%37.2lf\n", valorPagar);
							
							printf("\n =======================================================\n");
							
							do
							{
								printf("\n Troco para quanto > R$ \t\t\t   ");
                            	scanf("%lf", &entrada);
                            	
                            	if(entrada < valorPagar || entrada < 0)
                            	{
                            		printf(" Desculpe, mas o valor informado é inválido!\n");
								}
							}while(entrada < valorPagar || entrada < 0);
                           
                            troco = entrada - valorPagar;
                           
                            printf("\n Seu troco é  R$ %.2lf", troco);
							
							printf("\n\n Tecle ENTER para encerrar");
							Sleep(300);
							printf(".");
							Sleep(300);
							printf(".");
							Sleep(300);
							printf(".");
							
							getch();
							
						}
						
						
					}while(op != 0);
				}
		
				break;
				
			default:
				
				printf("\n Opção invalida.");
				printf("\n Voltando...");
				
				sleep(1);
				
				break;
		}
	}while(loop != 0);
}
void desenharCabecalhoNota()
{	
	printf("\n =======================================================\n");
	printf("\t\t Pobr's Wallet - NOTA FISCAL");
	printf("\n =======================================================\n");	
}
void desenharCabecalho()
{
	printf(AZUL "\n =======================================================\n");
	printf("\t\t Pobr's Wallet");
	printf("\n =======================================================\n" RESET);
}
void desenharCabecalhoEstoque()
{
	printf(AMARELO "\n =======================================================\n");
	printf("\t\t Estoque - Pobr's Wallet");
	printf("\n =======================================================\n" RESET);
}
void desenharCabechalhoAdmin()
{
	printf(VERDE "\n =======================================================\n");
	printf("\t\t ADMIN - Pobr's Wallet");
	printf("\n =======================================================\n" RESET);
}
int WriteProduto(struct produto Produto)
{
	Produto.id = GetQuantidade() + 1;
	
	file = fopen(ARQUIVO, "ab");
	
	if (fwrite(&Produto, sizeof(struct produto), 1, file) != 1)
	{
		printf("Erro de gravacao do produto.\n");
		return 0;
	}
	
	fclose(file);
	return 1;
}
void ListarProdutos()
{
	struct produto Produto;
	file = fopen(ARQUIVO, "rb");
	
	if (file == NULL) printf("\n Nenhum produto registrado.");
	else
	{
		while(1)
		{
			fread(&Produto, sizeof(struct produto), 1, file);
			
			if (feof(file)) break;
			
			printf("\n ID = %2d", Produto.id);
			printf("\tNOME = %10s", Produto.nome);
			printf("\tValor = %8.2lf", Produto.valor);
		}	
	}
	
	fclose(file);
}
int GetQuantidade()
{
	struct produto Produto;
	
	file = fopen(ARQUIVO, "rb");
	
	if (file == NULL) return 0;
	
	fseek(file, sizeof(struct produto)*(-1), SEEK_END);
	
	fread(&Produto, sizeof(struct produto), 1, file);
	
	fclose(file);
	
	return Produto.id;
}
