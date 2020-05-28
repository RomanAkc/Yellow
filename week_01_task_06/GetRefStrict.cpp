#include <map>
#include <exception>

template<typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, const K& key);

template<typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, const K& key)
{
	if (m.find(key) == m.end())
		throw std::runtime_error("no key");

	return m[key];
}