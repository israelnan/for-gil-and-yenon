// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Ex6 , Yarin Benizri , 205778855
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef HASH_SET_H
#define HASH_SET_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

#define DEFAULT_ELEMENTS_AMOUNT 0
#define RESIZE_CONST 2
#define LOWER_BOND_CAPACITY 1
#define CAPACITY 16
#define LOWER_BOND_LF 0.25
#define UPPER_BOND_LF 0.75

#define LENGTH_ERROR_MSG "vectors not same length"
#define INVALID_KEY_MSG "ERROR MESSAGE, Invalid key: key not in data"
/**
 * Generic Hash table class, for more info:
 * https://en.wikipedia.org/wiki/Hash_table
 * @tparam KeyT has default ctor,std::hash,  ==, =
 * @tparam ValueT has default ctor, ==, =
 * @param _capacity int
 * @param _elems_amount int
 * @param _data a pointer
 */
template<typename KeyT, typename ValueT>
class HashMap {
 protected:
  int _elems_amount{};
  int _capacity{};
  std::vector<std::pair<KeyT, ValueT>> *_data;

  /**
 * calculate new capacity
 * @return new_cap int by condition to resize
 */
  int get_new_capacity ()
  {
    int new_cap = 0;
    if (get_load_factor () < LOWER_BOND_LF)
      {
        new_cap = _capacity / RESIZE_CONST;
      }
    else
      {
        new_cap = _capacity * RESIZE_CONST;
      }
    return new_cap;
  }

  /**
   * resize data according to the load factor criterion
   */
  void resize_hash ()
  {
    int temp_capacity = get_new_capacity ();
    try
      {
        replace_hash (temp_capacity);
      }
    catch (std::exception &exception_caught)
      {
        _capacity = temp_capacity;
        throw (std::bad_alloc ());
      }
  }
  /**
   * replace _data to new data and delete the older one
   */
  void replace_hash (int new_capacity)
  {
    auto *new_data = new std::vector<std::pair<KeyT, ValueT>>[new_capacity];
    for (int i = 0; i < _capacity; i++)
      {
        for (auto kv: _data[i])
          {
            new_data[hash_function(kv.first)].emplace_back
            (kv.first,kv.second);
          }
      }
    delete[] _data;
    _data = new_data;
  }

  /**
   *
   * getter first bucket index of non-empty vector
   * @return int index.
   */
  int get_first_bucket () const
  {
    int dummy_index = 0;
    for (int i = 0; i < _capacity; i++)
      {
        if (!(_data[i].empty ()))
          {
            return i;
          }
      }
    return dummy_index;
  }

  /**
   * getter last bucket index of non-empty vector
   * @return int index.
   */
  int get_last_bucket () const
  {
    int dummy_index = 0;
    for (int i = 0; i <= _capacity - 1; i++)
      {
        if (!(this->_data[_capacity - 1 - i].empty ()))
          {
            return _capacity - 1 - i;
          }
      }
    return dummy_index;
  }

  class ConstIterator {

   private:
    const HashMap<KeyT, ValueT> *_current_data;
    typename std::vector<std::pair<KeyT, ValueT>>::const_iterator
        _current_iter;
    int _bucket_i{};
    int _iter_cnt{};

   public:
    typedef std::pair<KeyT, ValueT> value_type;
    typedef const std::pair<KeyT, ValueT> &reference;
    typedef const std::pair<KeyT, ValueT> *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef ConstIterator const_iterator_type;

    /**
     * default ConstIterator;
     */
    ConstIterator () = default;

    /**
     * ctor
     * @param hashmap *Hashmap
     * @param current_iter const_iterator
     * @param bucket_i
     */
    ConstIterator (const HashMap<KeyT, ValueT> *hashmap,
                    typename std::vector<std::pair<KeyT, ValueT>>::
    const_iterator current_iter,
    int bucket_i)
    : _current_data (hashmap), _current_iter (current_iter),
        _bucket_i (bucket_i),_iter_cnt (DEFAULT_ELEMENTS_AMOUNT)
    {}

    /**
     * @return the dereference of the iterator.
     */
    value_type operator* () const
    {
      return *_current_iter;
    }

    /**
     * @param other const ConstIterator
     * @return bool result of == operator
     */
    bool operator== (const ConstIterator &other) const
    {
      return _current_iter == other._current_iter;
    }

    /**
     * @param other const ConstIterator
     * @return bool opposite result of == operator
     */
    bool operator!= (const ConstIterator &other) const
    {
      return !(_current_iter == other._current_iter);
    }

    /**
     * @return reference
     */
    const value_type *operator-> () const
    {
      return &(*_current_iter);
    }

    /**
     * setter bucket_i
     * @param bucket_i int.
     */
    void set_bucket_i (int bucket_i)
    {
      _bucket_i = bucket_i;
    }

    /**
     * operator ++
     * @return ConstIterator
     */
    ConstIterator &operator++ ()
    {
      _current_iter++;
      _iter_cnt++;
      if (_iter_cnt == _current_data->_elems_amount)
        {
          int index = _current_data->get_last_bucket ();
          _current_iter = _current_data->_data[index].cend ();
          return *this;
        }

      if (_current_iter != _current_data->_data[_bucket_i].cend ()
          || _bucket_i == _current_data->_capacity - 1)
        {
          return *this;
        }
      for (int i = _bucket_i + 1;i < _current_data->_capacity; i++)
        {
          if (!_current_data->_data[i].empty ())
            {
              set_bucket_i (i);
              _current_iter = _current_data->_data[i].cbegin ();
              return *this;
            }
          if (i == _current_data->_capacity - 1)
            {
              set_bucket_i (i);
              _current_iter = _current_data->_data[i].cend ();
              return *this;
            }
        }
      return *this;
    }

    /**
     * @brief post increment ++ using the previous increment.
     */
    ConstIterator operator++ (int)
    {
      auto temp = *this;
      ++*this;
      return temp;
    }

  };

 public:
  /**
   * default ctor , _capacity = 16 , _elems_amount = 0 , _data = std::vector
   */
  HashMap () noexcept (false)
  : _elems_amount (DEFAULT_ELEMENTS_AMOUNT), _capacity (CAPACITY),
  _data (new std::vector<std::pair<KeyT, ValueT>>[_capacity])
  {}

  /**
   *  copy ctor
   */
  HashMap (const HashMap &other) noexcept (false)
  : _elems_amount (DEFAULT_ELEMENTS_AMOUNT), _capacity (other._capacity),
  _data (new std::vector<std::pair<KeyT, ValueT>>[_capacity])
  {
    for (int i = 0; i < _capacity; i++)
      {
        for (auto kv: other._data[i])
          {
            this->insert (kv.first, kv.second);
          }
      }
  }

/**
   * copy ctor with deep copy.
   */
  HashMap (const std::vector<KeyT> &keys, const std::vector<ValueT> &values)
  noexcept (false): HashMap ()
  {
    if (keys.size () != values.size ())
      {
        throw std::length_error (LENGTH_ERROR_MSG);
      }
    auto v = values.begin ();
    for (auto k = keys.begin (); k != keys.end (); v++, k++)
      {
        if (!contains_key (*k))
          {
            this->insert (*k, *v);
          }
        else
          {
            this->at (*k) = *v;
          }
      }
  }

  /**
   *  dector
   **/
  virtual ~HashMap () noexcept
  {
    delete[] _data;
    _data = nullptr;
  }

  /**
   * hash function
   * @param key const KeyT &
   * @return int
   */
  int hash_function (const KeyT &key) const noexcept
  {
    int v = std::hash<KeyT>{} (key);
    return v & (_capacity - 1);
  }

  /**
   * size getter
   * @return _elems_amount int number of (keys,values) in data.
   */
  int size () const noexcept
  {
    return _elems_amount;
  }

  /**
   * @brief capacity getter
   * @return  capacity int number of buckets.
   */
  int capacity () const noexcept
  {
    return _capacity;
  }

  /**
   * @return bool true if data has no pairs.
   */
  bool empty () const noexcept
  {
    return _elems_amount == 0;
  }

  /**
 * function check if key is in pair in _data
 * @param key const KeyT&
 * @return bool
 */
  bool contains_key (const KeyT &key) const noexcept
  {
    int hash_index = hash_function (key);
    for (auto kv: _data[hash_index])
      {
        if (kv.first == key)
          {
            return true;
          }
      }
    return false;
  }

  /**
   * insert to _data
   * @param key const KeyT&
   * @param value const ValueT&
   * @return bool true if success.
   */
  bool insert (const KeyT &key, const ValueT &value) noexcept
  {
    if (contains_key (key))
      {
        return false;
      }
    _elems_amount++;
    if (get_load_factor () > UPPER_BOND_LF)
      {
        try
          {
            resize_hash ();
          }
        catch (std::bad_alloc &exception_catch)
          {
            --_elems_amount;
            return false;
          }
      }
    _data[hash_function (key)].emplace_back (key, value);
    return true;
  }

  /**
    * getter for value by key
    * @param key const KeyT&
    * @return value ValueT when value = _Data[key] in key:value in _data
    */
  const ValueT &at (const KeyT &key) const noexcept (false)
  {
    int hash_index = hash_function (key);
    auto iter = std::find_if (_data[hash_index].begin (),
                              _data[hash_index].end (),
                              [&key] (const std::pair<KeyT, ValueT>
                              &element){ return element.first == key; });
    if (iter == _data[hash_index].end ())
      {
        throw std::out_of_range (INVALID_KEY_MSG);
      }
    return iter->second;
  }

  /**
   * getter for value by key
   * @param key const KeyT&
   * @return value ValueT when value = _Data[key] in key:value in _data
   */
  ValueT &at (const KeyT &key) noexcept (false)
  {
    int hash_index = hash_function (key);
    auto find_iter = std::find_if (_data[hash_index].begin (),
                                   _data[hash_index].end (), [&key]
                                       (const std::pair<KeyT, ValueT>
                                        &element)
                                   { return element.first == key; });
    if (find_iter == _data[hash_index].end ())
      {
        throw std::out_of_range (INVALID_KEY_MSG);
      }
    return find_iter->second;
  }

  /**
   * erase
   * @param key const KeyT&
   * @return bool true on succeed operation.
   */
  virtual bool erase (const KeyT &key)
  {
    if (!(this->contains_key (key)))
      {
        return false;
      }
    if ((_capacity == 2 && _elems_amount == 1) ||
        (get_load_factor () <= LOWER_BOND_LF
         && _capacity > LOWER_BOND_CAPACITY))
      {
        try
          {
            resize_hash ();
          }
        catch (std::bad_alloc &except)
          {
            return false;
          }
      }
    int hash_index = hash_function (key);
    auto erase_iter = std::find_if (_data[hash_index].begin (),
                                    _data[hash_index].end (), [&key]
                                        (const std::pair<KeyT, ValueT>
                                         &element)
                                    { return element.first == key; });
    if (erase_iter->first == key)
      {
        _data[hash_index].erase (erase_iter);
        _elems_amount--;
        return true;
      }
    return false;
  }

/**
 * getter load factor
 * @return double
 */
  double get_load_factor () const noexcept
  {
    return (double) (_elems_amount / _capacity);
  }

/**
 * getter for bucket size
 * @param keyconst KeyT&
 * @return int
 */
  int bucket_index (const KeyT &key) const noexcept (false)
  {
    if (!contains_key (key))
      {
        throw std::out_of_range (INVALID_KEY_MSG);
      }
    return hash_function (key);
  }

/**
 * getter
 * @param key const KeyT&
 * @return int size of bucket
 */
  int bucket_size (const KeyT &key) const noexcept (false)
  {
    int hash_key = bucket_index (key);
    return _data[hash_key].size ();
  }

/**
 * delete values of hashmap without changing capacity.
 */
  void clear () noexcept
  {
    for (int i = 0; i < _capacity; i++)
      {
        _data[i].clear ();
      }
    _elems_amount = 0;
  }

/**
 * operator == for hashmap per pairs init.
 * @param other const HashMap&
 * @return bool true if same
 */
  bool operator== (const HashMap &other) const noexcept
  {
    if (_elems_amount != other._elems_amount || _capacity != other._capacity)
      {
        return false;
      }
    for (int i = 0; i < _capacity; i++)
      {
        for (auto kv: _data[i])
          {
            try
              {
                if (other.at (kv.first) != kv.second)
                  {
                    return false;
                  }
              }
            catch (std::out_of_range &exception_catch)
              {
                return false;
              }
          }
      }
    return true;
  }

/**
 * operator != for hashmap per pairs init.
 * @param other const HashMap&
 * @return bool true if not same
 */
  bool operator!= (const HashMap &other) const noexcept
  {
    return !(*this == other);
  }

/**
 * assignment operator
 * @param other const HashMap&
 * @return Hashmap&
 */
  HashMap &operator= (const HashMap &other) noexcept (false)
  {
    if (this == &other)
      {
        return *this;
      }
    this->clear ();
    delete[] _data;
    _capacity = other._capacity;
    _data = new std::vector<std::pair<KeyT, ValueT>>[other._capacity];
    for (int i = 0; i < other._capacity; i++)
      {
        for (auto kv: other._data[i])
          {
            this->insert (kv.first, kv.second);
          }
      }
    return *this;
  }

/**
 * operator[] get object by key if not exists makes it
 * @param key const KeyT&
 * @return ValueT&
 */
  ValueT& operator[] (const KeyT &key) noexcept
  {
    if (!(this->contains_key (key)))
      {
        insert (key, ValueT ());
      }
    return this->at(key);
  }

/**
 * operator[] const get object by key if not exists makes it
 * @param key const KeyT&
 * @return ValueT&
 */
  ValueT operator[] (const KeyT &key) const noexcept
  {
    if (this->contains_key(key))
      {
        return this->at(key);
      }
    return ValueT();
  }

/**
 * @return ConstIterator start of _data
 */
  ConstIterator cbegin () const
  {
    if (empty ())
      {
        return cend ();
      }
    int first_bucket_i = get_first_bucket ();
    auto current_iter = _data[first_bucket_i].cbegin ();
    return ConstIterator (this, current_iter, first_bucket_i);
  }

/**
* @return ConstIterator end of _data
*/
  ConstIterator cend () const
  {
    int i = _capacity - 1;
    if (!(this->empty ()))
      {
        i = get_last_bucket ();
      }
    auto current_iter = (_data[i].cend ());
    return ConstIterator (this, current_iter, i);
  }

/**
 * @return cbegin iterator.
 */
  ConstIterator begin () const
  {
    return this->cbegin();
  }

/**
 * @return cend iterator.
 */
  ConstIterator end () const
  {
    return this->cend();
  }

};
#endif
