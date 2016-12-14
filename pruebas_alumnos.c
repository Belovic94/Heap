#include "heap.h"
#include "vector_dinamico.h"
#include "testing.h"
#include <stdio.h>
#include "pila.h"
#define VALORES 10

/*************************************************************************
 *                          FUNCIONES AUXILIARES                         *
 *************************************************************************/
int cmp_pila(const void *a, const void *b){
   bool a_vacia = pila_esta_vacia((pila_t*)a);
   bool b_vacia = pila_esta_vacia((pila_t*)b);
   if (a_vacia && !b_vacia) return 1;
   if (!a_vacia && b_vacia) return -1;
   return 0;
}

void destructor_pila(void* pila){
   pila_destruir((pila_t*)pila);
}

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

void pruebas_heapsort(int tam){
  void *vec[tam];
  int vec_aux[tam];
  int j = 0;
  for(int i = 0; i < tam; i++){
    j = tam - i;
    vec_aux[i] = j;
    vec[i] = &vec_aux[i];
  }
  bool ok = true;
  heap_sort(vec, tam, comparar);
  for(int i = 0; i < tam; i++){
    if(*(int*)vec[i] != i) ok = false;
  }
  print_test("Prueba de heapsort", ok);
}


void pruebas_varias(){
   pila_t* pila1 = pila_crear();
   pila_t* pila2 = pila_crear();
   pila_apilar(pila1, NULL);
   heap_t* heap = heap_crear(cmp_pila);
   bool ok = true;
   ok &= heap_encolar(heap, pila1);
   ok &= heap_encolar(heap, pila2);
   print_test("Encolar pilas en heap", ok);
   heap_destruir(heap, destructor_pila);
   print_test("Destruir heap", true);
}
void pruebas_heap_alumno(void){
  pruebas_heap_vacio();
  pruebas_heap_volumen();
  pruebas_heapsort(VALORES);
  pruebas_varias();
}
