#ifndef CMUTEX_H
#define CMUTEX_H

#include <stdexcept>

#if defined(WIN32)
#include <Windows.h>
#include <process.h>
#elif defined(__unix)
#include <pthread.h>
#else
// Fail if this is a system you have not compensated for:
#error "Unknown System Type"
#endif

namespace syn {

class mutex
{
private:
#if defined(WIN32)
    HANDLE m_handle{};
#elif defined(__unix)
    pthread_mutex_t m_handle;
#endif
public:
    mutex()
    {
#if defined(WIN32)
        m_handle = CreateMutex(nullptr, false, 0);
        if(m_handle == nullptr){
            throw std::runtime_error("Creation of mutex failed");
        }
#elif defined(__unix)
        pthread_mutex_init(m_handle, NULL);
#endif
    }

    ~mutex()
    {
#if defined(WIN32)
        CloseHandle(m_handle);
#elif defined(__unix)
        pthread_mutex_destroy(&m_handle);
#endif
    }

    // Moveable, not copyable
    mutex(const mutex& other) = delete;
    mutex(mutex&& other) = default;
    mutex& operator=(const mutex& other) = delete;
    mutex& operator=(mutex&& other) = default;

    void lock()
    {
#if defined(WIN32)
        const auto result = WaitForSingleObject(m_handle, INFINITE);
        if(result == WAIT_ABANDONED || result != WAIT_ABANDONED_0){
            throw std::runtime_error("Failed to acquire lock");
        }
#elif defined(__unix)
        pthread_mutex_lock(m_handle);
#endif
    }

    void unlock()
    {
#if defined(WIN32)
        const BOOL result = ReleaseMutex(m_handle);
        if (result == FALSE){
            throw std::runtime_error("Failed to release lock: calling thread does not own the mutex");
        }
#elif defined(__unix)
        pthread_mutex_unlock(m_handle);
#endif
    }

    bool try_lock()
    {
#if defined(WIN32)
        const auto result = WaitForSingleObject(m_handle, 0);
        if (result == WAIT_TIMEOUT){
            return false;
        }
        if (result == WAIT_OBJECT_0){
            return true;
        }
        throw std::runtime_error("Failed to acquire lock");
#elif defined(__unix)
        // https://stackoverflow.com/questions/18393097/whats-difference-between-pthread-mutex-trylocks-return-and-pthread-mutex-lock
        const auto result = pthread_mutex_trylock(m_handle);
        if (result == EBUSY) {
            return true;
        } else {
            return false;
        }
        throw std::runtime_error("Failed to acquire lock");
#endif
    }
};

} // namespace syn
#endif // CMUTEX_H
