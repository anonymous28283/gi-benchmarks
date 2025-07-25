



















pub fn neg_log_likelihood(
    y_true: &[f64],
    y_pred: &[f64],
) -> Result<f64, NegativeLogLikelihoodLossError> {

    if y_true.len() != y_pred.len() {
        return Err(NegativeLogLikelihoodLossError::InputsHaveDifferentLength);
    }

    if y_pred.is_empty() {
        return Err(NegativeLogLikelihoodLossError::EmptyInputs);
    }

    if !are_all_values_in_range(y_true) || !are_all_values_in_range(y_pred) {
        return Err(NegativeLogLikelihoodLossError::InvalidValues);
    }

    let mut total_loss: f64 = 0.0;
    for (p, a) in y_pred.iter().zip(y_true.iter()) {
        let loss: f64 = -a * p.ln() - (1.0 - a) * (1.0 - p).ln();
        total_loss += loss;
    }
    Ok(total_loss / (y_pred.len() as f64))
}

#[derive(Debug, PartialEq, Eq)]
pub enum NegativeLogLikelihoodLossError {
    InputsHaveDifferentLength,
    EmptyInputs,
    InvalidValues,
}

fn are_all_values_in_range(values: &[f64]) -> bool {
    values.iter().all(|&x| (0.0..=1.0).contains(&x))
}

#[cfg(test)]
mod tests {
    use super::*;

    macro_rules! test_with_wrong_inputs {
        ($($name:ident: $inputs:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (values_a, values_b, expected_error) = $inputs;
                    assert_eq!(neg_log_likelihood(&values_a, &values_b), expected_error);
                    assert_eq!(neg_log_likelihood(&values_b, &values_a), expected_error);
                }
            )*
        }
    }

    test_with_wrong_inputs! {
        different_length: (vec![0.9, 0.0, 0.8], vec![0.9, 0.1], Err(NegativeLogLikelihoodLossError::InputsHaveDifferentLength)),
        different_length_one_empty: (vec![], vec![0.9, 0.1], Err(NegativeLogLikelihoodLossError::InputsHaveDifferentLength)),
        value_greater_than_1: (vec![1.1, 0.0, 0.8], vec![0.1, 0.2, 0.3], Err(NegativeLogLikelihoodLossError::InvalidValues)),
        value_greater_smaller_than_0: (vec![0.9, 0.0, -0.1], vec![0.1, 0.2, 0.3], Err(NegativeLogLikelihoodLossError::InvalidValues)),
        empty_input: (vec![], vec![], Err(NegativeLogLikelihoodLossError::EmptyInputs)),
    }

    macro_rules! test_neg_log_likelihood {
        ($($name:ident: $inputs:expr,)*) => {
            $(
                #[test]
                fn $name() {
                    let (actual_values, predicted_values, expected) = $inputs;
                    assert_eq!(neg_log_likelihood(&actual_values, &predicted_values).unwrap(), expected);
                }
            )*
        }
    }

    test_neg_log_likelihood! {
        set_0: (vec![1.0, 0.0, 1.0], vec![0.9, 0.1, 0.8], 0.14462152754328741),
        set_1: (vec![1.0, 0.0, 1.0], vec![0.1, 0.2, 0.3], 1.2432338162113972),
        set_2: (vec![0.0, 1.0, 0.0], vec![0.1, 0.2, 0.3], 0.6904911240102196),
        set_3: (vec![1.0, 0.0, 1.0, 0.0], vec![0.9, 0.1, 0.8, 0.2], 0.164252033486018),
    }
}
