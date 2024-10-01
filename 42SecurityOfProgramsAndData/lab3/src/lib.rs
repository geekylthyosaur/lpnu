use {
    crate::cipher::{encrypt_block, expand_key},
    cipher::decrypt_block,
    error::Error,
    secrecy::{ExposeSecret, SecretVec, Zeroize},
    std::mem::size_of,
    word::Word,
};

pub mod cipher;
pub mod error;
pub mod word;

pub struct Context<W: Word = u32> {
    expanded_key: SecretVec<W>,
}

impl<W: Word> Context<W> {
    pub fn new(mut key: Vec<u8>, rounds: usize) -> Result<Self, Error> {
        let expanded_key = expand_key::<W>(&key, rounds)?;
        key.zeroize();

        Ok(Self {
            expanded_key: SecretVec::new(expanded_key),
        })
    }

    pub fn encrypt(&self, plaintext: &[u8], iv: &[u8]) -> Result<Vec<u8>, Error> {
        let word_bytes = size_of::<W>();
        let block_size = 2 * word_bytes;

        if plaintext.len() % block_size != 0 {
            return Err(Error::InvalidInputLength);
        }

        let mut prev_block = [
            W::from_le_bytes(&iv[0..word_bytes])?,
            W::from_le_bytes(&iv[word_bytes..block_size])?,
        ];
        let mut ciphertext = Vec::with_capacity(plaintext.len());
        for block in plaintext.chunks(block_size) {
            let mut block = [
                W::from_le_bytes(&block[0..word_bytes])?,
                W::from_le_bytes(&block[word_bytes..block_size])?,
            ];

            block[0] = block[0].bitxor(prev_block[0]);
            block[1] = block[1].bitxor(prev_block[1]);

            let encrypted_block = encrypt_block::<W>(self.expanded_key.expose_secret(), block)?;

            ciphertext.extend(encrypted_block.iter().flat_map(|w| w.to_le_bytes()));

            prev_block = encrypted_block;
        }

        Ok(ciphertext)
    }

    pub fn decrypt(&self, ciphertext: &[u8], iv: &[u8]) -> Result<Vec<u8>, Error> {
        let word_bytes = size_of::<W>();
        let block_size = 2 * word_bytes;

        if ciphertext.len() % block_size != 0 {
            return Err(Error::InvalidInputLength);
        }

        let mut prev_block = [
            W::from_le_bytes(&iv[0..word_bytes])?,
            W::from_le_bytes(&iv[word_bytes..block_size])?,
        ];
        let mut plaintext = Vec::with_capacity(ciphertext.len());
        for block in ciphertext.chunks(block_size) {
            let block = [
                W::from_le_bytes(&block[0..word_bytes])?,
                W::from_le_bytes(&block[word_bytes..block_size])?,
            ];

            plaintext.extend(
                decrypt_block::<W>(self.expanded_key.expose_secret(), block)?
                    .into_iter()
                    .enumerate()
                    .flat_map(|(i, mut w)| {
                        w = w.bitxor(prev_block[i]);
                        prev_block[i] = block[i];
                        w.to_le_bytes()
                    }),
            );
        }

        Ok(plaintext)
    }
}

pub fn encrypt<W: Word>(
    key: &[u8],
    plaintext: &[u8],
    rounds: usize,
    iv_seed: usize,
) -> Result<Vec<u8>, Error> {
    let rng = random::Random::new((u32::MAX - 1) as usize, 16807, 17711, iv_seed);
    let iv = rng
        .skip(10)
        .take(2)
        .flat_map(|n| n.to_le_bytes())
        .collect::<Vec<_>>();
    Context::<W>::new(key.to_vec(), rounds)?.encrypt(&plaintext, &iv)
}

pub fn decrypt<W: Word>(
    key: &[u8],
    ciphertext: &[u8],
    rounds: usize,
    iv_seed: usize,
) -> Result<Vec<u8>, Error> {
    let rng = random::Random::new((u32::MAX - 1) as usize, 16807, 17711, iv_seed);
    let iv = rng
        .skip(10)
        .take(2)
        .flat_map(|n| n.to_le_bytes())
        .collect::<Vec<_>>();
    Context::<W>::new(key.to_vec(), rounds)?.decrypt(ciphertext, &iv)
}
