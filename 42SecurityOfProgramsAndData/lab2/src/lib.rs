use std::convert;
use std::fmt;
use std::ops;

use std::io;

#[derive(Clone, Copy, Eq, Hash, PartialEq)]
pub struct Digest(pub [u8; 16]);

impl convert::From<Digest> for [u8; 16] {
    #[inline]
    fn from(digest: Digest) -> Self {
        digest.0
    }
}

impl fmt::Debug for Digest {
    #[inline]
    fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
        fmt::LowerHex::fmt(self, formatter)
    }
}

impl ops::Deref for Digest {
    type Target = [u8; 16];

    #[inline]
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl ops::DerefMut for Digest {
    #[inline]
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.0
    }
}

macro_rules! implement {
    ($kind:ident, $format:expr) => {
        impl fmt::$kind for Digest {
            fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                for value in &self.0 {
                    write!(formatter, $format, value)?;
                }
                Ok(())
            }
        }
    };
}

implement!(LowerHex, "{:02x}");
implement!(UpperHex, "{:02X}");

#[derive(Clone)]
pub struct Context {
    buffer: [u8; 64],
    count: [u32; 2],
    state: [u32; 4],
}

const PADDING: [u8; 64] = [
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
];

impl Context {
    #[inline]
    pub fn new() -> Context {
        Context {
            buffer: [0; 64],
            count: [0, 0],
            state: [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476],
        }
    }

    #[cfg(target_pointer_width = "64")]
    pub fn consume<T: AsRef<[u8]>>(&mut self, data: T) {
        for chunk in data.as_ref().chunks(std::u32::MAX as usize) {
            consume(self, chunk);
        }
    }

    pub fn compute(mut self) -> Digest {
        let mut input = [0u32; 16];
        let k = ((self.count[0] >> 3) & 0x3f) as usize;
        input[14] = self.count[0];
        input[15] = self.count[1];
        consume(
            &mut self,
            &PADDING[..(if k < 56 { 56 - k } else { 120 - k })],
        );
        let mut j = 0;
        for i in 0..14 {
            input[i] = ((self.buffer[j + 3] as u32) << 24)
                | ((self.buffer[j + 2] as u32) << 16)
                | ((self.buffer[j + 1] as u32) << 8)
                | (self.buffer[j] as u32);
            j += 4;
        }
        transform(&mut self.state, &input);
        let mut digest = [0u8; 16];
        let mut j = 0;
        for i in 0..4 {
            digest[j] = ((self.state[i]) & 0xff) as u8;
            digest[j + 1] = ((self.state[i] >> 8) & 0xff) as u8;
            digest[j + 2] = ((self.state[i] >> 16) & 0xff) as u8;
            digest[j + 3] = ((self.state[i] >> 24) & 0xff) as u8;
            j += 4;
        }
        Digest(digest)
    }
}

impl convert::From<Context> for Digest {
    #[inline]
    fn from(context: Context) -> Digest {
        context.compute()
    }
}

impl io::Write for Context {
    #[inline]
    fn write(&mut self, data: &[u8]) -> io::Result<usize> {
        self.consume(data);
        Ok(data.len())
    }

    #[inline]
    fn flush(&mut self) -> io::Result<()> {
        Ok(())
    }
}

#[inline]
pub fn compute<T: AsRef<[u8]>>(data: T) -> Digest {
    let mut context = Context::new();
    context.consume(data);
    context.compute()
}

fn consume(
    Context {
        buffer,
        count,
        state,
    }: &mut Context,
    data: &[u8],
) {
    let mut input = [0u32; 16];
    let mut k = ((count[0] >> 3) & 0x3f) as usize;
    let length = data.len() as u32;
    count[0] = count[0].wrapping_add(length << 3);
    if count[0] < length << 3 {
        count[1] = count[1].wrapping_add(1);
    }
    count[1] = count[1].wrapping_add(length >> 29);
    for &value in data {
        buffer[k] = value;
        k += 1;
        if k == 0x40 {
            let mut j = 0;
            for i in 0..16 {
                input[i] = ((buffer[j + 3] as u32) << 24)
                    | ((buffer[j + 2] as u32) << 16)
                    | ((buffer[j + 1] as u32) << 8)
                    | (buffer[j] as u32);
                j += 4;
            }
            transform(state, &input);
            k = 0;
        }
    }
}

fn transform(state: &mut [u32; 4], input: &[u32; 16]) {
    let (mut a, mut b, mut c, mut d) = (state[0], state[1], state[2], state[3]);
    macro_rules! add(
        ($a:expr, $b:expr) => ($a.wrapping_add($b));
    );
    macro_rules! rotate(
        ($x:expr, $n:expr) => (($x << $n) | ($x >> (32 - $n)));
    );
    {
        macro_rules! F(
            ($x:expr, $y:expr, $z:expr) => (($x & $y) | (!$x & $z));
        );
        macro_rules! T(
            ($a:expr, $b:expr, $c:expr, $d:expr, $x:expr, $s:expr, $ac:expr) => ({
                $a = add!(add!(add!($a, F!($b, $c, $d)), $x), $ac);
                $a = rotate!($a, $s);
                $a = add!($a, $b);
            });
        );
        const S1: u32 = 7;
        const S2: u32 = 12;
        const S3: u32 = 17;
        const S4: u32 = 22;
        T!(a, b, c, d, input[0], S1, 3614090360);
        T!(d, a, b, c, input[1], S2, 3905402710);
        T!(c, d, a, b, input[2], S3, 606105819);
        T!(b, c, d, a, input[3], S4, 3250441966);
        T!(a, b, c, d, input[4], S1, 4118548399);
        T!(d, a, b, c, input[5], S2, 1200080426);
        T!(c, d, a, b, input[6], S3, 2821735955);
        T!(b, c, d, a, input[7], S4, 4249261313);
        T!(a, b, c, d, input[8], S1, 1770035416);
        T!(d, a, b, c, input[9], S2, 2336552879);
        T!(c, d, a, b, input[10], S3, 4294925233);
        T!(b, c, d, a, input[11], S4, 2304563134);
        T!(a, b, c, d, input[12], S1, 1804603682);
        T!(d, a, b, c, input[13], S2, 4254626195);
        T!(c, d, a, b, input[14], S3, 2792965006);
        T!(b, c, d, a, input[15], S4, 1236535329);
    }
    {
        macro_rules! F(
            ($x:expr, $y:expr, $z:expr) => (($x & $z) | ($y & !$z));
        );
        macro_rules! T(
            ($a:expr, $b:expr, $c:expr, $d:expr, $x:expr, $s:expr, $ac:expr) => ({
                $a = add!(add!(add!($a, F!($b, $c, $d)), $x), $ac);
                $a = rotate!($a, $s);
                $a = add!($a, $b);
            });
        );
        const S1: u32 = 5;
        const S2: u32 = 9;
        const S3: u32 = 14;
        const S4: u32 = 20;
        T!(a, b, c, d, input[1], S1, 4129170786);
        T!(d, a, b, c, input[6], S2, 3225465664);
        T!(c, d, a, b, input[11], S3, 643717713);
        T!(b, c, d, a, input[0], S4, 3921069994);
        T!(a, b, c, d, input[5], S1, 3593408605);
        T!(d, a, b, c, input[10], S2, 38016083);
        T!(c, d, a, b, input[15], S3, 3634488961);
        T!(b, c, d, a, input[4], S4, 3889429448);
        T!(a, b, c, d, input[9], S1, 568446438);
        T!(d, a, b, c, input[14], S2, 3275163606);
        T!(c, d, a, b, input[3], S3, 4107603335);
        T!(b, c, d, a, input[8], S4, 1163531501);
        T!(a, b, c, d, input[13], S1, 2850285829);
        T!(d, a, b, c, input[2], S2, 4243563512);
        T!(c, d, a, b, input[7], S3, 1735328473);
        T!(b, c, d, a, input[12], S4, 2368359562);
    }
    {
        macro_rules! F(
            ($x:expr, $y:expr, $z:expr) => ($x ^ $y ^ $z);
        );
        macro_rules! T(
            ($a:expr, $b:expr, $c:expr, $d:expr, $x:expr, $s:expr, $ac:expr) => ({
                $a = add!(add!(add!($a, F!($b, $c, $d)), $x), $ac);
                $a = rotate!($a, $s);
                $a = add!($a, $b);
            });
        );
        const S1: u32 = 4;
        const S2: u32 = 11;
        const S3: u32 = 16;
        const S4: u32 = 23;
        T!(a, b, c, d, input[5], S1, 4294588738);
        T!(d, a, b, c, input[8], S2, 2272392833);
        T!(c, d, a, b, input[11], S3, 1839030562);
        T!(b, c, d, a, input[14], S4, 4259657740);
        T!(a, b, c, d, input[1], S1, 2763975236);
        T!(d, a, b, c, input[4], S2, 1272893353);
        T!(c, d, a, b, input[7], S3, 4139469664);
        T!(b, c, d, a, input[10], S4, 3200236656);
        T!(a, b, c, d, input[13], S1, 681279174);
        T!(d, a, b, c, input[0], S2, 3936430074);
        T!(c, d, a, b, input[3], S3, 3572445317);
        T!(b, c, d, a, input[6], S4, 76029189);
        T!(a, b, c, d, input[9], S1, 3654602809);
        T!(d, a, b, c, input[12], S2, 3873151461);
        T!(c, d, a, b, input[15], S3, 530742520);
        T!(b, c, d, a, input[2], S4, 3299628645);
    }
    {
        macro_rules! F(
            ($x:expr, $y:expr, $z:expr) => ($y ^ ($x | !$z));
        );
        macro_rules! T(
            ($a:expr, $b:expr, $c:expr, $d:expr, $x:expr, $s:expr, $ac:expr) => ({
                $a = add!(add!(add!($a, F!($b, $c, $d)), $x), $ac);
                $a = rotate!($a, $s);
                $a = add!($a, $b);
            });
        );
        const S1: u32 = 6;
        const S2: u32 = 10;
        const S3: u32 = 15;
        const S4: u32 = 21;
        T!(a, b, c, d, input[0], S1, 4096336452);
        T!(d, a, b, c, input[7], S2, 1126891415);
        T!(c, d, a, b, input[14], S3, 2878612391);
        T!(b, c, d, a, input[5], S4, 4237533241);
        T!(a, b, c, d, input[12], S1, 1700485571);
        T!(d, a, b, c, input[3], S2, 2399980690);
        T!(c, d, a, b, input[10], S3, 4293915773);
        T!(b, c, d, a, input[1], S4, 2240044497);
        T!(a, b, c, d, input[8], S1, 1873313359);
        T!(d, a, b, c, input[15], S2, 4264355552);
        T!(c, d, a, b, input[6], S3, 2734768916);
        T!(b, c, d, a, input[13], S4, 1309151649);
        T!(a, b, c, d, input[4], S1, 4149444226);
        T!(d, a, b, c, input[11], S2, 3174756917);
        T!(c, d, a, b, input[2], S3, 718787259);
        T!(b, c, d, a, input[9], S4, 3951481745);
    }
    state[0] = add!(state[0], a);
    state[1] = add!(state[1], b);
    state[2] = add!(state[2], c);
    state[3] = add!(state[3], d);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let input = "";
        let output = "D41D8CD98F00B204E9800998ECF8427E";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "a";
        let output = "0CC175B9C0F1B6A831C399E269772661";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "abc";
        let output = "900150983CD24FB0D6963F7D28E17F72";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "message digest";
        let output = "F96B697D7CB7938D525A2F31AAF161D0";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "abcdefghijklmnopqrstuvwxyz";
        let output = "C3FCD3D76192E4007DFB496CCA67E13B";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        let output = "D174AB98D277D9F5A5611C2C9F419D9F";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input = "abcdefghijklmnopqrstuvwxyz";
        let output = "C3FCD3D76192E4007DFB496CCA67E13B";
        assert_eq!(format!("{:X}", compute(input)), output);

        let input =
            "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
        let output = "57EDF4A22BE3C955AC49DA2E2107B67A";
        assert_eq!(format!("{:X}", compute(input)), output);
    }
}
