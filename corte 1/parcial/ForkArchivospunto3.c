#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BLKSIZE 80
int main(){
	int i,j,estado;
	int fdOrigen;
	int fdDestino;
	int bytes_read;
	int vector[10];
	char buffer[BLKSIZE];
	char nombre[100];
	char nombreCopia[100];
	ssize_t in, out;
	int borrar;

	printf("\n Nombre del Archivo y extension:\n");
	gets (nombre);

//Creacion de un proceso Padre e hijo

	if (fork() != 0){
		printf("Proceso Padre \n");
		fdOrigen= creat(nombre,0600);	// captura los datos
		for(i=0;i<10;i++){
			vector[i]=i;

		}
		write (fdOrigen,vector,sizeof(vector));
		printf("\n Archivo Creado\n");	
		printf("Proceso Hijo \n");
		//Abrir el primer archivo
		printf("\n Nombre del Archivo a copiar:\n");
		gets (nombre);
		fdOrigen =open(nombre,O_RDWR);
	 	if (fdOrigen==-1)
			perror("Error al abrir el fichero");	
		
	}


	else{

		//Crear y Abrir el otro archivo para ser copiado
		printf("\n Nombre de la copia del Archivo:\n");
		gets (nombreCopia);
		fdDestino = creat(nombreCopia,0600);
		fdDestino = open(nombreCopia,O_RDWR);
	 	if (fdDestino==-1){
			perror("Error al abrir el fichero");
		}
		while((in=read(fdOrigen,&buffer,BLKSIZE))>0){
			out=write(fdDestino,&buffer,(ssize_t) in);
		} // comprueba los archivos
		printf("Copia realizada satisfactoriamente\n");
		printf("Nombre del archivo a eliminar:\n");
		gets (nombre);
		borrar=remove(nombre);
		if(borrar==0)
			printf("El archivo fue borrado\n");
		else
			perror("Error al eliminar el archivo");
	}
	wait(&estado);	// aca se puede configurar el 
	//tiempo de pausa para que se actualice o mande informacion	usleep (1500) para 15 segundos ;
}	
// nota: profe no logre que entender muy bien lo de captura por consola 
// y retornar a la misma por medio de unainterfaz aunque creo que este cumple todos
//los estandares que usted pidio cinseramente deberiamos profundisar mas en esto 
//ya que hemos tenido muy poca informacion y ejemplos practicos .