#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isSubsetSum(int set[], int n, int sum) {

    int subset[n + 1][sum + 1];

    for (int i = 0; i <= n; i++) {
        subset[i][0] = 1;
    }
    for (int i = 1; i <= sum; i++){
        subset[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if (j >= set[i - 1])
                subset[i][j] = subset[i - 1][j]
                               || subset[i - 1][j - set[i - 1]];
        }
    }

    return subset[n][sum];
}


int main(){
        int capacity;
        int i;
        int *value;
        char nome[100];

        printf("Qual o nome do arquivo?\n");
        fgets(nome,100,stdin);
        nome[strlen(nome)-1] = '\0';

        FILE *name = fopen(nome, "r");

        printf("Qual o tamanho?\n");
        scanf("%d", &capacity);

        fseek(name, 0L, SEEK_END);

        int size = ftell(name);
        int temp = 0;
        int aux = 0;
        int j = 0;

        rewind(name);
        value= (int*)malloc((sizeof(int)*size));

        while (!feof (name))
        {
            fscanf (name, "%d", &temp, &aux);
            value[j] = temp;
            j++;
        }

    int n = sizeof(value) / sizeof(value[0]);
    if (isSubsetSum(value, n, value) == 1)
        printf("Achei uma combinaçao");
    else
        printf("Nao achei subset sum");
    return 0;
}