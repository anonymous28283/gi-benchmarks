





pub fn bucket_sort(arr: &[usize]) -> Vec<usize> {
    if arr.is_empty() {
        return vec![];
    }

    let max = *arr.iter().max().unwrap();
    let len = arr.len();
    let mut buckets = vec![vec![]; len + 1];

    for x in arr {
        buckets[len * *x / max].push(*x);
    }

    for bucket in buckets.iter_mut() {
        super::insertion_sort(bucket);
    }

    let mut result = vec![];
    for bucket in buckets {
        for x in bucket {
            result.push(x);
        }
    }

    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::sorting::have_same_elements;
    use crate::sorting::is_sorted;

    #[test]
    fn empty() {
        let arr: [usize; 0] = [];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }

    #[test]
    fn one_element() {
        let arr: [usize; 1] = [4];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }

    #[test]
    fn already_sorted() {
        let arr: [usize; 3] = [10, 19, 105];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }

    #[test]
    fn basic() {
        let arr: [usize; 4] = [35, 53, 1, 0];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }

    #[test]
    fn odd_number_of_elements() {
        let arr: [usize; 5] = [1, 21, 5, 11, 58];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }

    #[test]
    fn repeated_elements() {
        let arr: [usize; 4] = [542, 542, 542, 542];
        let cloned = arr;
        let res = bucket_sort(&arr);
        assert!(is_sorted(&res) && have_same_elements(&res, &cloned));
    }
}
