/*
 * 4_0_Min_Heap.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct min_heap
{
  int values[128];
  int last;
};
typedef struct min_heap min_heap_t;

#define parent(x)   ((x - 1) >> 2)
#define left_child(x)   ((x << 1) + 1)
#define right_child(x)   ((x << 1) + 2)

#define has_left_child(_h, x)  (left_child(x) < (_h)->last)
#define has_right_child(_h, x)  (right_child(x) < (_h)->last)
#define size_heap(_h) (sizeof((_h)->values)/sizeof((_h)->values[0]))

#define swap(a,b) \
do {  \
  int tmp = b; \
  b = a;  \
  a = tmp; \
} while(0)

void heapifyUp(min_heap_t *heap, int idx)
{
  int par;

  if (idx <= 0) return;

  par = parent(idx);

  if (heap->values[idx] < heap->values[par]) {
    swap(heap->values[idx], heap->values[par]);
    heapifyUp(heap, par);
  }
}

void add(min_heap_t *heap, int value)
{
  if (heap->last >= size_heap(heap)) return;

  heap->values[heap->last] = value;
  heapifyUp(heap, heap->last);
  heap->last ++;

  return;
}

void heapifyDown(min_heap_t *heap, int idx)
{
  int min_idx = idx;

  if (has_left_child(heap, idx) && heap->values[left_child(idx)] < heap->values[min_idx]) {
    min_idx = left_child(idx);
  }

  if (has_right_child(heap, idx) && heap->values[right_child(idx)] < heap->values[min_idx]) {
    min_idx = right_child(idx);
  }

  if (min_idx == idx) return;

  swap(heap->values[idx], heap->values[min_idx]);
  heapifyDown(heap, min_idx);

  return;
}

int extract(min_heap_t *heap)
{
  int tmp;

  if (heap->last <= 0) return INT_MIN;

  tmp = heap->values[0];

  heap->values[0] = heap->values[--heap->last];
  heap->values[heap->last] = 0;

  heapifyDown(heap, 0);

  return tmp;
}

void print(min_heap_t *heap)
{
  int value;
  int i;

  for (i = 0; i < size_heap(heap) && (value = heap->values[i]) != 0; i++) {
    printf("%d ", value); 
  }
  printf("\n");

  return;
}

int main()
{
  int val;
  min_heap_t heap = {0};
  srand(time(NULL));

  for(int i = 0; i < 10; i++) {
    add(&heap, rand() % 1000);
  }

  print(&heap);

  while ((val = extract(&heap)) != INT_MIN) {
    printf("%d\n", val);
  }

  return 0;
}

