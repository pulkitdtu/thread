#ifndef SAFEQUEUE_H_INCLUDED
#define SAFEQUEUE_H_INCLUDED

#include <queue>
#include <mutex>
using namespace std;
template <class T>
class SafeQueue
{
public:
  void enqueue(T t)
  {
    std::lock_guard<std::mutex> lock(static_mutex);
    q.push(t);
  }
  T dequeue(void)
  {
      std::lock_guard<std::mutex> lock(static_mutex);
      T val;
      if(q.size() > 0)
      {
        val = q.front();
        q.pop();
      }
      return val;
  }
  int size()
  {
      return q.size();
  }
  string getResult()
  {
      return result;
  }
  void setResult(string s)
  {
      result =string(s);
  }
  string getHash()
  {
      return hash;
  }
  void setHash(string _hash)
  {
      hash = string(_hash);
  }
private:
  static std::queue<T> q;
  static std::mutex static_mutex;
  static std::string result;
  static std::string hash;
};
template <class T>
std::mutex SafeQueue<T>::static_mutex;
template <class T>
std::queue<T> SafeQueue<T>::q;
template <class T>
std::string SafeQueue<T>::result = "";
template <class T>
string SafeQueue<T>::hash = "e1faffb3e614e6c2fba74296962386b7";
#endif // SAFEQUEUE_H_INCLUDED
