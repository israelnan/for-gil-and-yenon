// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Ex6 , Yarin Benizri , 205778855
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "HashMap.hpp"
#include <stdexcept>

class InvalidKey : public std::invalid_argument {
 public:
  explicit InvalidKey () : invalid_argument (INVALID_KEY_MSG)
  {}
};

class Dictionary : public HashMap<std::string, std::string> {
 public:
  /** keeps default ctor
   */
  Dictionary()=default;

  Dictionary(const std::vector<std::string> &keys,
             const std::vector<std::string> &values)
  noexcept (false): HashMap<std::string, std::string> (keys,values){};

  /**
     * Dictionary erase over rides HashMap erase , works the same except
     * trhows Invalidkey if key not in instead of return false
     * @return bool true if succeed, throw InvalidKey for invalid key
     */
  bool erase (const std::string &key) override
  {
    if (!(this->contains_key (key)))
      {
        throw InvalidKey ();
      }
    return this->HashMap<std::string, std::string>::erase (key);
  }

  /**
     * add key,values from iterator to Dictionary
     * @return void
     */
  template<class Iter>
  void update (Iter starts, Iter ends) noexcept (false)
  {
    for (auto kv = starts; kv != ends; kv++)
      {
        if (!contains_key (kv->first))
          {
            this->insert (kv->first, kv->second);
          }
        else
          {
            this->at (kv->first) = kv->second;
          }
      }
  }
};

