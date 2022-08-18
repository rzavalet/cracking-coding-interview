/*
 * 3_6_Animal_Shelter.c
 * Copyright (C) 2022 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * Create a data structure to maintain the animal shelter system. Implement operations such as:
 *    - enqueue
 *    - dequeueAny
 *    - dequeueDog
 *    - dequeueCat
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL    1

enum pet_type
{
  CAT = 0,
  DOG
};
typedef enum pet_type pet_type_t;

unsigned int global_ts = 0;

struct node
{
  char pet_name[128];
  pet_type_t type;
  unsigned int ts;
  struct node *next;
};
typedef struct node node_t;

struct queue
{
  node_t *out;
  node_t *in;
};
typedef struct queue queue_t;

queue_t *alloc_queue()
{
  queue_t *queue = calloc(1, sizeof(queue_t));

  return queue;
}

void free_queue(queue_t *queue)
{
  node_t *tmp;

  while (queue->out) {
    tmp = queue->out;
    queue->out = tmp->next;
    free(tmp);
  }

  free(queue);
}

void enqueue(queue_t *queue, const char *pet_name, pet_type_t type)
{
  node_t *node = calloc(1, sizeof(node_t));

  strcpy(node->pet_name, pet_name);
  node->type = type;
  node->ts = global_ts ++;
  node->next = NULL;

  if (queue->in == NULL) {
    queue->out = node;
  }
  else {
    queue->in->next = node;
  }

  queue->in = node;

  return;
}

int dequeue(queue_t *queue, char *pet_name, pet_type_t *type)
{
  node_t *tmp = NULL;

  if (queue->out == NULL) {
    pet_name[0] = '\0';
    return FAIL;
  }
  else {
    tmp = queue->out;

    if (queue->out == queue->in) {
      queue->in = NULL;
    }

    queue->out = tmp->next;

    strcpy(pet_name, tmp->pet_name);
    *type = tmp->type;

    free(tmp);
  }

  return SUCCESS;
}

struct shelter
{
  queue_t *dogs;
  queue_t *cats;
};
typedef struct shelter shelter_t;

shelter_t *alloc_shelter()
{
  shelter_t *shelter = calloc(1, sizeof(shelter_t));

  shelter->dogs = calloc(1, sizeof(queue_t));
  shelter->cats = calloc(1, sizeof(queue_t));

  return shelter;
}

void free_shelter(shelter_t *shelter)
{
  free_queue(shelter->dogs);
  free_queue(shelter->cats);

  free(shelter);

  return;
}

void enqueue_to_shelter(shelter_t *shelter, const char *pet_name, pet_type_t type)
{
  if (type == CAT) {
    enqueue(shelter->cats, pet_name, type);
  }
  else {
    enqueue(shelter->dogs, pet_name, type);
  }

  return;
}

int dequeueDog(shelter_t *shelter, char *pet_name, pet_type_t *type)
{
  return dequeue(shelter->dogs, pet_name, type);
}

int dequeueCat(shelter_t *shelter, char *pet_name, pet_type_t *type)
{
  return dequeue(shelter->cats, pet_name, type);
}


int dequeueAny(shelter_t *shelter, char *pet_name, pet_type_t *type)
{
  if (shelter->dogs->out != NULL && shelter->cats->out != NULL) {
    if (shelter->dogs->out->ts <= shelter->cats->out->ts) {
      return dequeueDog(shelter, pet_name, type);
    }
    else {
      return dequeueCat(shelter, pet_name, type);
    }
  }
  else if (shelter->dogs->out != NULL) {
    return dequeueDog(shelter, pet_name, type);
  }
  else if (shelter->cats->out != NULL) {
    return dequeueCat(shelter, pet_name, type);
  }
  else {
    pet_name[0] = '\0';
    return FAIL;
  }

  return FAIL;
}

int main()
{
  int rc = SUCCESS;
  char pet_name[100];
  pet_type_t type;
  shelter_t *shelter = alloc_shelter();

  enqueue_to_shelter(shelter, "Chino", DOG);
  enqueue_to_shelter(shelter, "Canela", DOG);
  enqueue_to_shelter(shelter, "Tomy", CAT);
  enqueue_to_shelter(shelter, "Botas", CAT);
  enqueue_to_shelter(shelter, "Blacky", DOG);
  enqueue_to_shelter(shelter, "Catty", CAT);
  
  rc = dequeueAny(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueCat(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueDog(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueAny(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueAny(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueCat(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueDog(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueAny(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");

  rc = dequeueAny(shelter, pet_name, &type);
  if (rc == SUCCESS) printf("Adopted: %s, %s\n", pet_name, type == CAT ? "Cat" : "Dog");


  free_shelter(shelter);

  return 0;
}

