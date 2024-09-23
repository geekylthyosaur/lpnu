use {
    crate::{error::Error, word::Word},
    num::integer::div_ceil,
    std::{cmp::max, mem::size_of},
};

/// Block Encryption
///
/// We assume that the input block is given in two w-bit registers A and B. We
/// also assume that key-expansion has already been performed, so that the array
/// S[0...t−1] has been computed. Here is the encryption algorithm in
/// pseudo-code:
///
/// A = A + S[0];
/// B = B + S[1];
/// for i = 1 to r do
///   A = ((A ⊕ B) < B) + S[2 ∗ i];
///   B = ((B ⊕ A) < A) + S[2 ∗ i + 1];
/// end for
///
/// The output is in the registers A and B.
pub fn encrypt_block<W: Word>(
    expanded_key: &[W],
    mut block: [W; 2], // A and B
) -> Result<[W; 2], Error> {
    let num_rounds = (expanded_key.len() / 2) - 1;
    block[0] = block[0].wrapping_add(&expanded_key[0]);
    block[1] = block[1].wrapping_add(&expanded_key[1]);

    for i in 1..=num_rounds {
        let rotation = block[1].to_u128().ok_or(Error::InvalidWordSize)? % W::BITS as u128;
        block[0] = (block[0].bitxor(block[1]))
            .rotate_left(rotation as u32)
            .wrapping_add(&expanded_key[2 * i]);

        let rotation = block[0].to_u128().ok_or(Error::InvalidWordSize)? % W::BITS as u128;
        block[1] = (block[1].bitxor(block[0]))
            .rotate_left(rotation as u32)
            .wrapping_add(&expanded_key[2 * i + 1]);
    }

    Ok(block)
}

/// Block Decryption
///
/// The decryption routine is easily derived from the encryption routine.
/// for i=r downto 1 do
///   B = ((B − S[2 ∗ i + 1]) > A) ⊕ A;
///   A = ((A − S[2 ∗ i]) > B) ⊕ B;
///   
/// B = B − S[1];
/// A = A − S[0];
pub fn decrypt_block<W: Word>(expanded_key: &[W], mut block: [W; 2]) -> Result<[W; 2], Error> {
    let num_rounds = (expanded_key.len() / 2) - 1;

    for i in (1..=num_rounds).rev() {
        let rotation = block[0].to_u128().ok_or(Error::InvalidWordSize)? % W::BITS as u128;

        block[1] = (block[1].wrapping_sub(&expanded_key[2 * i + 1]))
            .rotate_right(rotation as u32)
            .bitxor(block[0]);

        let rotation = block[1].to_u128().ok_or(Error::InvalidWordSize)? % W::BITS as u128;
        block[0] = (block[0].wrapping_sub(&expanded_key[2 * i]))
            .rotate_right(rotation as u32)
            .bitxor(block[1]);
    }

    block[1] = block[1].wrapping_sub(&expanded_key[1]);
    block[0] = block[0].wrapping_sub(&expanded_key[0]);

    Ok(block)
}

/// Key expansion algorithm
pub fn expand_key<W: Word>(key: &[u8], rounds: usize) -> Result<Vec<W>, Error> {
    // limit described in the paper.
    const MAX_ROUNDS: usize = 256;
    const MAX_KEY_SIZE: usize = 256;

    if key.len() > MAX_KEY_SIZE {
        return Err(Error::InvalidKeySize);
    }

    if rounds > MAX_ROUNDS {
        return Err(Error::InvalidRoundsCount);
    }

    // 1. key bytes to words:
    let mut words: Vec<W> = key_to_words(key);

    // 2. Initialize the key-independent array S
    // S[0] = Pw;
    // for i = 1 to t − 1 do
    //  S[i] = S[i − 1] + Qw;
    let mut subkeys: Vec<W> = initialize_subkeys(rounds);

    // the main key scheduling loop
    // i = j = 0
    // A = B = 0
    // do 3 * max(t, c) times:
    //    A = S[i] = (S[i] + A + B) <<< 3
    //    B = L[j] = (L[j] + A + B) <<< (A + B)
    //    i = (i + 1) mod t
    //    j = (j + 1) mod c

    let mut i = 0;
    let mut j = 0;
    let mut a = W::zero();
    let mut b = W::zero();

    // 3 * max(t, c)
    let iters = max(subkeys.len(), words.len()) * 3;

    for _ in 0..iters {
        subkeys[i] = subkeys[i].wrapping_add(&a).wrapping_add(&b).rotate_left(3);
        a = subkeys[i];

        // this could be larger than the word size, so we need to mod it
        let rotation =
            a.wrapping_add(&b).to_u128().ok_or(Error::InvalidWordSize)? % W::BITS as u128;

        words[j] = words[j]
            .wrapping_add(&a)
            .wrapping_add(&b)
            .rotate_left(rotation as u32);
        b = words[j];

        i = (i + 1) % subkeys.len();
        j = (j + 1) % words.len();
    }

    Ok(subkeys)
}

/// Pseudocode:
///
/// c = [max(b, 1) / u]
/// for i = b - 1 downto 0 do
///   L[i/u] = (L[i/u] <<< 8) + K[i]
fn key_to_words<W: Word>(key: &[u8]) -> Vec<W> {
    let words_len = div_ceil(max(key.len(), 1), size_of::<W>());
    let mut words = vec![W::zero(); words_len];
    for i in (0..key.len()).rev() {
        let word_index = i / size_of::<W>();
        let word = W::from(key[i]).expect("minimum word size is 8");
        words[word_index] = words[word_index].rotate_left(8).wrapping_add(&word);
    }
    words
}

/// Initialize the key-independent array S
/// S[0] = Pw;
/// for i = 1 to t − 1 do
///  S[i] = S[i − 1] + Qw;
fn initialize_subkeys<W: Word>(rounds: usize) -> Vec<W> {
    let subkey_count = 2 * (rounds + 1); // t
    let mut subkeys = vec![W::zero(); subkey_count];

    subkeys[0] = W::P;
    for i in 1..subkey_count {
        subkeys[i] = subkeys[i - 1].wrapping_add(&W::Q);
    }

    subkeys
}
