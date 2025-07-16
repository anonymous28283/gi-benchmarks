




using std::cin;
using std::cout;
using std::vector;












ll mat_size;


vector<ll> fib_b, fib_c;


vector<vector<ll>> multiply(const vector<vector<ll>> &A,
                            const vector<vector<ll>> &B) {
    vector<vector<ll>> C(mat_size + 1, vector<ll>(mat_size + 1));
    for (ll i = 1; i <= mat_size; i++) {
        for (ll j = 1; j <= mat_size; j++) {
            for (ll z = 1; z <= mat_size; z++) {
                C[i][j] = (C[i][j] + (A[i][z] * B[z][j]) % MOD) % MOD;
            }
        }
    }
    return C;
}


vector<vector<ll>> power(const vector<vector<ll>> &A, ll p) {
    if (p == 1)
        return A;
    if (p % 2 == 1) {
        return multiply(A, power(A, p - 1));
    } else {
        vector<vector<ll>> X = power(A, p / 2);
        return multiply(X, X);
    }
}


ll ans(ll n) {
    if (n == 0)
        return 0;
    if (n <= mat_size)
        return fib_b[n - 1];

    vector<ll> F1(mat_size + 1);
    for (ll i = 1; i <= mat_size; i++) F1[i] = fib_b[i - 1];


    vector<vector<ll>> T(mat_size + 1, vector<ll>(mat_size + 1));
    for (ll i = 1; i <= mat_size; i++) {
        for (ll j = 1; j <= mat_size; j++) {
            if (i < mat_size) {
                if (j == i + 1)
                    T[i][j] = 1;
                else
                    T[i][j] = 0;
                continue;
            }
            T[i][j] = fib_c[mat_size - j];
        }
    }

    T = power(T, n - 1);


    ll res = 0;
    for (ll i = 1; i <= mat_size; i++) {
        res = (res + (T[1][i] * F1[i]) % MOD) % MOD;
    }
    return res;
}


int main() {
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    ll i, j, x;
    while (t--) {
        cin >> mat_size;
        for (i = 0; i < mat_size; i++) {
            cin >> x;
            fib_b.pb(x);
        }
        for (i = 0; i < mat_size; i++) {
            cin >> x;
            fib_c.pb(x);
        }
        cin >> x;
        cout << ans(x) << endl;
        fib_b.clear();
        fib_c.clear();
    }
    return 0;
}
