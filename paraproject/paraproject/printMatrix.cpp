#include "stdio.h"
#include "string.h"

//Create structure to store the various states and their counter
struct Store_state{
	char state[state_length+1];
	int counter_s;
} store_state[128];

//Create structure to store the various tansition and their counter
struct Store_transition{
	char transition[state_length*2+1];
	int counter_t;
} store_transition[128];
void output_MC(int sequence_state){
	printf("The markov chain states are: \n");
	for (int i=0;i<sequence_state;i++){
		printf("%s\t",store_state[i].state);
		printf("\n");
	}
}

void output_MC_counter(int sequence_state){
	printf("The markov chain states` counts are: \n");
	for (int i=0;i<sequence_state;i++){
		printf("%d\t",store_state[i].counter_s);
		printf("\n");
	}
}

void output_statetransition(int sequence_transition){
	printf("The state transition pairs are: \n");
	for (int i=0;i<sequence_transition;i++){
		printf("%s\t",store_transition[i].transition);
		printf("\n");
	}
}

void output_statetransition_count(int sequence_transition){
	printf("The state transition pairs` counts are: \n");
	for (int i=0;i<sequence_transition;i++){
		printf("%d\t",store_transition[i].counter_t);
		printf("\n");
	}
}

void output_transition_matrix_counter(int* matrix_counter,int sequence_state){
	printf("The matrix for counts is: \n");
	for (int i=0;i<sequence_state;i++){
		for (int j=0;j<sequence_state;j++){
			printf("%d\t",matrix_counter[i*sequence_state+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void output_transition_matrix(float* matrix,int sequence_state){
	printf("The matrix is: \n");
	for (int i=0;i<sequence_state;i++){
		for (int j=0;j<sequence_state;j++){
			printf("%f\t",matrix[i*sequence_state+j]);
		}
		printf("\n");
	}
	printf("\n");
}