#include <stdio.h>
#include <stdlib.h>
 
/*SOBRE


	Existe um vetor que armazena o valor das cartas do topo do monte dos jogadores
		os índices do vetor correspondem aos jogadores
		

    Existe um vetor que armazena o tamanho dos montes dos jogadores
   	   os índices do vetor correspondem aos jogadores
   	   
    Existe um vetor que armazena quais cartas estão na área de descarte
    	os índices do vetor indicam o valor da carta
    	os valores de cada elemento indicam se a carta está ou não na área de descarte
    		descarte[x] = 0 -> a carta x não está no monte
    		descarte[x] = 1 -> a carta x está no monte 
*/


/*Encontrar maior valor em um dado vetor v de tamanho n,  é usado ao final do jogo para selecionar jogadores 
Com a maior quantidade de cartas*/
int max (int *v, int n) {
    int i, m = v[0];
     
    for (i = 0; i < n; i++) {
        if (v[i] > m) {
			m = v[i];
		}
	}
    return m;//retorna o valor mais alto dentre os valores de um vetor
}
 

/*Seta todas as posições do vetor para 0 (importante quando se usa a posição do vetor para 
indicar alguma informação)*/
void zeraVetor (int *v, int n) {
    int i;
    for (i = 0; i < n; i++) v[i] = 0;
}
 

//Utilizado para buscar a carta da vez no topo dos montes de outros jogadores
//pos = busca (carta, topos, J, jogador);
/*
x = valor procurado
*v = vetor onde a busca ocorrerá
n = número de jogadores
jogador = jogador da vez (deve ser ignorado na busca)
*/
int busca (int x, int *v, int n, int jogador) { 
    int i;
	//Busca nos montes de jogadores do início até o jogador anterior ao atual
    for (i = 0; i < jogador; i++){
		if (v[i] == x){
		 	 return i;
		}
	} 
	
	//Busca nos montes de jogadores depois do jogador atual
    for (i = jogador+1; i < n; i++) {
		if (v[i] == x) {
			return i;
		}
	}   
    return i;//retorna a posição onde a carta foi encontrada ou um número maior que o tamanho do vetor
}

	//Para percorrer o vetor inteiro procurando e desconsiderar o jogador atual (alternativa)
	int busca_teste (int x, int *v, int n, int jogador){
		int i;
		for(i = 0; i < n; i++){
			if(v[i] == x){
				if(i != jogador){
					return i;
				}
			}
		}
		return i;
	}
 
int main () {
    int NumCartas, NumJogadores;//Número de cartas, Número de jogadores
    int i, jogadorDaVez, cartaDaVez, maiorMonteQtd, pos;
    /*
    
    N = quantidade de cartas
    J = quantidade de jogadores
    
	i = 
	j = jogador da vez
	carta = carta da vez
	m
	pos = posição de uma carta buscada (auxiliar para procurar a carta da vez no topo dos montes dos oponentes)
	*/
    
    
	
	int descarte[13]; // cartas de 1 a 13, vetor de 0 a 12		//Monte de descarte
    int tamMontes[20]; // jogadores de 2 a 20, vetor de 0 a 18 	//Altura dos montes
    int topos[20]; // jogadores de 2 a 20, vetor de 0 a 18		//Valor da carta dos topos
     
    //scanf ("%d%d", &N, &J);
    
    printf("Numero de Jogadores: ");
    scanf ("%d", &NumJogadores);
    
    printf("Numero de Cartas: ");
    scanf ("%d", &NumCartas);
    
    while (NumCartas!=0 || NumJogadores!=0) {//Enquanto monte de compra não acabar ou haverem 0 jogadores (código para sair do programa)
        //Zerando os vetores
		zeraVetor (descarte, 13);
        zeraVetor (tamMontes, NumJogadores);
        zeraVetor (topos, NumCartas);

 	   
        jogadorDaVez = 0;//Jogador da vez
         
         
        for (i = 0; i < NumCartas; i++) {//Inserir cartas = tirando carta do monte
            printf("Carta na pilha de compra: ");
			scanf ("%d", &cartaDaVez);/*Não é preciso um vetor para armazenar a pilha de compra, 
									o processamento é feito assim que a carta é inserida*/
             
             // ACHOU A CARTA NO MONTE DE DESCARTE
            if (descarte[cartaDaVez-1] == 1) { /*No vetor descarte, índice + 1 corresponde ao valor 
										da carta e valor = 0 indica que a carta não existe no monte e valor = 1
								  	  	  indica que a carta existe*/
                tamMontes[jogadorDaVez] += 2;   //Aumenta o monte em 2 (carta do saque + carta do descarte)
                topos[jogadorDaVez] = cartaDaVez;	//Atualiza o topo do monte do jogador atual
				descarte[cartaDaVez-1] = 0;	//Removendo indicador de que a carta está no monte de descarte
            }
            else {
                pos = busca (cartaDaVez, topos, NumJogadores, jogadorDaVez);//Busca carta da vez no topo do monte de outros jogadores
				//pos = busca_teste(carta, topos, J, jogador);
                
                // ACHOU A CARTA NO MONTE DE OUTRO JOGADOR
                if (pos < NumJogadores) { //Testa se a posição retornada pela função busca está dentro do vetor
                    tamMontes[jogadorDaVez] += tamMontes[pos] + 1;//Ao monte do jogador atual é adicionado a quantidade de cartas do oponente
                    tamMontes[pos] = 0;//O monte do oponente recebe altura 0
                    
					topos[jogadorDaVez] = cartaDaVez; //O topo do monte do jogador da vez recebe o valor da carta da vez
                    topos[pos] = 0;//O topo do monte do oponente recebe 0 (indicação de vazio)
                }
                else {
                	//ACHOU A CARTA NO TOPO DO PRÓPRIO MONTE
                    if (topos[jogadorDaVez] == cartaDaVez) { //O topo do monte do jogador da vez tem o mesmo valor que a carta da vez
                        tamMontes[jogadorDaVez] += 1;//Incrementa o monte do jogador da vez em 1
                    }
                    else {//NÃO ACHOU A CARTA EM NEHUM LUGAR
                        descarte[cartaDaVez-1] = 1;//Coloca o indicador de que a carta existe no monte de descarte
                        jogadorDaVez = (jogadorDaVez + 1) % NumJogadores;//Passa a vez para o próximo jogador quando a única opção é colocar na área de descarte
						//A operação evita ter de usar um if para zerar o valor de jogador quando chegar a vez do último
					}
                }
            }
        }
         
        maiorMonteQtd = max (tamMontes, NumJogadores);//Buscar número de cartas do maior monte ao final jogo
 
 		
        //printf ("%d ", maiorMonteQtd);
        printf ("\n\nMaior monte: %d \n", maiorMonteQtd);
        
        //Busca jogadores que tem número de cartas igual ao do maior monte
        for (i = 0; i < NumJogadores; i++)
            if (tamMontes[i] == maiorMonteQtd) printf ("Jogador: %d ", i+1); //printf ("%d ", i+1);
        printf ("\n\n");
	
	
		for(i = 0; i < NumJogadores; i++){
			char ganhou = (tamMontes[i] == maiorMonteQtd) ? 's' : 'n';
			printf("Jogador: %d | Qtd. Cartas: %d | Topo: %d | Ganhou: %c |\n", i+1, tamMontes[i], topos[i], ganhou);
		}
		
		printf("Monte de descarte: ");
		for(i = 0; i < 13; i++){
			if(descarte[i]){
				printf("[%d] ", i+1);
			}
		}
		
		
		
		printf ("\n\n");
        scanf ("%d%d", &NumCartas, &NumJogadores);
    }
     
    return 0;
}