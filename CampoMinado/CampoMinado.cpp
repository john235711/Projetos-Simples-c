// campo minado
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void preencher_matriz(int m[10][10], int n){
	short unsigned int quant_bombas,x , y;
	if (n > 3) n = n%3;
	
	// definindo o nivel 
	if (n == 1) quant_bombas = 4;
	if (n == 2) quant_bombas = 7;
	if (n == 3) quant_bombas = 13; 
	

	// preenchendo ao redor com 1 e o interior com 0
	for (int lin = 0; lin < 10; lin++){
		for (int col = 0; col < 10; col++){
			if (lin == 0 || lin == 9 || col == 0 || col == 9){
				m[lin][col] = 1;
			}else{
				m[lin][col] = 0;
			}
		}
	}
	//sorteando as bombas
	while (quant_bombas){
		x = rand()%8 + 1;
		y = rand()%8 + 1;
		
		m[y][x] = 9;
		quant_bombas--;
	}	
}

int bombas_ao_redor(int m[10][10], int lin, int col){
	int q = 0;
	
	if (m[lin][col+1] == 9) q++;
	if (m[lin][col-1] == 9) q++;
	if (m[lin-1][col] == 9) q++;
	if (m[lin-1][col-1] == 9) q++;
	if (m[lin-1][col+1] == 9) q++;
	if (m[lin+1][col] == 9) q++;
	if (m[lin+1][col-1] == 9) q++;
	if (m[lin+1][col+1] == 9) q++;
	
	return q;
	
}

void marcar_matriz(int m[10][10]){
	for (int lin = 1; lin < 9; lin++){
		for (int col = 1; col < 9; col++){
			if (m[lin][col] == 0) m[lin][col] = bombas_ao_redor(m, lin, col);
		}
	}
}

int par_in_vetor(short int quant, short int vetor_maior[], short int pos[]){
	for (int i = 0; i < quant; i+=2){
		if (pos[0] == vetor_maior[i] && pos[1] == vetor_maior[i+1]) return 1;
	}
	return 0;
}

int exibir_campo_e_ver_se_e_bomba(int m[10][10], short int pos[2]){
	static short int campos_marcados[64], index = 0;
	short int pos_atual[2], e_bomba = 0;
	
	if (m[pos[0]][pos[1]] == 9) e_bomba = 1;
	
	if (!(par_in_vetor(index, campos_marcados, pos))){
		campos_marcados[index++] = pos[0];
		campos_marcados[index++] = pos[1];
	}
	
	//exibir cordenadas para o jogador das colunas
	putchar(' ');
	for (int k = 1; k <= 8; k++){
		printf("%d", k);
	}
	putchar('\n');
	
	for (int lin = 1; lin < 9; lin++){
		//exibir as cordenadas para o jogador das linhas
		printf("%d",lin);
		
		for (int col = 1; col < 9; col++){
			pos_atual[0] = lin;
			pos_atual[1] = col;
			
			if (par_in_vetor(index, campos_marcados, pos_atual)){
				if (e_bomba  &&  lin == pos[0] && col == pos[1]) printf("%c",15);
				else printf("%d", m[lin][col]);
			}else{
				printf("%c",4);
			}
		}
		putchar('\n');
	}
	
	if (e_bomba) return 1;
	else return 0;
}

int main(){
	int matriz[10][10];
	short int bomba = 0, pos_jogada[] = {0, 0},acertos = 0;
	
	
	preencher_matriz(matriz, 3);
	marcar_matriz(matriz);
	
	while (1){
		system("cls");
		bomba = exibir_campo_e_ver_se_e_bomba(matriz, pos_jogada);
		
		if (bomba){
			printf("Acertou na bomba perdeu");
			break;
		}else{
			if (pos_jogada[0] >= 1 && pos_jogada[0] <= 8 && pos_jogada[1] >= 1 && pos_jogada[1] <= 8) acertos++;
		}
		
		if (acertos == 51){
			printf("Ganhou parabens");
			break;
		}
		
		printf("\nDigite as coordenadas (y, x)");
		scanf("%hi %hi", &pos_jogada[0], &pos_jogada[1]);
		
	}
	
}
