#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>
#include<malloc.h>

void main(int argc, char **argv){
    int nproc;
    int mytid;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &mytid);

    char saludo[50] = "  -Soy el proceso ";
    char id [4];

            
    if(mytid == 0){
	   	//Donde se guardaran los mensajes recibidos
	    char *mensajes;

    	MPI_Status status;
    	// se pide memoria para almacenar todos los mensajes
    	mensajes = (char *) malloc (sizeof (saludo) * nproc);
    	strcpy(mensajes,"");
    	printf("Soy el proceso 0 y los demas procesos dicen: \n");
    	//recibe  los mensajes de los demas procesos
    	for (int i = 1; i < nproc; ++i)//inicia desde 1 ya que no contamos el proceso 0
    	{
    		MPI_Recv(saludo, 50, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

            //Se imprime los mensajes recibidos
            printf("%s",saludo);

    		strcat(mensajes,saludo);
    	}
    	strcat(mensajes,"\0");
    	//Se libera memoria
        free (mensajes);
    }
    else{
    	//cast de int a string
	    sprintf(id, "%d\n", mytid);
	    //concatenar mensaje e id
	    strcat(saludo, id);
	    //envio del mensaje al proceso 0
	    MPI_Send(saludo, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}