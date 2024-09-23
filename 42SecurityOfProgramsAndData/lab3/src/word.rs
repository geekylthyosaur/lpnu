use {
    crate::error::Error,
    num::{
        traits::{WrappingAdd, WrappingSub},
        Num, NumCast, PrimInt,
    },
    secrecy::Zeroize,
    std::{fmt::Debug, mem::size_of, ops::BitXor},
};

pub trait Word:
    Num + BitXor + WrappingAdd + WrappingSub + PrimInt + NumCast + Debug + Zeroize
where
    Self: Sized,
{
    /// This is the W parameter of the RC5 algorithm.
    const BITS: usize = size_of::<Self>() * 8;

    const P: Self; // Odd((e − 2)2^w)
    const Q: Self; // Odd((φ − 1)2^w)

    /// Converts a little endian byte slice to a word
    fn from_le_bytes(bytes: &[u8]) -> Result<Self, Error>;

    /// Converts a word to a little endian byte slice
    fn to_le_bytes(&self) -> Vec<u8>;
}

macro_rules! impl_word {
    ($typ:tt, $q:expr, $p:expr) => {
        impl Word for $typ {
            const P: $typ = $p;
            const Q: $typ = $q;

            fn from_le_bytes(bytes: &[u8]) -> Result<Self, Error> {
                if bytes.len() != size_of::<Self>() {
                    return Err(Error::InvalidBytes);
                }

                Ok($typ::from_le_bytes(
                    bytes.try_into().map_err(|_| Error::InvalidBytes)?,
                ))
            }

            fn to_le_bytes(&self) -> Vec<u8> {
                $typ::to_le_bytes(*self).to_vec()
            }
        }
    };
}

impl_word!(u16, 0x9E37, 0xB7E1);
impl_word!(u32, 0x9E3779B9, 0xB7E15163);
impl_word!(u64, 0x9E3779B97F4A7C15, 0xB7E151628AED2A6B);
impl_word!(
    u128,
    0x9E3779B97F4A7C15F39CC0605CEDC835,
    0xB7E151628AED2A6ABF7158809CF4F3C7
);
