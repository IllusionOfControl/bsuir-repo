#pragma once

#include <Windows.h>
#include <string>
#include <iostream>


enum class ThreadState {
    RUNNABLE,
    CREATED_SUSPENDED,
    SUSPENDED,
    TERMINATED
};


class Thread {
protected:
    HANDLE _hThread;
    ThreadState _state;
    Thread() {}
public:
    ~Thread();

    static Thread* CreateRunnableThread(LPTHREAD_START_ROUTINE lpStartAddress) {
        Thread* t = new Thread();
        t->_hThread = CreateThread(NULL, 0, lpStartAddress, NULL, 0, NULL);
        t->_state = ThreadState::RUNNABLE;

        std::cout << "Thread 1 created" << std::endl;
        return t;
    }

    static Thread* CreateSuspendThread(LPTHREAD_START_ROUTINE lpStartAddress) {
        Thread* t = new Thread();
        t->_hThread = CreateThread(NULL, 0, lpStartAddress, NULL, CREATE_SUSPENDED, NULL);
        t->_state = ThreadState::CREATED_SUSPENDED;

        std::cout << "Thread 1 suspended created" << std::endl;

        return t;
    }

    virtual BOOL SuspendWorkedThread();
    virtual BOOL TerminateWorkThread();
    virtual BOOL ResumeWorkThread();

    std::wstring GetFormatedWorkTime();
    DWORD GetId();
    std::wstring GetTextState();
    DWORD GetPriority();
    std::wstring GetTextDescriptor();
};


class MainThread : public Thread {
public:
    MainThread();
    ~MainThread();

    BOOL SuspendWorkedThread() override;
    BOOL TerminateWorkThread() override;
};