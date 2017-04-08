#include "queuep.h"

boolean IsEmpty (Queue Q)
{
	return (Head(Q) == NIL && Tail(Q) == NIL);
}

boolean IsFull (Queue Q)
{
	return (NbElmt(Q) == MaxEl(Q));
}

int NbElmt (Queue Q)
{
	if(IsEmpty(Q))
		return 0;
	else if(Tail(Q) >= Head(Q))
		return (Tail(Q) - Head(Q) + 1);
	else
		return (Tail(Q) - Head(Q) + 1 + MaxEl(Q));
}

void CreateEmpty (Queue *Q, int Max)
{
	Q->T = (pointc *) malloc((Max + 1) * sizeof(pointc));
	Head(*Q) = NIL;
	Tail(*Q) = NIL;
	MaxEl(*Q) = Max;
}

void DeAlokasi (Queue *Q)
{
	free(Q->T);
	MaxEl(*Q) = 0;
}

void AddQ(Queue * Q, pointc X)
{
	if(IsEmpty(*Q)) 
	{
		Head(*Q) = 1;
		Tail(*Q) = 1;
	} 
	else 
	{
		if(IsFull(*Q)) 
		{
			if(Head(*Q) == MaxEl(*Q)) 
			{
				Head(*Q) = 1;
			} 
			else 
			{
				Head(*Q)++;
			}
		}
		if(Tail(*Q) == MaxEl(*Q)) 
		{
			Tail(*Q) = 1;
		} 
		else 
		{
			Tail(*Q)++;
		}
	}
	InfoTail(*Q) = X;
}

void DelQ(Queue *Q, pointc *X)
{
	*X = InfoHead(*Q);
	if(Head(*Q) == Tail(*Q)) 
	{
		Head(*Q) = NIL;
		Tail(*Q) = NIL;
	} 
	else if(Head(*Q) == MaxEl(*Q)) 
	{
		Head(*Q) = 1;
	} 
	else 
	{
		Head(*Q)++;
	}
}

