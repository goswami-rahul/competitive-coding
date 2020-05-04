#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// To use most bits rather than just the lowest ones:
struct chash { // large odd number for C
  const uint64_t C = Long(4e18 * acos(0)) | 71;
  Long operator()(Long x) const { return __builtin_bswap64(x * C); }
};
 
template<typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, chash>;
