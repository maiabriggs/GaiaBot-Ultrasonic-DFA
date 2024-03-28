#include "Arduino.h"
#include "PriorityQueue.h"

void pq_init(priorityQueue* pq, int capacity) {
    pq->nodes = (pqNode*)malloc(sizeof(pqNode) * capacity);
    pq->capacity = capacity;
    pq->size = 0;
}

void pq_push(priorityQueue* pq, int priority, int value) {
    if (pq->size == pq->capacity) {
        // Priority queue is full
        return;
    }
    pqNode newNode;
    newNode.priority = priority;
    newNode.value = value;
    int index = pq->size++;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (pq->nodes[parentIndex].priority <= priority) {
            break;
        }
        pq->nodes[index] = pq->nodes[parentIndex];
        index = parentIndex;
    }
    pq->nodes[index] = newNode;
}

int pq_top(priorityQueue* pq) {
    if (pq->size == 0) {
        // Priority queue is empty
        return -1;
    }
    return pq->nodes[0].value;
}

void pq_pop(priorityQueue* pq) {
    if (pq->size == 0) {
        // Priority queue is empty
        return;
    }
    int lastIndex = --pq->size;
    pqNode temp = pq->nodes[lastIndex];
    int index = 0;
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild >= pq->size) {
            break;
        }
        int minChild = leftChild;
        if (rightChild < pq->size && pq->nodes[rightChild].priority < pq->nodes[leftChild].priority) {
            minChild = rightChild;
        }
        if (pq->nodes[minChild].priority >= temp.priority) {
            break;
        }
        pq->nodes[index] = pq->nodes[minChild];
        index = minChild;
    }
    pq->nodes[index] = temp;
}

bool pq_empty(priorityQueue* pq) {
    return pq->size == 0;
}
