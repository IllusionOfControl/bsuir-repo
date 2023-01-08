#include "Thread.h"


std::wstring Thread::GetFormatedWorkTime() {
    FILETIME ft_start, ft_end, unused, delta;
    GetThreadTimes(_hThread, &ft_start, &unused, &unused, &unused);
    GetSystemTimeAsFileTime(&ft_end);

    delta.dwHighDateTime = ft_end.dwHighDateTime - ft_start.dwHighDateTime;
    delta.dwLowDateTime = ft_end.dwLowDateTime - ft_start.dwLowDateTime;

    // Convert 100ns units to double seconds.
    double secs = delta.dwHighDateTime * 429.496 + delta.dwLowDateTime / 1E7;
    return std::to_wstring(secs);
}


DWORD Thread::GetId() {
    return GetThreadId(_hThread);
}


std::wstring Thread::GetTextState() {
    switch (_state)
    {
    case ThreadState::RUNNABLE:
        return L"Runnable";
        break;
    case ThreadState::CREATED_SUSPENDED:
        return L"Created suspended";
        break;
    case ThreadState::SUSPENDED:
        return L"Suspended";
        break;
    default:
        break;
    }
    return L"";
}


DWORD Thread::GetPriority() {
    return GetThreadPriority(_hThread);
}


std::wstring Thread::GetTextDescriptor() {
    return std::to_wstring((int) _hThread);
}


BOOL Thread::SuspendWorkedThread() {
    if (_state == ThreadState::RUNNABLE) {
        _state = ThreadState::SUSPENDED;
        SuspendThread(_hThread);
        std::cout << "Thread 1 suspended" << std::endl;
        return TRUE;
    }
    return FALSE;
}

BOOL Thread::TerminateWorkThread() {
    if (_state == ThreadState::RUNNABLE || _state == ThreadState::SUSPENDED) {
        _state = ThreadState::TERMINATED;
        TerminateThread(_hThread, 0);
        std::cout << "Thread 1 terminated" << std::endl;
        return TRUE;
    }
    return FALSE;
}

BOOL Thread::ResumeWorkThread() {
    if (_state == ThreadState::SUSPENDED || _state == ThreadState::CREATED_SUSPENDED) {
        _state = ThreadState::RUNNABLE;
        std::cout << "Thread 1 resumed" << std::endl;
        ResumeThread(_hThread);
        return TRUE;
    }
    return FALSE;
}




MainThread::MainThread() {
    _hThread = GetCurrentThread();
    _state = ThreadState::RUNNABLE;
}

BOOL MainThread::SuspendWorkedThread() {
    return FALSE;
}

BOOL MainThread::TerminateWorkThread() {
    return FALSE;
}