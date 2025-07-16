

type Adj = [Vec<usize>];

pub struct HeavyLightDecomposition {



    pub position: Vec<usize>,


    pub head: Vec<usize>,



    pub big_child: Vec<usize>,


    current_position: usize,
}

impl HeavyLightDecomposition {
    pub fn new(mut num_vertices: usize) -> Self {
        num_vertices += 1;
        HeavyLightDecomposition {
            position: vec![0; num_vertices],
            head: vec![0; num_vertices],
            big_child: vec![0; num_vertices],
            current_position: 1,
        }
    }
    fn dfs(&mut self, v: usize, parent: usize, adj: &Adj) -> usize {
        let mut big_child = 0usize;
        let mut bc_size = 0usize;
        let mut subtree_size = 1usize;
        for &u in adj[v].iter() {
            if u == parent {
                continue;
            }
            let u_size = self.dfs(u, v, adj);
            subtree_size += u_size;
            if u_size > bc_size {
                big_child = u;
                bc_size = u_size;
            }
        }
        self.big_child[v] = big_child;
        subtree_size
    }
    pub fn decompose(&mut self, root: usize, adj: &Adj) {
        self.current_position = 1;
        self.dfs(root, 0, adj);
        self.decompose_path(root, 0, root, adj);
    }
    fn decompose_path(&mut self, v: usize, parent: usize, head: usize, adj: &Adj) {
        self.head[v] = head;
        self.position[v] = self.current_position;
        self.current_position += 1;
        let bc = self.big_child[v];
        if bc != 0 {

            self.decompose_path(bc, v, head, adj);
        }
        for &u in adj[v].iter() {
            if u == parent || u == bc {
                continue;
            }

            self.decompose_path(u, v, u, adj);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct LinearCongruenceGenerator {

        multiplier: u32,
        increment: u32,
        state: u32,
    }

    impl LinearCongruenceGenerator {
        fn new(multiplier: u32, increment: u32, state: u32) -> Self {
            Self {
                multiplier,
                increment,
                state,
            }
        }
        fn next(&mut self) -> u32 {
            self.state =
                (self.multiplier as u64 * self.state as u64 + self.increment as u64) as u32;
            self.state
        }
    }

    fn get_num_paths(
        hld: &HeavyLightDecomposition,
        mut v: usize,
        parent: &[usize],
    ) -> (usize, usize) {

        let mut ans = 0usize;
        let mut height = 0usize;
        let mut prev_head = 0usize;
        loop {
            height += 1;
            let head = hld.head[v];
            if head != prev_head {
                ans += 1;
                prev_head = head;
            }
            v = parent[v];
            if v == 0 {
                break;
            }
        }
        (ans, height)
    }

    #[test]
    fn single_path() {
        let mut adj = vec![vec![], vec![2], vec![3], vec![4], vec![5], vec![6], vec![]];
        let mut hld = HeavyLightDecomposition::new(6);
        hld.decompose(1, &adj);
        assert_eq!(hld.head, vec![0, 1, 1, 1, 1, 1, 1]);
        assert_eq!(hld.position, vec![0, 1, 2, 3, 4, 5, 6]);
        assert_eq!(hld.big_child, vec![0, 2, 3, 4, 5, 6, 0]);

        adj[3].push(2);
        adj[2].push(1);
        hld.decompose(3, &adj);
        assert_eq!(hld.head, vec![0, 2, 2, 3, 3, 3, 3]);
        assert_eq!(hld.position, vec![0, 6, 5, 1, 2, 3, 4]);
        assert_eq!(hld.big_child, vec![0, 0, 1, 4, 5, 6, 0]);
    }

    #[test]
    fn random_tree() {


        let n = 1e4 as usize;
        let threshold = 14;
        let mut adj: Vec<Vec<usize>> = vec![vec![]; n + 1];
        let mut parent: Vec<usize> = vec![0; n + 1];
        let mut hld = HeavyLightDecomposition::new(n);
        let mut lcg = LinearCongruenceGenerator::new(1103515245, 12345, 314);
        parent[2] = 1;
        adj[1].push(2);
        #[allow(clippy::needless_range_loop)]
        for i in 3..=n {


            let par_max = i - 1;
            let par_min = (10 * par_max + 1) / 11;

            let par = (lcg.next() as usize % (par_max - par_min + 1)) + par_min;
            adj[par].push(i);
            parent[i] = par;
        }

        let leaves: Vec<usize> = (1..=n)
            .rev()
            .filter(|&v| adj[v].is_empty())
            .take(100)
            .collect();
        hld.decompose(1, &adj);
        for l in leaves {
            let (p, _h) = get_num_paths(&hld, l, &parent);
            assert!(p <= threshold);
        }
    }
}
