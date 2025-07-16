











struct Edge {
    unsigned int src;
    unsigned int dest;

    Edge() = delete;
    ~Edge() = default;
    Edge(Edge&&) = default;
    Edge& operator=(Edge&&) = default;
    Edge(Edge const&) = default;
    Edge& operator=(Edge const&) = default;


    Edge(unsigned int source, unsigned int destination)
        : src(source), dest(destination) {}
};

using AdjList = std::map<unsigned int, std::vector<unsigned int>>;


class Graph {
 public:
    Graph() : m_adjList({}) {}
    ~Graph() = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;
    Graph(Graph const&) = default;
    Graph& operator=(Graph const&) = default;


    Graph(unsigned int vertices, AdjList adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}


    Graph(unsigned int vertices, AdjList&& adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}


    Graph(unsigned int vertices, std::vector<Edge> const& edges)
        : m_vertices(vertices) {
        for (auto const& edge : edges) {
            if (edge.src >= vertices || edge.dest >= vertices) {
                throw std::range_error(
                    "Either src or dest of edge out of range");
            }
            m_adjList[edge.src].emplace_back(edge.dest);
        }
    }


    std::remove_reference<AdjList>::type const& getAdjList() const {
        return m_adjList;
    }


    unsigned int getVertices() const { return m_vertices; }


    void addVertices(unsigned int num = 1) { m_vertices += num; }


    void addEdge(Edge const& edge) {
        if (edge.src >= m_vertices || edge.dest >= m_vertices) {
            throw std::range_error("Either src or dest of edge out of range");
        }
        m_adjList[edge.src].emplace_back(edge.dest);
    }


    void addEdge(unsigned int source, unsigned int destination) {
        if (source >= m_vertices || destination >= m_vertices) {
            throw std::range_error(
                "Either source or destination of edge out of range");
        }
        m_adjList[source].emplace_back(destination);
    }

 private:
    unsigned int m_vertices = 0;
    AdjList m_adjList;
};


class CycleCheck {
 private:
    enum nodeStates : uint8_t { not_visited = 0, in_stack, visited };


    static bool isCyclicDFSHelper(AdjList const& adjList,
                                  std::vector<nodeStates>* state,
                                  unsigned int node) {

        (*state)[node] = in_stack;



        auto const it = adjList.find(node);
        if (it != adjList.end()) {
            for (auto child : it->second) {


                auto state_of_child = (*state)[child];
                if (state_of_child == not_visited) {
                    if (isCyclicDFSHelper(adjList, state, child)) {
                        return true;
                    }
                } else if (state_of_child == in_stack) {



                    return true;
                }
            }
        }



        (*state)[node] = visited;

        return false;
    }

 public:

    static bool isCyclicDFS(Graph const& graph) {
        auto vertices = graph.getVertices();


        std::vector<nodeStates> state(vertices, not_visited);


        for (unsigned int node = 0; node < vertices; node++) {



            if (state[node] == not_visited) {

                if (isCyclicDFSHelper(graph.getAdjList(), &state, node)) {
                    return true;
                }
            }
        }



        return false;
    }


    static bool isCyclicBFS(Graph const& graph) {
        auto graphAjdList = graph.getAdjList();
        auto vertices = graph.getVertices();

        std::vector<unsigned int> indegree(vertices, 0);

        for (auto const& list : graphAjdList) {
            auto children = list.second;
            for (auto const& child : children) {
                indegree[child]++;
            }
        }

        std::queue<unsigned int> can_be_solved;
        for (unsigned int node = 0; node < vertices; node++) {


            if (!indegree[node]) {
                can_be_solved.emplace(node);
            }
        }


        auto remain = vertices;

        while (!can_be_solved.empty()) {
            auto solved = can_be_solved.front();

            can_be_solved.pop();

            remain--;


            auto it = graphAjdList.find(solved);
            if (it != graphAjdList.end()) {
                for (auto child : it->second) {

                    if (--indegree[child] == 0) {


                        can_be_solved.emplace(child);
                    }
                }
            }
        }



        return !(remain == 0);
    }
};


int main() {

    Graph g(7, std::vector<Edge>{{0, 1}, {1, 2}, {2, 0}, {2, 5}, {3, 5}});

    std::cout << CycleCheck::isCyclicBFS(g) << '\n';


    std::cout << CycleCheck::isCyclicDFS(g) << '\n';
    return 0;
}
