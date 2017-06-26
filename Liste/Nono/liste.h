typedef struct nodo Lista;
typedef Lista *ListaPointer;

ListaPointer initLista();

int getElemento(ListaPointer);
void setElemento(ListaPointer, int);

void inserisciNodoTesta (ListaPointer *, int);
void inserisciNodoCoda (ListaPointer *, int);
void inserisciNodoOrdinato (ListaPointer *, int);

void printLista(ListaPointer);

int lunghezzaLista (const ListaPointer);

ListaPointer searchLista (const ListaPointer, int);
ListaPointer copyLista (ListaPointer);

void svuotaLista (ListaPointer);
void cencellaElemento (ListaPointer *, int);
void cancellaTutteOccorrenze (ListaPointer *, int);

ListaPointer mergeSort (ListaPointer *);


ListaPointer concatena (const ListaPointer, const ListaPointer);
ListaPointer concatenaDue (ListaPointer, ListaPointer);