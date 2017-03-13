#include <stdio.h>
#include <stdlib.h>
 


int max (int *v, int n) {
    int i, m = v[0];
    for (i = 0; i < n; i++) if (v[i] > m) m = v[i];
	
    return m;
}


void zeraVetor (int *v, int n) {
    int i;
    for (i = 0; i < n; i++) v[i] = 0;
}
 
int busca (int x, int *v, int n, int jogador) { 
    int i;
    for (i = 0; i < jogador; i++) if (v[i] == x) 
		return i;
		
    for (i = jogador+1; i < n; i++) if (v[i] == x) 
			return i;
		
    return i;
}

int main () {
    int NumCartas, NumJogadores;//Número de cartas, Número de jogadores
    int i, jogadorDaVez, cartaDaVez, maiorMonteQtd, pos;

	int descarte[13]; 	// cartas de 1 a 13, vetor de 0 a 12		//Monte de descarte
    int tamMontes[20];  // jogadores de 2 a 20, vetor de 0 a 18 	//Altura dos montes
    int topos[20]; 		// jogadores de 2 a 20, vetor de 0 a 18		//Valor da carta dos topos
     
     
     /*COMENTAR*/
    printf("ENTRADAS: <qtd. de jogadores>   <qtd. de cartas>  \n <numero da carta>  \n <numero da carta>...\n");
    printf("SAIDAS: <qtd. no monte do(s) vencedor(es)>   <num. do jogador que venceu>   <num. do jogador que venceu>...\n");
	/*COMENTAR*/
	
	scanf ("%d %d", &NumJogadores, &NumCartas);
    
    
    while (NumCartas!=0 || NumJogadores!=0) {
        zeraVetor (tamMontes, NumJogadores);
        zeraVetor (topos, NumCartas);
 	   
        jogadorDaVez = 0;
        for (i = 0; i < NumCartas; i++) {
			scanf ("%d", &cartaDaVez);
             // ACHOU A CARTA NO MONTE DE DESCARTE
            if (descarte[cartaDaVez-1] == 1) {
                tamMontes[jogadorDaVez] += 2;
                topos[jogadorDaVez] = cartaDaVez;
				descarte[cartaDaVez-1] = 0;
            }
            else {
                pos = busca (cartaDaVez, topos, NumJogadores, jogadorDaVez);
                
                // ACHOU A CARTA NO MONTE DE OUTRO JOGADOR
                if (pos < NumJogadores) {
                    tamMontes[jogadorDaVez] += tamMontes[pos] + 1;
                    tamMontes[pos] = 0;
					topos[jogadorDaVez] = cartaDaVez;
                    topos[pos] = 0;
                }
                else {
                	//ACHOU A CARTA NO TOPO DO PRÓPRIO MONTE
                    if (topos[jogadorDaVez] == cartaDaVez) 
                        tamMontes[jogadorDaVez] += 1;
                    
                    else {//NÃO ACHOU A CARTA EM NEHUM LUGAR
                        descarte[cartaDaVez-1] = 1;
                        jogadorDaVez = (jogadorDaVez + 1) % NumJogadores;
					}
                }
            }
        }
   
        maiorMonteQtd = max (tamMontes, NumJogadores);
        printf ("%d ", maiorMonteQtd);
      

        for (i = 0; i < NumJogadores; i++)
            if (tamMontes[i] == maiorMonteQtd) 
				printf ("%d ", i+1);
        printf ("\n");
        scanf ("%d%d", &NumCartas, &NumJogadores);
    }
     
    return 0;
}