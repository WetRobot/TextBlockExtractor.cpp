namespace utils{
template<typename T, typename Allocator>
int match(T &x, std::vector<T, Allocator> &y);

template<typename T, typename Allocator>
bool is_in(T &x, std::vector<T, Allocator> &y);
}