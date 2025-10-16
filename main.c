#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday((&t), NULL) < 0) {
        return 0.0;
    }
    return (double)(t.tv_usec + t.tv_sec * 1000000);
}

void aleatorio(int v[], int n) {
    int i;
    int m = 2 * n + 1;
    for(i = 0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}

void listar_vector(int v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}

void rellenar_v_asc(int v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        v[i] = i + 1;
    }
}

void rellenar_v_desc(int v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void rellenar_v_hibbard(int inc[], int *m, int n) {

    int k = 1;
    int val = 1;
    int i = 0;
    int temp[50];

    // Generar secuencia ascendente
    while (val < n) {
        temp[i++] = val;
        k++;
        val = (1 << k) - 1;  // más rápido y limpio que pow
    }

    // Invertirla en inc[]
    for (int j = 0; j < i; j++) {
        inc[j] = temp[i - j - 1];
    }

    *m = i; // tamaño real

    // Mostrar (opcional)
    for (int j = 0; j < *m; j++) {
        printf("%d ", inc[j]);
    }

    printf("\n");
}

void rellenar_v_knuth(int v[], int m, int max) {

    int k, i;
    for (k = 1, i = 0; k <= max && i < m; k = 3 * k + 1, i++) {
        v[i] = k;
    }
}

void rellenar_v_sedgewick(int v[], int m, int max) {
    int h = 1;
    int i = 0;

    for (h = 1, i = 0; h <= max && i < m; i++) {
        v[i] = h;
        h = pow(4, i) + 3 * pow(2, i - 1) + 1;
        if (h >= 500) break; 
    }
}

void rellenar_v_ciura(int inc[], int *m, int n) {
    int base[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int i, k = 9; // hay 9 valores base
    int next;

    // Copiar los valores base
    for (i = 0; i < k && base[i] < n; i++) {
        inc[i] = base[i];
    }

    next = base[k - 1];

    // Ampliar con multiplicaciones por 2.25
    while ((int)(next * 2.25) < n && i < 50) {  // por si acaso no te pasas de tamaño
        next = (int)(next * 2.25 + 0.5); // redondeo
        inc[i++] = next;
    }

    // Invertir orden, porque Shell sort empieza con los gaps grandes
    for (int j = 0; j < i / 2; j++) {
        int tmp = inc[j];
        inc[j] = inc[i - j - 1];
        inc[i - j - 1] = tmp;
    }

    *m = i;

    // Mostrar para comprobar
    for (int j = 0; j < *m; j++) {
        printf("%d ", inc[j]);
    }
    printf("\n");
}





void ord_ins(int v[], int n) {
    int i, j, x;

    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void ord_shell(int v[], int n, int inc[], int m) {
    int h, i, j, k, x;

    for (k = 0; k < m; k++) {
        h = inc[k];

        for (i = h; i < n; i++) {
            x = v[i];
            j = i;

            while (j > h && v[j - h] > x) {
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = x;
        }
    }
}

void insercion_tiempos() {
    int n = 500;
    int v_rand[32000];
    int v_asc[32000];
    int v_desc[32000];
    double tb, ta;

    printf("\n\nOrdenacion por insercion con iniciacion ascendente\n");
    printf("%11sn%12st(n)%6st(n)/n^0.8%10st(n)/n%6st(n)/n^1.2\n", "", "", "", "", "");
    while (n <= 32000) {
        rellenar_v_asc(v_asc, n);
        tb = microsegundos();
        ord_ins(v_asc, n);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb,
                                                (ta - tb) / pow(n, 0.8),
                                                (ta - tb) / n,
                                                (ta - tb) / pow(n, 1.2));
        n *= 2;
    }

    n = 500;
    printf("\nOrdenacion por insercion con iniciacion descendente\n");
    printf("%11sn%12st(n)%6st(n)/n^1.8%8st(n)/n^2%6st(n)/n^2.2\n", "", "", "", "", "");
    while (n <= 32000) {
        rellenar_v_desc(v_desc, n);
        tb = microsegundos();
        ord_ins(v_desc, n);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb,
                                                (ta - tb) / pow(n, 1.8),
                                                (ta - tb) / pow (n, 2),
                                                (ta - tb) / pow(n, 2.2));
        n *= 2;
    }

    n = 500;
    printf("\nOrdenacion por insercion con iniciacion aleatoria\n");
    printf("%11sn%12st(n)%6st(n)/n^1.8%8st(n)/n^2%6st(n)/n^2.2\n", "", "", "", "", "");
    while (n <= 32000) {
        aleatorio(v_rand, n);
        tb = microsegundos();
        ord_ins(v_rand, n);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb,
                                                (ta - tb) / pow(n, 1.8),
                                                (ta - tb) / pow (n, 2),
                                                (ta - tb) / pow(n, 2.2));
        n *= 2;
    }
}

void insercion_test() {
    int n = 17;
    int v_rand[n];
    int v_desc[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    aleatorio(v_rand, n);
    printf("Inicializacion aleatoria\n");
    listar_vector(v_rand, n);

    ord_ins(v_rand, n);
    printf("\nOrdenacion por Insercion\n");
    listar_vector(v_rand, n);

    printf("\nInicializacion descendente\n");
    listar_vector(v_desc, 10);

    ord_ins(v_desc, 10);
    printf("\nOrdenacion por Insercion\n");
    listar_vector(v_desc, 10);

    insercion_tiempos();
}

void shell_test() {
    int n = 32000; 
    int m = 50;
    int v[n];
    int inc[m];

    rellenar_v_hibbard(inc, &m, n);
    rellenar_v_knuth(inc, m, n);
    rellenar_v_sedgewick(inc, m, n);
    rellenar_v_ciura(inc, &m, n);


}


int main() {
    inicializar_semilla();
    // insercion_test();
    shell_test();

    return 0;
}