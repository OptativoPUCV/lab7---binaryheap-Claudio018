#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){

    if (pq->size == 0) return NULL;
    
    return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
    if(pq->size == pq->capac)
    {
        pq->capac = (pq->capac * 2) + 1;
        pq->heapArray =  (heapElem *) realloc(pq->heapArray,sizeof(heapElem) * pq->capac);
    }

    int indice = pq->size;
    pq->heapArray[indice].data = data;
    pq->heapArray[indice].priority = priority;
    pq->size++;

    while(indice > 0 && pq->heapArray[indice].priority > pq->heapArray[(indice-1)/2].priority)
    {
        heapElem swap = pq->heapArray[indice];
        pq->heapArray[indice] = pq->heapArray[(indice-1)/2];
        pq->heapArray[(indice-1)/2] = swap;
        indice = (indice - 1) / 2;
    }
    
    
}


void heap_pop(Heap* pq){
    if(pq->size == 0) return;

    pq->heapArray[0] = pq->heapArray[pq->size - 1];
    int indice = 0;

    while(pq->size > (2*indice) + 1)
    {
        int hijoIzq = (2*indice) + 1,
            hijoDer = (2*indice) + 2;
        int mayor;
        if(pq->heapArray[hijoDer].priority > pq->heapArray[hijoIzq].priority)
            mayor = hijoDer;
        else   
            mayor = hijoIzq;

        if(pq->heapArray[indice].priority < pq->heapArray[mayor].priority)
        {
            heapElem swap = pq->heapArray[indice];
            pq->heapArray[indice] = pq->heapArray[mayor];
            pq->heapArray[mayor] = swap;
            indice = mayor;
        }
        else break;

        
    }
    pq->size--;
}

Heap* createHeap(){
    Heap* new = (Heap *) malloc(sizeof(Heap));
    new->size = 0;
    new->capac = 3;
    //new->heapArray = NULL;
    new->heapArray = (heapElem *) malloc(sizeof(heapElem)*new->capac);
   return new;
}
