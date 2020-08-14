namespace FFT {
  typedef i64 res_t;
  typedef double num_t;
  struct Complex {
    num_t real, imag;
    Complex() = default;
    Complex(const num_t x, const num_t y = 0): real(x), imag(y) {}
    
    Complex& operator *= (const Complex &rhs) {
      const num_t temp = real * rhs.real - imag * rhs.imag;
      imag = real * rhs.imag + imag * rhs.real; real = temp;
      return *this;
    }
    friend Complex operator * (Complex lhs, const Complex &rhs) {
      lhs *= rhs; return lhs;
    }
    Complex& operator += (const Complex &rhs) {
      real += rhs.real, imag += rhs.imag; return *this;
    }
    friend Complex operator + (Complex lhs, const Complex &rhs) {
      lhs += rhs; return lhs;
    }
    Complex& operator -= (const Complex &rhs) {
      real -= rhs.real, imag -= rhs.imag; return *this;
    }
    friend Complex operator - (Complex lhs, const Complex &rhs) {
      lhs -= rhs; return lhs;
    }
    Complex& operator /= (const num_t &rhs) {
      real /= rhs, imag /= rhs; return *this;
    }
  };
  
  const num_t PI = acos((num_t) -1);
  const int MAX = 1 << 19;
  static int bits[MAX];
  static Complex root[MAX], iroot[MAX];
  
  inline void prepare_roots() {
    root[1] = iroot[1] = 1;
    for (int len = 2; len < MAX; len *= 2) {
      const Complex w(cos(PI / len), sin(PI / len)), iw(w.real, -w.imag);
      for (int i = len >> 1; i < len; ++i) {
        root[i + i] = root[i]; root[i + i + 1] = root[i] * w;
        iroot[i + i] = iroot[i]; iroot[i + i + 1] = iroot[i] * iw;
      }
    }
  }
  inline void prepare_cache(int n) {
    static int last = -1;
    if (last == n) return; last = n;
    int lg = 0;
    while (1 << (lg + 1) < n) ++lg;
    for (int i = 1; i < n; ++i) 
      bits[i] = (bits[i >> 1] >> 1) | ((i & 1) << lg);
  }
  
  void fft(vector<Complex> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;
    for (int i = 1; i < n; i++) if (i > bits[i]) swap(a[i], a[bits[i]]);
    const auto ws = (invert ? iroot : root); 
    for (int len = 1; len < n; len *= 2) {
      for (int i = 0; i < n; i += len << 1) {
        for (int j = 0; j < len; j++) {
          const Complex u = a[i + j], v = a[i + j + len] * ws[len + j];
          a[i + j] = u + v; a[i + j + len] = u - v;
        }
      }
    }
    if (invert) for (Complex &x : a) x /= n;
  }
  vector<res_t> multiply(vector<res_t> const &a, vector<res_t> const &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) (a.size() + b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    
    prepare_cache(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<res_t> result(n);
    for (int i = 0; i < n; i++) result[i] = (res_t) rintl(fa[i].real);
    while (!result.empty() && result.back() == 0) result.pop_back();
    return result;
  }
  vector<res_t> square(vector<res_t> const &a) {
    vector<Complex> fa(a.begin(), a.end());
    int n = 1;
    while (n < (int) (a.size() + a.size())) n <<= 1;
    fa.resize(n);
    
    prepare_cache(n);
    fft(fa, false); 
    for (int i = 0; i < n; i++) fa[i] *= fa[i];
    fft(fa, true);

    vector<res_t> result(n);
    for (int i = 0; i < n; i++) result[i] = (res_t) rintl(fa[i].real);
    while (!result.empty() && result.back() == 0) result.pop_back();
    return result;
  }
} // namespace FFT


/******************************/

// faster to write
namespace FFT {
	using DBL = double; // !!! change to long double if needed
	using cd = complex<DBL>;
	const DBL PI = acos(-1);

	int reverse(int num, int lg_n) {
		int res = 0;
		for (int i = 0; i < lg_n; ++i) {
			if (num & (1 << i)) {
				res |= 1 << (lg_n - 1 - i);
			}
		}
		return res;
	}

	void fft(vector<cd>& a, bool invert) {
		int n = a.size(); int lg_n = 0;
		while ((1 << lg_n) < n) lg_n++;
		for (int i = 0; i < n; ++i) {
			if (i < reverse(i, lg_n)) {
				swap(a[i], a[reverse(i, lg_n)]);
			}
		}
		for (int len = 2; len <= n; len <<= 1) {
		    DBL ang = 2 * PI / len * (invert ? -1 : 1);
		    cd wlen(cos(ang), sin(ang));
		    for (int i = 0; i < n; i += len) {
		        cd w(1);
		        for (int j = 0; j < len / 2; j++) {
		            cd u = a[i+j], v = a[i+j+len/2] * w;
		            a[i+j] = u + v;
		            a[i+j+len/2] = u - v;
		            w *= wlen;
		        }
		    }
		}
        if (invert) {
            for (cd&x: a) {
                x /= n;
            }
        }
	}

	void convolveSelf(vector<LL>& a) {
        int m = a.size();
	    int n = 1;
	    while (n < m) n <<= 1;
	    n <<= 1;
        vector<cd> va(n, 0), ia(n, 0);
        for (int i = 0; i < m; ++i) {
            va[i] = a[i];
            ia[i] = a[m - i - 1];
        }
        fft(va, false);
        fft(ia, false);
        for (int i = 0; i < n; ++i) {
            va[i] *= ia[i];
        }
        fft(va, true);
        for (int i = 0; i < m; ++i) {
            a[i] = LL(round(va[m - 1 + i].real()));
        }
	}
};



const int MOD = 998244353;
 
int mod_add(int a, int b) {
    int sum = a + b;
    return sum >= MOD ? sum - MOD : sum;
}
 
int mod_sub(int a, int b) {
    int diff = a - b;
    return diff < 0 ? diff + MOD : diff;
}
 
int mod_mul(int a, int b, int m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
    return (long long) a * b % m;
#endif
    uint64_t x = (uint64_t) a * b;
    unsigned x_high = x >> 32, x_low = (unsigned) x;
    unsigned div, mod;
    asm(
        "divl %4; \n\t"
        : "=a" (div), "=d" (mod)
        : "d" (x_high), "a" (x_low), "r" (m)
    );
    return mod;
}
 
long long mod_inv(long long a, long long m = MOD) {
    return a == 1 ? 1 : m - mod_inv(m % a, a) * m / a;
}
 
long long mod_pow(long long a, long long p, long long m = MOD) {
    long long result = 1;
 
    while (p > 0) {
        if (p & 1)
            result = mod_mul(result, a, m);
 
        a = mod_mul(a, a, m);
        p >>= 1;
    }
 
    return result;
}
 
namespace NTT {
    vector<int> roots = {0, 1};
    vector<int> bit_reverse;
    int max_size = -1;
    int root;
 
    bool is_power_of_two(int n) {
        return (n & (n - 1)) == 0;
    }
 
    int round_up_power_two(int n) {
        assert(n > 0);
 
        while (n & (n - 1))
            n = (n | (n - 1)) + 1;
 
        return n;
    }
 
    // Given n (a power of two), finds k such that n == 1 << k.
    int get_length(int n) {
        assert(is_power_of_two(n));
        return __builtin_ctz(n);
    }
 
    // Rearranges the indices to be sorted by lowest bit first, then second lowest, etc., rather than highest bit first.
    // This makes even-odd div-conquer much easier.
    void bit_reorder(int n, vector<int> &values) {
        if ((int) bit_reverse.size() != n) {
            bit_reverse.assign(n, 0);
            int length = get_length(n);
 
            for (int i = 0; i < n; i++)
                bit_reverse[i] = (bit_reverse[i >> 1] >> 1) + ((i & 1) << (length - 1));
        }
 
        for (int i = 0; i < n; i++)
            if (i < bit_reverse[i])
                swap(values[i], values[bit_reverse[i]]);
    }
 
    void find_root() {
        int order = MOD - 1;
        max_size = 1;
 
        while (order % 2 == 0) {
            order /= 2;
            max_size *= 2;
        }
 
        root = 2;
 
        // Find a max_size-th primitive root of MOD.
        while (!(mod_pow(root, max_size) == 1 && mod_pow(root, max_size / 2) != 1))
            root++;
    }
 
    void prepare_roots(int n) {
        if (max_size < 0)
            find_root();
 
        if ((int) roots.size() >= n)
            return;
 
        int length = get_length(roots.size());
        roots.resize(n);
 
        // The roots array is set up such that for a given power of two n >= 2, roots[n / 2] through roots[n - 1] are
        // the first half of the n-th primitive roots of MOD.
        while (1 << length < n) {
            // z is a 2^(length + 1)-th primitive root of MOD.
            int z = mod_pow(root, max_size >> (length + 1));
 
            for (int i = 1 << (length - 1); i < 1 << length; i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = mod_mul(roots[i], z);
            }
 
            length++;
        }
    }
 
    void fft_iterative(int N, vector<int> &values) {
        assert(is_power_of_two(N));
        prepare_roots(N);
        bit_reorder(N, values);
        assert(N <= max_size);
 
        for (int n = 1; n < N; n *= 2)
            for (int start = 0; start < N; start += 2 * n)
                for (int i = 0; i < n; i++) {
                    int even = values[start + i];
                    int odd = mod_mul(values[start + n + i], roots[n + i]);
                    values[start + i] = mod_add(even, odd);
                    values[start + n + i] = mod_sub(even, odd);
                }
    }
 
    const int FFT_CUTOFF = 150;
 
    vector<int> mod_multiply(vector<int> left, vector<int> right, bool trim = true) {
        int n = left.size();
        int m = right.size();
 
        for (int i = 0; i < n; i++)
            assert(0 <= left[i] && left[i] < MOD);
 
        for (int i = 0; i < m; i++)
            assert(0 <= right[i] && right[i] < MOD);
 
        // Brute force when either n or m is small enough.
        if (min(n, m) < FFT_CUTOFF) {
            const uint64_t ULL_BOUND = numeric_limits<uint64_t>::max() - (uint64_t) MOD * MOD;
            vector<uint64_t> result(n + m - 1);
 
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    result[i + j] += (uint64_t) left[i] * right[j];
 
                    if (result[i + j] > ULL_BOUND)
                        result[i + j] %= MOD;
                }
 
            for (int i = 0; i < (int) result.size(); i++)
                if (result[i] >= (uint64_t) MOD)
                    result[i] %= MOD;
 
            if (trim) {
                while (!result.empty() && result.back() == 0)
                    result.pop_back();
            }
 
            return vector<int>(result.begin(), result.end());
        }
 
        int N = round_up_power_two(n + m - 1);
        left.resize(N);
        right.resize(N);
 
        bool equal = left == right;
        fft_iterative(N, left);
 
        if (equal)
            right = left;
        else
            fft_iterative(N, right);
 
        int inv_N = mod_inv(N);
 
        for (int i = 0; i < N; i++)
            left[i] = mod_mul(mod_mul(left[i], right[i]), inv_N);
 
        reverse(left.begin() + 1, left.end());
        fft_iterative(N, left);
        left.resize(n + m - 1);
 
        if (trim) {
            while (!left.empty() && left.back() == 0)
                left.pop_back();
        }
 
        return left;
    }
 
    vector<int> power(const vector<int> &v, int exponent) {
        assert(exponent >= 0);
        vector<int> result = {1};
 
        if (exponent == 0)
            return result;
 
        for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
            result = mod_multiply(result, result);
 
            if (exponent & 1 << k)
                result = mod_multiply(result, v);
        }
 
        return result;
    }
};
