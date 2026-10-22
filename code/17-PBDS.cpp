#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;

os.find_by_order(x); // mengambil index ke x
os.order_of_key(x); // berapa banyak elemen yang  < x

// Does: Maintains distinct sorted keys with rank and kth-element queries.
// Example: ordered_set<int> os; os.insert(5); os.insert(9);
// *os.find_by_order(0) == 5; os.order_of_key(9) == 1; // ranks are 0-based
