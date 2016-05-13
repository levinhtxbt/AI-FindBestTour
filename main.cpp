#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define MAX_PEAK 10
#define FILE_NAME "D:\\LeVinhAI\\GTS\\data.txt"

using namespace std;

struct GRAPH{
       int totalPeak;
       int cost[MAX_PEAK][MAX_PEAK];
};

struct TOUR{
       GRAPH graph;
       int path[MAX_PEAK];
       int cost;
};

void readFile(GRAPH &graph);
void initializeCycle(TOUR &tour);
int isNotVisited(int peak,TOUR tour);
//Find peak is not visible
int findPeak(int currentPeak,TOUR tour);
TOUR GTS1(GRAPH graph,int startPeak);
TOUR GTS2(GRAPH grap);
void displayTour(TOUR tour);
void displayGraph(GRAPH graph);

int main(int argc, char *argv[])
{
    GRAPH graph;


    readFile(graph);
    displayGraph(graph);

    TOUR bestTour = GTS2(graph);
    displayTour(bestTour);

    system("PAUSE");
    return EXIT_SUCCESS;
}

void readFile(GRAPH &graph){
    FILE *f;
    f = fopen(FILE_NAME,"rt");
    if(f==NULL){
        printf("Can not open file %s",FILE_NAME);
        exit(1);
    }
    fscanf(f,"%d\n",&graph.totalPeak);
    for(int i=0;i<graph.totalPeak;i++){
        for(int j=0;j<graph.totalPeak;j++){
            fscanf(f,"%d",&graph.cost[i][j]);
        }
    }
    fclose(f);
}

void displayGraph(GRAPH graph){
    printf("Total peak: %d\n",graph.totalPeak);
    for(int i=0;i<graph.totalPeak;i++){
        for(int j=0;j<graph.totalPeak;j++){
            printf("%d\t",graph.cost[i][j]);
        }
        printf("\n");
    }
}

void initializeCycle(TOUR &tour){

    for(int i=0;i<MAX_PEAK;i++){
        tour.path[i] = -1;
    }
    tour.cost = 0;
}

//if peak's not visible will be return 1.
int isNotVisited(int peak,TOUR tour){

    for(int i=0;i< MAX_PEAK;i++){
        if(peak == tour.path[i])
            return 0;
    }
    return 1;
}

int findPeak(int currentPeak,TOUR tour){
    int costMin=9999;
    int positon = -1;
    for(int i = 0;i<tour.graph.totalPeak;i++){
        if((currentPeak!=i)&&isNotVisited(i,tour)){
            if(costMin>tour.graph.cost[currentPeak][i]){
                costMin = tour.graph.cost[currentPeak][i];
                positon = i;
            }
        }
    }
    return positon;
}

TOUR GTS1(GRAPH graph,int startPeak){
    TOUR tour;
    initializeCycle(tour);
    tour.graph = graph;
    int N = tour.graph.totalPeak;
    int currentPeak = startPeak;
    tour.path[0] = startPeak;
    int nextPeak;
    for(int k=1;k<N;k++){
        nextPeak = findPeak(currentPeak,tour);
        if(nextPeak!=-1){
            tour.path[k] = nextPeak;
            tour.cost += tour.graph.cost[currentPeak][nextPeak];
            currentPeak = nextPeak;
        }

    }
    tour.path[N]= startPeak;
    tour.cost +=tour.graph.cost[currentPeak][startPeak];
    return tour;
}

TOUR GTS2(GRAPH graph){
    TOUR bestTour = GTS1(graph,0);
    for(int i=1;i<graph.totalPeak;i++){
        TOUR temp = GTS1(graph,i);
        if(bestTour.cost>temp.cost)
        {
            bestTour = temp;
        }
    }
    return bestTour;
}


void displayTour(TOUR tour){
    printf("Tour: ");
    for(int i=0;i<=tour.graph.totalPeak;i++){
        printf("%d",tour.path[i]+1);
        if(tour.path[i+1]!=-1)
            printf(" -> ");
    }
    printf("\nCost: %d",tour.cost);
}
