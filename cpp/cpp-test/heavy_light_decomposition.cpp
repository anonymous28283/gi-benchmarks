












namespace range_queries {

namespace heavy_light_decomposition {

template <typename X> class Tree {


private:
  std::vector<std::list<int>>
      t_adj;
  const int t_nodes,
      t_maxlift;
  std::vector<std::vector<int>>
      t_par;
  std::vector<int> t_depth,
      t_size;

  int t_root;
  std::vector<X> t_val;
  template <typename T> friend class HLD;


  void dfs_size(int u, int p = -1) {
    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_size(v, u);
        t_size[u] += t_size[v];
      }
    }
  }


  void dfs_lca(int u, int p = -1) {
    t_par[u][0] = p;
    if (p != -1) {
      t_depth[u] = 1 + t_depth[p];
    }
    for (int k = 1; k < t_maxlift; k++) {
      if (t_par[u][k - 1] != -1) {
        t_par[u][k] = t_par[t_par[u][k - 1]][k - 1];
      }
    }

    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_lca(v, u);
      }
    }
  }

public:

  explicit Tree(int nodes)
      : t_nodes(nodes), t_maxlift(static_cast<int>(floor(log2(nodes))) + 1) {

    t_root = 0;
    t_adj.resize(t_nodes);
    t_par.assign(t_nodes, std::vector<int>(t_maxlift, -1));
    t_depth.assign(t_nodes, 0);
    t_size.assign(t_nodes, 1);
    t_val.resize(t_nodes);
  }


  void add_edge(const int u, const int v) {
    t_adj[u].push_back(v);
    t_adj[v].push_back(u);
  }


  void change_root(int new_root) { t_root = new_root; }


  void set_node_val(const std::vector<X> &node_val) {
    assert(static_cast<int>(node_val.size()) == t_nodes);
    t_val = node_val;
  }


  void init() {
    assert(t_nodes > 0);
    dfs_size(t_root);
    dfs_lca(t_root);
  }


  void lift(int *const p, int dist) {
    for (int k = 0; k < t_maxlift; k++) {
      if (*p == -1) {
        return;
      }
      if (dist & 1) {
        *p = t_par[*p][k];
      }
      dist >>= 1;
    }
  }


  int kth_ancestor(int p, const int &dist) {
    lift(&p, dist);
    return p;
  }


  int lca(int a, int b) {
    assert(a >= 0 and b >= 0 and a < t_nodes and b < t_nodes);
    if (t_depth[a] > t_depth[b]) {
      lift(&a, t_depth[a] - t_depth[b]);
    }
    if (t_depth[b] > t_depth[a]) {
      lift(&b, t_depth[b] - t_depth[a]);
    }
    if (a == b) {
      return a;
    }
    for (int k = t_maxlift - 1; k >= 0; k--) {
      if (t_par[a][k] != t_par[b][k]) {
        a = t_par[a][k];
        b = t_par[b][k];
      }
    }
    return t_par[a][0];
  }
};


template <typename X> class SG {
private:


  std::vector<X> s_tree;
  int s_size;
  X sret_init = 0;
  template <typename T> friend class HLD;


  X combine(X lhs, X rhs) { return lhs + rhs; }


  explicit SG(int size) {
    s_size = size;
    s_tree.assign(2 * s_size, 0ll);
  }


  void update(int p, X v) {
    for (p += s_size; p > 0; p >>= 1) {
      s_tree[p] += v;
    }
  }


  X query(int l, int r) {
    X lhs = sret_init, rhs = sret_init;
    for (l += s_size, r += s_size + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        lhs = combine(lhs, s_tree[l++]);
      }
      if (r & 1) {
        rhs = combine(s_tree[--r], rhs);
      }
    }
    return combine(lhs, rhs);
  }


  void set_sret_init(X new_sret_init) { sret_init = new_sret_init; }
};


template <typename X> class HLD : public Tree<X>, public SG<X> {
private:
  int label;
  std::vector<int> h_label,
      h_heavychlid,
      h_parent;


  void dfs_hc(int u, int p = -1) {
    int hc_size = -1, hc_id = -1;
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p) {
        dfs_hc(v, u);
        if (Tree<X>::t_size[v] > hc_size) {
          hc_size = Tree<X>::t_size[v];
          hc_id = v;
        }
      }
    }
    h_heavychlid[u] = hc_id;
  }


  void dfs_par(int u, int p = -1) {
    if (h_heavychlid[u] != -1) {
      h_parent[h_heavychlid[u]] = h_parent[u];
      dfs_par(h_heavychlid[u], u);
    }
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p and v ^ h_heavychlid[u]) {
        dfs_par(v, u);
      }
    }
  }


  void dfs_labels(int u, int p = -1) {
    h_label[u] = label++;
    if (h_heavychlid[u] != -1) {
      dfs_labels(h_heavychlid[u], u);
    }
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p and v ^ h_heavychlid[u]) {
        dfs_labels(v, u);
      }
    }
  }


  X chain_query(int a, int b) {
    X ret = SG<X>::sret_init;
    if (Tree<X>::t_depth[a] < Tree<X>::t_depth[b]) {
      std::swap(a, b);
    }
    while (Tree<X>::t_depth[a] >= Tree<X>::t_depth[b]) {
      int l = h_label[h_parent[a]];
      int r = h_label[a];
      if (Tree<X>::t_depth[h_parent[a]] < Tree<X>::t_depth[b]) {
        l += Tree<X>::t_depth[b] - Tree<X>::t_depth[h_parent[a]];
      }
      ret = SG<X>::combine(ret, SG<X>::query(l, r));
      a = Tree<X>::t_par[h_parent[a]][0];
      if (a == -1) {
        break;
      }
    }
    return ret;
  }

public:

  explicit HLD<X>(int nodes) : Tree<X>(nodes), SG<X>(nodes) {

    label = 0;
    h_label.assign(Tree<X>::t_nodes, -1);
    h_heavychlid.assign(Tree<X>::t_nodes, -1);
    h_parent.resize(Tree<X>::t_nodes);
    iota(h_parent.begin(), h_parent.end(), 0);
  }


  void init() {
    Tree<X>::init();


    label = 0;
    dfs_hc(Tree<X>::t_root);
    dfs_par(Tree<X>::t_root);
    dfs_labels(Tree<X>::t_root);


    for (int i = 0; i < Tree<X>::t_nodes; i++) {
      SG<X>::s_tree[h_label[i] + Tree<X>::t_nodes] = Tree<X>::t_val[i];
    }
    for (int i = Tree<X>::t_nodes - 1; i > 0; i--) {
      SG<X>::s_tree[i] =
          SG<X>::combine(SG<X>::s_tree[i << 1], SG<X>::s_tree[i << 1 | 1]);
    }
  }


  void update(int node, X val) {
    X diff = val - Tree<X>::t_val[node];
    SG<X>::update(h_label[node], diff);
    Tree<X>::t_val[node] = val;
  }


  X query(int a, int b) {
    int lc = Tree<X>::lca(a, b);
    X ret = SG<X>::sret_init;
    assert(lc != -1);
    ret += chain_query(a, lc);
    ret += chain_query(b, lc);
    return ret - Tree<X>::t_val[lc];
  }
};
}
}


static void test_1() {
  std::cout << "Test 1:\n";


  int n = 5;
  std::vector<int64_t> node_values = {4, 2, 5, 2, 1};
  std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};
  std::vector<std::vector<int>> queries = {
      {2, 1, 4},
      {1, 3, 2},
      {2, 1, 4},
  };
  std::vector<int> expected_result = {11, 8};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest 1 passed!\n";
}


static void test_2() {
  std::cout << "Test 2:\n";


  int n = 10;
  std::vector<int64_t> node_values = {1, 8, 6, 8, 6, 2, 9, 2, 3, 2};
  std::vector<std::vector<int>> edges = {
      {10, 5}, {6, 2}, {10, 7}, {5, 2}, {3, 9}, {8, 3}, {1, 4}, {6, 4}, {8, 7}};
  std::vector<std::vector<int>> queries = {
      {2, 1, 10}, {2, 1, 6}, {1, 3, 4}, {2, 1, 9}, {1, 5, 3},
      {1, 7, 8},  {2, 1, 4}, {2, 1, 8}, {1, 1, 4}, {1, 2, 7}};
  std::vector<int> expected_result = {27, 11, 45, 9, 34};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest2 passed!\n";
}


static void test_3() {
  std::cout << "Test 3:\n";


  int n = 8;
  std::vector<int64_t> node_values = {1, 8, 6, 8, 6, 2, 9, 2};
  std::vector<std::vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 5},
                                         {6, 3}, {7, 5}, {8, 7}};
  std::vector<std::vector<int>> queries = {
      {2, 6, 8}, {2, 3, 6}, {1, 3, 4}, {2, 7, 1}, {1, 5, 3},
      {1, 7, 8}, {2, 6, 4}, {2, 7, 8}, {1, 1, 4}, {1, 2, 7}};
  std::vector<int> expected_result = {34, 8, 16, 14, 10};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest3 passed!\n";
}


int main() {
  test_1();
  test_2();
  test_3();
  return 0;
}
