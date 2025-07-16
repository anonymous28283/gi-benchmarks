











 namespace graph { 


class HKGraph
{
    int m{};
    int n{};
    const int NIL{0};
    const int INF{INT_MAX};

    std::vector<std::list<int> >adj;

    std::vector<int> pair_u;
    std::vector<int> pair_v;
    std::vector<int> dist;

public:
    HKGraph();
    HKGraph(int m, int n);
    void addEdge(int u, int v);
    
    bool bfs();
    bool dfs(int u);
	
    int hopcroftKarpAlgorithm();
};



int HKGraph::hopcroftKarpAlgorithm()
{



    pair_u = std::vector<int>(m + 1,NIL); 



    pair_v = std::vector<int>(n + 1,NIL); 

    dist = std::vector<int>(m + 1);

    int result = 0;


    while (bfs())
    {

        for (int u = 1; u <= m; u++){




            if (pair_u[u] == NIL && dfs(u)){
                result++;
	    }
	}
    }
    return result;
}



bool HKGraph::bfs()
{
    std::queue<int> q;


    for (int u = 1; u <= m; u++)
    {

        if (pair_u[u] == NIL){
            
            dist[u] = 0;
            q.push(u);
        }

        else{
            dist[u] = INF;
	}
    }

    
    dist[NIL] = INF;


    while (!q.empty())
    {
        int u = q.front();
        q.pop();


        if (dist[u] < dist[NIL])
        {

            std::list<int>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); ++it)
            {
                int v = *it;


                if (dist[pair_v[v]] == INF)
                {
                    dist[pair_v[v]] = dist[u] + 1; 
                    q.push(pair_v[v]);
                }
            }
        }
    }

   
   
    return (dist[NIL] != INF);
}


bool HKGraph::dfs(int u)
{
    if (u != NIL)
    {
        std::list<int>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            
            int v = *it;


            if (dist[pair_v[v]] == dist[u] + 1)
            {

                if (dfs(pair_v[v]) == true)
                {   
                    pair_v[v] = u;
                    pair_u[u] = v;
                    return true;
                }
            }
        }

        
        dist[u] = INF;
        return false;
    }
    return true;
}


HKGraph::HKGraph() = default;


HKGraph::HKGraph(int m, int n) {
    this->m = m;
    this->n = n;
    adj = std::vector<std::list<int> >(m + 1);
}


void HKGraph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

}

using graph::HKGraph;


void tests(){

	     int v1a = 3, v1b = 5, e1 = 2;
	     HKGraph g1(v1a, v1b);

	     g1.addEdge(0,1);
	     g1.addEdge(1,4);

	     int expected_res1 = 0;
	     int res1 = g1.hopcroftKarpAlgorithm();

	     assert(res1 == expected_res1);
	

     	     int v2a = 4, v2b = 4, e2 = 6;
	     HKGraph g2(v2a, v2b);

             g2.addEdge(1,1);
	     g2.addEdge(1,3);
	     g2.addEdge(2,3);
	     g2.addEdge(3,4);
	     g2.addEdge(4,3);
             g2.addEdge(4,2);
	
	     int expected_res2 = 0;
	     int res2 = g2.hopcroftKarpAlgorithm();

	     assert(res2 == expected_res2);
	

     	     int v3a = 6, v3b = 6, e3 = 4;
	     HKGraph g3(v3a, v3b);

             g3.addEdge(0,1);
	     g3.addEdge(1,4);
	     g3.addEdge(1,5);
	     g3.addEdge(5,0);

	     int expected_res3 = 0;
	     int res3 = g3.hopcroftKarpAlgorithm();

	     assert(res3 == expected_res3);
	
	
    	
}


int main()
{
    tests();

    int v1 = 0, v2 = 0, e = 0;
    std::cin >> v1 >> v2 >> e;
    HKGraph g(v1, v2);  
    int u = 0, v = 0;
    for (int i = 0; i < e; ++i)
    {
        std::cin >> u >> v;
        g.addEdge(u, v);
    }
  
    int res = g.hopcroftKarpAlgorithm();
    std::cout << "Maximum matching is " << res <<"\n";

    return 0;

}
