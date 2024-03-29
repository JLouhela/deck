#include <algorithm>
#include <deque>
#include <iterator>
#include <random>

namespace jlo
{

template <typename T, typename Container = std::deque<T>>
class Deck
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using difference_type = typename Container::difference_type;
    using size_type = typename Container::size_type;

    // Add value to top of the deck
    // @param[in] value
    void add(const T& value)
    {
        m_container.push_back(value);
    }

    // Add value to top of the deck
    // @param[in] value
    void add(T&& value)
    {
        m_container.push_back(std::move(value));
    }

    // Remove topmost value from the deck and return a copy of it
    // Behavior is undefined if the deck is empty
    // @return topmost value of the deck
    T draw()
    {
        T value = std::move(m_container.back());
        m_container.pop_back();
        return value;
    }

    // Get value from the top of the deck
    // Behavior is undefined if the deck is empty
    // @return topmost value of the deck
    const T& top() const
    {
        return m_container.back();
    }

    // Get value from the top of the deck
    // Behavior is undefined if the deck is empty
    // @return topmost value of the deck
    T& top()
    {
        return m_container.back();
    }

    // Get value from the bottom of the deck
    // Behavior is undefined if the deck is empty
    // @return bottom value of the deck
    const T& bottom() const
    {
        return m_container.front();
    }

    // Get value from the bottom of the deck
    // Behavior is undefined if the deck is empty
    // @return bottom value of the deck
    T& bottom()
    {
        return m_container.front();
    }

    // Get number of values stored in the deck
    // @return Number of values in the deck
    std::size_t size()
    {
        return m_container.size();
    }

    // Get maximum supported capacity of the deck
    // @return amount of values that deck can store
    std::size_t max_size()
    {
        return m_container.max_size();
    }

    // Check if container contains any values
    // @return true if container is empty
    bool empty()
    {
        return m_container.empty();
    }

    // Get iterator to first value in the deck
    // Equal to end if deck is empty
    // @return iterator
    iterator begin()
    {
        return m_container.begin();
    }

    // Get iterator to first value in the deck
    // Equal to end() if deck is empty
    // @return iterator
    const_iterator begin() const
    {
        return m_container.begin();
    }

    // Get const iterator to first value in the deck
    // Equal to cend() if deck is empty
    // @return const iterator
    const_iterator cbegin() const
    {
        return m_container.begin();
    }

    // Get iterator beyond the last value in the deck
    // @return iterator after the last value in the deck
    iterator end()
    {
        return m_container.end();
    }

    // Get iterator beyond the last value in the deck
    // @return iterator after the last value in the deck
    const_iterator end() const
    {
        return m_container.end();
    }

    // Get const iterator beyond the last value in the deck
    // @return const iterator after the last value in the deck
    const_iterator cend() const
    {
        return m_container.cend();
    }

    // Reorder values in the deck
    // Requires random number generator to be provided by the caller
    // param[in] urbg - an object filling UniformRandomBitGenerator requirements (i.e. std::mt19937)
    template <typename URBG>
    void shuffle(URBG&& urbg)
    {
        std::shuffle(m_container.begin(), m_container.end(), std::forward<URBG>(urbg));
    }

    friend bool operator==(const Deck<T, Container>& lhs, const Deck<T, Container>& rhs)
    {
        return lhs.m_container == rhs.m_container;
    }

    friend bool operator!=(const Deck<T, Container>& lhs, const Deck<T, Container>& rhs)
    {
        return lhs.m_container != rhs.m_container;
    }

private:
    Container m_container;
};

}  // namespace jlo
