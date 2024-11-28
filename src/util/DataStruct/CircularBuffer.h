#pragma once

template <typename T, size_t Size>
class CircularBuffer {
public:
    void push_back(T value) {
        mData[mIndex] = value;
        mIndex = (mIndex + 1) % Size;
        if (mSize < Size) {
            ++mSize;
        }
    }

    const std::array<T, Size>& data() const { return mData; }

    size_t size() const { return mSize; }

    std::array<T, Size>::const_iterator begin() { return mData.begin(); }
    std::array<T, Size>::const_iterator end() { return mData.begin() + mSize; }

private:
    std::array<T, Size> mData{};
    size_t mIndex = 0;
    size_t mSize = 0;
};