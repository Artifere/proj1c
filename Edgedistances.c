#include <stdio.h>
#include <stdlib.h>

void readEdgesCities(char *filename, float ***adjacence)
{
	int sommet1,sommet2,inutile;
	float distance;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%d!",&inutile);
	while (fscanf(file, "%d %d: %f!", &sommet1, &sommet2, &distance) != EOF)
	{
		(*adjacence)[sommet1][sommet2] = distance;
	}
	fclose(file);
}

int main()
{
	FILE *file = fopen("testEdgesDistances","r");
	int taille,i,j;
	fscanf(file,"%d!",&taille);
	fclose(file);
	float **adjacence = malloc(taille * sizeof(float));
	readEdgesCities("testEdgesDistances",&adjacence);
	for(i = 1; i < taille+1; i++)
	{
		for(j = 1; j < taille+1; j++)
			printf("%d ->%f %d \n",i,adjacence[i][j],j);
	}
	free(adjacence);
	return 0;
}
