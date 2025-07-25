
int visited[MAX_NODES];


bool dfsPathCheck(Graph g, int nV, Vertex v, Vertex dest)
{
    Vertex w;
    for (w = 0; w < nV; w++)
        if (adjacent(g, v, w) && visited[w] == -1)
        {
            visited[w] = v;
            if (w == dest)
                return true;
            else if (dfsPathCheck(g, nV, w, dest))
                return true;
        }
    return false;
}

bool findPathDFS(Graph g, int nV, Vertex src, Vertex dest)
{
    Vertex v;
    for (v = 0; v < nV; v++) visited[v] = -1;
    visited[src] = src;
    return dfsPathCheck(g, nV, src, dest);
}

int main(void)
{
    int V = 6;
    Graph g = newGraph(V);

    Edge e;
    e.v = 0;
    e.w = 1;
    insertEdge(g, e);
    e.v = 0;
    e.w = 4;
    insertEdge(g, e);
    e.v = 0;
    e.w = 5;
    insertEdge(g, e);
    e.v = 5;
    e.w = 4;
    insertEdge(g, e);
    e.v = 4;
    e.w = 2;
    insertEdge(g, e);
    e.v = 4;
    e.w = 3;
    insertEdge(g, e);
    e.v = 5;
    e.w = 3;
    insertEdge(g, e);
    e.v = 1;
    e.w = 2;
    insertEdge(g, e);
    e.v = 3;
    e.w = 2;
    insertEdge(g, e);

    int src = 0, dest = 5;
    if (findPathDFS(g, V, src, dest))
    {
        Vertex v = dest;
        while (v != src)
        {
            printf("%d - ", v);
            v = visited[v];
        }
        printf("%d\n", src);
    }
    return 0;
}
























