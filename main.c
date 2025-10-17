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

int esta_ordenado(int v[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        if (v[i-1] > v[i]) return 0;
    }
    return 1;
}

void revertir_vector(int v[], int n) {
    int i, aux;

    for (i = 0; i < n / 2; i++) {
        aux = v[i];
        v[i] = v[n - i - 1];
        v[n - i - 1] = aux;
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
    int i, j = 0, aux;

    for (i = 1;; i++) {
        aux = (int)pow(2, i) - 1;
        if (aux > n) {
            break;
        }
        inc[j++] = aux;
    }
    *m = j;
    revertir_vector(inc, j);
}

void rellenar_v_knuth(int inc[], int *m, int n) {
    int i, j = 0, aux;

    for (i = 1;; i++) {
        aux = ((int)pow(3, i) - 1) / 2;
        if (aux > n) {
            break;
        }
        inc[j++] = aux;
    }
    *m = j;
    revertir_vector(inc, j);
}

void rellenar_v_sedgewick(int inc[], int *m, int n) {
    int i, j = 0, aux;

    inc[j++] = 1;
    for (i = 1;; i++) {
        aux = (int)pow(4, i) + 3 * (int)pow(2, i - 1) + 1;
        if (aux > n) {
            break;
        }
        inc[j++] = aux;
    }
    *m = j;
    revertir_vector(inc, j);
}

void rellenar_v_ciura(int inc[], int *m, int n) {
    int base[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int i, j = 0, aux;

    for (i = 0; i < 9; i++) {
        if (base[i] > n) {
            break;
        }
        inc[j++] = base[i];
    }
    aux = base[8];
    while (1) {
        aux = (int)(aux * 2.25);
        if (aux > n) break;
        inc[j++] = aux;
    }
    *m = j;
    revertir_vector(inc, j);
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

            while (j >= h && v[j - h] > x) {
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
    printf("\nOrdenado? %d\n", esta_ordenado(v_rand, n));


    ord_ins(v_rand, n);
    printf("\nOrdenacion por Insercion\n");
    listar_vector(v_rand, n);
    printf("\nOrdenado? %d\n", esta_ordenado(v_rand, n));


    printf("\nInicializacion descendente\n");
    listar_vector(v_desc, 10);
    printf("\nOrdenado? %d\n", esta_ordenado(v_desc, 10));


    ord_ins(v_desc, 10);
    printf("\nOrdenacion por Insercion\n");
    listar_vector(v_desc, 10);
    printf("\nOrdenado? %d\n", esta_ordenado(v_desc, 10));


    insercion_tiempos();
}

void shell_test() {
    int n = 500; 
    int m_hibbard = 50, m_knuth = 50, m_sedgewick = 50, m_ciura = 50;
    int v[32000];
    int inc[50];
    double tb, ta;

    printf("\nOrdenacion por Shell | Hibbard\n");
    printf("%11sn%12st(n)%10st(n)/n%4st(n)/n^(5/4)%8st(n)/n^2\n", "", "", "", "", "");
    while (n <= 32000) {
        aleatorio(v, n);
        rellenar_v_hibbard(inc, &m_hibbard, n);
        tb = microsegundos();
        ord_shell(v, n, inc, m_hibbard);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb, 
                                                        (ta - tb) / n,
                                                        (ta - tb) / pow(n, 1.25), 
                                                        (ta - tb) / pow (n, 2));
        n *= 2;
    }
    n = 500;
    printf("\nOrdenacion por Shell | Knuth\n");
    printf("%11sn%12st(n)%10st(n)/n%4st(n)/nlog(n)%6st(n)/n^3/2\n", "", "", "", "", "");
    while (n <= 32000) {
        aleatorio(v, n);
        rellenar_v_knuth(inc, &m_knuth, n);
        tb = microsegundos();
        ord_shell(v, n, inc, m_knuth);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb, 
                                                        (ta - tb) / n,
                                                        (ta - tb) / (n * log(n)), 
                                                        (ta - tb) / pow (n, 1.5));

        n *= 2;
    }
    n = 500;
    printf("\nOrdenacion por Shell | Sedgewick\n");
    printf("%11sn%12st(n)%10st(n)/n%4st(n)/nlog(n)%5st(n)/n^3/2\n", "", "", "", "", "");
    while (n <= 32000) {
        aleatorio(v, n);
        rellenar_v_sedgewick(inc, &m_sedgewick, n);
        tb = microsegundos();
        ord_shell(v, n, inc, m_sedgewick);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb, 
                                                        (ta - tb) / n,
                                                        (ta - tb) / (n * log(n)), 
                                                        (ta - tb) / pow (n, 1.5));
        n *= 2;
    }
    n = 500;
    printf("\nOrdenacion por Shell | Ciura\n");
    printf("%11sn%12st(n)%10st(n)/n%4st(n)/nlog(n)%5st(n)/n^3/2\n", "", "", "", "", "");
    while (n <= 32000) {
        aleatorio(v, n);
        rellenar_v_ciura(inc, &m_ciura, n);
        tb = microsegundos();
        ord_shell(v, n, inc, m_ciura);
        ta = microsegundos();
        printf("%12d\t%12.3f\t%12.8f\t%12.8f\t%12.8f\n", n, ta - tb, 
                                                        (ta - tb) / n,
                                                        (ta - tb) / (n * log(n)), 
                                                        (ta - tb) / pow (n, 1.5));
        n *= 2;
    }
}


int main() {
    inicializar_semilla();
    insercion_test();
    shell_test();

    return 0;
}