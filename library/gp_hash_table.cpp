#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
struct chash {
  int operator()(int x) const {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
  }
};
template<typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, chash>;
