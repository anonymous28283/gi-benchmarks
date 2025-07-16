


























pub fn longest_common_subsequence(first_seq: &str, second_seq: &str) -> String {
    let first_seq_chars = first_seq.chars().collect::<Vec<char>>();
    let second_seq_chars = second_seq.chars().collect::<Vec<char>>();

    let lcs_lengths = initialize_lcs_lengths(&first_seq_chars, &second_seq_chars);
    let lcs_chars = reconstruct_lcs(&first_seq_chars, &second_seq_chars, &lcs_lengths);

    lcs_chars.into_iter().collect()
}

fn initialize_lcs_lengths(first_seq_chars: &[char], second_seq_chars: &[char]) -> Vec<Vec<usize>> {
    let first_seq_len = first_seq_chars.len();
    let second_seq_len = second_seq_chars.len();

    let mut lcs_lengths = vec![vec![0; second_seq_len + 1]; first_seq_len + 1];


    (1..=first_seq_len).for_each(|i| {
        (1..=second_seq_len).for_each(|j| {
            lcs_lengths[i][j] = if first_seq_chars[i - 1] == second_seq_chars[j - 1] {
                lcs_lengths[i - 1][j - 1] + 1
            } else {
                lcs_lengths[i - 1][j].max(lcs_lengths[i][j - 1])
            };
        });
    });

    lcs_lengths
}

fn reconstruct_lcs(
    first_seq_chars: &[char],
    second_seq_chars: &[char],
    lcs_lengths: &[Vec<usize>],
) -> Vec<char> {
    let mut lcs_chars = Vec::new();
    let mut i = first_seq_chars.len();
    let mut j = second_seq_chars.len();
    while i > 0 && j > 0 {
        if first_seq_chars[i - 1] == second_seq_chars[j - 1] {
            lcs_chars.push(first_seq_chars[i - 1]);
            i -= 1;
            j -= 1;
        } else if lcs_lengths[i - 1][j] >= lcs_lengths[i][j - 1] {
            i -= 1;
        } else {
            j -= 1;
        }
    }

    lcs_chars.reverse();
    lcs_chars
}

#[cfg(test)]
mod tests {
    use super::*;

    macro_rules! longest_common_subsequence_tests {
        ($($name:ident: $test_case:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (first_seq, second_seq, expected_lcs) = $test_case;
                    assert_eq!(longest_common_subsequence(&first_seq, &second_seq), expected_lcs);
                }
            )*
        };
    }

    longest_common_subsequence_tests! {
        empty_case: ("", "", ""),
        one_empty: ("", "abcd", ""),
        identical_strings: ("abcd", "abcd", "abcd"),
        completely_different: ("abcd", "efgh", ""),
        single_character: ("a", "a", "a"),
        different_length: ("abcd", "abc", "abc"),
        special_characters: ("$#%&", "#@!%", "#%"),
        long_strings: ("abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh",
                      "bcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgha",
                      "bcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh"),
        unicode_characters: ("你好，世界", "再见，世界", "，世界"),
        spaces_and_punctuation_0: ("hello, world!", "world, hello!", "hello!"),
        spaces_and_punctuation_1: ("hello, world!", "world, hello!", "hello!"),
        random_case_1: ("abcdef", "xbcxxxe", "bce"),
        random_case_2: ("xyz", "abc", ""),
        random_case_3: ("abracadabra", "avadakedavra", "aaadara"),
    }
}
