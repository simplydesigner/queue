#include <iostream>

struct foo
{
    std::size_t m_value;
    foo(std::size_t value) : m_value(value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    foo(foo const & other)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_value = other.m_value;
    }
    
    foo(foo && other)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_value = other.m_value;
    }
    
    foo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~foo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

template <typename T>
class queue
{
public:
    queue()
    {
    }
    
    queue(queue const & ) = delete;
    auto operator =(queue const &) -> queue & = delete;
    
    auto try_pop() -> std::shared_ptr<T>
    {
        if ( m_head ) {
            auto const result = std::make_shared<T>(std::move(m_head->data));
            m_head = std::move(m_head->next);
            return result;
        }
        else {
            return nullptr;
        }
    }
    
    template <typename U>
    auto push(U && new_value) -> void
    {
        std::unique_ptr<node> p { new node(new_value) };
        auto const new_tail = p.get();
        
        if ( m_tail ) {
            m_tail->next = std::move(p);
        }
        else {
            m_head = std::move(p);
        }
        
        m_tail = new_tail;
    }
private:
    struct node
    {
        T data;
        std::unique_ptr<node> next;
        
        template <typename U>
        node(U && p_data) : data(p_data)
        {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
    };
    std::unique_ptr<node> m_head;
    node * m_tail;
};

int main(int argc, const char * argv[]) {
    
    
    queue<foo> q;
    
    
    q.push(5);
    
    return 0;
}
