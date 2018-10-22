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
}


/*Graph makegraph(char *pages, int numNodes){
	//new graph
	Graph world = newGraph(numNodes);
	int k = 0;
	while(k < numNodes){
		char buf[100];
		char temp = pages[k];
		fprintf(stderr,"%s", temp);
		sprintf(buf, "%s.txt", pages[k]);
		fprintf(stderr,"send help");
		FILE *fp;
		fp = fopen(buf, "r");
		char outstr[1000];
		int flag1 = 0;
		int flag2 = 0;
		while(fscanf(fp, "%s", outstr) == 1){
			if(strcmp(outstr, "#start") == 0){
				flag1 = 1;
				fprintf(stderr,"flag1 %s, %d\n", pages[k], k);
			}
			else if(strcmp(outstr, "Section-1") == 0){
				flag2 = 1;
				fprintf(stderr,"flag2 %s, %d\n", pages[k], k);
			}
			else if(strcmp(outstr, "#end") == 0){
				flag1 = 0;
				fprintf(stderr,"noflag1 %s, %d\n", pages[k], k);
			}
			else if(flag1 == 1 && flag2 ==1){
				//add into graph
				fprintf(stderr,"enter the beast %s, %d\n", pages[k], k);
				int j = 0;
				while(j < numNodes){
					fprintf(stderr,"is this the crash? %s, %d\n", pages[k], k);
					char *temp = &pages[j];
					if(!strcmp(outstr, temp)){
						//add edge into graph
						insertEdge(world, k, j, 1); 
					}
					j++;
				}
			}
			fprintf(stderr,"inside %s, %d\n", pages[k], k);
		}
		fclose(fp);
		k++;
		fprintf(stderr,"outside %s, %d\n", pages[k], k);
	}
	return world;
}
*/


//ok this is the page rank algorithm
/*void PageRankW(d, diffPR, maxIterations){
	int iteration = 0;
	diff = diffPR;
	
}
*/
