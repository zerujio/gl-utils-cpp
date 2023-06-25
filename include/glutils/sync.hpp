#ifndef PROCEDURALPLACEMENTLIB_SYNC_HPP
#define PROCEDURALPLACEMENTLIB_SYNC_HPP

#include <chrono>
#include <memory>

struct __GLsync;

namespace GL {

/// A wrapper for a GL sync object.
class Sync
{
public:
    explicit Sync(__GLsync *sync) : m_ptr(sync)
    {}

    enum class Status
    {
        already_signaled = 0x911A,
        timeout_expired = 0x911B,
        condition_satisfied = 0x911C,
        wait_failed = 0x911D
    };

    /// wraps glClientWaitSync()
    [[nodiscard]]
    Status clientWait(bool flush_commands, std::chrono::nanoseconds timeout = std::chrono::nanoseconds::zero()) const;

    /// wraps glWaitSync()
    void wait(std::chrono::nanoseconds timeout = std::chrono::nanoseconds::zero()) const;

    /// get the native GLsync object pointer.
    [[nodiscard]]
    __GLsync *getPtr() const
    { return m_ptr.get(); }

private:
    struct DeleteSync
    {
        void operator()(__GLsync *sync) const;
    };

    std::unique_ptr<__GLsync, DeleteSync> m_ptr;
};

/// calls glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0) and returns the resulting sync object.
[[nodiscard]]
Sync createFenceSync();

} // GL

#endif //PROCEDURALPLACEMENTLIB_SYNC_HPP
