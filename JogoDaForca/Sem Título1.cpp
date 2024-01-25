#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>


void exibirForca(short int nivel){
	char forcas[7][69] = {
	  " ---------\n |       |\n         |\n         |\n         |\n  _______|\n",
	  " ---------\n |       |\n 0       |\n         |\n         |\n  _______|\n",
	  " ---------\n |       |\n 0       |\n/        |\n         |\n  _______|\n",
      " ---------\n |       |\n 0       |\n/|       |\n         |\n  _______|\n",
	  " ---------\n |       |\n 0       |\n/|\\      |\n         |\n  _______|\n",
	  " ---------\n |       |\n 0       |\n/|\\      |\n/        |\n  _______|\n",
	  " ---------\n |       |\n 0       |\n/|\\      |\n/ \\      |\n  _______|\n"};
	  
	puts(forcas[nivel]);
}
char *sortearPalavra(char *palavras[], int quantidadePalavras){
	return palavras[rand()%quantidadePalavras];
		
}

short int caracterInString(char car, char string[]){
	int i = 0;
	while (string[i] != '\0'){
		if (car == string[i]) return 1;
		i++;
	}
	return 0;
}
void colocarLinhasOuLetras(char palavraSorteada[], char LetrasAcertadas[]){
	for (int i = 0; i < strlen(palavraSorteada); i++){
		if (caracterInString(palavraSorteada[i], LetrasAcertadas)){
			printf(" %c ",palavraSorteada[i]);
		}else{
			printf(" %c ", '_');
		}
	}
	printf("\n");
}

short int ganhou(char palavraSorteada[], char letrasAcertadas[]){
	for (int i = 0; i < strlen(palavraSorteada); i++){
		if (!caracterInString(palavraSorteada[i],letrasAcertadas)) return 0;
	}
	return 1;
}
short int perdeu(short int nivel){
	return (nivel == 6);
}


void zerarString(char string[]){
	for (int i = 0; i < strlen(string); i++){
		string[i] = '0';
	}
}
void resetarVariaveis(char *palavras[] ,char **palavraSorteada, char *letrasAcertadas, short int *nivel, short int *indexLa){
	*palavraSorteada = sortearPalavra(palavras, 10);
	zerarString(letrasAcertadas);
	*nivel = 0;
	*indexLa = 0;
}

short int querJogarNovamente(){
	char tecla;
	printf("DESEJA CONTINUAR O JOGO? S para sim ou qualquer outra tecla para nao");
	
	tecla = tolower(getch());
	
	if (tecla == 115) return 1;
	return 0;
}
int main(){
	srand(time(NULL));
	char *palavras[] = {"Carvalho","onibus","ceu","abacaxi","manga","pedra","paralelepipedo","cagado","museu","jabuticaba"};
	char *palavraSorteada = sortearPalavra(palavras, 10);
	char letrasAcertadas[strlen(palavraSorteada)];
	short int nivel = 0; // o nivel indica em que faze a forca esta
	short int indexLetrasAcertadas = 0;
	char letra;
	
	zerarString(letrasAcertadas); // preciso disso para que a string seja '00000...' e assim fica facil de fazer as comparacoes

	while(1){
		system("cls"); // se estiver no linus use clear
		exibirForca(nivel);
		colocarLinhasOuLetras(palavraSorteada, letrasAcertadas);
		
		puts("DIGITE UMA LETRA: ");
		letra = tolower(getch());
		
		if (caracterInString(letra, palavraSorteada)){
			if (!caracterInString(letra, letrasAcertadas)){
				letrasAcertadas[indexLetrasAcertadas] = letra;
				indexLetrasAcertadas++;	
			}
		}else{
			nivel++;
		}
		
		
		if (ganhou(palavraSorteada, letrasAcertadas) || perdeu(nivel)){
			system("cls");
			exibirForca(nivel);
			// na funcao abaixo o parametro Letras acertadas tera como argumento palavraSorteadas
			// pois assim garanto que toda a palavra apareca para o usuario indepedente se acertou as letras ou perdeu
			colocarLinhasOuLetras(palavraSorteada, palavraSorteada);
			
			if (perdeu(nivel)) printf("%s","INFELISMENTE PERDEU!\n");
			else printf("%s", "GANHOU PARABENS!\n");
			
			if (querJogarNovamente()) resetarVariaveis(palavras, &palavraSorteada, letrasAcertadas, &nivel, &indexLetrasAcertadas);
			else break;
			
			
		}
		
		
	}
	//depois que terminar
	system("cls");
	puts("JOGO FINALIZADO");
	
	if(rand()%2 == 0){
		printf("ALEGRO");
	}else{
		printf("SDL");
	}
	
	
}
