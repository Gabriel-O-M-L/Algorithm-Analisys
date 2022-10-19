#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//o algoritmo de Boyer-Moore, ao invés de testar o alinhamento com cada carácter, pula caracteres que
//previamente não foram alinhados na palavra, pois já sabe que ali não haverá
//alinhamentos, o que torna o algoritmo mais rápido que o de força bruta, porque pode
//pular alinhamentos previamente falhos e torna “strings” grandes mais fáceis de
//percorrer, pois, haverá diversas ocorrências de padrões na “string” percorrida
//em que alinhamentos não funcionariam, e uma vez reconhecidas e repetidas,
//ao invés de tentar repetir o alinhamento, o algoritmo irá pular até a última
//parte da “string”, já que sabe que na posição os caracteres não serão alinhados.
//Dessa forma, sua eficiẽncia aumenta quanto maior for a “string” a ser percor-
//rida e quanto mais caracteres diferentes existirem, tornando-o um dos algoritmos
//preferidos a ser utilizado para procurar partes em registros, como no caso desta
//pesquisa.
//Seu pior caso é de O(n/m), 0(n·m) para a procura da “string”, já o pre-processamento é de O(m+σ), o seu melhor
// caso sera O(n) sendo n o a quantidade de comparações nescessarias, isto é o tamanho da string procurada, considerando somente a procura da string .
    void preBmGs(char *pattern, int pat_length, int *bmGs);
    void preBmBc(char *pattern, int pat_length, int *bmBc);
    void suffixes(char *pattern, int pat_length, int *suff);
    int BoyerMoore(char *pattern, char *string);
    int KR(char *x, int m, char *y, int n);

void preBmBc(char *pattern, int pat_length, int *bmBc) {
        int i;

        for (i = 0; i < pat_length; ++i)
            bmBc[i] = pat_length;
        for (i = 0; i < pat_length - 1; ++i)
            bmBc[pattern[i]] = pat_length - i - 1;
    }


    void suffixes(char *pattern, int pat_length, int *suff) {
        int f, g, i;

        suff[pat_length - 1] = pat_length;
        g = pat_length - 1;
        for (i = pat_length - 2; i >= 0; --i) {
            if (i > g && suff[i + pat_length - 1 - f] < i - g)
                suff[i] = suff[i + pat_length - 1 - f];
            else {
                if (i < g)
                    g = i;
                f = i;
                while (g >= 0 && pattern[g] == pattern[g + pat_length - 1 - f])
                    --g;
                suff[i] = f - g;
            }
        }
    }

    void preBmGs(char *pattern, int pat_length, int *bmGs) {
        int i, j;
        int *suff;

        suff = (int*) malloc(pat_length * sizeof(int));
        suffixes(pattern, pat_length, suff);

        for (i = 0; i < pat_length; ++i)
            bmGs[i] = pat_length;
        j = 0;
        for (i = pat_length - 1; i >= 0; --i)
            if (suff[i] == i + 1)
                for (; j < pat_length - 1 - i; ++j)
                    if (bmGs[j] == pat_length)
                        bmGs[j] = pat_length - 1 - i;
        for (i = 0; i <= pat_length - 2; ++i)
            bmGs[pat_length - 1 - suff[i]] = pat_length - 1 - i;

        free(suff);
    }

    int BoyerMoore(char *pattern, char *string) {
        int i, j;
        int pat_length = strlen(pattern);
        int str_length = strlen(string);
        int  *bmGs, *bmBc;

        bmGs = (int*) malloc(pat_length * sizeof(int));
        bmBc = (int*) malloc(pat_length * sizeof(int));

        /* Preprocessing */
        preBmGs(pattern, pat_length, bmGs);
        preBmBc(pattern, pat_length, bmBc);

        /* Searching */
        j = 0;
        while (j <= str_length - pat_length) {
            for (i = pat_length - 1; i >= 0 && pattern[i] == string[i + j]; --i);
            if (i < 0) {
                free(bmGs);
                free(bmBc);
                return j;
                //j += bmGs[0];
            }
            else
                j += MAX(bmGs[i], bmBc[string[i + j]] - pat_length + 1 + i);
        }
        free(bmGs);
        free(bmBc);
        return -1;


    }


int KR(char *x, int m, char *y, int n) {
    int d, hx, hy, i, j;

    /* Preprocessing */
    /* computes d = 2^(m-1) with
       the left-shift operator */
    for (d = i = 1; i < m; ++i)
        d = (d<<1);

    for (hy = hx = i = 0; i < m; ++i) {
        hx = ((hx<<1) + x[i]);
        hy = ((hy<<1) + y[i]);
    }

    /* Searching */
    j = 0;

    while (j <= n-m) {
        if (hx == hy && memcmp(x, y + j, m) == 0)
            return j;
        hy = REHASH(y[j], y[j + m], hy);
        ++j;
    }


}

int main(){
    char string_n[512] = "roeu";
    char string_m[1024] = "O rato roeu a roupa do rei de roma";
    int algoritmo;
    int indice;
    printf("1: Boyer moore\n2: Rabin-Karp\n");
    scanf("%d", &algoritmo);
    if(algoritmo == 1) {
        indice = BoyerMoore(string_n, string_m);
        if (indice != -1) {
            printf("\nString achada no indice %d \n", indice);
        } else {
            printf("\nString nao encontrada \n");
        }
    } else{
        printf("string achada no indice %d", KR(string_n, strlen(string_n), string_m, strlen(string_m)));
    }
}
