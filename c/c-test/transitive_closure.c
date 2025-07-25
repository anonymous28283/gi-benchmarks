
int digraph[NODES][NODES] = {
    {0, 1, 1, 1}, {1, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
int tc[NODES][NODES];

void warshall()
{
    int i, s, t;
    for (s = 0; s < NODES; s++)
        for (t = 0; t < NODES; t++) tc[s][t] = digraph[s][t];

    for (i = 0; i < NODES; i++)
        for (s = 0; s < NODES; s++)
            for (t = 0; t < NODES; t++)
                if (tc[s][i] && tc[i][t])
                    tc[s][t] = 1;
}

int main(void)
{
    warshall();
    int i, j;
    for (i = 0; i < NODES; i++)
    {
        for (j = 0; j < NODES; j++)
        {
            printf("%d ", tc[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
























