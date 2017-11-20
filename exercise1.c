#include <stdio.h>
int rozmiar;
int *kolor;
int **macierz;
int cyklicznosc, dwudzielnosc;
void dfs(int wierzcholek, int poprzedni, int jakikolor)
{
	kolor[wierzcholek]=jakikolor;
	if(jakikolor==1) jakikolor=-1;
	else jakikolor=1;
	for(int i=0; i<rozmiar; i++) 
	{
		if(macierz[wierzcholek][i]==1 && kolor[i]!=0 && i!=poprzedni) cyklicznosc=1;//SPRAWDZANIE CYKLICZNOSCI
		if(macierz[wierzcholek][i]==1 && kolor[i]==kolor[wierzcholek]) dwudzielnosc=0;//SPRAWDZANIE 2DZIELNOŚCI
		if(macierz[wierzcholek][i]==1 && kolor[i]==0) dfs(i,wierzcholek,jakikolor);		
	}
}
int main(int argc, char **argv)
{
	int testy, x, spojnosc, skladowesp, drzewiastosc;
	scanf("%d",&testy);
	for(int i=0; i<testy; i++){
		cyklicznosc=0;
		dwudzielnosc=1;
		spojnosc=0;
		skladowesp=1;
		drzewiastosc=0;
		scanf("%d",&rozmiar);
		macierz = malloc(sizeof(int *) * rozmiar);
		for(int j=0; j<rozmiar; j++) 
			macierz[j] = malloc(sizeof(int)*rozmiar); 
		for(int j=0; j<rozmiar; j++)
			for(int k=0; k<rozmiar; k++)
			{
				scanf("%d",&x);
				macierz[j][k] = x;
			}
		
		//PRZECHODZENIE GRAFU W GŁĄB (DFS) z kolorowaniem
		kolor = malloc(sizeof(int[rozmiar]));
		for(int j=0; j<rozmiar; j++) kolor[j]=0;
		dfs(0, NULL, 1);
		//SPRAWDZANIE SPÓJNOŚCI
		spojnosc=1;
		for(int j=0; j<rozmiar; j++)
			if(kolor[j]==0) spojnosc=0;
		//SPRAWDZANIE SKŁADOWYCH SPÓJNOŚCI - przechodzenie i kolorowanie niespójnych części grafu
		if(spojnosc==0)
		{
			int wierzcholek;
			do
			{
				wierzcholek=0;
				for(int j=0; j<rozmiar; j++)
					if(kolor[j]==0)
					{
						wierzcholek=j;
						skladowesp++;
						dfs(wierzcholek,NULL,1);
						break;
					}		
			}while(wierzcholek!=0);
		}
		//SPRAWDZANIE CZY DRZEWO
		if(spojnosc!=0 && cyklicznosc==0) drzewiastosc=1;
		
		printf("Graf %d\nDwudzielny ", i+1);
		if(dwudzielnosc) printf("TAK");
		else printf("NIE");
		printf("\nSpojny ");
		if(spojnosc) printf("TAK");
		else printf("NIE");
		printf(" (%d)\nCykle ", skladowesp);
		if(cyklicznosc) printf("TAK");
		else printf("NIE");
		printf("\nDrzewo ");
		if(drzewiastosc) printf("TAK\n");
		else printf("NIE\n");
		free(macierz);
		free(kolor);
	}
	return 0;
}
