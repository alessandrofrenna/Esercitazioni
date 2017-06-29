#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF 30

struct persona {
    char cognome[BUFF];
    char nome[BUFF];
    int eta;
};

typedef struct persona Persona;

Persona defaultPersona ();
FILE * openFile (char *nome, char *modo); 
void initDefaultFile (FILE *fp, size_t howMany);
void readFromFile (FILE *fp, Persona *array, size_t size);
size_t getFileSize (FILE *fp);
void writeRecord(FILE *fp, Persona persona);
void writeRecords(FILE *fp, Persona *people, size_t howMany);
void updateFile (FILE *fp, Persona *people, size_t howMany);


int main (int argc, char **argv)
{   
    if(argc != 3){
        puts("Nome file non dato!");
        return 0;
    }

    FILE *people = openFile(argv[1], argv[2]);

    if(strcmp(argv[2], "wb") == 0 || strcmp(argv[2], "wb+") == 0) {
        initDefaultFile(people, 10);
        fclose(people);
    } else {
        size_t numPeople = getFileSize (people);
        Persona fileInside[numPeople];
        readFromFile(people, fileInside, numPeople);
        fclose(people);

        printf("Quanti elementi vuoi modificare? (minimo 1 massimo %lu) ", numPeople);
        int how;
        scanf("%d", &how);
        getchar();
        if(how != 0) {        
            for(size_t i = 0; i < how; i++){
                printf("Inserisci cognome: ");
                fgets(fileInside[i].cognome, BUFF, stdin);
                printf("Inserisci Nome: ");
                fgets(fileInside[i].nome, BUFF, stdin);
                printf("Inserisci età: ");
                scanf("%d", &fileInside[i].eta);
                getchar();
                puts("");
            }

            people = openFile(argv[1], "wb");
            updateFile(people, fileInside, numPeople);
            fclose(people);
        }
    }


    
}

FILE * openFile (char *nome, char *modo)
{
    FILE *fp = fopen(nome, modo);
    if(fp || strcmp(modo, "wb") || strcmp(modo, "wb+")){
        return fp;
    } else {
        return NULL;
    }
}

Persona defaultPersona ()
{
    Persona defP;
    strcpy(defP.cognome, "unassigned");
    strcpy(defP.nome, "");
    defP.eta = 0;
    return defP;
}

void initDefaultFile (FILE *fp, size_t howMany)
{
    Persona person = defaultPersona();
    size_t nopW = fwrite(&person, sizeof(Persona), howMany, fp);
    printf("Ho inserito nel file %lu persone\n\n", nopW);
}

void readFromFile (FILE *fp, Persona *array, size_t size)
{
    size_t nopR = fread(array, sizeof(Persona), size, fp);
    printf("Ho letto dal file %lu persone\n\n", nopR);
}

size_t getFileSize (FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp)/sizeof(Persona);
    fseek(fp, 0, SEEK_SET);
    return size;
}

void writeRecord(FILE *fp, Persona persona)
{
    size_t nopW = fwrite(&persona, sizeof(Persona), 1, fp);
    printf("Ho inserito nel file %lu persone\n\n", nopW);
}

void writeRecords(FILE *fp, Persona *people, size_t howMany)
{
    size_t nopW = fwrite(people, sizeof(Persona), howMany, fp);
}

void updateFile (FILE *fp, Persona *people, size_t howMany)
{
    writeRecords(fp, people, howMany);
}