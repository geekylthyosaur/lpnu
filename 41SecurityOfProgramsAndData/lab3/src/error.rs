use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("Invalid key size")]
    InvalidKeySize,

    #[error("Invalid word size")]
    InvalidWordSize,

    #[error("Invalid bytes. Can't convert to a word.")]
    InvalidBytes,

    #[error(
        "Invalid plaintext or cyphertext length. Must be a multiple of the block \
     size"
    )]
    InvalidInputLength,

    #[error("Invalid number of rounds")]
    InvalidRoundsCount,
}
