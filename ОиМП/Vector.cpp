#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd(time(0));

template <typename T>
struct RawMemory {
    T* buf = nullptr;
    size_t cp = 0;
    static T* Allocate(size_t n) {
        return static_cast<T*>(operator new(n * sizeof(T)));
    }
    static void Deallocate(T* buf) {
        operator delete(buf);
    }
    RawMemory() = default;
    RawMemory(size_t n) {
        buf = Allocate(n);
        cp = n;
    }
    RawMemory(const RawMemory&) = delete;
    RawMemory(RawMemory&& other) {
        swap(other);
    }

    RawMemory& operator=(const RawMemory&) = delete;

    RawMemory& operator=(RawMemory&& other) noexcept {
        swap(other);
        return *this;
    }

    void swap(RawMemory& other) {
        std::swap(buf, other.buf);
        std::swap(cp, other.cp);
    }
    T* operator+(size_t i) {
        return buf + i;
    }
    const T* operator+(size_t i) const {
        return buf + i;
    }
    T& operator[](size_t i) {
        return buf[i];
    }
    const T& operator[](size_t i) const {
        return buf[i];
    }

    ~RawMemory() {
        Deallocate(buf);
    }
};

template <typename T>
class Vector {
private:
    RawMemory<T> data;
    size_t sz = 0;

    static void Constructor(void* buf) {
        new (buf) T();
    }
    static void Constructor(void* buf, const T& elem) {
        new (buf) T(elem);
    }
    static void Constructor(void* buf, T&& elem) { //NOLINT
        new (buf) T(std::move(elem));
    }
    static void Destroy(T* buf) {
        buf->~T();
    }

public:
    Vector() = default;
    explicit Vector(size_t n): data(n), sz(n) {
        std::uninitialized_value_construct_n(data.buf, n);
    }
    Vector(const Vector& other): data(other.sz), sz(other.sz) {
        std::uninitialized_copy_n(other.data.buf, other.sz, data.buf);
    }
    void swap(Vector& other) {
        data.swap(other.data);
        std::swap(sz, other.sz);
    }
    Vector(Vector&& other) noexcept {
        swap(other);
    }
    void reserve(size_t n) {
        if (n > data.cp) {
            RawMemory<T> data2(n);
            std::uninitialized_move_n(data.buf, sz, data2.buf);
            std::destroy_n(data.buf, sz);
            data.swap(data2);
        }
    }

    size_t size() const {
        return sz;
    }
    size_t capacity() const {
        return data.cp;
    }
    T& operator[](size_t i) {
        return data[i];
    }
    const T& operator[](size_t i) const {
        return data[i];
    }
    T* begin() {
        return data + 0;
    }
    const T* begin() const {
        return data + 0;
    }
    T* end() {
        return data + sz;
    }
    const T* end() const {
        return data + sz;
    }

    Vector& operator=(const Vector& other) {
        if (other.sz > data.cp) {
            Vector tmp(other);
            swap(tmp);
        } else {
            for (size_t i = 0; i < sz && i < other.sz; ++i) {
                data[i] = other[i];
            }
            if (sz < other.sz) {
                std::uninitialized_copy_n(other.data.buf + sz, other.sz - sz, data.buf + sz);
            } else if (sz > other.sz) {
                std::destroy_n(data.buf + other.sz, sz - other.sz);
            }
        }
        sz = other.sz;
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        Swap(other);
        return *this;
    }

    void resize(size_t n) {
        reserve(n);
        if (sz < n) {
            std::uninitialized_value_construct_n(data + sz, n - sz);
        } else if (sz > n) {
            std::destroy_n(data + n, sz - n);
        }
        sz = n;
    }
    void push_back(const T& elem) {
        if (sz == data.cp) {
            reserve(sz == 0 ? 1 : sz * 2);
        }
        new (data + sz) T(elem);
        ++sz;
    }
    void push_back(T&& elem) {
        if (sz == data.cp) {
            reserve(sz == 0 ? 1 : sz * 2);
        }
        new (data + sz) T(std::move(elem));
        ++sz;
    }
    void pop_back() {
        std::destroy_at(data + sz - 1);
        --sz;
    }
    void clear() {
        while (sz != 0) {
            pop_back();
        }
    }

    ~Vector() {
        std::destroy_n(data.buf, sz);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif



#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
