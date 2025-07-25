











pub fn kld_loss(actual: &[f64], predicted: &[f64]) -> f64 {

    let eps = 0.00001f64;
    let loss: f64 = actual
        .iter()
        .zip(predicted.iter())
        .map(|(&a, &p)| ((a + eps) * ((a + eps) / (p + eps)).ln()))
        .sum();
    loss
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_kld_loss() {
        let test_vector_actual = vec![1.346112, 1.337432, 1.246655];
        let test_vector = vec![1.033836, 1.082015, 1.117323];
        assert_eq!(
            kld_loss(&test_vector_actual, &test_vector),
            0.7752789394328498
        );
    }
}
