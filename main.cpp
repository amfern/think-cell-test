#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <limits>
// #include <algorithm>


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
    if (keyBegin > keyEnd)
      return;


    for (auto i = keyBegin; i < keyEnd; i++) {
      m_map.insert_or_assign(m_map.lower_bound(i), i, val);
    }

    // auto start = m_map.lower_bound(keyBegin);
    // auto end = m_map.upper_bound(keyEnd);

    // for (; true; start++) {
    //   std::cout << start->first << std::endl;
    //   // m_map.insert_or_assign(start, start->first, val);
    // }
    // typename std::map<K,V>::iterator low, up;

    // low=std::lower_bound (m_map.begin(), m_map.end(), keyBegin);
    // up=std::upper_bound (m_map.begin(), m_map.end(), keyEnd);

    // for(i keyBegin, auto entry : m_map) {
    //   m_map.insert_or_assign(entry);
    // }


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
  interval_map<unsigned int, char> imap {'a'};

  imap.assign(1, 3, 'B');
  imap.assign(3, 5, 'C');
  // imap.assign(3, 5, 'D');

  imap.show();
  return 0;
}
