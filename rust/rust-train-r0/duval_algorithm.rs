


















pub fn duval_algorithm(s: &str) -> Vec<String> {
    factorize_duval(&s.chars().collect::<Vec<char>>())
}











fn factorize_duval(s: &[char]) -> Vec<String> {
    let mut start = 0;
    let mut factors: Vec<String> = Vec::new();

    while start < s.len() {
        let mut end = start + 1;
        let mut repeat = start;

        while end < s.len() && s[repeat] <= s[end] {
            if s[repeat] < s[end] {
                repeat = start;
            } else {
                repeat += 1;
            }
            end += 1;
        }

        while start <= repeat {
            factors.push(s[start..start + end - repeat].iter().collect::<String>());
            start += end - repeat;
        }
    }

    factors
}

#[cfg(test)]
mod test {
    use super::*;

    macro_rules! test_duval_algorithm {
        ($($name:ident: $inputs:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (text, expected) = $inputs;
                    assert_eq!(duval_algorithm(text), expected);
                }
            )*
        }
    }

    test_duval_algorithm! {
        repeating_with_suffix: ("abcdabcdababc", ["abcd", "abcd", "ababc"]),
        single_repeating_char: ("aaa", ["a", "a", "a"]),
        single: ("ababb", ["ababb"]),
        unicode: ("അഅഅ", ["അ", "അ", "അ"]),
        empty_string: ("", Vec::<String>::new()),
        single_char: ("x", ["x"]),
        palindrome: ("racecar", ["r", "acecar"]),
        long_repeating: ("aaaaaa", ["a", "a", "a", "a", "a", "a"]),
        mixed_repeating: ("ababcbabc", ["ababcbabc"]),
        non_repeating_sorted: ("abcdefg", ["abcdefg"]),
        alternating_increasing: ("abababab", ["ab", "ab", "ab", "ab"]),
        long_repeating_lyndon: ("abcabcabcabc", ["abc", "abc", "abc", "abc"]),
        decreasing_order: ("zyxwvutsrqponm", ["z", "y", "x", "w", "v", "u", "t", "s", "r", "q", "p", "o", "n", "m"]),
        alphanumeric_mixed: ("a1b2c3a1", ["a", "1b2c3a", "1"]),
        special_characters: ("a@b#c$d", ["a", "@b", "#c$d"]),
        unicode_complex: ("αβγδ", ["αβγδ"]),
        long_string_performance: (&"a".repeat(1_000_000), vec!["a"; 1_000_000]),
        palindrome_repeating_prefix: ("abccba", ["abccb", "a"]),
        interrupted_lyndon: ("abcxabc", ["abcx", "abc"]),
    }
}
