/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;

typedef struct Graf{
   int vertices;
   int *visited;
   struct Node **adjacency_lists;
} Graf;

NODE *create_node(int valoare_nod){
   NODE *nod_nou = malloc(sizeof(NODE));
   nod_nou->data = valoare_nod;
   nod_nou->next = NULL;

   return nod_nou;
}

Graf *creeare_graf(int vertices){
    int index;
    Graf *graf = malloc(sizeof(Graf));
    graf->vertices = vertices;
    graf->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graf->visited = malloc(sizeof(int) * vertices);

    for (index = 0; index < vertices; index++)
    {
        graf->adjacency_lists[index] = NULL;
        graf->visited[index] = 0;
    }
    return graf;
}

void adauga_muchie(Graf *graf, int sursa, int destinatie)
{
    NODE *nod_nou = create_node(destinatie);
    nod_nou->next = graf->adjacency_lists[sursa];
    graf->adjacency_lists[sursa] = nod_nou;

    nod_nou = create_node(sursa);
    nod_nou->next = graf->adjacency_lists[destinatie];
    graf->adjacency_lists[destinatie] = nod_nou;
}
int adaugare_muchii(int nr_noduri, int nr_laturi, Graf *graf){
    int sursa, destinatie, index;
    printf("Adauga %d muchii (de la 0 la %d)\n", nr_laturi, nr_noduri);

    for (index = 0; index < nr_laturi; index++){

        printf("Sursa: "); scanf("%d", &sursa);
        printf("Destinatie: "); scanf("%d", &destinatie);

       adauga_muchie(graf, sursa, destinatie);
    }
}

int is_empty(NODE *queue){
    if (queue==NULL)
        return 1;
    else return 0;
}

void enqueue(NODE **queue, int data){
    NODE *new_node = create_node(data);

    if (is_empty(*queue)==1)
        *queue = new_node;
    else {
       NODE *temp = *queue;
       while (temp->next){
         temp = temp->next;
       }
       temp->next = new_node;
    }
}

int dequeue(NODE **queue){
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;

    return data;
}

void print_graph(Graf *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++){
      NODE *temp = graph->adjacency_lists[i];
      while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
      }
      printf("\n");
    }
}

void print_queue(NODE *queue){

   while (queue != NULL){
     printf("%d ", queue->data);
     queue = queue->next;
   }
}


void wipe_visited_list(Graf *graf, int numar_noduri){

    for (int index = 0; index < numar_noduri; index++) {
         graf->visited[index] = 0;
    }
}

void DFS(Graf *graf, int start){
    NODE *lista_adiacenta = graf->adjacency_lists[start];
    NODE *temporar = lista_adiacenta;

    graf->visited[start] = 1;
    printf("%d->", start);

    while (temporar != NULL){
    int connected_vertex = temporar->data;

    if (graf->visited[connected_vertex] == 0){
        DFS(graf, connected_vertex);
    }
       temporar = temporar->next;
  }

}

void BFS(Graf *graf, int start){
   NODE *queue = NULL;
   graf->visited[start] = 1;
   enqueue(&queue, start);

   while (is_empty(queue)==0){

       int current = dequeue(&queue);
       printf("%d ", current);
       NODE *temporar = graf->adjacency_lists[current];

       while (temporar != NULL){
           int nod_adiacent = temporar->data;

           if (graf->visited[nod_adiacent] == 0){
               graf->visited[nod_adiacent] = 1;
               enqueue(&queue, nod_adiacent);
            }
         temporar = temporar->next;
       }
    }
}

int main(){

    int nr_noduri, nr_muchii;
    int nod_de_plecare;

    printf("Cate noduri are graful?");
    scanf("%d",&nr_noduri);

    printf("Cate muchii are graful?");
    scanf("%d",&nr_muchii);

    Graf *graf = creeare_graf(nr_noduri);
    adaugare_muchii(nr_noduri, nr_muchii, graf);

    printf("De unde plecam in DFS?");
    scanf("%d", &nod_de_plecare);

    printf("Parcurgere cu DFS:");
    DFS(graf, nod_de_plecare);

    wipe_visited_list(graf, nr_noduri);
    printf("\n");

    printf("De unde plecam in BFS?");
    scanf("%d", &nod_de_plecare);

    printf("Parcurgere cu BFS:");
    BFS(graf, nod_de_plecare);

    return 0;
}
