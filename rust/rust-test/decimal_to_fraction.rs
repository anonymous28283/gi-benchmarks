pub fn decimal_to_fraction(decimal: f64) -> (i64, i64) {

    let fractional_part = decimal - decimal.floor();


    if fractional_part == 0.0 {
        (decimal as i64, 1)
    } else {

        let number_of_frac_digits = decimal.to_string().split('.').nth(1).unwrap_or("").len();


        let numerator = (decimal * 10f64.powi(number_of_frac_digits as i32)) as i64;
        let denominator = 10i64.pow(number_of_frac_digits as u32);


        let mut divisor = denominator;
        let mut dividend = numerator;
        while divisor != 0 {
            let r = dividend % divisor;
            dividend = divisor;
            divisor = r;
        }


        let gcd = dividend.abs();
        let numerator = numerator / gcd;
        let denominator = denominator / gcd;

        (numerator, denominator)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_decimal_to_fraction_1() {
        assert_eq!(decimal_to_fraction(2.0), (2, 1));
    }

    #[test]
    fn test_decimal_to_fraction_2() {
        assert_eq!(decimal_to_fraction(89.45), (1789, 20));
    }

    #[test]
    fn test_decimal_to_fraction_3() {
        assert_eq!(decimal_to_fraction(67.), (67, 1));
    }

    #[test]
    fn test_decimal_to_fraction_4() {
        assert_eq!(decimal_to_fraction(45.2), (226, 5));
    }

    #[test]
    fn test_decimal_to_fraction_5() {
        assert_eq!(decimal_to_fraction(1.5), (3, 2));
    }

    #[test]
    fn test_decimal_to_fraction_6() {
        assert_eq!(decimal_to_fraction(6.25), (25, 4));
    }
}
