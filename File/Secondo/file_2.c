#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF 30

struct ferramenta {
    int id;
    char descrizione[BUFF];
    int qta;
    double punit;
};

typedef struct ferramenta Attrezzo;
void writeRecords(FILE *fp, int howMany);
size_t FileHasRecords(FILE *fp);
int menu();
void nuovoAttrezzo (FILE *fp);
void displayAttrezzi (FILE *fp);
void editAttrezzo(FILE *fp, int id, int scelta);

int main (int argc, char **argv)
{
    if(argc != 3){
        puts("Inserisci nome file e metodo di apertura!");
        return 0;
    }

    FILE *ferramenta = fopen(argv[1], argv[2]);
    if(!ferramenta){
        puts("File not found!");
        return 0;
    }

    size_t fsize = FileHasRecords(ferramenta);
    if(fsize == 0){
        writeRecords(ferramenta, 10);
    }
    do {
        int scelta = menu();
        switch(scelta){
            case 1:
                displayAttrezzi(ferramenta);
                break;
            case 2:
                nuovoAttrezzo(ferramenta);
                break;
            case 3:
            case 4:
            case 5:
                system("clear");
                printf("Inserisci id elemento da modificare: (da 1 a %ld) ", fsize);
                int id;
                scanf("%d", &id);
                editAttrezzo(ferramenta, id, scelta);
            case 6:
                return 0;
            default: 
                menu();
                break;
        }   
    } while(1);
}

void writeRecords(FILE *fp, int howMany)
{
    Attrezzo record = {0, "\0", 0, 0};
    for(size_t i = 0; i < howMany; i++) {
        record.id = 0;
         fwrite(&record, sizeof(Attrezzo), 1, fp);
    }
}

size_t FileHasRecords(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp)/sizeof(Attrezzo);
    fseek(fp, 0, SEEK_SET);
    return size;
}

int menu ()
{
    puts("Scegli:");
    puts("1)Controlla il contenuto del file;");
    puts("2)Inserisci elemento;");
    puts("3)Elimina elemento;");
    puts("4)Modifica quantità elemento;");
    puts("5)Modifica prezzo elemento;");
    puts("6)Esci.");
    printf("Scelta? ");
    int scelta;
    scanf("%d", &scelta);
    return scelta;
}

void nuovoAttrezzo (FILE *fp)
{
    Attrezzo nuovo = {0, "\0", 0, 0.00};
    printf("Inserisci codice attrezzo: ");
    scanf("%d", &nuovo.id);
    getchar();
    fseek(fp, (nuovo.id - 1)*sizeof(Attrezzo), SEEK_SET);

    printf("Inserisci descrizione: ");
    fgets(nuovo.descrizione, BUFF, stdin);
    printf("Inserisci quantità: ");
    scanf("%d", &nuovo.qta);
    printf("Inserisci prezzo unitario: ");
    scanf("%lf", &nuovo.punit);

    fwrite(&nuovo, sizeof(Attrezzo), 1, fp);
}

void displayAttrezzi (FILE *fp)
{
    size_t size = FileHasRecords(fp);
    if(size != 0) {
        
        Attrezzo inventario[size];
        fread(inventario, sizeof(Attrezzo), size, fp);
        puts("Inventario prodotti: \n");
        for(size_t i = 0; i < size; i++){
            if(inventario[i].id != 0) {
                inventario[i].descrizione[strlen(inventario[i].descrizione)-1] = '\0';

                printf("ID: %d \nDescrizione: %s\nQuantità: %d\nPrezzo: %.2lf\n\n", inventario[i].id, inventario[i].descrizione, 
                inventario[i].qta, inventario[i].punit);
            }

        }
    }
}

void editAttrezzo(FILE *fp, int id, int scelta)
{
    Attrezzo edit;
    system("clear");
    fseek(fp, (id - 1) * (sizeof(Attrezzo)), SEEK_SET);
    fread(&edit, sizeof(Attrezzo), 1, fp);
    fseek(fp, (edit.id - 1) * (sizeof(Attrezzo)), SEEK_SET);
    switch(scelta){
        case 3: 
            edit.id = 0;
            strcpy(edit.descrizione,"\0");
            edit.qta = 0;
            edit.punit = 0;
            break;
        case 4:
            printf("\nInserisci nuova quantità per il prodotto: ");
            scanf("%d", &edit.qta);
            
            break;
        case 5:
            printf("\nInserisci nuovo prezzo per il prodotto: ");
            scanf("%lf", &edit.punit);
            break;
    }
    fwrite(&edit, sizeof(Attrezzo), 1, fp);
}