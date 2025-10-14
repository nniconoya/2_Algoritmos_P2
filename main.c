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

void rellenar_v_hibbard(int v[], int m, int max) {

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
    int n, m = 10;
    int v[n];
    int inc[m];

    rellenar_v_hibbard(inc, m, n);


}


int main() {
    inicializar_semilla();
    insercion_test();
    shell_test();

    return 0;
}