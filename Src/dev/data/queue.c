/*
 * queue.c
 *
 *  Created on: 2018. 11. 6.
 *      Author: kdj6724
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int init_queue(Queue* queue) {
  queue->front = NULL;
  queue->rear = NULL;
  queue->count = 0;
  return 0;
}
int is_empty(Queue* queue) {
  return (queue->count == 0);
}
int is_full(Queue* queue) {
  return (queue->count >= QUEUE_MAX_DATA);
}
void enqueue(Queue* queue, char* data, int len) {
  Node* newNode;

  if (is_full(queue))
    return;
  newNode = (Node*) malloc(sizeof(Node));
  newNode->data = (char*) malloc(len);

  if (is_empty(queue))
    queue->front = newNode;
  else
    queue->rear->next = newNode;

  queue->rear = newNode;
  queue->count++;
}
int dequeue(Queue* queue, char* data) {
  Node* node;
  int len = 0;
  if (is_empty(queue))
    return 0;
  if (data == NULL)
    return -1;

  node = queue->front;
  memcpy(data, node->data, strlen(node->data));
  len = strlen(data);
  queue->front = node->next;
  free(node->data);
  free(node);
  queue->count--;

  return len;
}
