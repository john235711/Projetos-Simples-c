//jogo da velha em c
#include <stdio.h>
#include <conio.h>
#include <windows.h>

char velha[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};


int char_to_int(char c){
	return c-48;
}

char int_to_char(int n){
	return n+48;
}

void resetar_velha(){
	for (int i = 0; i < 3; i++){
		for (int c = 0; c < 3; c++){
			if (i == 0) velha[0][c] = int_to_char(c+1);
			if (i == 1) velha[1][c] = int_to_char(c+4);
			if (i == 2) velha[2][c] = int_to_char(c+7);
		}
	}
	
}

void exibir_velha(){
	printf("%c | %c | %c\n", velha[0][0], velha[0][1], velha[0][2]);
	printf("---+----+--\n");
	printf("%c | %c | %c\n", velha[1][0], velha[1][1], velha[1][2]);
	printf("---+----+--\n");
	printf("%c | %c | %c\n", velha[2][0], velha[2][1], velha[2][2]);
}

void definir_cordenadas(void);// implementar depois

int esta_ocupado(unsigned int pos){
	int x, y;
	
	if (pos < 4) {
		y = 0;
		x = pos-1;
	}else if (pos < 7){
		y = 1;
		x = pos - 4;
	}else{
		y = 2;
		x = pos-7;
	}
	
	if (velha[y][x] != 'X' && velha[y][x] != 'O') return 0;
	else return 1;
	
	
}

void modificar_velha(char jogador, unsigned int pos){
	int x, y;
	
	if (pos < 4) {
		y = 0;
		x = pos-1;
	}else if (pos < 7){
		y = 1;
		x = pos - 4;
	}else{
		y = 2;
		x = pos-7;
	}
	
	velha[y][x] = jogador;
	
}

int empatou(){
	for (int i = 0; i < 3; i++){
		for (int c = 0; c < 3; c++){
			if (velha[i][c] != 'X' && velha[i][c] != 'O') return 0;
		}
	}
	
	return 1;
}

int ganhou(){
	int lin, col;
	
	//verificar as linhas
	for (lin = 0; lin < 3; lin++){
		for (col = 0; col < 2; col++){
			if (velha[lin][col] != velha[lin][col+1]) break;
		}
		if (col == 2) return 1;
	}
	
	//vefiricar as colunas
	for (col = 0; col < 3; col++){
		for (lin = 0; lin < 2; lin++){
			if (velha[lin][col] != velha[lin+1][col]) break;
		}
		if (lin == 2) return 1;
	}
	
	// vefiricar as diagonais
	if (velha[0][0] == velha[1][1] && velha[1][1] == velha[2][2]) return 1;
	
	return 0;
}

char definir_jogador(int cont){
	if (cont%2 == 0) return 'X';
	else return 'O';
}

int main(){
	unsigned int pos;
	short unsigned int cont = 0, continuar;
	char jogador;
	
	while (1){
		system("cls");
		
		jogador = definir_jogador(cont);
		
		exibir_velha();
	
		printf("DIGITE SUA JOGADA %c", jogador);
		scanf("%u", &pos);
	
		while (pos > 9 || esta_ocupado(pos)){
			printf("Jogada invalida");
			printf("DIGITE SUA JOGADA");
			scanf("%u", &pos);
		}
		
		modificar_velha(jogador, pos);
		
		
		if (ganhou() || empatou()){
			system("cls");
			exibir_velha();
			
			if (empatou()) printf("Houve empate\n");
			else printf("Parabenw o jogador %c ganhour\n", jogador);
			
			
			printf("QUER COTINUAR: [1] SIM/ QUALQUER OUTRA TECLA PARA NAO");
			scanf("%u", &continuar);
			
			if (continuar == 1){
				resetar_velha();
				cont = 0;	
			}else{
				printf("Finalizando o jogo...");
				Sleep(500);
				break;
			}
			
		}else cont++;
				
	}
	
	printf("JOGO DA VELHA FINALIZADO");
	
}
