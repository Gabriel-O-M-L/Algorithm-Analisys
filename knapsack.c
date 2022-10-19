#include <stdio.h>
#include <string.h>
void main()
{
    int capacity, no_items, cur_weight, item;
    int used[10];
    float total_profit;
    int i;
    int *weight;
    int *value;
    char nome[100];

    printf("Qual o nome do arquivo?\n");
    fgets(nome,100,stdin);
    nome[strlen(nome)-1] = '\0';

    FILE *name = fopen(nome, "r");

    printf("Qual o peso maximo?\n");
    scanf("%d", &capacity);

    fseek(name, 0L, SEEK_END);

    int size = ftell(name);
    float temp = 0;
    float aux = 0;
    int j = 0;

    rewind(name);
    *value= (int*)malloc((sizeof(int)*size));
    *weight= (int*)malloc((sizeof(int)*size));

    while (!feof (name))
    {
        fscanf (name, "%f;%f", &temp, &aux);
        value[j] = temp;
        weight[j] = aux;
        j++;
    }


    for (i = 0; i < no_items; ++i)
        used[i] = 0;

    cur_weight = capacity;
    while (cur_weight > 0)
    {
        item = -1;
        for (i = 0; i < no_items; ++i)
            if ((used[i] == 0) &&
                ((item == -1) || ((float) value[i] / weight[i] > (float) value[item] / weight[item])))
                item = i;

        used[item] = 1;
        cur_weight -= weight[item];
        total_profit += value[item];
        if (cur_weight >= 0)
            printf("Adcionei o objeto %d (%d Rs., %dKg) Completamente na mochila. Espaco livre: %d.\n", item + 1, value[item], weight[item], cur_weight);
        else
        {
            int item_percent = (int) ((1 + (float) cur_weight / weight[item]) * 100);
            printf("Adicionou %d%% (%d Rs., %dKg) do objeto %d na mochila.\n", item_percent, value[item], weight[item], item + 1);
            total_profit -= value[item];
            total_profit += (1 + (float)cur_weight / weight[item]) * value[item];
        }
    }

    printf("A mochile possui o valor total de %.2f Rs.\n", total_profit);
}
