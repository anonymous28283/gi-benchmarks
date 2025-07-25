






pub fn wiggle_sort(nums: &mut Vec<i32>) -> &mut Vec<i32> {









    let len = nums.len();
    for i in 1..len {
        let num_x = nums[i - 1];
        let num_y = nums[i];
        if (i % 2 == 1) == (num_x > num_y) {
            nums[i - 1] = num_y;
            nums[i] = num_x;
        }
    }
    nums
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::sorting::have_same_elements;

    fn is_wiggle_sorted(nums: &[i32]) -> bool {
        if nums.is_empty() {
            return true;
        }
        let mut previous = nums[0];
        let mut result = true;
        nums.iter().enumerate().skip(1).for_each(|(i, &item)| {
            if i != 0 {
                result =
                    result && ((i % 2 == 1 && previous < item) || (i % 2 == 0 && previous > item));
            }

            previous = item;
        });
        result
    }

    #[test]
    fn wingle_elements() {
        let arr = vec![3, 5, 2, 1, 6, 4];
        let mut cloned = arr.clone();
        let res = wiggle_sort(&mut cloned);
        assert!(is_wiggle_sorted(res));
        assert!(have_same_elements(res, &arr));
    }

    #[test]
    fn odd_number_of_elements() {
        let arr = vec![4, 1, 3, 5, 2];
        let mut cloned = arr.clone();
        let res = wiggle_sort(&mut cloned);
        assert!(is_wiggle_sorted(res));
        assert!(have_same_elements(res, &arr));
    }

    #[test]
    fn repeated_elements() {
        let arr = vec![5, 5, 5, 5];
        let mut cloned = arr.clone();
        let res = wiggle_sort(&mut cloned);


        assert!(!is_wiggle_sorted(res));
        assert!(have_same_elements(res, &arr));
    }
}
