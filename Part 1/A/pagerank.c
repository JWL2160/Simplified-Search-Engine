#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

double inLink (int baselink, int original, int nV, Graph g);
double outLink (int baselink, int original, int nV, Graph g);


int main (int argc, char *argv[]){
	char str1[1000], str2[1000];
	//The code below is for counting how many links are in the file
	int counter = 0;
	FILE *fp1;
	fp1 = fopen("collection.txt", "r");
	int i = 0;
	while(fscanf(fp1, "%s", str1) == 1){
		i++;
	}
	//the array of strings
	char *pages[i];
	//pages = calloc(i, sizeof(str1));
	fclose(fp1);
	//loading the strings into the array
	FILE *fp2;
	fp2 = fopen("collection.txt", "r");
	int j = 0;
	while(fscanf(fp2, "%s", str1) == 1){
		pages[j] = strdup(str1);
		//printf("%s, %s, %d\n", pages[j], &str1, j);
		j++;
	}
	fclose(fp2);
	//Graph webpages = makegraph(*pages, i);
	Graph webpages = newGraph(i);
	int k = 0;
	while(k < i){
		char buf[100];
		snprintf(buf, 100, "%s.txt", pages[k]);
		FILE *fp3;
		fp3 = fopen(buf, "r");
		char outstr[1000];
		int flag1 = 0;
		int flag2 = 0;
		while(fscanf(fp3, "%s", outstr) == 1){
			if(strcmp(outstr, "#start") == 0){
				flag1 = 1;
			}
			else if(strcmp(outstr, "Section-1") == 0){
				flag2 = 1;
			}
			else if(strcmp(outstr, "#end") == 0){
				flag1 = 0;
			}
			else if(flag1 == 1 && flag2 == 1){
				int l = 0;
				while(l < i){
					char *temp = pages[l];
					if(strcmp(outstr, temp) == 0){
						insertEdge(webpages, k, l, 1);
						//webpages->edges[k][l] = 1;
						//webpages->nE++;
					}
				l++;
				}
			}
		}
		fclose(fp3);
		k++;
	}
	showGraph(webpages, pages);
	int x = 0;
	while(x<i){
		int y = 0;
		int number = 0;
		while(y<i){
			number = number + connection(webpages, y, x);
			y++;
		}
		printf("%s has %d incoming links\n", pages[x], number);
		x++;
	}

	//this be page rank
	double bpr = (1/(double)i);
	double *pageranks, *oldpageranks;
	pageranks = calloc(i,sizeof(double));
	oldpageranks = calloc(i,sizeof(double));
	int counter5 = 0;
	while(counter5 < i){
		oldpageranks[counter5] = bpr;
		pageranks[counter5] = bpr;
		counter5++;
	}
	int iteration = 1;
	double d = atof(argv[1]);
	double diff = atof(argv[2]);
	while(iteration < (int)argv[3] && diff >= atof(argv[2])){
		printf("%s iteration", iteration);
		int a = 0;
		while(a < i){
			int b = 0;
			double sum = 0;
			while(b < i){
				sum = sum + oldpageranks[b]*inLink(a,1,i,webpages)/inLink(b,0,i,webpages)*outLink(a,1,i,webpages)/outLink(b,0,i,webpages);
				b++;
			}
			pageranks[a] =((1-d)/i) + d* sum;
			diff = pageranks[a]-oldpageranks[a];
			a++;
		}
		int c = 0;
		while(c < i){
			oldpageranks[c] = pageranks[c];
		}
		iteration++;
	}
	int zounter = 0;
	while(zounter < i){
		printf("%s has pagerank of %lf\n", pages[zounter], pageranks[zounter]);
		zounter++;
	}
}




//ok this is the page rank algorithm
double inLink(int baselink, int original, int nV, Graph g){
	double numLinks = 0;
	if(original == 0){
		int counter = 0;
		while(counter < nV){
			if(connection(g, baselink, counter)){
				int counter2 = 0;
				while(counter2 < nV){
					numLinks = numLinks + (double)connection(g, counter2, counter);
					counter2++;
				}
			}
			counter++;
		}
		return numLinks;
	}
	else if(original == 1){
		int counter = 0;
		while(counter < nV){
			numLinks = numLinks + (double)connection(g, counter, baselink);
			counter++;
		}
		return numLinks;
	}
	else
		return 0;

}

double outLink (int baselink, int original, int nV, Graph g){
	double numLinks;
	if(original == 0){
		int counter = 0;
		while(counter < nV){
			if(connection(g, baselink, counter)){
				int counter2 = 0;
				while(counter2 < nV){
					numLinks = numLinks + (double)connection(g, counter, counter2);
					counter2++;
				}
			}
			counter++;
		}
		if(numLinks == 0){
			numLinks = 0.5;
		}
		return numLinks;
	}
	else if(original == 1){
		int counter = 0;
		while(counter < nV){
			numLinks = numLinks + (double)connection(g, baselink, counter);
			counter++;
		}
		return numLinks;
	}
	else
		return 0;


}
