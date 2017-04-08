#ifndef QUEUEP_H
#define QUEUEP_H

#include "pixel.h"

#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q) (Q).MaxEl

typedef struct {
  pointc *T;
  address HEAD;
  address TAIL;
  int MaxEl;
} Queue;


boolean IsEmpty (Queue Q);
boolean IsFull (Queue Q);

int NbElmt (Queue Q);

void CreateEmpty (Queue *Q, int Max);
void DeAlokasi (Queue *Q);

void AddQ(Queue * Q, pointc X);
void DelQ(Queue *Q, pointc *X);

#endif 
