#include "glutils/sync.hpp"

#include "glutils/gl.hpp"

namespace GL {

Sync::Status Sync::clientWait(bool flush_commands, std::chrono::nanoseconds timeout) const
{
    return static_cast<Sync::Status>(glClientWaitSync(m_ptr.get(), flush_commands ? GL_SYNC_FLUSH_COMMANDS_BIT : 0,
                                                      timeout.count()));
}

void Sync::wait(std::chrono::nanoseconds timeout) const
{
    glWaitSync(m_ptr.get(), 0, timeout.count());
}

Sync createFenceSync()
{
    return Sync(glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0));
}

void Sync::DeleteSync::operator()(__GLsync *sync) const
{
    glDeleteSync(sync);
}

} // GL