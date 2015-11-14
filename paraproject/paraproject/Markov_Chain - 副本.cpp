#include "stdio.h"
#include "string.h"

#define state_length 1
#define nullsymblo 42
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

//next(abc) returns a and updates the trace to bc
char next(char* state){
	int i=0;
	//Set char first_char as the first char in state;
	char first_char;
	first_char=state[0];
	//Move the second char in trace to the first;
	//Move the third char to the second;
	for (i=1;i<strlen(state);i++){
		state[i-1]=state[i];
	}
	//Since the window size is 3, we finish the moving part;
	//Set the last char as NULL;
	state[i-1]=nullsymblo;
	return first_char;
}

//shift(aba; c) is equal to bac
void shift(char* state, char* trace){
	//Use ¡°next¡± function to shift the trace;
	//Set char first_char as the return value of ¡°next¡±;
	char first_char=next(trace);
	//Use ¡°next¡± function to shift the state;
	char unused=next(state);
	//Add the first_char to the end of the state;
	state[state_length-1]=first_char;
}

/*Use the input trace to form a state and a transition*/

//After all these, we got every possible states out of the trace, and the times they happened; also we got every adjacent transition
//b)	Pseudo Code for Creating local classifier when the mis-rate metric is used
//z, m, xi, yi will be further define
//This function classifies the generated MC
//Good MC returns 1, bad returns 0
int classifier(int r, int u){
	int flag=0;
	if (u>=r)
	flag=1;
	else
	flag=0;
	return flag;
}
 
//This function used to calculate local matrix
float local_matrix(float* x,float* y,float m,float z){
	int k;
	float sum_x=0;
	float sum_y=0;
	//Set int k to be the bigger one between 0 and (m-z+1)
	k=0>(m-z+1)?0:(m-z+1);
	for (int i=k;i<m;i++){
		sum_x=sum_x+x[i];
		sum_y=sum_y+y[i];
	}
	return (sum_x/sum_y);
}

/*This function check if a state have a valid transition, true returns 1, fulse returns 0*/
int valid(char* state,int m,int z){
	int k;
	//Set int k to be the bigger one between 0 and (m-z+1)
	k=0>(m-z+1)?0:(m-z+1);
	int cmp_result=0;
	for (int i=k;i<m;i++){
		char check_state[state_length];
		for (int j=0;j<state_length;j++){
			check_state[j]=store_transition[i].transition[j];
		}
		//Compare the left 3 char of all store_transition.transition with state;
        cmp_result+=strcmp(check_state,state);
		//If they are the same
	 }
	if (cmp_result==0){
		return 1;
	}
	else return 0;
}

/*This function check if the current_state have a same state in the forming markov chain, true returns 1, fulse returns 0*/
int exist_state(char* current_state,int sequence_state,int* same_state_number){
	int cmp_result=0;
	int flag=0;
	for (int i=0;i<sequence_state;i++){
		//Compare the left (state_length) char of all store_transition.transition with state;
		cmp_result=strcmp(store_state[i].state,current_state);
		//strcmp return 0 if str1==str2
		if (cmp_result==0){
			*same_state_number=i;flag=1;
		}
	}
//If they are the same,flag is 1
	return flag;
}

int exist_transition(char* new_transition,int sequence_transition,int* same_transition_number){
	int cmp_result=0;
	int flag=0;
	for (int i=0;i<sequence_transition;i++){
		//Compare the left 3 char of all store_transition.transition with state;
		cmp_result=strcmp(store_transition[i].transition,new_transition);
		//strcmp return 0 if str1==str2
		if (cmp_result==0){
			*same_transition_number=i;flag=1;
		}
	}
//If they are the same,flag is 1
	return flag;
}

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

//**************************main function**************************
void main(){
	//trace can be input from keyboard, or files, this string is just for test
	char trace[]="SRRRRRRRRRRRSRRSRRRRRRSRRSSSSSS";
	int sequence_state=0;
	int sequence_transition=0;
	int same_state_number;
	int same_transition_number;
	printf("The input trace is: %s\n",trace);
	//set initial value of store_state
	for (int i=0;i<state_length;i++){
		for (int j=0;j<state_length;j++){
			store_state[i].state[j]=nullsymblo;
			if (j==(state_length-1)){
				store_state[i].state[j+1]=0;
			}
		}
		store_state[i].counter_s=0;
	}

	char current_state[state_length+1];
	char last_state[state_length+1];
	//set initial value for current_stateand and last_state
	for (int j=0;j<state_length;j++){
		current_state[j]=nullsymblo;last_state[j]=nullsymblo;
		if (j==(state_length-1)){
		current_state[j+1]=0;last_state[j+1]=0;
		}
	}

	//initializing passed!
	//This is the beginning of MC training
	for (int i=0;i<strlen(trace);i++){
		int same_state_number=0;
		int same_transition_number=0;
		for (int j=0;j<state_length;j++){
			last_state[j]=current_state[j];
		}
		//Use ¡°shift¡± function to shift current_state and add one char of trace to the end of it;
		shift(current_state,trace);
		//Form the MC and their counter
		//If there is a store_state.state[x] is the same as current_state
		int have_this_s=0;
		have_this_s=exist_state(current_state,sequence_state,&same_state_number);
		if (have_this_s==1){
			store_state[same_state_number].counter_s++;
		}
		else{
			//Set store_state[sequence_state].state as this newly created state
			for (int j=0;j<state_length;j++){
				store_state[sequence_state].state[j]=current_state[j];
			}
			store_state[sequence_state].counter_s=1;
			sequence_state++;
		}
		//Form the transition and their counter
		//Set store_transtion[i].transition as NULL;
		//Set store_transition[i].counter as 0;
		for (int j=0;j<state_length*2;j++){
			store_transition[i].transition[j]=nullsymblo;
			if (j==(state_length*2-1)){
				store_transition[i].transition[j+1]=0;
			}
		}
		store_transition[i].counter_t=0;
		//Combine current_state and last_state as ¡°last_state,current_state¡±
		//Named the combination as new_transition
		char new_transition[state_length*2+1]="0";
		for (int j=0;j<state_length;j++){
			new_transition[j]=last_state[j];
		}
		for (int j=state_length;j<state_length*2;j++){
			new_transition[j]=current_state[j-state_length];
			if (j==(state_length*2-1)){
				new_transition[j+1]=0;
			}
		}
		int have_this_t=0;
		have_this_t=exist_transition(new_transition,sequence_transition,&same_transition_number);
		//If there is a store_transtion[x].transition is the same as new_transition;
		if (have_this_t==1){
			store_transition[same_transition_number].counter_t++;
		}
		else{
			//Set store_transition[sequence].transition as new_transition
			for (int j=0;j<state_length*2+1;j++){
				store_transition[sequence_transition].transition[j]=new_transition[j];
			}
			store_transition[sequence_transition].counter_t=1;
			sequence_transition++;
		}
	}
	//*state and transition capture pass************************************
	output_MC(sequence_state);
	output_MC_counter(sequence_state);
	output_statetransition(sequence_transition);
	output_statetransition_count(sequence_transition);

	//now build the MC matrix
	//This matrix have raw of sequence_state, colomn too
	int *matrix_counter=new int[sequence_state*sequence_state];
	//merge state[0] and [1],check if there is a transition is the same as it, then post the counter
	for (int i=0;i<sequence_state;i++){
		for (int j=0;j<sequence_state;j++){
			matrix_counter[i*sequence_state+j]=0;
			char node[state_length*2+1]="0";
			for (int k=0;k<state_length;k++){
				node[k]=store_state[i].state[k];
			}
			for (int k=state_length;k<state_length*2;k++){
				node[k]=store_state[j].state[k-state_length];
			}
			node[state_length*2]=0;
			int have_this_m=0;
			have_this_m=exist_transition(node,sequence_transition,&same_transition_number);
			//if there is a trasition is the store_transition, then just set matrix[i][j] as the counter_t
			if (have_this_m==1){
				matrix_counter[i*sequence_state+j]=store_transition[same_transition_number].counter_t;
			}
		}
	}

	float *matrix=new float[sequence_state*sequence_state];
	for (int i=0;i<sequence_state;i++){
		for (int j=0;j<sequence_state;j++){
			int raw_sum=0;
			for (int k=0;k<sequence_state;k++)raw_sum+=matrix_counter[i*sequence_state+k];
			matrix[i*sequence_state+j]=float(matrix_counter[i*sequence_state+j])/float(raw_sum);
			//if there is a trasition is the store_transition, then just set matrix[i][j] as the counter_t
		}
	}

	output_transition_matrix_counter(matrix_counter,sequence_state);
	output_transition_matrix(matrix,sequence_state);
	printf("Press anykey......\n");
	char anykey;
	scanf("%c",&anykey);
	delete matrix;
	delete matrix_counter;
}