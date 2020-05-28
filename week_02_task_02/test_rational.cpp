#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

class Rational {
	int p{ 0 };
	int q{ 1 };

public:
	Rational() = default;
	Rational(int numerator, int denominator) {
		p = numerator;
		q = denominator;
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}
};

bool operator!=(const Rational& lhs, const Rational& rhs)
{
	return lhs.Numerator() != rhs.Numerator()
		|| lhs.Denominator() != rhs.Denominator();
}

ostream& operator<<(ostream& os, const Rational& m)
{
	os << "{p = " << m.Numerator() << "; q = " << m.Denominator() << "} ";
	return os;
}

void TestCtor() {
	Rational r;
	AssertEqual(r, Rational(0, 1), "ululu");
}

int MYgcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

void TestReduce1() {
	int p = 10;
	int q = 20;
	Rational r(p, q);
	int g = MYgcd(p, q);
	AssertEqual(r, Rational(p / g, q / g), "aaa");
}

void TestMinus() {
	Rational r(1, -2);
	AssertEqual(r.Numerator(), -1, "bla11");
	AssertEqual(r.Denominator(), 2, "bla12");

	Rational r2(-3, 4);
	AssertEqual(r2.Numerator(), -3, "bla21");
	AssertEqual(r2.Denominator(), 4, "bla22");

	Rational r3(5, 6);
	AssertEqual(r3.Numerator(), 5, "bla31");
	AssertEqual(r3.Denominator(), 6, "bla32");

	Rational r4(-7, -8);
	AssertEqual(r4.Numerator(), 7, "bla41");
	AssertEqual(r4.Denominator(), 8, "bla42");
}

void TestDenom() {
	Rational r(0, 2);
	AssertEqual(r.Denominator(), 1, "qwe1");

	Rational r2;
	AssertEqual(r2.Denominator(), 1, "qwe2");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestCtor, "TestCtor");
  runner.RunTest(TestReduce1, "TestReduce1");
  runner.RunTest(TestMinus, "TestMinus");
  runner.RunTest(TestDenom, "TestDenom");
  // добавьте сюда свои тесты
  return 0;
}
