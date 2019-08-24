#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <limits>
#include <iterator>
// #include <algorithm>


template<typename T>
class ThinkCellKey : std::numeric_limits<T>{
	T v;

public:
  ThinkCellKey( T const& val) {
    v = val;
  }

  // inline bool operator< (const ThinkCellKey & s1, const ThinkCellKey & s2) {
  //   return  s1.v < s2.v;
  // }

  // overloaded < operator
  bool operator <(const ThinkCellKey& d) const {
    return v < d.v;
  }

  ThinkCellKey operator ++(int) {
    this->v++;
    return *this;
  }

  ThinkCellKey operator --(int) {
    this->v--;
    return *this;
  }

  friend std::ostream & operator << (std::ostream &out, const ThinkCellKey<T> &c) {
      out << c.v;
      return out;
  }

  static const ThinkCellKey<T> lowest() {
    return std::numeric_limits<T>::lowest();
  }

  // ThinkCellKey& operator= (const ThinkCellKey&) {
  //   return *this;
  // }
};

template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
  // constructor associates whole range of K with val by inserting (K_min, val)
  // into the map
  interval_map( V const& val) {
    m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
  }

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
    if (!(keyBegin < keyEnd))
      return;

    // if inserting into range of the same value before, don't insert
    // if the value existing already after out pointer, erase it
    auto before_begin_bound = --(m_map.lower_bound(keyBegin));
    auto insert_res = before_begin_bound->second == val ?
      before_begin_bound : m_map.insert_or_assign(before_begin_bound, keyBegin, val);

    auto end_interval = m_map.lower_bound(keyEnd);

    if (end_interval != m_map.end() && end_interval->second == val)
      end_interval++;

    insert_res++;
    m_map.erase(insert_res, end_interval);

    if (end_interval == m_map.end())
      this->assign(keyEnd, std::numeric_limits<K>::max(), before_begin_bound->second);
    else
      this->assign(keyEnd, end_interval->first, before_begin_bound->second);
  }

  // look-up of the value associated with key
  V const& operator[]( K const& key ) const {
    return ( --m_map.upper_bound(key) )->second;
  }


	// a print function for debugging
	void show() {
		std::cout << "show" << std::endl;
		for(auto entry : m_map) {
			std::cout << entry.first << entry.second << std::endl;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.


int main(int argc, char* argv[])
{
  // TODO: test interval map with different stl algorithm methods
  // TODO: make 4 spaces tab
  // interval_map<ThinkCellKey<unsigned int>, char> imap {'a'};
  interval_map<unsigned int, char> imap {'A'};

  // imap.assign(3, 5, 'B');
  // imap.assign(5, 7, 'C');
  // imap.assign(2, 7, 'D');


  // imap.assign(8, 10, 'k');

  imap.assign(8, 12, 'k');
	imap.assign(2, 12, 'k');
	imap.assign(2, 12, 'b');
	imap.assign(5, 12, 'b');
	imap.assign(4, 10, 'b');
	imap.assign(4, 12, 'b');
	imap.assign(8, 13, 'a');
  imap.assign(6, 9, 'j');


  // imap.assign(4, 4, 'j'); // its ok 
	// imap.assign(0, 10, 'e');
	// imap.assign(0, 10, 'e');

  // imap.assign(2,6, 'B');
  // imap.assign(3,10, 'C');
  // imap.assign(4, 7, 'B');
  // imap.assign(3, 5, 'B');

  imap.show();
  return 0;
}
