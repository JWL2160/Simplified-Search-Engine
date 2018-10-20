#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

Graph makegraph(char *pages, int numNodes);

int main (){
	char str1[1000], str2[1000];
	//The code below is for counting how many links are in the file
	int counter = 0;
	FILE *fp;
	fp = fopen("collection.txt", "r");
	int i = 0;
	while(fscanf(fp, "%s", str1) == 1){
		i++;
	}
	//the array of strings
	char *pages[i];
	fclose(fp);
	//loading the strings into the array
	fp = fopen("collection.txt", "r");
	i = 0;
	while(fscanf(fp, "%s", str1) == 1){
		pages[i] = strdup(str1);
		printf("%s, %s, %d\n", pages[i], &str1, i);
		i++;
	}
	fclose(fp);
	Graph webpages = makegraph(*pages, i);
	showGraph(webpages, pages);
}


Graph makegraph(char *pages, int numNodes){
	//new graph
	Graph world = newGraph(numNodes);
	int k = 0;
	while(k < numNodes){
		char buf[100];
		
		snprintf(buf, sizeof(buf), "%s.txt", pages[k]);
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
