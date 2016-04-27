#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int TAM = 4;
int NUM_THREAD = 1;
   
   int linha_processar = 0;
   long long int **A;
   long long int **B;
   long long int **C;

pthread_mutex_t mutex;

void *runner(void *param);

void preenche_matriz(long long int **MAT);

void main(int argc, char* argv[]) {

	int i,j, count = 0;

        NUM_THREAD = atoi(argv[1]);
        TAM = atoi(argv[2]);     

	// Cria o mutex e threads
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid[TAM];

	//ALOCA MATRIZ A
	A = (long long int**) malloc (TAM * sizeof(long long int ) );
     	for(i=0; i<TAM; i++)
        	A[i]= (long long int*) malloc (TAM * sizeof(long long int ) );
	//ALOCA MATRIZ B
	B = (long long int**) malloc (TAM * sizeof(long long int ) );
     	for(i=0; i<TAM; i++)
        	B[i]= (long long int*) malloc (TAM * sizeof(long long int ) );

	//ALOCA MATRIZ C
	C = (long long int**) malloc (TAM * sizeof(long long int ) );
     	for(i=0; i<TAM; i++)
        	C[i]= (long long int*) malloc (TAM * sizeof(long long int ) );



	preenche_matriz(A);
	preenche_matriz(B);
	
	for(i = 0; i < NUM_THREAD; i++) {
		//Criar a thread
         	pthread_create(&tid[i],NULL ,runner, (void *)i);
		//Verifique se a thread espera por toda linha para completar			
	}
	for(i = 0; i< NUM_THREAD; i++){
		pthread_join(tid[i], NULL); //para a thread;	
	}

	pthread_mutex_destroy(&mutex);

//Imprime matriz resultante
/*        printf("\n");
	for(i = 0; i < TAM; i++) {
		for(j = 0; j < TAM; j++) {
			printf("%lld ", C[i][j]);
		}
		printf("\n");
	}*/
}//FIM DO MAIN




//Função que começa o controle das Threads
void *runner(void *param) {
        
	int i, n, j;

        int id = (int)param;

	while(i<(TAM-NUM_THREAD)){	
		pthread_mutex_lock(&mutex);		
		i = linha_processar;
		linha_processar++;

	        //printf("\nThread %d - Linha processar :  %d", id, i);
         	pthread_mutex_unlock(&mutex);	
		//Multiplica Linha por Coluna
		for(j =0; j< TAM; j++){
			for(n = 0; n< TAM; n++){
				C[i][j] += A[i][n] * B[n][j];
			}
		}
	}

}



void preenche_matriz(long long int **MAT){
	int i,j;
	srand(time(NULL));

		for(i=0; i<TAM; i++){
		     for(j=0;j<TAM;j++){
		        	MAT[i][j] = rand()/999;
			}
		}

}
