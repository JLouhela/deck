#include <iterator>
#include <vector>

template <typename T, typename Container = std::vector<T>>
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

    // Remove value from top of the deck and return a copy of it
    // Undefined behavior if the deck is empty
    // @return top value of the deck
    T draw()
    {
        T value = m_container.back();
        m_container.pop_back();
        return value;
    }

    // Peek top value of the deck
    // Undefined behavior if the deck is empty
    // @return top value of the deck
    const T& top() const
    {
        return m_container.back();
    }

    // Peek top value of the deck
    // Undefined behavior if the deck is empty
    // @return top value of the deck
    T& top()
    {
        return m_container.back();
    }

    // Peek bottom value of the deck
    // Undefined behavior if the deck is empty
    // @return bottom value of the deck
    const T& bottom() const
    {
        return m_container.front();
    }

    // Peek bottom value of the deck
    // Undefined behavior if the deck is empty
    // @return bottom value of the deck
    T& bottom()
    {
        return m_container.front();
    }

    // Get number of values in the deck
    // @return Number of values in the deck
    std::size_t size()
    {
        return m_container.size();
    }

    // Check if container contains any values
    // @return true if no container is empty
    bool empty()
    {
        return m_container.empty();
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
