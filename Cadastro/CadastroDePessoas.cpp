//projeto cadastro de clientes c
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <fileapi.h>
#define W 119
#define S 115
#define ENTER 13

void gotoxy(short int x, short int y){
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

short int MenuPricipal(){
	short int x_pricipal = 20, y_pricipal = 4;
	short int x_cursor = x_pricipal, y_cursor = y_pricipal;
	short int tecla;
	
	gotoxy(x_pricipal, y_pricipal);
	printf("CADASTRAR CLIENTE");
	gotoxy(x_pricipal, y_pricipal+1);
	printf("VER CLIENTE");
	gotoxy(x_pricipal, y_pricipal+2);
	printf("VER TODOS OS CLIENTES");
	gotoxy(x_pricipal, y_pricipal+3);
	printf("EXCLUIR CLIENTE");
	gotoxy(x_pricipal, y_pricipal+4);
	printf("SAIR");
	
	
	while(1){
		gotoxy(x_cursor+22, y_cursor);
		putchar(219);
		
	
		tecla = getch();
			
		if (tecla == W || tecla == S ){
			gotoxy(x_cursor+22, y_cursor);
			putchar(' ');
		}
			
		switch(tecla){
			case W:
				if (y_cursor == y_pricipal) y_cursor += 4;
				else y_cursor--;
				break;
					
			case S:
				if (y_cursor == y_pricipal+4) y_cursor = y_pricipal;
				else y_cursor++;
				break;
					
			case ENTER:
				return y_cursor - y_pricipal + 1;
		}
		
	}
	
}
typedef struct{
	int dia,mes,ano;
}DATA;
typedef struct{
	char nome [30];
	DATA data;
	char cpf[16];
	char nomeDoPai[30];
	char nomeDaMae[30];
	char telefone[15];	
}CLIENTE;


short int validarNome(char nome[]){
	for (int i = 0; i < strlen(nome); i++){
		if (!isalpha(nome[i]) && nome[i] != ' ') return 0;
	}
	return 1;
}

short int strSoTemNumeros(char string[]){
	for (int i = 0; i < strlen(string); i++){
		if (!isdigit(string[i])) return 0;
	}
	return 1;
}
short int validarTelefone(char telefone[]){
	for (int i = 0; i < strlen(telefone); i++){
		if (!isdigit(telefone[i])) return 0;
	}
	return 1;
}

int charToInt(char c){
	return c-48;
}
short int validarCpf(char cpf[]){
	int soma = 0, d1, d2;
	int multiplicador = 10;
	if (strlen(cpf) != 11 || !strSoTemNumeros(cpf)) return 0;
	

	for (int i = 0 ; i < 9; i++){
		soma += charToInt(cpf[i])*(multiplicador);
		multiplicador--;
	}
	soma = (soma*10)%11;
	d1 = (soma == 10)? 0:soma;
	
	
	soma = 0;
	multiplicador = 10;
	for (int i = 1; i < 10; i++){
		soma += charToInt(cpf[i])*(multiplicador);
		multiplicador--;
	}
	soma = (soma*10)%11;
	d2 = (soma == 10)? 0:soma;
	
	
	if (charToInt(cpf[9]) != d1 || charToInt(cpf[10]) !=d2) return 0;
	
	return 1;
	
	
}

short int validarData(DATA data){
	time_t tempo;
	time(&tempo);
	struct tm dataAtual = *localtime(&tempo);
	int anoMax = (dataAtual.tm_year + 1900) - 18;
	
	//validando ano tem que estar entre 1935 e anoMax
	if (data.ano < 1935 || data.ano > anoMax) return 0;
	
	if (data.mes < 0 || data.mes > 12) return 0;
	
	if (data.dia < 0 || data.dia > 31) return 0;
	
	if (data.ano%4 == 0 && data.ano%100 == 0 && data.ano==0){ //  ano bisexto
		if (data.mes == 2 && data.dia > 29) return 0;										 
	}else if (data.mes == 2 && data.dia > 29)  return 0;
	
	if ((data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7
	 || data.mes == 8 || data.mes == 10 || data.mes == 12) && data.dia > 31) return 0;
	 
	if ((data.mes == 4 || data.mes == 9 || data.mes == 6 || data.mes == 11) && data.dia > 30) return 0;
	
	return 1;
	
	
}
void exibirErroNaTela(char dadoInvalido[], short int x, short int y){
	
	gotoxy(x, y);
	printf("%s ESTA INVALIDA", dadoInvalido);
}

short int  validarDados(CLIENTE cliente){
	short int validado = 1;
	
	if (!validarNome(cliente.nome))
	{
		exibirErroNaTela("Nome", 50, 0);      
		validado = 0;
	}
	if (!validarNome(cliente.nomeDaMae))    
	{
		exibirErroNaTela("Nome da mae", 50, 1);
		validado = 0;
	}
	if (!validarNome(cliente.nomeDoPai))
	{
		exibirErroNaTela("Nome do pai", 50, 2);
		validado = 0;
	}
	if (!validarData(cliente.data))
	{
		exibirErroNaTela("Data",50,3);         
		validado = 0;
	}
	if (!validarTelefone(cliente.telefone))
	{
		exibirErroNaTela("Telefone ", 50, 3);  
		validado = 0;
	}
	if (!validarCpf(cliente.cpf)) 
	{
		exibirErroNaTela("CPF", 50, 4);        
		validado = 0;
		
	}
	
	return validado;
	
}


short int jaExisteEsteCpfNoBanco(char cpf[]){
	FILE *arq;
	CLIENTE cliente;
	arq = fopen("InformacoesDoCadastro.dat", "rb");
	
	while (1){
		fread(&cliente, sizeof(CLIENTE), 1, arq);
		if (feof(arq)) break;
		
		if (strcmp(cpf, cliente.cpf) == 0) return 1; 
	}
	fclose(arq);
	return 0;
}

short int decisaoVoltar(void){
	printf("APERTE QUALQUER TECLA PARA TENTAR INSERIR NOVAMENTE (V PARA VOLTAR A TELA INICIAL)");
	if (getch() == 118) return 1;
	return 0;
}
void CadastrarCliente(void){
	short int estaValido = 0;
	CLIENTE cliente;
	
	while(1){
		gotoxy(0, 0);
		system("cls");
		printf("NOME: ");
		scanf("%s",cliente.nome);
		printf("DATA\n");
		printf("DIA: ");
		scanf("%d", &cliente.data.dia);
		printf("MES: ");
		scanf("%d", &cliente.data.mes);
		printf("ANO: ");
		scanf("%d", &cliente.data.ano);
		printf("cpf: ");
		scanf("%s", cliente.cpf);
		printf("NOME DO PAI: ");
		scanf("%s", cliente.nomeDoPai);
		printf("NOME DA MAE: ");
		scanf("%s",cliente.nomeDaMae);
		printf("TELEFONE: ");
		scanf("%s",cliente.telefone);
		
		estaValido = validarDados(cliente);
		gotoxy(10, 25);
		if (!estaValido)
		{
			if(decisaoVoltar()) break;	
		}
		else
		{
			printf("TODOS OS DADOS ESTAO VALIDOS");
			
			if (jaExisteEsteCpfNoBanco(cliente.cpf))
			{
				printf(" POREM JA EXISTE ALGUEM COM ESSE CPF\n");
				if (decisaoVoltar()) break;
				
			}
			else
			{
				FILE *arq;
				arq = fopen("InformacoesDoCadastro.dat","ab");
				if (arq != NULL)
				{
					fwrite(&cliente, sizeof(CLIENTE), 1, arq);
					
					system("cls");
					
					printf("CLIENTE CADASTRADO  NO SISTEMA COM SUCESSO!");
					fclose(arq);
					break;
					
				}
				
			}
		}
	}
	
}
void exibirDadosDoCliente(CLIENTE cliente){
	printf("\t---------------DADOS DO CLIENTE------------------\n");
	printf("Nome:      \t %s\n", cliente.nome);
	printf("DATA-NASC: \t %02d/%02d/%d\n", cliente.data.dia, cliente.data.mes, cliente.data.ano);
	printf("CPF:       \t %s\n",cliente.cpf);
	printf("NOME DO PAI\t %s\n", cliente.nomeDoPai);
	printf("NOME DA MAE\t %s\n", cliente.nomeDaMae);
	printf("\t-----------------------------------------------------\n");
}

void VerCliente(void){
	char cpf[16];
	CLIENTE cliente;
	short int CpfEstaRegistrado = 0;
	FILE *arq;
	
	while(1){
		system("cls");
		printf("DIGITE AQUI O CPF DO CLIENTE");
		scanf("%s", cpf);
	

		arq = fopen("InformacoesDoCadastro.dat","rb");
	
		if (arq != NULL){
			while(1){
				fread(&cliente, sizeof(CLIENTE), 1, arq);
				if (feof(arq)) break;
			
				if (strcmp(cliente.cpf, cpf) == 0){
					CpfEstaRegistrado = 1;
					
					system("cls");
					exibirDadosDoCliente(cliente);
				
					break;
				
				}
			}
		}
		fclose(arq);
	
		if (!CpfEstaRegistrado) printf("NAO EXISTE ALGUEM COM ESSE CPF\n");
	
		if (decisaoVoltar()) break;
	}
	
}
void VerTodosOsClientes(void){
	FILE *arq;
	CLIENTE cliente;
	system("cls");
	
	arq = fopen("InformacoesDoCadastro.dat","rb");
	

	while (1){
		fread(&cliente, sizeof(CLIENTE), 1, arq);
		if (feof(arq)) break;
		exibirDadosDoCliente(cliente);
	}
	
	printf("PRESICONE QUALQUER TECLA PARA VOLTAR");
	getch();
}

int CalcularQuantidadeDeClientes(){
	int quant = 0;
	FILE *arq;
	arq = fopen("InformacoesDoCadastro.dat","rb");
	CLIENTE cliente;
	while(1){
		fread(&cliente, sizeof(CLIENTE),1, arq);
		if (feof(arq)) break;
		quant++;
	}
	fclose(arq);
	return quant;
}
void ExcluirCliente(){
	char cpf[16];
	FILE *arq;
	FILE *arq_novo;
	CLIENTE cliente;
	

    while(1){
		system("cls");
		printf("DIGITE O CPF DO CLIENTE QUE DESEJA EXCLUIR\n");
		printf("CPF: ");
		scanf("%s", cpf);
		system("cls");
		if (!jaExisteEsteCpfNoBanco(cpf)){   
			printf("NAO EXISTE ALGUEM COM ESSE CPF");
			if (decisaoVoltar()) break;
		}else{
			arq = fopen("InformacoesDoCadastro.dat","rb");
			arq_novo = fopen("COPIA.dat","ab"); 
			
			if (arq_novo == NULL){
				printf("ERRO AO ABRIR ARQUIVO AUXILIAR");
				break;
			}
			if (arq != NULL){
				while(1){ // varrendo todos os clientes
					fread(&cliente, sizeof(CLIENTE), 1, arq);
					if (feof(arq)) break;
					
					if (strcmp(cliente.cpf, cpf) != 0){ // colocando na tabela so os clientes com o cpf != do cpf a retirar
						fwrite(&cliente, sizeof(CLIENTE), 1, arq_novo);
					}
				}
				fclose(arq);
				fclose(arq_novo);
				
				MoveFileA("InformacoesDoCadastro.dat","inf.dat");
				if(remove("inf.dat") == -1){ // por algum motivo nao consigo apagar o arquivo aqui
					printf("ERRO AO EXLUIR ARQUIVO");
					break;
				}
				MoveFileA("COPIA.dat","InformacoesDoCadastro.dat");
				
				printf("CLIENTE EXCLUIDO DO SITEMA COM SUCESSO!\n");
				if (decisaoVoltar()) break;
				
			}
		}
	}
	
	
	
}

int main(){
	while (1){
		system("cls");
		switch(MenuPricipal()){
			case 1:
				CadastrarCliente();
				break;
			case 2:
				VerCliente();
				break;
			case 3:
				VerTodosOsClientes();
				break;
			case 4:
				ExcluirCliente();
				break;
			case 5:
				exit(1);
		}
	}
	
}
