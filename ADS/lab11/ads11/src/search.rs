pub trait Haystack {
    fn pattern_table(needle: &[u8]) -> Vec<usize> {
        let mut i = 0;
        let mut j = 1;
        let mut arr = vec![0; needle.len()];
        while j < needle.len() {
            if needle[i] == needle[j] {
                i += 1;
                arr[j] = i;
                j += 1;
            } else {
                if i != 0 {
                    i = arr[i - 1];
                } else {
                    arr[j] = i;
                    j += 1;
                }
            }
        }
        arr
    }

    fn contains_needle<N: AsRef<[u8]>>(&self, needle: N) -> bool;

    fn first_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize>;

    fn last_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize>;

    fn indexesof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<Vec<usize>>;
}

impl<H: AsRef<[u8]>> Haystack for H {
    fn contains_needle<N: AsRef<[u8]>>(&self, needle: N) -> bool {
        let needle = needle.as_ref();
        let pattern_table = Self::pattern_table(needle);
        let haystack = &self.as_ref();

        let mut haystack_c = 0usize;
        let mut needle_c = 0usize;

        let haystack_len = haystack.len();
        let needle_len = needle.len();

        while haystack_c < haystack_len {
            if haystack[haystack_c] == needle[needle_c] {
                haystack_c += 1;
                needle_c += 1;
            }
            if needle_c == needle_len {
                return true;
            } else {
                if haystack_c < haystack_len && haystack[haystack_c] != needle[needle_c] {
                    if needle_c != 0 {
                        needle_c = pattern_table[needle_c - 1];
                    } else {
                        haystack_c += 1;
                    }
                }
            }
        }
        false
    }

    fn first_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize> {
        let needle = needle.as_ref();
        let pattern_table = Self::pattern_table(needle);
        let haystack = &self.as_ref();

        let mut haystack_c = 0usize;
        let mut needle_c = 0usize;

        let haystack_len = haystack.len();
        let needle_len = needle.len();

        while haystack_c < haystack_len {
            if haystack[haystack_c] == needle[needle_c] {
                haystack_c += 1;
                needle_c += 1;
            }
            if needle_c == needle_len {
                return Some(haystack_c - needle_len);
            } else {
                if haystack_c < haystack_len && haystack[haystack_c] != needle[needle_c] {
                    if needle_c != 0 {
                        needle_c = pattern_table[needle_c - 1];
                    } else {
                        haystack_c += 1;
                    }
                }
            }
        }
        None
    }

    fn last_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize> {
        let needle = needle.as_ref();
        let pattern_table = Self::pattern_table(needle);
        let haystack = &self.as_ref();

        let mut haystack_c = 0usize;
        let mut needle_c = 0usize;

        let haystack_len = haystack.len();
        let needle_len = needle.len();

        let mut index: Option<usize> = None;

        while haystack_c < haystack_len {
            if haystack[haystack_c] == needle[needle_c] {
                haystack_c += 1;
                needle_c += 1;
            }
            if needle_c == needle_len {
                index = Some(haystack_c - needle_len);
                needle_c = 0;
            } else {
                if haystack_c < haystack_len && haystack[haystack_c] != needle[needle_c] {
                    if needle_c != 0 {
                        needle_c = pattern_table[needle_c - 1];
                    } else {
                        haystack_c += 1;
                    }
                }
            }
        }
        index
    }

    fn indexesof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<Vec<usize>> {
        let needle = needle.as_ref();
        let pattern_table = Self::pattern_table(needle);
        let haystack = &self.as_ref();

        let mut haystack_c = 0usize;
        let mut needle_c = 0usize;

        let haystack_len = haystack.len();
        let needle_len = needle.len();

        let mut indexes = Vec::new();

        while haystack_c < haystack_len {
            if haystack[haystack_c] == needle[needle_c] {
                haystack_c += 1;
                needle_c += 1;
            }
            if needle_c == needle_len {
                indexes.push(haystack_c - needle_len);
                needle_c = 0;
            } else {
                if haystack_c < haystack_len && haystack[haystack_c] != needle[needle_c] {
                    if needle_c != 0 {
                        needle_c = pattern_table[needle_c - 1];
                    } else {
                        haystack_c += 1;
                    }
                }
            }
        }
        if indexes.len() > 0 {
            Some(indexes)
        } else {
            None
        }
    }
}
