//projeto que simula a atracao gravitacional de planetas no terminal
//posso colocar bordas no programa e colocar colisoes dos planetas
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#define G 1
void gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

typedef struct{
	float x;
	float y;
	float velocity[2];
	float massa;
}PLANETA;

void renderizar_planetas(PLANETA planetas[], int size){
	for (int i = 0; i <size; i++){
		gotoxy(int(planetas[i].x), int((planetas[i].y)));
		putchar('*');
	}
}

void limpar_rastro_planetas(PLANETA planetas[], int size){
	for (int i = 0; i <size; i++){
		gotoxy(int(planetas[i].x), int(planetas[i].y));
		putchar(' ');
	}
}

void update_position(PLANETA planetas[], int size){
	for (int i = 0; i < size; i++){
		planetas[i].x += planetas[i].velocity[0];
		planetas[i].y += planetas[i].velocity[1];
	}
}

float *calcular_centro_de_massa(PLANETA planetas[], int size){
	static float coordenadas_e_massa_centro_massa[3];
	float soma_total_das_massas = 0;
	
	coordenadas_e_massa_centro_massa[0] = 0;
	coordenadas_e_massa_centro_massa[1] = 0;
	coordenadas_e_massa_centro_massa[2] = 0;
	
	for (int i = 0; i < size; i++){
		coordenadas_e_massa_centro_massa[0] += (planetas[i].x)*(planetas[i].massa);
		coordenadas_e_massa_centro_massa[1] += (planetas[i].y)*(planetas[i].massa);
		soma_total_das_massas += planetas[i].massa;
	}
	
	coordenadas_e_massa_centro_massa[0] /= soma_total_das_massas;
	coordenadas_e_massa_centro_massa[1] /= soma_total_das_massas;
	coordenadas_e_massa_centro_massa[2] = soma_total_das_massas;
	return coordenadas_e_massa_centro_massa;
	
	
}

float distancia(float x1, float y1, float x2, float y2){
	return sqrt(pow(x1-x2, 2) + pow(y1 - y2, 2));
}

void update_velocity(PLANETA planetas[], int size){
	float *coord_e_massa_do_centro_massa = calcular_centro_de_massa(planetas, size);
	float xc, yc;
	float cos, sin, dx, dy; // dx e dy sao a distancia em x e y da particula em relacao ao centro de massa
	float hipotenuza;
	float aceleracao;
	
	// modo de cauculo levando em conta so centro de massa do sistema
	/* for (int i = 0; i < size; i++){
		xc = coord_e_massa_do_centro_massa[0];
		yc = coord_e_massa_do_centro_massa[1];
		hipotenuza = distancia(planetas[i].x, planetas[i].y, xc, yc);
		
		aceleracao = (coord_e_massa_do_centro_massa[2]*G)/pow(hipotenuza, 2);
		
		dx = xc - planetas[i].x;
		dy = yc - planetas[i].y;
		cos = dx/hipotenuza;
		sin = dy/hipotenuza;
		
		planetas[i].velocity[0] += aceleracao*cos;
		planetas[i].velocity[1] += aceleracao*sin;
	}*/
	
	
	//modo de calculo onde calculo cada forca de um planeta
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (i!=j){
				hipotenuza = distancia(planetas[i].x, planetas[i].y, planetas[j].x, planetas[j].y);
				dx = planetas[j].x - planetas[i].x;
				dy = planetas[j].y - planetas[i].y;
				
				aceleracao = planetas[j].massa*G/pow(hipotenuza, 2);
				
				cos = dx/hipotenuza;
				sin = dy/hipotenuza;
				
				planetas[i].velocity[0] += aceleracao*cos;
				planetas[i].velocity[1] += aceleracao*sin;
			}
		}
	}
	
}


void editar(PLANETA planetas[], int size){
	int x = 0, y = 0, tecla, planetas_ja_criados = 0;
	
	printf("ESCOLHA O LOCAL DOS PLANETAS E SUAS VARIAVEIS\n");
	printf("USE W-S-A-D PARA MOVIMENTAR G PARA ESCOLHER O LOCAL\nE DURANTE A ANIMACAO APERTE P PARA VOLTAR e E PARA SAIR DO PROGRAMA");
	getch();
	system("cls");
	while(1){
		gotoxy(x, y);
		putchar(219);
		
		tecla = getch();
		gotoxy(x, y);
		putchar(' ');
		switch(tolower(tecla)){
			case 'a':
				if (x > 0) x--;
				break;
			case 'd':
				if (x < 120) x++;
				break;
			case 's':
				y++;
				break;
			case 'w':
				if (y >  0) y--;
				break;
			case 'g':
				PLANETA planeta;
				planeta.x = x;
				planeta.y = y;
				
				gotoxy(x, y + 3);
				printf("MASSA: ");
				scanf("%f", &planeta.massa);
				gotoxy(x, y+4);
				printf("VELOCIDADE X: ");
				scanf("%f", &planeta.velocity[0]);
				gotoxy(x, y+5);
				printf("VELOCIDADE Y: ");
				scanf("%f", &planeta.velocity[1]);
				
				planetas[planetas_ja_criados] = planeta;
				planetas_ja_criados++;
				system("cls");
				gotoxy(x, y);
				putchar('*'); // deixo aqui o local do planeta que ele escolheu

				if (planetas_ja_criados == size){
					return;
				}
				
		}
		
	}
	
}

int main(){
	int size, tecla;
	while(1){
		system("cls");
		printf("DIGITE A QUANTIDADE DE PLANETAS: ");
		scanf("%d", &size);
		PLANETA planetas[size];

		editar(planetas, size); 
	
		while(1){
			// faco a animacao
			renderizar_planetas(planetas, size);
			Sleep(60);
			limpar_rastro_planetas(planetas, size);
			update_velocity(planetas, size);
			update_position(planetas, size);
		
			if (kbhit()){
				tecla = tolower(getch());
			
				if (tecla == 'p') break;
				else if (tecla == 'e') exit(1);
			}
		}
	}
	
}
