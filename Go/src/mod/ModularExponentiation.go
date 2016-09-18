package mod

type Integer uint64

func Exponent(base, exponent, modulo Integer) Integer {
	var result Integer = 1
	base = base % modulo

	for exponent > 0 {

		if exponent&1 == 1 {
			result = (result * base) % modulo
		}

		exponent = exponent >> 1
		base = (base * base) % modulo
	}

	return result
}
