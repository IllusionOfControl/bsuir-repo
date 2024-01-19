package org.example;

public class Memory {
    private final int memorySize;
    private int memoryFree;

    public Memory(int memorySize) {
        this.memorySize = memorySize;
        this.memoryFree = memorySize;
    }

    public boolean isFree() {
        return memoryFree > 0;
    }

    public boolean isEmpty() {
        return memoryFree == memorySize;
    }

    public boolean push() {
        if (isFree()) {
            memoryFree--;
            return true;
        }
        return false;
    }

    public boolean pop() {
        if (!isEmpty()) {
            memoryFree++;
            return true;
        }
        return false;
    }
}