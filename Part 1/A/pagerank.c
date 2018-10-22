#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

Graph makegraph(char *pages, int numNodes);

int main (){
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
		printf("%s, %s, %d\n", pages[j], &str1, j);
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
	double bpr = 1/i;
	double *pageranks;
	pageranks = calloc(i,sizeof(double));
	int counter5 = 0;
	while(counter < i){
		pageranks[counter] = bpr;
		counter5++;
	}
	int iteration = 1;
	int maxIteration = 30;
	double diff = 1;
	while(iteration <= maxIteration && diff > 0){
		/*int sum1 = 0;
		int counter = 0;
		while(counter < webpages->nV){
			int counter2 = 0;
			int ino = 0;
			int iny = 0;
			int outo = 0;
			int outy = 0;
			while(counter2 < webpages->nV){
				ino = ino + connection(webpages,counter2,counter);
				if(connection(webpages,iteration,counter2)){
					int counter3 = 0;
					while(counter3 < webpages->nV){
						iny = iny + connection(webpages,counter3,counter2);
						counter3++;
					}
				}
				outo = outo(
				counter2++
			}
			sum = sum + pagerank[counter]*(ino/iny)*(outo/outy);
			counter++;
		}
		pageranks[counter] = ((1-(0.85))/(webpages->nV))+(0.85)
		*/
		int counter6 = 0;
		while(counter6 < i){
			int sum = 0;
			int counter2 = 0;
			while(counter2 < i){
				int In1 = 0;
				int In2 = 0;
				int Out1 = 0;
				int Out2 = 0;
				int counter3 = 0;
				while(counter3 < i){
					In1 = In1 + connection(webpages,counter3,counter6);
					Out1 = Out1 + connection(webpages,counter6,counter3);
					if(connection(webpages,counter2,counter3)){
						int counter4 = 0;
						while(counter4 < i){
							In2 = In2 + connection(webpages,counter4,counter3);
							Out2 = Out2 + connection(webpages,counter3,counter4);
							counter4++;
						}
					}
					counter3++;
				}
				sum = pageranks[counter2]*(In1/In2)*(Out1/Out2);
				counter2++;
			}
			diff = pageranks[counter6] - ((1-(0.85))/i)+(0.85)*sum;
			pageranks[counter6] = ((1-(0.85))/i)+(0.85)*sum;
			counter6++;
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
