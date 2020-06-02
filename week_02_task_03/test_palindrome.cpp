#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
	return false;
}

void TestAll() {
	Assert(IsPalindrom(""), "1");
	Assert(IsPalindrom("1"), "2");
	Assert(IsPalindrom("madam"), "3");
	Assert(IsPalindrom("asddsa"), "4");
	Assert(!IsPalindrom("madame"), "5");
	Assert(!IsPalindrom("emadam"), "6");
	Assert(!IsPalindrom("a rosa upala na lapu asora"), "7");
	Assert(!IsPalindrom("A rosa upala na lapu asora"), "8");
	Assert(!IsPalindrom("A rosa upala na lapu asorA"), "9");
	Assert(!IsPalindrom("a rosa upala na lapu asorA"), "10");
	Assert(!IsPalindrom("A rosa upala na lapu asorA"), "11");
	Assert(IsPalindrom("777777"), "12");
	Assert(IsPalindrom("7777777"), "13");
	Assert(!IsPalindrom("7777778"), "14");
	Assert(!IsPalindrom("777778"), "15");
	Assert(!IsPalindrom("8777777"), "16");
	Assert(!IsPalindrom("877777"), "17");
	Assert(!IsPalindrom("   AbA  "), "18");
	Assert(!IsPalindrom("  AbA   "), "18");

	Assert(IsPalindrom(""), "0 - 0 - 0");	
	Assert(IsPalindrom("A"), "0 - 1 - 0");	
	Assert(IsPalindrom("AA"), "1 - 0 - 1");	
	Assert(IsPalindrom("ABA"), "1 - 1 - 1");	
	Assert(IsPalindrom("ABBA"), "2 - 0 - 2");	
	Assert(IsPalindrom("ABoBA"), "2 - 1 - 2");	
	Assert(IsPalindrom("ABsiisBA"), "4 - 0 - 4");	
	Assert(IsPalindrom("ABsioisBA"), "4 - 1 - 4");	
	Assert(!IsPalindrom("ABshBA"), "Typical");	
	Assert(!IsPalindrom(" ABsioisBA"), "First space should be included");	
	Assert(!IsPalindrom("  ABsioisBA"), "First space should be included");	
	Assert(!IsPalindrom("ABsioisBA "), "Last space should be included");	
	Assert(!IsPalindrom("ABsioisBA  "), "Last space should be included");	
	Assert(!IsPalindrom("qABsioisBA"), "First symbol should be included");	
	Assert(!IsPalindrom("ABsioisBAq"), "Last symbol should be included");	
	Assert(!IsPalindrom("AB sioisBA"), "Space in word should be included");	
	Assert(!IsPalindrom("ABsi oisBA"), "Pre-central space should be included");
	Assert(!IsPalindrom("AB1sioisBA"), "Number in word should be included");	
	Assert(!IsPalindrom("ABsi1oisBA"), "Pre-central number should be included");	
	Assert(!IsPalindrom("ABsIoisBA"), "Case sensetive");	
	Assert(!IsPalindrom("asdfAasdf"), "Not only central");	
	Assert(!IsPalindrom("asdfABBAasdf"), "Not only central");	
	Assert(!IsPalindrom("AasdfAasdfA"), "Not only central");	
	Assert(!IsPalindrom("ABasdfABBAasdfBA"), "Not only central");
}



int main() {
  TestRunner runner;
  runner.RunTest(TestAll, "TestAll");

  return 0;
}
