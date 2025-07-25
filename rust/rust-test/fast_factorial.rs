


use crate::math::sieve_of_eratosthenes;
use num_bigint::BigUint;
use num_traits::One;
use std::collections::BTreeMap;


fn index(p: usize, n: usize) -> usize {
    let mut index = 0;
    let mut i = 1;
    let mut quot = n / p;

    while quot > 0 {
        index += quot;
        i += 1;
        quot = n / p.pow(i);
    }

    index
}


pub fn fast_factorial(n: usize) -> BigUint {
    if n < 2 {
        return BigUint::one();
    }


    let primes = sieve_of_eratosthenes(n);


    let p_indices = primes
        .into_iter()
        .map(|p| (p, index(p, n)))
        .collect::<BTreeMap<_, _>>();

    let max_bits = p_indices[&2].next_power_of_two().ilog2() + 1;


    let mut a = vec![BigUint::one(); max_bits as usize];


    for (p, i) in p_indices {
        let mut bit = 1usize;
        while bit.ilog2() < max_bits {
            if (bit & i) > 0 {
                a[bit.ilog2() as usize] *= p;
            }

            bit <<= 1;
        }
    }

    a.into_iter()
        .enumerate()
        .map(|(i, a_i)| a_i.pow(2u32.pow(i as u32)))
        .product()
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::math::factorial::factorial_bigmath;

    #[test]
    fn fact() {
        assert_eq!(fast_factorial(0), BigUint::one());
        assert_eq!(fast_factorial(1), BigUint::one());
        assert_eq!(fast_factorial(2), factorial_bigmath(2));
        assert_eq!(fast_factorial(3), factorial_bigmath(3));
        assert_eq!(fast_factorial(6), factorial_bigmath(6));
        assert_eq!(fast_factorial(7), factorial_bigmath(7));
        assert_eq!(fast_factorial(10), factorial_bigmath(10));
        assert_eq!(fast_factorial(11), factorial_bigmath(11));
        assert_eq!(fast_factorial(18), factorial_bigmath(18));
        assert_eq!(fast_factorial(19), factorial_bigmath(19));
        assert_eq!(fast_factorial(30), factorial_bigmath(30));
        assert_eq!(fast_factorial(34), factorial_bigmath(34));
        assert_eq!(fast_factorial(35), factorial_bigmath(35));
        assert_eq!(fast_factorial(52), factorial_bigmath(52));
        assert_eq!(fast_factorial(100), factorial_bigmath(100));
        assert_eq!(fast_factorial(1000), factorial_bigmath(1000));
        assert_eq!(fast_factorial(5000), factorial_bigmath(5000));
    }
}
