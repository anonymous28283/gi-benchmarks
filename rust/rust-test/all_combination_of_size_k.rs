



#[derive(Debug, PartialEq)]
pub enum CombinationError {
    KGreaterThanN,
    InvalidZeroRange,
}












pub fn generate_all_combinations(n: usize, k: usize) -> Result<Vec<Vec<usize>>, CombinationError> {
    if n == 0 && k > 0 {
        return Err(CombinationError::InvalidZeroRange);
    }

    if k > n {
        return Err(CombinationError::KGreaterThanN);
    }

    let mut combinations = vec![];
    let mut current = vec![0; k];
    backtrack(0, n, k, 0, &mut current, &mut combinations);
    Ok(combinations)
}











fn backtrack(
    start: usize,
    n: usize,
    k: usize,
    index: usize,
    current: &mut Vec<usize>,
    combinations: &mut Vec<Vec<usize>>,
) {
    if index == k {
        combinations.push(current.clone());
        return;
    }

    for num in start..=(n - k + index) {
        current[index] = num;
        backtrack(num + 1, n, k, index + 1, current, combinations);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    macro_rules! combination_tests {
        ($($name:ident: $test_case:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (n, k, expected) = $test_case;
                    assert_eq!(generate_all_combinations(n, k), expected);
                }
            )*
        }
    }

    combination_tests! {
        test_generate_4_2: (4, 2, Ok(vec![
            vec![0, 1],
            vec![0, 2],
            vec![0, 3],
            vec![1, 2],
            vec![1, 3],
            vec![2, 3],
        ])),
        test_generate_4_3: (4, 3, Ok(vec![
            vec![0, 1, 2],
            vec![0, 1, 3],
            vec![0, 2, 3],
            vec![1, 2, 3],
        ])),
        test_generate_5_3: (5, 3, Ok(vec![
            vec![0, 1, 2],
            vec![0, 1, 3],
            vec![0, 1, 4],
            vec![0, 2, 3],
            vec![0, 2, 4],
            vec![0, 3, 4],
            vec![1, 2, 3],
            vec![1, 2, 4],
            vec![1, 3, 4],
            vec![2, 3, 4],
        ])),
        test_generate_5_1: (5, 1, Ok(vec![
            vec![0],
            vec![1],
            vec![2],
            vec![3],
            vec![4],
        ])),
        test_empty: (0, 0, Ok(vec![vec![]])),
        test_generate_n_eq_k: (3, 3, Ok(vec![
            vec![0, 1, 2],
        ])),
        test_generate_k_greater_than_n: (3, 4, Err(CombinationError::KGreaterThanN)),
        test_zero_range_with_nonzero_k: (0, 1, Err(CombinationError::InvalidZeroRange)),
    }
}
