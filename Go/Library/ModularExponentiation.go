package mod

type integer uint64

func Exponent(base, exponent, modulo integer) integer {
	var result integer = 1
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
