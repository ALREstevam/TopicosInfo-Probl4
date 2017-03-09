#include <stdio.h>
#include <stdlib.h>
 

//Encontrar maior valor em um vetor
int maximo (int *v, int n) {
    int i, m = v[0];
     
    for (i = 0; i < n; i++) {
        if (v[i] > m) {
			m = v[i];
		}
	}
    return m;
}
 

//Seta todas as posições do vetor para 0
void zeraVetor (int *v, int n) {
    int i;
    for (i = 0; i < n; i++) v[i] = 0;
}
 
int busca (int x, int *v, int n, int jogador) {
    int i;
     
    for (i = 0; i < jogador; i++){
		if (v[i] == x){
		 	 return i;
		}
	} 
	
    for (i = jogador+1; i < n; i++) if (v[i] == x) {
		return i;
	}
         
    return i;
}
 
int main () {
    int N, J;//Número de cartas, Número de jogafores
    int i, jogador, carta, m, pos;
    
    
	
	int baralho[13]; // cartas de 1 a 13, vetor de 0 a 12		//Monte de descarte
    int montes[20]; // jogadores de 2 a 20, vetor de 0 a 18 	//Altura dos montes
    int topos[20]; // jogadores de 2 a 20, vetor de 0 a 18		//Valor da carta dos topos
     
    //scanf ("%d%d", &N, &J);
    
    printf("Numero de Jogadores: ");
    scanf ("%d", &J);
    
    printf("Numero de Cartas: ");
    scanf ("%d", &N);
    
    while (N!=0 || J!=0) {//Enquanto monte de compra não acabar ou haverem 0 jogadores
        zeraVetor (baralho, 13);
        zeraVetor (montes, J);
        zeraVetor (topos, J);
 
        jogador = 0;//Jogador da vez
         
         
        for (i = 0; i < N; i++) {//Inserir cartas = tirando carta do monte
            scanf ("%d", &carta);
             
             // Achou a carta nos descartes
            if (baralho[carta-1] == 1) { 
                montes[jogador] += 2;   //aumenta o monte em 2 (carta do saque + carta do descarte)
                topos[jogador] = carta;	//atualiza o topo
                
				baralho[carta-1] = 0;	//Removendo indicador de que a carta está no monte de descarte
            }
            else {
                pos = busca (carta, topos, J, jogador);
                
                // Achou a carta no topo do monte de outro jogador
                if (pos < J) { 
                    montes[jogador] += montes[pos] + 1;//aumenta o monte dele com cartas do outro jogador
                    montes[pos] = 0;//monte do outro jogador tem altura 0
                    
					topos[jogador] = carta;
                    topos[pos] = 0;
                }
                else {
                	// Achou a carta no topo dele mesmo
                    if (topos[jogador] == carta) { 
                        montes[jogador] += 1;//aumenta o monte dele em 1
                    }
                    else {//Não achou a carta em nenhum lugar
                        baralho[carta-1] = 1;//Coloca o indicador de que a carta existe no monte de descarte
                    
                        jogador = (jogador + 1) % J;// próximo jogador
                    }
                }
            }
        }
         
        m = maximo (montes, J);//Buscar número de cartas do maior monte ao final jogo
 
 
        //printf ("%d ", m);
        printf ("Maior monte: %d \n", m);
        
        //Busca jogadores que tem número de cartas igual ao do maior monte
        for (i = 0; i < J; i++)
            if (montes[i] == m) printf ("Jogador: %d ", i+1); //printf ("%d ", i+1);
        printf ("\n");
         
        scanf ("%d%d", &N, &J);
    }
     
    return 0;
}