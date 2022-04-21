#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

typedef struct Device
{
	char nom[10];
	char id[3];
	char marque[10];
	char type[10];
	char addresse[20];
} Device;

typedef enum 
{
	false,
	true
} Bool;
/*--------------------------------------------*/
Bool InitDeviceFile(char *name)
{
	FILE *deviceFile =fopen(name, "r");
	if(deviceFile==NULL)
	{
		deviceFile=fopen(name, "w");
		if(deviceFile==NULL)
			return false;
		//fprintf(deviceFile, "{\n\n}");
		return true;
	}else
	{
		fprintf(stderr, "CETTE FICHIER DEJA EXISTE\n");
		exit(1);
	}
}
/*--------------------------------------------*/
void pushDevice(Device *device, char *FileName)
{
	FILE *deviceFile=fopen(FileName, "a");
	if(deviceFile==NULL){
		fprintf(stderr, "FICHIER INTROUVABLE OU PROBLEME LORS DE LOUVERTURE");
		exit(1);
	}
	fprintf(deviceFile, "\" %s \":{\"id\":\" %s \", \"marque\":\" %s \", \"type\":\" %s \", \"addresse\":\" %s \" },\n", device->nom, device->id, device->marque, device->type, device->addresse);
	printf("Device inserted\n");
	fclose(deviceFile);
}

/*--------------------------------------------*/

Device* deviceSearch(char *FileName, char *DeviceName)
{
	FILE *deviceFile=fopen(FileName, "r");
	static Device localDevice;
	if(deviceFile==NULL){
		fprintf(stderr, "FICHIER INTROUVABLE OU PROBLEME LORS DE LOUVERTURE");
		exit(1);
	}
	while(!feof(deviceFile))
	{
		if(fscanf(deviceFile, "\" %s \":{\"id\":\" %s \", \"marque\":\" %s \", \"type\":\" %s \", \"addresse\":\" %s \" },", localDevice.nom, localDevice.id, localDevice.marque, localDevice.type, localDevice.addresse)){
			if(strcmp(DeviceName, localDevice.nom)==0){
			fclose(deviceFile);
			return &localDevice;
		}
	}else
		break;
	}
	printf("cette device n'existe pas\n");
	fclose(deviceFile);
	return NULL;
	
}



/*--------------------------------------------*/
void printDevices(char* FileName){
	FILE *deviceFile=fopen(FileName, "r");
	Device localDevice;
	if(deviceFile==NULL){
		fprintf(stderr, "FICHIER INTROUVABLE OU PROBLEME LORS DE LOUVERTURE");
		exit(1);
	}
	while(!feof(deviceFile))
	{
		if(fscanf(deviceFile, "\" %s \":{\"id\":\" %s \", \"marque\":\" %s \", \"type\":\" %s \", \"addresse\":\" %s \" },\n", localDevice.nom, localDevice.id, localDevice.marque, localDevice.type, localDevice.addresse)){
			printf("%s :\n\tid : %s\n\tmarque : %s\n\ttype : %s\n\taddresse : %s\n", localDevice.nom, localDevice.id, localDevice.marque, localDevice.type, localDevice.addresse);
			printf("--------------------------------------------------------------------\n");
		}else
			break;
	}
	printf("Terminer\n");
}

/*--------------------------------------------*/
int main(int argc, char **argv)
{
	Bool validOp;
	char option;
	Device device1;
	Device *dev2;
	char rech[20];
	char FileNameFromCmd[20];
	//while(options=getopt(argc, argv, "iacp") != -1){
	if(argv[1]){
		option=argv[1][0];
		switch(option)
		{
			case 'i':
			/*initialkisation dune npouvelle fichier vide */
				printf("taper le nom de fichier avec son extension\n");
				scanf("%s", FileNameFromCmd);
				validOp=InitDeviceFile(FileNameFromCmd);
				if(validOp==true)
					printf("file initialiser avec succées\n");
				else
					printf("problemes lors de création de fichier\n");
				break;
				/*-----------------------------------------------------------*/
			case 'a':
				printf("taper le nom de fichier avec son extension\n");
				scanf("%s", FileNameFromCmd);
				printf("veiller taper les informations de votre device\n");
				scanf("nom:%s {id: %s, marque: %s, type: %s, addresse: %s}", &device1.nom, &device1.id, &device1.marque, &device1.type, &device1.addresse);
				/* ajouter un nouvelle objet a la fin de fichier  */
				pushDevice(&device1, FileNameFromCmd);
				break;
			case 'c':
				printf("taper le nom de fichier avec son extension\n");
				scanf("%s", FileNameFromCmd);
				printf("veiller taper le nom  de votre device a chercher\n");
				scanf("%s", rech);
				/*-----------------------------------------------------------*/
				/*                reacherche              */
				dev2=deviceSearch(FileNameFromCmd, rech);
				if(dev2!=NULL){
					printf("detecte...\n");
					printf("%s :\n\tid : %s\n\tmarque : %s\n\ttype : %s\n\taddresse : %s\n", dev2->nom, dev2->id, dev2->marque, dev2->type, dev2->addresse);
				}
				break;
			case 'p':
				/*--------------afficher tous les devices -------------*/
				printf("taper le nom de fichier avec son extension\n");
				scanf("%s", FileNameFromCmd);
				printDevices(FileNameFromCmd);
				break;
			default:
				printf("veiller voir la documentaion pour bien choisissez vos arguments\n");
				return 0;
		}
	//}
	}else
		printf("veiller voir la documentaion pour bien choisissez vos arguments\n");
	return 0;
}