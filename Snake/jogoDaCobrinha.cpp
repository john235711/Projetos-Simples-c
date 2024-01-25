//  corrigir bugs da geracao do alimento, e as veses o jogo trava de vez
#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define LARGURA_BORDA 25
#define ALTURA_BORDA 25
#define LARGURA 25
#define ALTURA 5
#define MAX_SCORE ((ALTURA_BORDA - 1)*2*(LARGURA_BORDA))
#define W 119
#define S 115
#define A 97
#define D 100
#define ENTER 13

void gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

short unsigned int menuMain(){
	short unsigned int valor_escolhido = 1, yescolha = ALTURA, tecla,
	JOGAR = ALTURA;
	
	system("cls");
	
	while(1){
		gotoxy(LARGURA,ALTURA);
		printf("JOGAR");
		gotoxy(LARGURA,ALTURA+1);
		printf("SAIR ");
		gotoxy(LARGURA, ALTURA+2);
		printf("VER RECORDE");
		
		
		
		gotoxy(LARGURA+11, yescolha);
		putchar(219);
		
		tecla = getch();
		// apagar o marco da posicao
		gotoxy(LARGURA+11, yescolha);
		putchar(' ');
		switch(tecla){
			case W:
				yescolha--;
				if (yescolha == ALTURA-1) yescolha = ALTURA + 2;
				break;
			case S:
				yescolha++;
				if (yescolha == ALTURA+3) yescolha = ALTURA;
				break;
			case ENTER:
				if (yescolha == JOGAR) return 1; // jogar
				
				if (yescolha == ALTURA+1) return 0; // sair
				
				if (yescolha == ALTURA+2){ // mostrar o recorde de pontos
					FILE *arq;
					arq = fopen("recorde.cpp","r");
					system("cls");
					
					if (arq == NULL){
						printf("ERRO AO ENCONTRAR O ARQUIVO");
						getch();
						system("cls");
						break;
					}else{
						int score_recorde;
						fscanf(arq, "%d", &score_recorde);
						
						printf("\t-----RECORDE------\n");
						printf("%d PONTOS", score_recorde);
						getch();
						system("cls");
						break;
					}	
				}
		}
		
	}
}

void borda(){
	int i;
	short unsigned int x = LARGURA, y = ALTURA;
	
	gotoxy(x, y);
	
	
	for (i = 0; i < LARGURA_BORDA; i++){ // parte horizontal superior
		printf("%c%c",178,178);
		gotoxy(x+=2, y);
	}
	
	x = LARGURA, y = ALTURA;
	gotoxy(x,y);
	for (i = 0;  i < ALTURA_BORDA; i++){  // parte vertical esquerdo
		printf("%c", 178);
		gotoxy(x, ++y);
	}
	
	for (i = 0; i < LARGURA_BORDA; i++){ // parte horizontal inferior
		printf("%c%c", 178,178);
		gotoxy(x+=2, y);
		
	}

	for (i = 0; i <= ALTURA_BORDA; i++){ // parte vertical direito
		printf("%c", 178);
		gotoxy(x, --y);
	}	
	

}

void posicionar_comida(short int pos[], short int corpo_cobra[][2], int size){
	//posicionar a comida num lugar onde nao esta o corpo da cobra
	short int e_igual = 0;
	while (1){
		pos[0] = rand()%LARGURA_BORDA + LARGURA+1;
		pos[1] = rand()%ALTURA_BORDA + ALTURA+1;
		
		for (int i = 0; i < size-1; i++){
			if (pos[0] == corpo_cobra[i][0] && pos[1] == corpo_cobra[i][1]){
				e_igual = 1;
				break;
			}
		}
		
		if (!e_igual) break;
	}
	gotoxy(pos[0], pos[1]);
	putchar(15);
}


short int colisao_comida_cobra(short int pos_cobra[], short int pos_comida[]){
	if (pos_comida[0] == pos_cobra[0] && pos_comida[1] == pos_cobra[1]) return 1;
	return 0;
}

short int colisao_borda_cobra(short int pos_cobra[], char *tipo_colisao_borda){ 
	
	if (pos_cobra[0] == LARGURA || pos_cobra[0] == LARGURA + LARGURA_BORDA*2){ // laterias
		if (pos_cobra[0] == LARGURA) *tipo_colisao_borda = 'E';
		else *tipo_colisao_borda = 'D';
		return 1;
	}
	if (pos_cobra[1] == ALTURA || pos_cobra[1] == ALTURA + ALTURA_BORDA){ // verticais
		if (pos_cobra[1] == ALTURA) *tipo_colisao_borda = 'C';
		else *tipo_colisao_borda = 'B';
		return 1;
	}
	
	return 0;
}

void exibir_score(int Score){
	gotoxy(LARGURA+LARGURA_BORDA*2 + 5, ALTURA);
	printf("SCORE: %hi", Score);
}

void atualizar_tempo(float *time, int score, double coef_angular){
	*time = coef_angular*score + 60;
}


void GameOver(){
	system("cls");
	//implementar arte depois;
	
	printf("GAME OVER\n");
	Sleep(200);
	
	
}

void atualizar_corpo(short int corpo_cobra[][2], short int pos_cobra[], int size_cobra, short int velocity[]){
	if (size_cobra >= 2){
		int i;
		for (i = size_cobra-2; i > 0; i--){
			corpo_cobra[i][0] = corpo_cobra[i-1][0];
			corpo_cobra[i][1] = corpo_cobra[i-1][1];
		}
		
		corpo_cobra[i][0] = pos_cobra[0];
		corpo_cobra[i][1] = pos_cobra[1];
	}
	
	pos_cobra[0] += velocity[0];
	pos_cobra[1] += velocity[1];
}

void exibir_cobra(short int pos_cobra[], short int corpo_cobra[][2], int size, float time){

	if (size >= 2){
		for (int i = 0; i < size-1; i++){
			gotoxy(corpo_cobra[i][0], corpo_cobra[i][1]);
			putchar(219);
		}
	}
	gotoxy(pos_cobra[0],pos_cobra[1]);
	putchar(219);
	Sleep(int(time));
	
	if (size >= 2){
		gotoxy(corpo_cobra[size-2][0],corpo_cobra[size-2][1]);
		putchar(' ');
	}else{
		gotoxy(pos_cobra[0], pos_cobra[1]);
		putchar('  ');
	}
	
}

short int colisao_cobra_cobra(short int pos_cobra[], short int corpo_cobra[][2], int size){
	for (int i = 0; i < size-1; i++){
		if (pos_cobra[0] == corpo_cobra[i][0] && pos_cobra[1] == corpo_cobra[i][1]) return 1;
	}
	return 0;
}

int gameRun(){
	char tipo_colisao_borda; // necessario para saber a colisao com a borda para atualizar a posicao E D C B siginifica ESQUERDO DIREITO e acim por diante
	int size_cobra = 1; // so conta o corpo sem levar em conta a cabeca
	short int corpo_cobra[MAX_SCORE][2];
	float time = 60;
	double coef_angular = (30 - time)/float(MAX_SCORE); // e necessario para a funcao que faz o tempo de parada diminuir fazendo o jogo ficar mais rapido
	int Score = 0;
	short int tecla, speed = 1;
	short int pos_cobra[] = {LARGURA+1, ALTURA+2}, pos_comida[2]; // posicao da cabeca da cobra
	short int velocity_snake[] = {1, 0};
	
	system("cls");
	borda();
	posicionar_comida(pos_comida,corpo_cobra,size_cobra);
	
	while (1){
		exibir_score(Score);
				
		atualizar_corpo(corpo_cobra, pos_cobra, size_cobra,velocity_snake);
		
		exibir_cobra(pos_cobra, corpo_cobra, size_cobra, time);
		
		if (colisao_cobra_cobra(pos_cobra, corpo_cobra, size_cobra)){
			GameOver();
			return Score;
			
		}
		
		
		if (colisao_comida_cobra(pos_cobra, pos_comida)){
			posicionar_comida(pos_comida,corpo_cobra, size_cobra);
			Score++;
			size_cobra++;
			atualizar_tempo(&time, Score, coef_angular);
			
			
			if (size_cobra == 2){
				corpo_cobra[0][0] = pos_cobra[0];
				corpo_cobra[0][1] = pos_cobra[1];
			}else{
				corpo_cobra[size_cobra-2][0] = corpo_cobra[size_cobra-3][0];
				corpo_cobra[size_cobra-2][0] = corpo_cobra[size_cobra-3][1];
			}
		}
		
		
		if (colisao_borda_cobra(pos_cobra,&tipo_colisao_borda)){
			switch(tipo_colisao_borda){
				case 'C':
					pos_cobra[1] = ALTURA + ALTURA_BORDA - 1;
					break;
				case 'B':
					pos_cobra[1] = ALTURA + 1;
					break;
				case 'D':
					pos_cobra[0] = LARGURA + 1;
					break;
				case 'E':
					pos_cobra[0] = LARGURA + LARGURA_BORDA*2 - 1;
					break;
			}
		}
	
		if (kbhit()){
			tecla = getch();

			switch (tecla){
				case A:
					if (velocity_snake[0] == 0){
						velocity_snake[0] = -speed;
						velocity_snake[1] = 0;
					}
					break;
				case D:
					if (velocity_snake[0] == 0){
						velocity_snake[0] = speed;
						velocity_snake[1] = 0;
					}
					break;
				case S:
					if (velocity_snake[1] == 0){
						velocity_snake[1] = speed;
						velocity_snake[0] = 0;
					}
					break;
				case W:
					if (velocity_snake[1] == 0){
						velocity_snake[1] = -speed;
						velocity_snake[0] = 0;
					}
					break;
			}
		}
	
	}
}

int main(){
	short int input = menuMain();
	int score,score_atual;
	FILE *arq;
	
	srand(time(NULL));
	while(input){
		//quando o jogo acaba ele retorna a quantidade de pontos feitos
		score = gameRun();
		
		// atualizando recordes
		arq = fopen("recorde.cpp","r");
		if (arq != NULL){
			fscanf(arq, "%d", &score_atual);
			if(score > score_atual){
				fclose(arq);
				arq = fopen("recorde.cpp", "w");
				fprintf(arq, "%d", score);
				
				printf("\tPARABENS NOVO RECORDE DE PONTOS ALCANCADO");
				getch();
				
			}
			fclose(arq);
		}
		input = menuMain();	
	}
	
	system("cls");
	printf("JOGO FINALIZADO");
	return 0;
	
	
	
}
