#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 20

typedef struct Satisfaction{
    int member;
    int item;
    int score;
}Satisfaction;

Satisfaction List[200], store[21], result[21];
int check_items[21], check_member[21];
int max_score = 0, indexx = 1;

void Read_File(void)
{
    int i = 0;
    char s[100];
    FILE *fp = fopen("satisfaction.txt", "r");
    fgets(s, 100, fp);
    while (fscanf(fp, "%d %d %d\n", &List[i].member, &List[i].item, &List[i].score))
        i++;
    fclose(fp);
}

void Init(void)
{
    for (int i = 1 ; i <= LENGTH ; i++)
    {
        check_items[i] = 0;
        check_member[i] = 0;
    }
    indexx = 1;
}

int Pick_random(void)
{
    srand(time(NULL));
    int ran = rand() % LENGTH + 1;
    while (check_member[ran])
        ran = rand() % LENGTH + 1;
    return ran;
}

int Get_item(int k)
{
    int maximum = 0;
    int select = 0;
    int i = 0;
    while (List[i].member != k)
        i++;
    while (List[i].member == k)
    {
        if (check_items[List[i].item] == 0 && maximum < List[i].score)
        {
            maximum = List[i].score;
            select = List[i].item;
        }
        i++;
    }
    if (maximum != 0)
    {
        store[indexx].member = k;
        store[indexx].item = select;
        store[indexx].score = maximum;
        check_member[k] = 1;
        check_items[select] = 1;
    }
    return check_items[select];
}

int Is_Finish(void)
{
    for (int i = 1 ; i <= LENGTH ; i++)
    {
        if (check_items[i] == 0)
            return 0;
    }
    return 1;
}

int Random_Selection(void)
{
    int sum = 0;
    int temp = 0;
    while(!Is_Finish())
    {
        temp = Get_item(Pick_random());
        if (!temp)
            Init();
        else
            indexx++;
    }
    for (int i = 1 ; i <= LENGTH ; i++)
        sum = sum + store[i].score;
    Init();
    return sum;
}

void Print(void)
{
    for (int i = 1 ; i <= LENGTH ; i++)
        printf("%2d Member's item : %2d, Score : %2d\n", result[i].member, result[i].item, result[i].score);
    printf("Total result : %d\n", max_score);
}

int main(void)
{
    int n = 1000, s = 1800, epoch = 0, temp = 0;
    Read_File();
    while (epoch < n && max_score < s)
    {
        temp = Random_Selection();
        epoch++;
        if (max_score < temp)
        {
            max_score = temp;
            for (int i = 1 ; i <= LENGTH ; i++)
            {
                result[i].member = store[i].member;
                result[i].item = store[i].item;
                result[i].score = store[i].score;
            }
        }
    }
    Print();
    return 0;
}
