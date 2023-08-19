#ifndef DLIST_H
#define DLIST_H

#include <iterator>

namespace  dlist {

template <typename T> class list
{
    struct lNode final
    {
        lNode() : next__(nullptr), prev__(nullptr), key__(T{0}) {}
        lNode(const T& item) : next__(nullptr), prev__(nullptr), key__(item) {}

        lNode *next__, *prev__;
        T key__ = T{0};
    };

private:
    lNode *head__;
    lNode *tail__;
    std::size_t size__ = 0;

public:
    class iterator : public std::iterator<std::input_iterator_tag, T>
    {
        iterator(lNode* pos) : node_ptr__(pos) {}
    public:
        iterator(const iterator& it) : node_ptr__(it.node_ptr__){}

        T& operator*() { return node_ptr__->key__; }

        iterator operator++() {
            node_ptr__ = node_ptr__->next__;
            return *this;
        }

        iterator operator++(int n) {
            iterator result = *this;
            node_ptr__ = node_ptr__->next__;
            return result;
        }

        iterator operator--() {
            node_ptr__ = node_ptr__->prev__;
            return *this;
        }

        iterator operator--(int n) {
            iterator result = *this;
            node_ptr__ = node_ptr__->prev__;
            return result;
        }

        bool operator==(const iterator& other) { return node_ptr__ == other.node_ptr__; }
        bool operator!=(const iterator& other) { return node_ptr__ != other.node_ptr__; }

        lNode* node_ptr__;
        friend class list;
    };

    using const_iterator = iterator;

  list() noexcept
  {
    head__ = tail__ = nullptr;
    size__ = 0;
  }

  explicit list(const T& key)
  {
    auto node = new lNode(key);
    head__ = tail__ = node;
    size__++;
  }

  ~list()
  {
    auto current = head__->next__;
    while(current != nullptr) {
      auto next = current->next__;
      delete current;
      current = next;
    }
    delete current;
  }

  const std::size_t size() const { return size__; }
  inline iterator begin() noexcept { return iterator(head__); }
  inline iterator end() noexcept { return iterator(tail__->next__); }
  T& front() const { return head__->key__; }
  T& back() const { return tail__->prev__->key__; }

  void push_back(const T& item)
  {
    auto newNode = new lNode(item);
    if((head__ == nullptr && tail__ == nullptr) || size__ == 0) {
      head__ = tail__ = newNode;
    }
    else{
      auto prev = tail__;
      prev->next__ = newNode;
      tail__ = newNode;
      newNode->prev__ = prev;
      newNode->next__ = nullptr;
    }
    size__++;
  }

  void pop_back()
  {
    auto toRemove = tail__;
    if((head__ == nullptr && tail__ == nullptr) || size__ == 0) return;
    else if(size__ == 1) {
      tail__ = head__;
      delete head__;
      head__ = tail__ = nullptr;
    }
    else {
      auto prev = toRemove->prev__;
      delete toRemove;
      tail__ = prev;
      prev->next__ = nullptr;
    }
    size__--;
  }

  void push_front(const T& item)
  {
    auto newNode = new lNode(item);
    if((head__ == nullptr && tail__ == nullptr) || size__ == 0) {
      head__ = tail__ = newNode;
    }
    else {
      auto next = head__;
      next->prev__ = newNode;
      newNode->next__ = next;
      newNode->prev__ = nullptr;
    }
    size__++;
  }

  void pop_front()
  {
    auto toRemove = head__;
    if((head__ == nullptr && tail__ == nullptr) || size__ == 0) return;
    else if(size__ == 1) {
      tail__ = head__;
      delete head__;
      head__ = tail__ = nullptr;
    }
    else {
      auto next = toRemove->next__;
      delete toRemove;
      head__ = next;
      head__->prev__ = nullptr;
    }
    size__--;
  }

  iterator insert(const iterator& pos, const T& item)
  {
    auto newNode = new lNode(item);
    auto prev = pos.node_ptr__->prev__;
    pos.node_ptr__->prev__ = newNode;
    newNode->next__ = pos.node_ptr__;
    prev->next__ = newNode;
    newNode->prev__ = prev;
    size__++;
    return iterator(newNode);
  }

  iterator erase(const iterator& pos)
  {
    if((head__ == nullptr && tail__ == nullptr) || size__ == 0) return this->end();
    else if(size__ == 1) {
      tail__ = head__;
      delete head__;
      head__ = tail__ = nullptr;
      return this->end();
    }
    else if(pos.node_ptr__ == head__) {
      auto next = head__->next__;
      delete head__;
      head__ = next;
      next->prev__ = nullptr;
      return iterator(next);
    }
    else if(pos.node_ptr__ == tail__) {
      auto prev = tail__->prev__;
      delete tail__;
      tail__ = prev;
      prev->next__ = nullptr;
      return this->end();
    }
    else {
      auto forErase = pos.node_ptr__;
      auto next = forErase->next__;
      auto prev = forErase->prev__;
      next->prev__ = prev;
      prev->next__ = next;
      delete forErase;
      size__--;
      return iterator(next);
    }
  }
};
} // namespace  dlist
#endif // DLIST_H
