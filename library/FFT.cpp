namespace FFT {
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
    if (invert) for (Complex &x: a) x /= n;
  }
  vector<int> multiply(vector<int> const &a, vector<int> const &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) (a.size() + b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    
    prepare_cache(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = (int) round(fa[i].real);
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
