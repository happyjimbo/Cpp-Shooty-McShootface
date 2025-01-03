#pragma once
#include <array>

template <typename T, size_t Size>
class CircularBuffer {
public:

    explicit CircularBuffer() = default;
    ~CircularBuffer() = default;

    CircularBuffer(const CircularBuffer&) = delete;
    CircularBuffer& operator=(const CircularBuffer&) = delete;

    CircularBuffer(CircularBuffer&&) = delete;
    CircularBuffer& operator=(CircularBuffer&&) = delete;

    void push_back(T value) {
        mData[mIndex] = value;
        mIndex = (mIndex + 1) % Size;
        if (mSize < Size) {
            ++mSize;
        }

        mMaxValue = (mSize == 1) ? value : std::max(mMaxValue, value);
    }

    const std::array<T, Size>& data() const { return mData; }

    size_t size() const { return mSize; }
    T maxValue() const { return mMaxValue; }

    std::array<T, Size>::const_iterator begin() const { return mData.begin(); }
    std::array<T, Size>::const_iterator end() const { return mData.begin() + mSize; }

private:
    std::array<T, Size> mData{};
    size_t mIndex = 0;
    size_t mSize = 0;
    T mMaxValue = T{};
};