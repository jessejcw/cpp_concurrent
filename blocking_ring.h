//
// Created by jessejcw@gmail.com on 2/28/17.
//

#ifndef BLOCKING_RING_H
#define BLOCKING_RING_H

#include <mutex>
#include <condition_variable>

// concurrent ring buffer
template <typename T, int SZ, typename ST=int>
class blocking_ring {
    typedef T   VALUE_T;
    typedef ST  SIZE_T;
    std::mutex  m_mutex;
    std::condition_variable m_cond;


protected:
    VALUE_T   m_buffer[SZ];
    SIZE_T   m_size;
    SIZE_T   m_front;
    SIZE_T   m_back;
public:
    blocking_ring() {
        std::unique_lock<std::mutex> mlock(m_mutex);
        clear();
    }
    ~blocking_ring(){}

    void push(const VALUE_T& x) {
        std::unique_lock<std::mutex> mlock(m_mutex);
        push();
        back() = x;
        mlock.unlock();
        m_cond.notify_one();
    }
    void pop() {
        std::unique_lock<std::mutex> mlock(m_mutex);
        while ( m_size == 0) {
            m_cond.wait(mlock);
        }
        m_size--;
        m_front = (m_front+1) % SZ;
    }
    void back_erase(const SIZE_T n) {
        std::unique_lock<std::mutex> mlock(m_mutex);
        if (n >= m_size)
            clear();
        else {
            m_size -= n;
            m_back = (m_front + m_size -1) % SZ;
        }
    }
    void front_erase(const SIZE_T n) {
        std::unique_lock<std::mutex> mlock(m_mutex);
        if (n >= m_size)
            clear();
        else {
            m_size -= n;
            m_front = (m_front+n)  % SZ;
        }
    }

private:
    SIZE_T   size()     const {return m_size;}
    SIZE_T   max_size() const { return SZ;}
    bool    empty()    const { return m_size == 0;}
    bool    full()     const { return m_size == SZ;}
    VALUE_T&  front()   { return m_buffer[m_front];}
    VALUE_T&  back()    { return m_buffer[m_back];}

    void clear() {
        m_size = 0;
        m_front = 0;
        m_back = SZ-1;
    }

    void push() {
        m_back = (m_back+1) % SZ;
        if (size() == SZ) {
            m_front = (m_front + 1) % SZ;
        } else {
            m_size++;
        }
    }
};


#endif //BLOCKING_RING
