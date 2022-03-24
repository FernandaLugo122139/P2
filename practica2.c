#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char **argv)
{	
	DIR *directorio;
	int band=0,i=0,descriptorFile;
	char ruta[200];
	char archivo[100];
	char dir[100];
	struct dirent *InfoDir;
	struct stat InfoFile;
	if(argc!=3)
	{
		printf("\nEl numero de argumentos que proporcionaste es incorrecto\n");
		exit(EXIT_FAILURE);
	}   
	for (i=0;i<argc;i++)
	{
		//printf("\nNombre del argumento:%s\n",argv[i]);
	}

	strcpy(dir,argv[1]);
	strcpy(archivo,argv[2]);

	//printf("\nNombre del directorio: %s \n",dir);
	//printf("\nNombre del archivo: %s \n",archivo);

	sprintf(ruta,"./%s",dir);
	//printf("\nRUTA: %s\n",ruta);

	do
	{
	directorio=opendir(ruta);
	if(!directorio)
	{	
		band=1;
		//printf("\nSe puede crear, no existe\n");
	}
	else
	{
		printf("\nEse directorio ya existe, dame otro nombre:\n");
		scanf("%s",dir);
		ruta[0]='\0';
		sprintf(ruta,"./%s",dir);
		//printf("\nNueva ruta: %s\n",ruta);
		closedir(directorio);

	}
 	}while(band==0);
	printf("Creando el directorio con el nombre de: %s\n",dir);
	//printf("\nRuta para crear el directorio: %s\n",ruta);
	mkdir(ruta,0777);
	band=0;
	ruta[0]='\0';
	sprintf(ruta,"./%s/%s.txt",dir,archivo);
        do
	{
	descriptorFile=open(ruta,O_RDWR);
	if(descriptorFile==-1)
	{
		printf("\nCreando archivo con el nombre:%s\n",archivo);
		//printf("\nLa ruta para crear el archivo es:%s\n",ruta);
		creat(ruta,0777);
		descriptorFile=open(ruta,O_RDWR);
		band=1;

	}
	else
	{
		printf("\nEl archivo ya existe, dame otro nombre:\n");
		scanf("%s",archivo);
		ruta[0]='\0';
		sprintf(ruta,"./%s/%s.txt",dir,archivo);
		close(descriptorFile);
	}
        }
	while(band==0);
	char cadena[100];
	sprintf(cadena,"Garcia Lugo Maria Fernada\nMendez Larios Emilio\nRivas Gutierrez Carlos Andres\nVillegas Aguilar Carlos\n");
	band=write(descriptorFile,cadena,strlen(cadena));
	if(band==-1)
	{
		printf("\nNo pude escribir en el archivo: %s\n",strerror(errno));
	}
	else
	{
		printf("\nSe escribio en el archivo con exito\n");
	}


	int hardlink,softlink;
	char aux2[200];
	sprintf(aux2,"%s%sHARDLINK",dir,archivo);
	//printf("\nRuta del enlace duro:%s\n",ruta);
	//printf("\nNombre de enlace: %s\n",aux2);
	hardlink=link(ruta,aux2);
	if(hardlink==-1)
	{
		printf("\nError al crear el enlace fisico\n");
	}
	if (hardlink==0)
	{
		printf("\nEnlace fisico creado con exito\n");
	}
	
	char aux[200];
	sprintf(aux,"%s%sSOFTLINK",dir,archivo);
	//printf("\nRuta del enlace suave:%s\n",ruta);
	//printf("\nNombre de enlace: %s\n",aux);
	softlink=symlink(ruta,aux);
	if(softlink==-1)
	{
		printf("\nError al crear el enlace simbolico\n");
	}
	if (softlink==0)
	{
		printf("\nEnlace simbolico creado con exito\n");
	}
	
	printf("\nInformacion Archivo\n");
	printf("----------------------------");
 	stat(ruta,&InfoFile);
	printf("\nTamaño en bytes del archivo: %ld\n",InfoFile.st_size);
	printf("\nInodo del archivo: %ld\n",InfoFile.st_ino);
	printf("\nEl numero de enlaces al archivo: %d\n",InfoFile.st_nlink);
	
	DIR *dirtrabajo;

	dirtrabajo=opendir("./");
	printf("\nInformacion Directorio\n");
	printf("----------------------------");
	while((InfoDir=readdir(dirtrabajo))!=NULL)
	{
		printf("\nEl nombre de la entrada es:%s\n",InfoDir->d_name);
		printf("\nEl inodo de la entrada es:%ld\n",InfoDir->d_ino);
	}

	closedir(dirtrabajo);
	close(descriptorFile);
	closedir(directorio);


	return 0;
}
