








pub fn reverse(text: &str) -> String {
    text.chars().rev().collect()
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
                    assert_eq!(reverse(input), expected);
                }
            )*
        };
    }

    test_cases! {
        test_simple_palindrome: ("racecar", "racecar"),
        test_non_palindrome: ("abcdef", "fedcba"),
        test_sentence_with_spaces: ("step on no pets", "step on no pets"),
        test_empty_string: ("", ""),
        test_single_character: ("a", "a"),
        test_leading_trailing_spaces: ("  hello  ", "  olleh  "),
        test_unicode_characters: ("你好", "好你"),
        test_mixed_content: ("a1b2c3!", "!3c2b1a"),
    }
}
