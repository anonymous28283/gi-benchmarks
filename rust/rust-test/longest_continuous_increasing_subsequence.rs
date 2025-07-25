use std::cmp::Ordering;















pub fn longest_continuous_increasing_subsequence<T: Ord>(arr: &[T]) -> &[T] {
    if arr.len() <= 1 {
        return arr;
    }

    let mut start = 0;
    let mut max_start = 0;
    let mut max_len = 1;
    let mut curr_len = 1;

    for i in 1..arr.len() {
        match arr[i - 1].cmp(&arr[i]) {


            Ordering::Less | Ordering::Equal => {
                curr_len += 1;
            }

            Ordering::Greater => {
                if curr_len > max_len {
                    max_len = curr_len;
                    max_start = start;
                }

                start = i;

                curr_len = 1;
            }
        }
    }


    if curr_len > max_len {
        max_len = curr_len;
        max_start = start;
    }

    &arr[max_start..max_start + max_len]
}

#[cfg(test)]
mod tests {
    use super::*;

    macro_rules! test_cases {
        ($($name:ident: $test_case:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (input, expected) = $test_case;
                    assert_eq!(longest_continuous_increasing_subsequence(input), expected);
                }
            )*
        };
    }

    test_cases! {
        empty_array: (&[] as &[isize], &[] as &[isize]),
        single_element: (&[1], &[1]),
        all_increasing: (&[1, 2, 3, 4, 5], &[1, 2, 3, 4, 5]),
        all_decreasing: (&[5, 4, 3, 2, 1], &[5]),
        with_equal_elements: (&[1, 2, 2, 3, 4, 2], &[1, 2, 2, 3, 4]),
        increasing_with_plateau: (&[1, 2, 2, 2, 3, 3, 4], &[1, 2, 2, 2, 3, 3, 4]),
        mixed_elements: (&[5, 4, 3, 4, 2, 1], &[3, 4]),
        alternating_increase_decrease: (&[1, 2, 1, 2, 1, 2], &[1, 2]),
        zigzag: (&[1, 3, 2, 4, 3, 5], &[1, 3]),
        single_negative_element: (&[-1], &[-1]),
        negative_and_positive_mixed: (&[-2, -1, 0, 1, 2, 3], &[-2, -1, 0, 1, 2, 3]),
        increasing_then_decreasing: (&[1, 2, 3, 4, 3, 2, 1], &[1, 2, 3, 4]),
        single_increasing_subsequence_later: (&[3, 2, 1, 1, 2, 3, 4], &[1, 1, 2, 3, 4]),
        longer_subsequence_at_start: (&[5, 6, 7, 8, 9, 2, 3, 4, 5], &[5, 6, 7, 8, 9]),
        longer_subsequence_at_end: (&[2, 3, 4, 10, 5, 6, 7, 8, 9], &[5, 6, 7, 8, 9]),
        longest_subsequence_at_start: (&[2, 3, 4, 5, 1, 0], &[2, 3, 4, 5]),
        longest_subsequence_at_end: (&[1, 7, 2, 3, 4, 5,], &[2, 3, 4, 5]),
        repeated_elements: (&[1, 1, 1, 1, 1], &[1, 1, 1, 1, 1]),
    }
}
