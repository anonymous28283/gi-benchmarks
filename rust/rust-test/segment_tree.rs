



use std::fmt::Debug;
use std::ops::Range;


#[derive(Debug, PartialEq, Eq)]
pub enum SegmentTreeError {

    IndexOutOfBounds,

    InvalidRange,
}



pub struct SegmentTree<T, F>
where
    T: Debug + Default + Ord + Copy,
    F: Fn(T, T) -> T,
{

    size: usize,

    nodes: Vec<T>,

    merge_fn: F,
}

impl<T, F> SegmentTree<T, F>
where
    T: Debug + Default + Ord + Copy,
    F: Fn(T, T) -> T,
{










    pub fn from_vec(arr: &[T], merge: F) -> Self {
        let size = arr.len();
        let mut buffer: Vec<T> = vec![T::default(); 2 * size];


        buffer[size..(2 * size)].clone_from_slice(arr);
        for idx in (1..size).rev() {
            buffer[idx] = merge(buffer[2 * idx], buffer[2 * idx + 1]);
        }

        SegmentTree {
            size,
            nodes: buffer,
            merge_fn: merge,
        }
    }













    pub fn query(&self, range: Range<usize>) -> Result<Option<T>, SegmentTreeError> {
        if range.start >= self.size || range.end > self.size {
            return Err(SegmentTreeError::InvalidRange);
        }

        let mut left = range.start + self.size;
        let mut right = range.end + self.size;
        let mut result = None;


        while left < right {
            if left % 2 == 1 {
                result = Some(match result {
                    None => self.nodes[left],
                    Some(old) => (self.merge_fn)(old, self.nodes[left]),
                });
                left += 1;
            }
            if right % 2 == 1 {
                right -= 1;
                result = Some(match result {
                    None => self.nodes[right],
                    Some(old) => (self.merge_fn)(old, self.nodes[right]),
                });
            }
            left /= 2;
            right /= 2;
        }

        Ok(result)
    }












    pub fn update(&mut self, idx: usize, val: T) -> Result<(), SegmentTreeError> {
        if idx >= self.size {
            return Err(SegmentTreeError::IndexOutOfBounds);
        }

        let mut index = idx + self.size;
        if self.nodes[index] == val {
            return Ok(());
        }

        self.nodes[index] = val;
        while index > 1 {
            index /= 2;
            self.nodes[index] = (self.merge_fn)(self.nodes[2 * index], self.nodes[2 * index + 1]);
        }

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::cmp::{max, min};

    #[test]
    fn test_min_segments() {
        let vec = vec![-30, 2, -4, 7, 3, -5, 6, 11, -20, 9, 14, 15, 5, 2, -8];
        let mut min_seg_tree = SegmentTree::from_vec(&vec, min);
        assert_eq!(min_seg_tree.query(4..7), Ok(Some(-5)));
        assert_eq!(min_seg_tree.query(0..vec.len()), Ok(Some(-30)));
        assert_eq!(min_seg_tree.query(0..2), Ok(Some(-30)));
        assert_eq!(min_seg_tree.query(1..3), Ok(Some(-4)));
        assert_eq!(min_seg_tree.query(1..7), Ok(Some(-5)));
        assert_eq!(min_seg_tree.update(5, 10), Ok(()));
        assert_eq!(min_seg_tree.update(14, -8), Ok(()));
        assert_eq!(min_seg_tree.query(4..7), Ok(Some(3)));
        assert_eq!(
            min_seg_tree.update(15, 100),
            Err(SegmentTreeError::IndexOutOfBounds)
        );
        assert_eq!(min_seg_tree.query(5..5), Ok(None));
        assert_eq!(
            min_seg_tree.query(10..16),
            Err(SegmentTreeError::InvalidRange)
        );
        assert_eq!(
            min_seg_tree.query(15..20),
            Err(SegmentTreeError::InvalidRange)
        );
    }

    #[test]
    fn test_max_segments() {
        let vec = vec![1, 2, -4, 7, 3, -5, 6, 11, -20, 9, 14, 15, 5, 2, -8];
        let mut max_seg_tree = SegmentTree::from_vec(&vec, max);
        assert_eq!(max_seg_tree.query(0..vec.len()), Ok(Some(15)));
        assert_eq!(max_seg_tree.query(3..5), Ok(Some(7)));
        assert_eq!(max_seg_tree.query(4..8), Ok(Some(11)));
        assert_eq!(max_seg_tree.query(8..10), Ok(Some(9)));
        assert_eq!(max_seg_tree.query(9..12), Ok(Some(15)));
        assert_eq!(max_seg_tree.update(4, 10), Ok(()));
        assert_eq!(max_seg_tree.update(14, -8), Ok(()));
        assert_eq!(max_seg_tree.query(3..5), Ok(Some(10)));
        assert_eq!(
            max_seg_tree.update(15, 100),
            Err(SegmentTreeError::IndexOutOfBounds)
        );
        assert_eq!(max_seg_tree.query(5..5), Ok(None));
        assert_eq!(
            max_seg_tree.query(10..16),
            Err(SegmentTreeError::InvalidRange)
        );
        assert_eq!(
            max_seg_tree.query(15..20),
            Err(SegmentTreeError::InvalidRange)
        );
    }

    #[test]
    fn test_sum_segments() {
        let vec = vec![1, 2, -4, 7, 3, -5, 6, 11, -20, 9, 14, 15, 5, 2, -8];
        let mut sum_seg_tree = SegmentTree::from_vec(&vec, |a, b| a + b);
        assert_eq!(sum_seg_tree.query(0..vec.len()), Ok(Some(38)));
        assert_eq!(sum_seg_tree.query(1..4), Ok(Some(5)));
        assert_eq!(sum_seg_tree.query(4..7), Ok(Some(4)));
        assert_eq!(sum_seg_tree.query(6..9), Ok(Some(-3)));
        assert_eq!(sum_seg_tree.query(9..vec.len()), Ok(Some(37)));
        assert_eq!(sum_seg_tree.update(5, 10), Ok(()));
        assert_eq!(sum_seg_tree.update(14, -8), Ok(()));
        assert_eq!(sum_seg_tree.query(4..7), Ok(Some(19)));
        assert_eq!(
            sum_seg_tree.update(15, 100),
            Err(SegmentTreeError::IndexOutOfBounds)
        );
        assert_eq!(sum_seg_tree.query(5..5), Ok(None));
        assert_eq!(
            sum_seg_tree.query(10..16),
            Err(SegmentTreeError::InvalidRange)
        );
        assert_eq!(
            sum_seg_tree.query(15..20),
            Err(SegmentTreeError::InvalidRange)
        );
    }
}
