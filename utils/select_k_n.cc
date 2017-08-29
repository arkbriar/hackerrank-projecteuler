#include <vector>
#include <cassert>

bool __select_k_n_distinct(std::vector<int>& last, int k, int n, bool unsafe) {
    if (last.empty()) {
        last.reserve(k);
        last.push_back(0);
        while (int(last.size()) != k) last.push_back(last.back() + 1);
        return true;
    }

    static std::vector<int> _st;
    if (!unsafe) _st = last;
    std::vector<int>& st = unsafe ? last : _st;

    auto l = n;
    while (!st.empty() && l >= int(n - k + st.size())) {
        l = st.back();
        st.pop_back();
    }
    if (st.empty()) return false;

    st.push_back(l + 1);
    while (int(st.size()) != k) st.push_back(st.back() + 1);
    if (!unsafe) last = st;
    return true;
}

bool __select_k_n(std::vector<int>& last, int k, int n, bool unsafe) {
    if (last.empty()) {
        last.reserve(k);
        while (int(last.size()) != k) last.push_back(0);
        return true;
    }

    static std::vector<int> _st;
    if (!unsafe) _st = last;
    std::vector<int>& st = unsafe ? last : _st;

    auto l = n;
    while (!st.empty() && l >= n - 1) {
        l = st.back();
        st.pop_back();
    }
    if (st.empty()) return false;

    st.push_back(l + 1);
    while (int(st.size()) != k) st.push_back(st.back());
    if (!unsafe) last = st;
    return true;
}

// Get the next unordered selection of (n, k), with elements distinct or not
// will return the first selection when last is empty
//
// Use of unsafe can avoid copy when doing the next selection and improve the performance,
// but `last` will be empty after the last selection
bool select_k_n(std::vector<int>& last, int k, int n, bool distinct = false, bool unsafe = true) {
    assert(k > 0 && n > 0 && (last.empty() || last.size() == k));
    if (distinct) {
        assert(n >= k);
        return __select_k_n_distinct(last, k, n, unsafe);
    } else {
        return __select_k_n(last, k, n, unsafe);
    }
}
