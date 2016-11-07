#include "heap.h"
#include "vector_dinamico.h"
#include <stdlib.h>
#define TAM_INICIAL 1

struct heap{
  vector_t *vector;
  cmp_func_t cmp;
  size_t cantidad;
};


void swap (void* valor1, void* valor2) {
	void* dato_aux = valor1;

	valor1 = valor2;
	valor2 = dato_aux;
}

void upheap(heap_t *heap, size_t pos, size_t cantidad){
  vector_t *vector = heap->vector;
  if(pos <= 0) return;
  size_t pos_padre = (i -1)/2;
  if(heap->cmp(vector_obtener(vector, pos), vector_obtener(vector, pos_padre)) > 0){
    swap(vector_obtener(vector, pos), vector_obtener(vector, pos_padre));
    upheap(heap, pos_padre, cantidad);
  }

}


void downheap(heap_t *heap, size_t pos, size_t cantidad){
  vector_t *vector = heap->vector;
  if(pos >= cantidad) return;
  size_t pos_h_izq = pos*2 -1, pos_h_der = 2*pos -1, pos_padre = pos;
  if(pos_h_izq < cantidad && heap->cmp(vector_obtener(vector, pos_padre), vector_obtener(vector, pos_h_izq)) < 0)
    pos_padre = pos_h_izq;
  if(pos_h_der < cantidad && heap->cmp(vector_obtener(vector, pos_padre), vector_obtener(vector, pos_h_der)) < 0)
    pos_padre = pos_h_der;
  if(pos != pos_padre){
    swap(vector_obtener(vector, pos_padre), vector_obtener(vector, pos));
    downheap(heap, pos_mayor, cantidad);
  }
}

void heapify(vector_t *arreglo, size_t cantidad){
  for(size_t i = (n/2)-1; i >= 0; i--){
    downheap(heap, i, n);
  }
}


/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

}



heap_t *heap_crear(cmp_func_t cmp){
  if(!cmp) return NULL;

  heap_t *heap = malloc(sizeof(heap_t));
  if(!heap) return NULL;

  heap->vector = vector_crear(TAM_INICIAL);
  if(!heap->vector){
    free(heap);
    return NULL;
  }

  heap->cmp = cmp;
  heap->cantidad = 0;
  return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
  heap_t *heap = heap_crear(cmp);
  if(!heap) return NULL;
  for(size_t i = 0; i < n; i++){
    if(!vector_guardar(heap->vector, arreglo[i])) return NULL;
  }
  heapify(heap, n);
  return heap;

}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  if(!heap) return;
  for(size_t i = 0; i < heap->cantidad; i++){
    if(destruir_elemento)
      destruir_elemento(heap->vector[i]);
  }
  free(heap);
}

size_t heap_cantidad(const heap_t *heap){
  if(!heap) return 0;
  return heap->cantidad;
}


bool heap_esta_vacio(const heap_t *heap){
  if(heap_cantidad(heap) == 0) return true;
  return false;
}

bool heap_encolar(heap_t *heap, void *elem){
  if(!heap || !vector_guardar(heap->vector, elem)) return false;

  heap->cantidad++;
  upheap(heap, heap->cantidad - 1, heap->cantidad);
  return true;
}

void *heap_ver_max(const heap_t *heap){
  if(!heap) return NULL;
  return vector_obtener(heap->vector, 0);
}

void *heap_desencolar(heap_t *heap){
  if(!heap) return NULL;

  swap(vector_obtener(heap->vector, heap->cantidad -1), vector_obtener(heap->vector, 0));
  void * dato = vector_borrar(heap->vector, heap->cantidad -1);
  heap->cantidad--;
  downheap(heap, 0, heap->cantidad);
  return dato;

}
