#ifndef list_C
#define list_C

#include "list.h"

boolean ListEmpty(List L)
{
	return (First(L) == Nil);
}

void CreateList(List *L)
{
	First(*L) = Nil;
}

address Alokasi(infotype X)
{
	address P;
	P = (address) malloc (sizeof (ElmtList));
	if ((P) != Nil)
	{
		info(P) = X;
		next(P) = Nil;
	}
	return (P);
}

void Dealokasi(address P)
{
	free(P);
}

address Search(List L, infotype X)
{
	boolean Found = false;
	address P;

	P = First(L);
	while ((P != Nil) && (!Found))
	{
		if ((X.x == info(P).x) && (X.y == info(P).y))
		{
			Found = true;
		}
		else
			P = next(P);
	}
	return(P);
}

boolean FSearch(List L, address P)
{
}

address SearchPrec (List L, infotype X, address *Prec)
{
}

void InsVFirst(List *L, infotype X)
{
	address P;
	P = Alokasi(X);
	if (P != Nil)
		InsertFirst(&(*L), P);
}

void InsVLast(List *L, infotype X)
{
	address P;
	P = Alokasi(X);
	if (P != Nil)
		InsertLast (&(*L), P);
}

void DelVFirst(List *L, infotype *X)
{/*
	address P;
	DelFirst(&(*L), &P);
	*X = info(P);
	Dealokasi(P);*/
}

void DelVLast(List *L, infotype *X)
{/*
	address P;
	DelLast(&(*L), &P);
	*X = info(P);
	Dealokasi(P);*/
}

void InsertFirst(List *L,address P)
{
	next(P) = First(*L);
	First(*L) = P;
}

void InsertAfter(List *L, address P, address Prec)
{
	next(P) = next(Prec);
	next(Prec) = P;
}

void InsertLast(List *L, address P)
{
	address Last;
	if (!ListEmpty(*L))
	{
		Last = First(*L);
		while (next(Last) != Nil)
			Last = next(Last);
		next(Last) = P;
	}
	else
		InsertFirst(&(*L), P);
}

void DelFirst(List *L, address *P)
{
	*P = First(*L);
	First(*L) = next(First(*L));
	next(*P) = Nil;
}

void DelP(List *L, infotype X)
{
/*	address P, Prec;
	P = First(*L);
	Prec = Nil;
	while ((info(P) != X) && (next(P) != Nil))
	{
		Prec = P;
		P = next(P);
	}
	if (info(P) == X)
	{
		next(Prec) = next(P);
	}*/
}

void DelLast(List *L, address *P)
{
	address Last, PrecLast;
	Last = First(*L);
	PrecLast = Nil;
	while (next(Last) != Nil)
	{
		PrecLast = Last;
		Last = next(Last);
	}
	*P = Last;
	if (PrecLast != Nil)
	{
		next(PrecLast) = Nil;
	}
	else
		First(*L) = Nil;
}

void DelAfter(List *L, address *PDel, address Prec)
{
	*PDel = next(Prec);
	next(Prec) = next(next(Prec));
	next(*PDel) = Nil;
}

void PrintInfo(List L)
{
	address P;
	P = First(L);
	if (P == Nil)
	{
		printf("List is empty");
	}
	else
	{
		do
		{
			printf("[%d]", info(P));
			P = next(P);
		}
		while (P != Nil);
	}
}

#endif
