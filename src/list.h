#ifndef list_H
#define list_H

#include "boolean.h"
#include "point.h"

#define Nil 0
#define info(P) (P)->info
#define next(P) (P)->next
#define First(L) ((L).First)
typedef point infotype;
typedef struct tElmtList *address;
typedef struct tElmtList
{
	infotype info;
	address next;
}ElmtList;

typedef struct 
{	address First;
}List;

boolean ListEmpty(List L);
void CreateList(List *L);
address Alokasi(infotype X);
void Dealokasi(address P);
address Search(List L, infotype X);
boolean FSearch(List L, address P);
address SearchPrec (List L, infotype X, address *Prec);
void InsVFirst(List *L, infotype X);
void InsVLast(List *L, infotype X);
void DelVFirst(List *L, infotype *X);
void DelVLast(List *L, infotype *X);
void InsertFirst(List *L,address P);
void InsertAfter(List *L, address P, address Prec);
void InsertLast(List *L, address P);
void DelFirst(List *L, address *P);
void DelP(List *L, infotype X);
void DelLast(List *L, address *P);
void DelAfter(List *L, address *PDel, address Prec);
void PrintInfo(List L);

#endif
