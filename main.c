#include <stdio.h>
#include <stdlib.h>
#include "cities.h"


int main(void)
{

//	freopen("error", "w", stdout);
	
	s_XYCity *XYTest = NULL;
	int nbCities = readXYCities("intermediateTownsTest.txt", &XYTest);
	FILE *testWrite = fopen("testXYCities", "w");
	if(testWrite == NULL)
		error("Erreur lors de l'ouverture du fichier test\n");
	if (XYTest == NULL)
		error("AIE AIE AIE, pointeur null ecrit par la fonction readXYCities\n");
	int i;


	//Bon, la j'ai mis un test ici... c'est provisoire ! A l'avenir, il sera dans un dossier de test, ou au moins dans un fichier separe !
	for (i = 0; i < nbCities; i++)
	{
		fprintf(testWrite, "%s: %lf; %lf!\n", XYTest[i].name, XYTest[i].x, XYTest[i].y);
	}

	for (i = 0; i < nbCities; i++)
		destroyXYCity(XYTest[i]);
	free(XYTest);

	return 0;
}
