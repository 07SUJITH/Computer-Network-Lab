#include<stdio.h>
#include<stdlib.h>

int cost[10][10];
int number_of_nodes;

struct RouterInfo{
    int distance[10];
    int next_hop[10];
} router[10];

void readCostMatrix(){
    printf("\nEnter the cost matrix\n");
    for(int i = 0; i < number_of_nodes; i++){
        for(int j = 0; j < number_of_nodes; j++){
            scanf("%d", &cost[i][j]);
            router[i].distance[j] = cost[i][j];
            router[i].next_hop[j] = j ;
        }
    }
}

void displayRoutingTable(){
    printf("\nRouting Table\n");
    for(int i = 0; i < number_of_nodes; i++){
        printf("\nRouter %d", i + 1);
        printf("\nDestination\tNext Hop\tDistance\n");
        for(int j = 0; j < number_of_nodes; j++){
            printf("%d\t\t%d\t\t%d\n", j + 1, router[i].next_hop[j] + 1, router[i].distance[j] );
        }
    }
}

void calculateRoutingTable(){
    for(int i = 0 ; i < number_of_nodes; i++){
        for(int j = 0; j < number_of_nodes; j++){
            for(int k = 0; k < number_of_nodes; k++){
                int new_distance = cost[i][k] + router[k].distance[j];
                if(router[i].distance[j] > new_distance){
                    router[i].distance[j] = new_distance;
                    router[i].next_hop[j] = k;
                }
            }
        }
    }
}

int main(){
    printf("Enter the number of nodes: ");
    scanf("%d", &number_of_nodes);
    readCostMatrix();
    calculateRoutingTable();
    displayRoutingTable();
    return 0;
}

/*
output
------
            11
    (4)--------(3)
    |  \        |
 1  |    \ 7    |
    |      \    | 3
    |        \  |
    (1)-------(2)
        2
(in the below output, 99 is considered as infinity)

sj@lenovo:~/distanceVectorRouting$ gcc dvr.c -o dvr
sj@lenovo:~/distanceVectorRouting$ ./dvr
Enter the number of nodes: 4

Enter the cost matrix
0  2  99  1
2  0  3   7
99 3  0   11
1  7  11  0        

Routing Table

Router 1
Destination     Next Hop        Distance
1               1               0
2               2               2
3               2               5
4               4               1

Router 2
Destination     Next Hop        Distance
1               1               2
2               2               0
3               3               3
4               1               3

Router 3
Destination     Next Hop        Distance
1               2               5
2               2               3
3               3               0
4               2               6

Router 4
Destination     Next Hop        Distance
1               1               1
2               1               3
3               1               6
4               4               0
sj@lenovo:~/distanceVectorRouting$ 
*/