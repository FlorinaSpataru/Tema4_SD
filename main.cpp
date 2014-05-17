#include "node.h"
#include "proc.h"

#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

// Check if a process is viable for execution
bool is_viable(int **matrix, int size, int index){
	int i; bool ok = true;
	if (index > size)
		return false;
	for (i=0; i<size; i++){
		if (matrix[i][index] != 0)
			ok = false;
	} 
	return ok;
}

int main(int argc, char* argv[]){
	int N, M, i, j, k, p ,q, curr_count, idle_count;
	int task_time, time = 0, curr_node =0;
	int **Matrix;
	int *exec_proc;
	Node *task;
	Proc *proc;
	
	// Read from .in file
	ifstream in(argv[1]);
	
	in >> N;
	task = new Node[N+1];
	
	Matrix = new int*[N+1];
	for (i=0; i<N+1; i++)
		Matrix[i] = new int[N+1];
	
	// Initialise matrix with zeros
	for (i=0; i<N+1; i++)
		for (j=0; j<N+1; j++)
			Matrix[i][j] = 0;
		
	// Create the adjacency matrix
	char buffer[512];
	char *aux_char;
	for (i=0; i<N+1; i++){
		in.getline(buffer, 512);
		aux_char = strtok(buffer, " ");
		while (aux_char != NULL){
			sscanf(aux_char, "%d", &j);
			Matrix[i][j] = 1;
			aux_char = strtok(NULL, " ");
		}
	}
	
	in.close();
	
	// Read from .txt file
	ifstream txt(argv[2]);
	
	txt >> M;
	proc = new Proc[M+1];
	
	for (i=1; i<M+1; i++){
		proc[i].index = i;
		proc[i].proc_index = 0;
		proc[i].exec_time = 0;
		proc[i].idle = true; // idle = true means the processor is idle
	}
	
	for (i=1; i<N+1; i++){
		txt >> task_time;
		task[i].index = i;
		task[i].time = task_time;
		task[i].check = false; // check = true means the process was executed
	}
	
	txt.close();
	
	while (curr_node != N){
		
		curr_count = 0; 
		idle_count = 0; 
		
		for (i=1; i<N+1; i++)
			if ((is_viable(Matrix, N+1, i) == true) && (task[i].check == false))
				curr_count++; // Count the viable, not executed processes
		
		for (i=1; i<M+1; i++)
			if (proc[i].idle == true)
				idle_count++; // Count the idle processors
			
		if (curr_count > idle_count)
			curr_count = idle_count; // See if we have enough processors idle
		
		exec_proc = new int[curr_count]; k = 0;
		// In exec_proc I store the processes that will be executed
		
		curr_node += curr_count;
		
		p = 1; q = 1; // Start search at process 1 and processor 1
		
		while (curr_count != 0){
			// Printf T
			if (p == 1 && q == 1) printf("T %d\n",time);
			
			if ((is_viable(Matrix, N+1, p) != true) || (task[p].check != false)){
				p++; // If the process is checked/not viable, go to the next one
			}
			else if (proc[q].idle == false){
				q++; // If the processor is idle, go to the next one
			}
			else {
				// Printf the pair <processor process> that is executed
				printf("%d %d\n",proc[q].index, task[p].index);
				proc[q].exec_time = task[p].time;
				proc[q].proc_index = p;
				proc[q].idle = false; // No longer idle
				task[p].check = true; // Executed process
				
				exec_proc[k] = p; k++;
				
				q++; p++; curr_count--;
			}
			
		}
		
		for (i=1; i<M+1; i++){
			if (proc[i].idle == false){
				// If process not idle, decrement the execution time
				proc[i].exec_time --; 
				if (proc[i].exec_time == 0){
					/* If process reaches execution time zero, mark it as idle and
					 * "delete" the process from the adjacency matrix
					 */
					for (j=1; j<N+1; j++)
						Matrix[proc[i].proc_index][j] = 0;
					proc[i].proc_index = 0;
					proc[i].idle = true;
				}
			}
		}
		
		time ++; // Increment the time
		
		delete [] exec_proc;
		
	}
	
	// Free memory
	delete [] task;
	delete [] proc;
	for (i=0; i<N+1; i++)
		delete [] Matrix[i];
	delete [] Matrix;
	
	return 0;
}
