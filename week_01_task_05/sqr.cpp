#include <vector>
#include <utility>
#include <map>

template<typename F, typename S>
std::pair<F, S> operator*(const std::pair<F, S>& lhs, const std::pair<F, S>& rhs);
template<typename K, typename V>
std::map<K, V> operator*(const std::map<K, V>& lhs, const std::map<K, V>& rhs);
template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs);
template<typename T>
T Sqr(T source);


template<typename F, typename S>
std::pair<F, S> operator*(const std::pair<F, S>& lhs, const std::pair<F, S>& rhs)
{
	std::pair<F, S> res;
	res.first = lhs.first * rhs.first;
	res.second = rhs.second * rhs.second;
	return res;
}

template<typename K, typename V>
std::map<K, V> operator*(const std::map<K, V>& lhs, const std::map<K, V>& rhs)
{
	std::map<K, V> res;
	for (auto itL = lhs.begin(), itR = rhs.begin();
		itL != lhs.end();
		++itL, ++itR
		)
	{
		res[itL->first] = itL->second * itR->second;
	}

	return res;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
	std::vector<T> res;
	for (size_t i = 0; i < lhs.size(); ++i)
		res.push_back(lhs[i] * rhs[i]);
	return res;
}


template<typename T>
T Sqr(T source)
{
	return source * source;
}