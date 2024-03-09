#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void print(sensor *v, int i, int numar_senzori)
{
    if (i >= 0 && i < numar_senzori) {
    if (v[i].sensor_type == TIRE) {
    printf("Tire Sensor\n");
    printf("Pressure: ");
    printf("%.2f\n", ((tire_sensor *)v[i].sensor_data)->pressure);
    printf("Temperature: ");
    printf("%.2lf\n", ((tire_sensor *)v[i].sensor_data)->temperature);
    printf("Wear Level: ");
    printf("%d", ((tire_sensor *)v[i].sensor_data)->wear_level);
    printf("%c\n", '%');
    printf("Performance Score: ");
    if (((tire_sensor *)v[i].sensor_data)->performace_score == 0)
    printf("Not Calculated\n");
else
    printf("%d\n", ((tire_sensor *)v[i].sensor_data)->performace_score);

} else {
    printf("Power Management Unit\n");
    printf("Voltage: ");
    printf("%.2lf\n", ((power_management_unit *)v[i].sensor_data)->voltage);
    printf("Current: ");
    printf("%.2lf\n", ((power_management_unit *)v[i].sensor_data)->current);
    printf("Power Consumption: ");
    printf("%.2lf\n", ((power_management_unit *)
    v[i].sensor_data)->power_consumption);
    printf("Energy Regen: ");
    printf("%d", ((power_management_unit *)v[i].sensor_data)->energy_regen);
    printf("%c\n", '%');
    printf("Energy Storage: ");
    printf("%d", ((power_management_unit *)v[i].sensor_data)->energy_storage);
    printf("%c\n", '%');
}
} else {
    printf("Index not in range!\n");
}
}

void analyze(sensor *v, int i, int numar_senzori)
{
if (i >= 0 && i < numar_senzori) {
    void (*lista_operatii[8])();
    get_operations((void **)lista_operatii);
/*la liniile 48 si 49 am declarat un vector de
 pointeri la functii pe care l-am completat cu operatiile
 ce vor fi efectuate asupra senzorilor,deoarece nu e permis
 sa se apeleze explicit functiile*/

    int j;
    for (j = 0; j < v[i].nr_operations ; j++) {
    int a = v[i].operations_idxs[j];
    (*lista_operatii[a])(v[i].sensor_data);
    }
} else {
    printf("Index not in range!\n");
}
}

int verifica(sensor *v, int i, int numar_senzori)
{
    if (i >= 0 && i < numar_senzori) {
    if (v[i].sensor_type == TIRE) {
    if (!(((tire_sensor *)v[i].sensor_data)->pressure >= 19 &&
    ((tire_sensor *)v[i].sensor_data)->pressure <= 28))
    return 0;
    if (!(((tire_sensor *)v[i].sensor_data)->temperature >= 0 &&
    ((tire_sensor *)v[i].sensor_data)->temperature <= 120))
    return 0;
    if (!(((tire_sensor *)v[i].sensor_data)->wear_level >= 0 &&
    ((tire_sensor *)v[i].sensor_data)->wear_level <= 100))
    return 0;
    } else {
    if (!(((power_management_unit *)v[i].sensor_data)->voltage >= 10  &&
    ((power_management_unit *)v[i].sensor_data)->voltage <= 20))
    return 0;
    if (!(((power_management_unit *)v[i].sensor_data)->current >= -100  &&
    ((power_management_unit *)v[i].sensor_data)->current <= 100))
    return 0;
    if (!(((power_management_unit *)v[i].sensor_data)->power_consumption >= 0 &&
    ((power_management_unit *)v[i].sensor_data)->power_consumption <= 1000))
    return 0;
    if (!(((power_management_unit *)v[i].sensor_data)->energy_regen >= 0  &&
    ((power_management_unit *)v[i].sensor_data)->energy_regen <= 100))
    return 0;
    if (!(((power_management_unit *)v[i].sensor_data)->energy_storage >= 0  &&
    ((power_management_unit *)v[i].sensor_data)->energy_storage <= 100))
    return 0;
    }
    return 1;
    }
    return 0;
}
/* functia "verifica" returneaza 1 daca senzorul este valid
sau 0 in caz contrar */

void clear(sensor *v, int numar_senzori, int *dim_noua)
{
/* metoda de lucru pentru functia "clear" este urmatoarea:
pasul 1:alocam memorie pentru un vector auxiliar v2
pasul 2:parcurgem vectorul v si atunci cand intalnim un senzor valid
il inseram in v2
pasul 3:eliberam memoria alocata pt v si inseram inapoi in el
numai senzorii valizi,retinuti in v2
pasul 4:eliberam memoria alocata pentru v2
 */

    sensor *v2 = (sensor *)malloc(numar_senzori * sizeof(sensor));
    if (v2 == NULL)
    return ;
    int k = 0, t;
    for (t = 0; t < numar_senzori; t++) {
    if (verifica(v, t, numar_senzori) == 1) {
    if (v[t].sensor_type == TIRE) {
    v2[k].sensor_type = TIRE;
    v2[k].sensor_data = (tire_sensor *) malloc(sizeof(tire_sensor));
    (((tire_sensor *) v2[k].sensor_data)->pressure) =
    (((tire_sensor *) v[t].sensor_data)->pressure);
    (((tire_sensor *) v2[k].sensor_data)->temperature) =
    (((tire_sensor *) v[t].sensor_data)->temperature);
    (((tire_sensor *) v2[k].sensor_data)->wear_level) =
    (((tire_sensor *) v[t].sensor_data)->wear_level);
    (((tire_sensor *) v2[k].sensor_data)->performace_score) =
    (((tire_sensor *) v[t].sensor_data)->performace_score);
    v2[k].nr_operations = v[t].nr_operations;
    v2[k].operations_idxs = (int *) malloc(v2[k].nr_operations * sizeof(int));
    for (int j = 0; j < v2[k].nr_operations; j++)
    v2[k].operations_idxs[j] = v[t].operations_idxs[j];
} else {
    v2[k].sensor_type = PMU;
    v2[k].sensor_data =
    (power_management_unit *) malloc(sizeof(power_management_unit));
    (((power_management_unit *) v2[k].sensor_data)->voltage) =
    (((power_management_unit *) v[t].sensor_data)->voltage);
    (((power_management_unit *) v2[k].sensor_data)->current) =
    (((power_management_unit *) v[t].sensor_data)->current);
    (((power_management_unit *) v2[k].sensor_data)->power_consumption) =
    (((power_management_unit *) v[t].sensor_data)->power_consumption);
    (((power_management_unit *) v2[k].sensor_data)->energy_regen) =
    (((power_management_unit *) v[t].sensor_data)->energy_regen);
    (((power_management_unit *) v2[k].sensor_data)->energy_storage) =
    (((power_management_unit *) v[t].sensor_data)->energy_storage);
    v2[k].nr_operations = v[t].nr_operations;
    v2[k].operations_idxs = (int *) malloc(v2[k].nr_operations * sizeof(int));
    for (int j = 0; j < v2[k].nr_operations; j++)
    v2[k].operations_idxs[j] = v[t].operations_idxs[j];
}
    k++;
}
}

    for (int i = numar_senzori - 1; i >= 0; i--) {
    free(v[i].sensor_data);
    free(v[i].operations_idxs);
    }
    free(v);
    for (t = 0; t < k; t++) {
    if (v2[t].sensor_type == TIRE) {
    v[t].sensor_type = TIRE;
    v[t].sensor_data = (tire_sensor *)malloc(sizeof(tire_sensor));
    (((tire_sensor *) v[t].sensor_data)->pressure) =
    (((tire_sensor *) v2[t].sensor_data)->pressure);
    (((tire_sensor *) v[t].sensor_data)->temperature) =
    (((tire_sensor *) v2[t].sensor_data)->temperature);
    (((tire_sensor *) v[t].sensor_data)->wear_level) =
    (((tire_sensor *) v2[t].sensor_data)->wear_level);
    (((tire_sensor *) v[t].sensor_data)->performace_score) =
    (((tire_sensor *) v2[t].sensor_data)->performace_score);
    v[t].nr_operations = v2[t].nr_operations;
    v[t].operations_idxs = (int *) malloc(v[t].nr_operations * sizeof(int));
    for (int j = 0; j < v2[t].nr_operations; j++)
    v[t].operations_idxs[j] = v2[t].operations_idxs[j];
} else {
    v[t].sensor_type = PMU;
    v[t].sensor_data =
    (power_management_unit *)malloc(sizeof(power_management_unit));
    (((power_management_unit *) v[t].sensor_data)->voltage) =
    (((power_management_unit *) v2[t].sensor_data)->voltage);
    (((power_management_unit *) v[t].sensor_data)->current) =
    (((power_management_unit *) v2[t].sensor_data)->current);
    (((power_management_unit *) v[t].sensor_data)->power_consumption) =
    (((power_management_unit *) v2[t].sensor_data)->power_consumption);
    (((power_management_unit *) v[t].sensor_data)->energy_regen) =
    (((power_management_unit *) v2[t].sensor_data)->energy_regen);
    (((power_management_unit *) v[t].sensor_data)->energy_storage) =
    (((power_management_unit *) v2[t].sensor_data)->energy_storage);
    v[t].nr_operations = v2[t].nr_operations;
    v[t].operations_idxs = (int *) malloc(v[t].nr_operations * sizeof(int));
    for (int j = 0; j < v[t].nr_operations; j++)
    v[t].operations_idxs[j] = v2[t].operations_idxs[j];
}
}
    *dim_noua = k;
    for (int i = numar_senzori - 1; i >= 0 ; i--) {
    free(v2[i].operations_idxs);
    free(v2[i].sensor_data);
}
    free(v2);
}

int main(int argc, char const *argv[])
{
    FILE *f1 = NULL;
    f1 = fopen(argv[1], "rb");
    if (f1 == NULL)
    return 0;
    char operatie[100] = "";
    int numar_senzori, i, *p, tip_senzor = -1, nr_pmu = 0, k = 0, poz = -1;
    int dim_noua = 0;
    p = &numar_senzori;
    fread(p, sizeof(int), 1, f1);
    sensor *v = (sensor *) malloc(numar_senzori * sizeof(sensor));
    sensor *v2 = (sensor *) malloc(numar_senzori * sizeof(sensor));
    if (v == NULL || v2 == NULL)
    return 0;
/* pentru a tine cont de prioritatea senzorilor,vom proceda astfel:
 pasul 1:alocam memorie pentru un vector auxiliar v2
 pasul 2:incepem sa citim datele si in functie de tipul senzorului avem
 urmatoarele scenarii:
 a) este de tip PMU,deci il inseram direct in v1,deoarece are prioritate
 b) este de tip TIRE,nu are prioritate,asa ca momentan il inseram in v2

 pasul 3:inseram in vectorul v elementele vectorului v2(senzorii de tip TIRE)
 in continuarea senzorilor de tip PMU
 pasul 4:eliberam memoria alocata pentru v2
*/
    for (i = 0; i < numar_senzori; i++) {
    fread(&(tip_senzor), sizeof(int), 1, f1);
    if (tip_senzor == 1) {
    v[nr_pmu].sensor_type = PMU;
    v[nr_pmu].sensor_data =
    (power_management_unit *) malloc(sizeof(power_management_unit));
    fread(&(((power_management_unit *) v[nr_pmu].sensor_data)->voltage),
    sizeof(float), 1, f1);
    fread(&(((power_management_unit *) v[nr_pmu].sensor_data)->current),
    sizeof(float), 1, f1);
    fread(&(((power_management_unit *)
    v[nr_pmu].sensor_data)->power_consumption),
    sizeof(float), 1, f1);
    fread(&(((power_management_unit *) v[nr_pmu].sensor_data)->energy_regen),
    sizeof(int), 1, f1);
    fread(&(((power_management_unit *) v[nr_pmu].sensor_data)->energy_storage),
    sizeof(int), 1, f1);
    fread(&(v[nr_pmu].nr_operations), sizeof(int), 1, f1);
    v[nr_pmu].operations_idxs =
    (int *) malloc(v[nr_pmu].nr_operations * sizeof(int));
    for (int j = 0; j < v[nr_pmu].nr_operations; j++)
    fread(&(v[nr_pmu].operations_idxs[j]), sizeof(int), 1, f1);
    nr_pmu++;
} else {
    v2[k].sensor_type = TIRE;
    v2[k].sensor_data = (tire_sensor *) malloc(sizeof(tire_sensor));
    fread(&(((tire_sensor *) v2[k].sensor_data)->pressure),
    sizeof(float), 1, f1);
    fread(&(((tire_sensor *) v2[k].sensor_data)->temperature),
    sizeof(float), 1, f1);
    fread(&(((tire_sensor *) v2[k].sensor_data)->wear_level),
    sizeof(int), 1, f1);
    fread(&(((tire_sensor *) v2[k].sensor_data)->performace_score),
    sizeof(int), 1, f1);
    fread(&(v2[k].nr_operations), sizeof(int), 1, f1);
    v2[k].operations_idxs =
    (int *) malloc(v2[k].nr_operations * sizeof(int));
    for (int j = 0; j < v2[k].nr_operations; j++)
    fread(&(v2[k].operations_idxs[j]), sizeof(int), 1, f1);
    k++;
    }
}

    k = 0;
    poz = nr_pmu;
    while (poz < numar_senzori) {
    v[poz].sensor_type = TIRE;
    v[poz].sensor_data = (tire_sensor *) malloc(sizeof(tire_sensor));
    (((tire_sensor *) v[poz].sensor_data)->pressure) =
    (((tire_sensor *) v2[k].sensor_data)->pressure);
    (((tire_sensor *) v[poz].sensor_data)->temperature) =
    (((tire_sensor *) v2[k].sensor_data)->temperature);
    (((tire_sensor *) v[poz].sensor_data)->wear_level) =
    (((tire_sensor *) v2[k].sensor_data)->wear_level);
    (((tire_sensor *) v[poz].sensor_data)->performace_score) =
    (((tire_sensor *) v2[k].sensor_data)->performace_score);
    v[poz].nr_operations = v2[k].nr_operations;
    v[poz].operations_idxs = (int *) malloc(v[poz].nr_operations * sizeof(int));
    for (int j = 0; j < v2[k].nr_operations; j++)
    v[poz].operations_idxs[j] = v2[k].operations_idxs[j];
    poz++;
    k++;
}

    int l;
    while (fgets(operatie, 100, stdin)) {

    if (strstr(operatie, "exit")) {
/* cand dam de exit eliberam memoria si nu mai
citim alte operatii*/
    for (i = numar_senzori - 1; i >= 0 ; i--) {
    free(v[i].operations_idxs);
    free(v[i].sensor_data);
    }
    free(v);

    for (i = numar_senzori - 1; i >= 0 ; i--) {
    free(v2[i].operations_idxs);
    free(v2[i].sensor_data);
    }
    free(v2);
    fclose(f1);
    return 0;
    }
/* daca nu am dat de exit,inseamna ca avem de executat
o comanda valida asupra unui senzor,deci parcurgem string-ul
"operatie" de la final catre inceput pana dam de primul spatiu
 si construim intr-o variabila de tip int valoarea corespunzatoare
 indexului pentru care vrem sa apelam uan dintre functiile print sau analyze
 (pentru functia clear nu are relevanta senzorul*/
    l = strlen(operatie) - 1;
    operatie[l] = '\0';
    l--;
    int p10 = 1, indice = 0;
    while (operatie[l] >= '0' && operatie[l] <= '9' && l >= 0) {
    indice = indice + ((int) (operatie[l]) - 48) * p10;
    p10 = p10 * 10;
    l--;
    }
    if (l >= 0 && operatie[l] == '-')
    indice = -indice;
    if (strstr(operatie, "print"))
    print(v, indice, numar_senzori);
    else if (strstr(operatie, "analyze"))
    analyze(v, indice, numar_senzori);
    else if (strstr(operatie, "clear"))
    clear(v, numar_senzori, &dim_noua);
    }
    return 0;
}