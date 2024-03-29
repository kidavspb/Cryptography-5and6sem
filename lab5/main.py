import matplotlib.pyplot as plt


def Berlekamp_Massey_algorithm(sequence):
    N = len(sequence)
    s = sequence[:]

    for k in range(N):
        if s[k] == 1:
            break
    f = set([k + 1, 0])  # use a set to denote polynomial
    l = k + 1

    g = set([0])
    a = k
    b = 0

    for n in range(k + 1, N):
        d = 0
        for ele in f:
            d ^= s[ele + n - l]

        if d == 0:
            b += 1
        else:
            if 2 * l > n:
                f ^= set([a - b + ele for ele in g])
                b += 1
            else:
                temp = f.copy()
                f = set([b - a + ele for ele in f]) ^ g
                l = n + 1 - l
                g = temp
                a = b
                b = n - l + 1

    # output the polynomial
    def print_poly(polynomial):
        result = ''
        lis = sorted(polynomial, reverse=True)
        for i in lis:
            if i == 0:
                result += '1'
            else:
                result += 'x^%s' % str(i)

            if i != lis[-1]:
                result += ' + '

        return result

    return (print_poly(f), l)


if __name__ == '__main__':
    our_seq = tuple(map(int, [*"001110101101011111101000101011001000011111010111000100111101010110111101100101111001010111011101001100001110010"]))

    lineal_span = []
    for i in range(1, 102):
        seq = our_seq[:i]
        (poly, span) = Berlekamp_Massey_algorithm(seq)
        lineal_span.append(span)

        # print('The input sequence is %s.' % str(seq))
        # print('Its characteristic polynomial is (%s),' % poly)
        print('and linear span is %d.' % span)

    plt.plot(lineal_span)
    plt.show()
