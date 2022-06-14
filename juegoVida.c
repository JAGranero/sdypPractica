#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//Dimension de la matriz
int dim = 100;
int ciclos= 1000;


//Nuestra la matriz
int mostrarMatriz(char **matriz){
    int i,j;
    for ( i = 0; i < dim; ++i)
    {
        for ( j = 0; j < dim; ++j)
        {
            printf(" %c ", matriz[i][j]);
        }
        printf("\n");
    }
    return(0);
}


char evaluacion(char estado, int vecinos){
    if(estado == '*')
        if (vecinos==2 || vecinos==3)
            return('*');
        else
            return('-');
    else
        if (vecinos == 3)
            return('*');
        else
            if (vecinos<2)
            {
                return('*');
            }
            else
                return(estado);
}


void actualizarMatriz(char ***matriz, char ***proxEstado){
    //Contador de vecinos vivos
    int contVecinos=0, i, j;

    char **aux;

    for ( i = 0; i < dim; ++i)
    {   
        for ( j = 0; j < dim; ++j)
        {
            //Primera Fila
            if(i == 0){
                //Primer columna
                if(j == 0){
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j+1]=='*')
                        contVecinos++;
                }
                //Ultima columna
                else if (i == dim-1)
                {
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')
                        contVecinos++;
                }
                //Columnas internas
                else{
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j+1]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')
                        contVecinos++;
                }
            }
            //Ultima fila
            else if (i == dim-1)
            {
                //Primer columna
                if (j == 0){
                    //Contar vecinos vivos
                    if ((*matriz)[i-1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j+1]=='*')
                        contVecinos++;
                }   
                //Ultima columna
                else if(i == dim-1){
                    //Contar vecinos vivos
                    if ((*matriz)[i-1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')
                        contVecinos++;
                }
                //Columnas internas
                else{
                    //Contar vecinos vivos
                    if ((*matriz)[i][j+1]=='*')
                        contVecinos++;
                    if ((*matriz)[i-1][j]=='*')
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')
                        contVecinos++;
                }
            }
            //Filas internas
            else{
                //Primer columna
                if (j == 0){
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')//abajo
                        contVecinos++;
                    if ((*matriz)[i-1][j]=='*')//arriba
                        contVecinos++;
                    if ((*matriz)[i][j+1]=='*')//derecha
                        contVecinos++;
                }
                //Ultima columna
                else if(i == dim-1){
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')// abajo
                        contVecinos++;
                    if ((*matriz)[i-1][j]=='*')//arriba
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')//izquierda
                        contVecinos++;
                }
                //Columnas internas
                else{
                    //Contar vecinos vivos
                    if ((*matriz)[i+1][j]=='*')// abajo
                        contVecinos++;
                    if ((*matriz)[i-1][j]=='*')//arriba
                        contVecinos++;
                    if ((*matriz)[i][j+1]=='*')//derecha
                        contVecinos++;
                    if ((*matriz)[i][j-1]=='*')//izquierda
                        contVecinos++;
                }
            }

            //Evalua proximo estado en base a los vecinos vivos y el estado actual
            (*proxEstado)[i][j] = evaluacion((*matriz)[i][j], contVecinos);
            //Setea contador de vecionos
            contVecinos=0;
        }
    }

    //Actualizar matriz actual (cambio de punteros)
    aux = (*matriz);
    (*matriz) = (*proxEstado);
    (*proxEstado) = aux;
}

void main(int argc, char const *argv[])
{
    char **matriz; 
    char **proxEstado;
    time_t t;
    int i, j;

    //Controlo que se pase como parametro la dimension de la matriz
    /*if(argc > 1 ){
        //dimension de la matriz
        dim = atoi(argv[1]);
        //cantidad de ciclos
        int ciclos= atoi(argv[2]);
    }*/

    //Inicializa la semilla del random
    srand((unsigned) time(&t));

    //Se crea la matriz
    matriz = (char**) malloc(sizeof(char *)*dim);
    for (i = 0; i < dim; ++i)
     {
        matriz[i] = (char*) malloc(sizeof(char)*dim);
        
        //Se inicializa la fila recien creada de la matriz
        for ( j = 0; j < dim; ++j)
        {
            if(rand()%100 < 30)
                matriz[i][j] = '*';
            else
                matriz[i][j] = '-';
        }
     }
     //Se asigna espacio para la matriz auxiliar
     proxEstado = (char**) malloc(sizeof(char *)*dim);
    for ( i = 0; i < dim; ++i)
     {
        proxEstado[i] = (char*) malloc(sizeof(char)*dim);
     }


     //ciclos de vida
     printf("Vida del automata:\n\n");
     for ( i = 1; i <= ciclos; ++i)
     {  
        //Mostrar ciclo y matriz
        printf("Ciclo nro. %d: \n\n", i);
        mostrarMatriz(matriz);
        printf("\n\n");

        //Calcular proximo estado
        actualizarMatriz(&matriz, &proxEstado);
     }
     



     for ( i = 0; i < dim; ++i)
     {
        free(matriz[i]);
        free(proxEstado[i]);
     }
     free(matriz);
     free(proxEstado);
     printf("FIN DE LA EJECUCION \n\n");
    getchar();
}