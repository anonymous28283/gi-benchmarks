
bool visited[MAX_NODES];

bool hamiltonR(Graph g, int nV, Vertex v, Vertex dest, int d)
{




    Vertex w;
    if (v == dest)
    {
        return (d == 0);
    }
    else
    {
        visited[v] = true;
        for (w = 0; w < nV; w++)
        {
            if (adjacent(g, v, w) && !visited[w])
            {
                if (hamiltonR(g, nV, w, dest, d - 1))
                {
                    return true;
                }
            }
        }
    }
    visited[v] = false;
    return false;
}

bool hasHamiltonianPath(Graph g, int nV, Vertex src, Vertex dest)
{
    Vertex v;
    for (v = 0; v < nV; v++) visited[v] = false;
    return hamiltonR(g, nV, src, dest, nV - 1);
}

int main(void)
{
    Edge e;
    int n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    Vertex src, dest;
    printf("Enter source node: ");
    scanf("%d", &src);
    printf("Enter destination node: ");
    scanf("%d", &dest);

    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1)
    {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Finished.\n");

    printf("The graph has ");
    if (hasHamiltonianPath(g, n, src, dest))
        printf("a");
    else
        printf("no");
    printf(" Hamiltonian path from %d to %d.\n", src, dest);

    freeGraph(g);
    return 0;
}
























