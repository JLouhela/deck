#include <vector>

template <typename T, typename Container = std::vector<T>>
class Deck
{
public:
    
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

    
private:
   Container m_container; 
};