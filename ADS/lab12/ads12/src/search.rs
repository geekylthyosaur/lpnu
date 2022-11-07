use std::str::from_utf8;

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
        println!("D(P,i) = {:?}", arr);
        arr
    }

    fn first_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize>;
}

impl<H: AsRef<[u8]>> Haystack for H {
    fn first_indexof_needle<N: AsRef<[u8]>>(&self, needle: N) -> Option<usize> {
        let needle = needle.as_ref();
        let pattern_table = Self::pattern_table(needle);
        let haystack = &self.as_ref();

        if needle.is_empty() {
            return Some(0);
        }

        let mut s: usize = 0;
        let mut i: usize = 1;

        loop {
            if i - 1 >= needle.len() {
                println!("Found '{}': ..{}..", from_utf8(&needle).unwrap(), from_utf8(&haystack[s.checked_sub(3).unwrap_or(0)..usize::min(s+needle.len()+3, haystack.len())]).unwrap());
                return Some(s);
            }
            if s + i - 1 >= haystack.len() {
                println!("Not found");
                return None;
            }
            if needle[i - 1] == haystack[s + i - 1] {
                println!("{} == {}", needle[i - 1] as char, haystack[s + i - 1] as char);
                i += 1;
            } else {
                println!("{} != {}", needle[i - 1] as char, haystack[s + i - 1] as char);
                match pattern_table[i - 1] {
                    0 => {
                        println!("shift {}", std::cmp::max(1, i-1));
                        s += std::cmp::max(1, i-1);
                        i = 1;
                    }
                    prefix_len => {
                        println!("shift {}", i - prefix_len);
                        s += i - prefix_len;
                        i = prefix_len;
                    }
                }
            }
        }
    }
}
