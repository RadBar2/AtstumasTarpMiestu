#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

#define MAX_CITIES 100
#define MAX_NAME_LEN 50

// Struktūra, skirta susieti miesto vardą su jo indeksu matricoje
typedef struct {
    char name[MAX_NAME_LEN];
} CityMap;

CityMap cities[MAX_CITIES];
int city_count = 0;

// Funkcija, kuri grąžina miesto indeksą arba užregistruoja naują miestą
int get_or_create_city_id(const char* name) {
    for (int i = 0; i < city_count; i++) {
        if (strcmp(cities[i].name, name) == 0) {
            return i;
        }
    }
    if (city_count >= MAX_CITIES) {
        fprintf(stderr, "Klaida: viršytas maksimalus miestų skaičius (%d).\n", MAX_CITIES);
        exit(1);
    }
    strcpy(cities[city_count].name, name);
    return city_count++;
}

// Funkcija, grąžinanti miesto pavadinimą pagal jo ID (kelio atstatymui)
const char* get_city_name(int id) {
    if (id >= 0 && id < city_count) {
        return cities[id].name;
    }
    return "Nežinomas";
}

// Pritaikyta maršruto išvedimo funkcija, naudojanti tekstinius miestų pavadinimus
void print_text_path(int* path, int source, int destination) {
    if (source == destination) {
        printf("%s", get_city_name(source));
        return;
    }
    if (path[destination] == -1) {
        printf("Maršrutas neegzistuoja.");
        return;
    }
    print_text_path(path, source, path[destination]);
    printf(" -> %s", get_city_name(destination));
}

// Funkcija, nuskaitanti duomenis ir sugeneruojanti grafą bei ieškomus taškus
void readParams(const char* filename, weightedAdjacencyMatrix** matrix, int* src_id, int* dest_id) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Klaida: Duomenų failas '%s' nerastas.\n", filename);
        exit(1);
    }

    char start_city[MAX_NAME_LEN];
    char end_city[MAX_NAME_LEN];
    
    // 1. Nuskaitome pirmąją eilutę: pradinį ir galinį kelionės tikslą
    if (fscanf(file, "%s %s", start_city, end_city) != 2) {
        fprintf(stderr, "Klaida: Nepavyko nuskaityti ieškomo maršruto miestų.\n");
        fclose(file);
        exit(1);
    }

    // Užregistruojame ieškomus miestus, kad gautume jų ID
    *src_id = get_or_create_city_id(start_city);
    *dest_id = get_or_create_city_id(end_city);

    // Laikinai išsaugome kelius iš failo, nes dar nežinome tikslaus matricų dydžio
    struct Edge {
        char u[MAX_NAME_LEN];
        char v[MAX_NAME_LEN];
        int dist;
    } edges[500];
    
    int edge_count = 0;
    char u_name[MAX_NAME_LEN], v_name[MAX_NAME_LEN];
    int dist;

    // 2. Nuskaitome visus kelius: miestas1 miestas2 atstumas
    while (fscanf(file, "%s %s %d", u_name, v_name, &dist) == 3) {
        get_or_create_city_id(u_name);
        get_or_create_city_id(v_name);
        
        strcpy(edges[edge_count].u, u_name);
        strcpy(edges[edge_count].v, v_name);
        edges[edge_count].dist = dist;
        edge_count++;
    }
    fclose(file);

    // 3. Sukuriame atitinkamo dydžio kaimynystės matricą
    *matrix = createMatrix(city_count);
    if (*matrix == NULL) {
        fprintf(stderr, "Klaida: Nepavyko sukurti kaimynystės matricos.\n");
        exit(1);
    }

    // 4. Užpildome matricą nuskaitytais keliais (laikome, kad keliai yra dvipusiai)
    for (int i = 0; i < edge_count; i++) {
        int u_id = get_or_create_city_id(edges[i].u);
        int v_id = get_or_create_city_id(edges[i].v);
        (*matrix)->weight[u_id][v_id] = edges[i].dist;
        (*matrix)->weight[v_id][u_id] = edges[i].dist; // Jei grafas orientuotas, šią eilutę ištrinkite
    }
}

int main(int argc, char *argv[]) {
    char file_name[256] = "";

    // Argumentų apdorojimas (ieškomas konfigūracijos/duomenų failas)
    for (int i = 1; i < argc; i++) {
        if (file_name[0] == '\0') {
            strcpy(file_name, argv[i]);
        }
    }

    // Jei failas nebuvo nurodytas, sugeneruojame jį pagal programos pavadinimą (.cfg)
    if (file_name[0] == '\0') {
        strcpy(file_name, argv[0]);
        char *dot = strrchr(file_name, '.');
        if (dot != NULL) {
            strcpy(dot, ".cfg");
        } else {
            strcat(file_name, ".cfg");
        }
    }

    weightedAdjacencyMatrix* matrix = NULL;
    int source_id = -1;
    int dest_id = -1;

    // Nuskaitome parametrus ir užpildome grafą
    readParams(file_name, &matrix, &source_id, &dest_id);

    printf("Ieškomas trumpiausias kelias iš '%s' į '%s'.\n\n", get_city_name(source_id), get_city_name(dest_id));

    // Dinamiškai išskiriame atmintį keliui saugoti
    int* path = (int*)malloc(matrix->matrixSize * sizeof(int));
    if (path == NULL) {
        printf("Klaida: Nepavyko išskirti atminties keliui.\n");
        deleteMatrix(matrix);
        return 1;
    }

    // Vykdome Dijkstros algoritmą
    int total_distance = dijkstra(matrix, source_id, dest_id, path);

    // Tikriname rezultatą ir numatome atvejį, kai maršrutas neegzistuoja
    if (total_distance == -1 || (source_id != dest_id && path[dest_id] == -1)) {
        printf("Rezultatas: Toks maršrutas neegzistuoja.\n");
    } else {
        printf("Trumpiausias maršrutas: ");
        print_text_path(path, source_id, dest_id);
        printf("\nBendras atstumas: %d km\n", total_distance);
    }

    // Išlaisviname atmintį
    free(path);
    deleteMatrix(matrix);

    return 0;
}