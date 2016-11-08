#include "heap.h"
#include "vector_dinamico.h"
#include "testing.h"
#include <stdio.h>
#define VALORES 10

/*************************************************************************
 *                          FUNCIONES AUXILIARES                         *
 *************************************************************************/


int comparar (const void *a, const void *b){
   return *(int*)a - *(int*)b;
 }

 void agregar_valores(heap_t *heap, int *vector, size_t cantidad){
   for(size_t i = 0; i < cantidad; i++){
     vector[i] = (int)(i + 1);
     heap_encolar(heap, &vector[i]);
   }
 }
bool quitar_valores(heap_t *heap, size_t cantidad){
  for(size_t i = 0; i < cantidad; i++){
    int *valor = heap_desencolar(heap);
    if(*valor != VALORES - i)
      return false;
  }
  return true;
}
/*void **generar_vector(size_t tam){
  void **vec_aux = malloc(tam * sizeof(void*));
  if(!vec_aux) return NULL;
  int *vec = malloc(tam * sizeof(int));
  for(size_t i = 0; i < tam; i++){
    vec[i] = (int)(i + 1);
    vec_aux[i] = &vec[i];
  }
  return vec_aux;
}*/

/*************************************************************************
 *                           PRUEBAS DEL HEAP                            *
 *************************************************************************/

void pruebas_heap_vacio(void){
  heap_t *heap = heap_crear(comparar);
  int valor = 5;

  print_test("Creo un heap vacio", heap);
  print_test("Verifico que este vacio", heap_esta_vacio(heap));
  print_test("Ver heap max en un heap vacio", !heap_ver_max(heap));
  print_test("Ver la cantidad en un heap vacio", heap_cantidad(heap) == 0);
  print_test("Desencolar de un heap vacio", !heap_desencolar(heap));
  print_test("Encolar en un heap vacio", heap_encolar(heap, &valor));
  print_test("Verifico que el heap no este vacio", !heap_esta_vacio(heap));
  print_test("Verifico que haya un elemento en el heap", heap_cantidad(heap) == 1);
  print_test("Verifico que el maximo sea el elemento que agregue", *(int*)heap_ver_max(heap) == valor);
  print_test("Desencolar el elemento agregado", *(int*)heap_desencolar(heap) == valor);
  print_test("Verifico que este vacio", heap_esta_vacio(heap));
  print_test("Ver heap max en un heap vacio", !heap_ver_max(heap));
  print_test("Ver la cantidad en un heap vacio", heap_cantidad(heap) == 0);
  heap_destruir(heap, NULL);
  print_test("Destruyo el heap", true);
}


void pruebas_heap_volumen(void){
  heap_t *heap = heap_crear(comparar);
  int vec_aux[VALORES];
  agregar_valores(heap, vec_aux, VALORES);

  print_test("Verifico si el heap tiene elementos", !heap_esta_vacio(heap));
  print_test("Verifico si se encolaron todos los elementos", heap_cantidad(heap) == VALORES);
  print_test("Verifico si el maximo es correcto", *(int*)heap_ver_max(heap) == VALORES);
  print_test("Desencolo los elementos del heap", quitar_valores(heap, VALORES));
  print_test("Verifico que este vacio", heap_esta_vacio(heap));
  print_test("Ver heap max en un heap vacio", !heap_ver_max(heap));
  print_test("Ver la cantidad en un heap vacio", heap_cantidad(heap) == 0);
  heap_destruir(heap, NULL);
  print_test("Destruyo el heap", true);
}


void pruebas_heapsort(size_t tam){
  void *vec[tam]; //generar_vector(tam);
  int vec_aux[tam];
  for(size_t i = 0; i < tam; i++){
    vec_aux[i] = (int)(i + 1);
    vec[i] = &vec_aux[i];
  }
  for(size_t i = 0; i < tam; i++){
    printf("%d\n", *(int*)vec[i]);
  }
  heap_sort(vec, tam, comparar);
  printf("Despues del Heap_sort\n");
  for(size_t i = 0; i < tam; i++){
    printf("%d\n", *(int*)vec[i]);
  }
}



void pruebas_heap_alumno(void){
  pruebas_heap_vacio();
  pruebas_heap_volumen();
  pruebas_heapsort(VALORES);
}
