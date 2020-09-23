#pragma once

// Include CBT
#include "CBTMacros.h"

// Include STD
#include <vector>
#include <utility>

NS_CBT_BEGIN

template <typename T>
class CBTFixedArray;

template <typename T>
class CBTDynamicArray;

/**
    \brief An template array of fixed size.
*/
template <typename T>
class CBTFixedArray
{
private:
    /// The number of elements in the array.
    cbtU32 m_Count;
    /// A pointer to the array.
    T* m_Array;

public:
    /**
        \brief Copy constructor.

        \param _other The CBTFixedArray to copy.

        \return A CBTFixedArray of size _count.
    */
    CBTFixedArray(const CBTFixedArray& _other)
    {
        m_Count = _other.GetCount();
        m_Array = cbtNew T[m_Count];
        for (cbtU32 i = 0; i < m_Count; ++i) { m_Array[i] = _other.m_Array[i]; }
    }
    /**
        \brief Constructs a CBTFixedArray of size _count.

        \param _count The number of elements in the array.

        \return A CBTFixedArray of size _count.
    */
    CBTFixedArray(cbtU32 _count) : m_Array(cbtNew T[_count]) {}
    /// Destructor
    ~CBTFixedArray() { delete[] m_Array; }

    /**
        \brief Get the number of elements in the array.

        \return The number of elements in the array.
    */
    inline cbtU32 GetCount() const { return m_Count;  }

    /**
        \brief Get the nth element of the array specified by _index.

        \return The nth element of the array specified by _index.

        \sa MemCpy(const CBTFixedArray& _other), operator=(const CBTFixedArray& _other)
    */
    inline const T& operator[](cbtS32 _index) const { return m_Array[_index]; }
    /**
        \brief Get the nth element of the array specified by _index.

        \return The nth element of the array specified by _index.

        \sa MemCpy(const CBTFixedArray& _other), operator=(const CBTFixedArray& _other)
    */
    inline T& operator[](cbtS32 _index) { return m_Array[_index]; }
    /**
        \brief
            Delete the current array and become a copy of another CBTFixedArray.
            This function copys the array element by element using the assignment operator.
            Use this for classes that cannot be shallow copied. It is safer to use this function instead of MemCpy(const CBTFixedArray& _other).

        \return The current CBTFixedArray after copying another CBTFixedArray _other.

        \sa MemCpy(const CBTFixedArray& _other), operator[](cbtS32 _index)
    */
    CBTFixedArray& operator=(const CBTFixedArray& _other)
    {
        delete[] m_Array;
        m_Count = _other.GetCount();
        m_Array = cbtNew T[m_Count];
        for (cbtU32 i = 0; i < m_Count; ++i) { m_Array[i] = _other.m_Array[i]; }

        return *this;
    }
    /**
        \brief
            Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
            This function copys the array by doing a direct copy of the memory of _other's m_Array to this CBTFixedArray's m_Array.
            It is safe to use this when copying basic data types or classes which can be shallow copied. Otherwise, use operator=(const CBTFixedArray& _other).

        \return The current CBTFixedArray after copying another CBTFixedArray _other.

        \sa operator=(const CBTFixedArray& _other), operator[](cbtS32 _index)
    */
    CBTFixedArray& MemCpy(const CBTFixedArray& _other)
    {
        delete[] m_Array;
        m_Count = _other.GetCount();
        m_Array = cbtNew T[m_Count];
        std::memcpy(m_Array, _other.m_Array, sizeof(T) * m_Count);

        return *this;
    }
};

/**
    \brief A template array of dynamic size.
*/
template <typename T>
class CBTDynamicArray
{
private:
    /// The dynamic array. Eventually I will implement my own dynamic array instead of just a wrapper.
    std::vector<T> m_Array; // TODO: Implement my own dynamic array when I have time.

public:
    /**
        \brief Constructor

        \return A CBTDynamicArray
    */
    CBTDynamicArray() {}
    /**
        \brief Destructor
    */
    ~CBTDynamicArray() {}

    /**
        \brief Get the number of elements in the array.

        \return The number of elements in the array.
    */
    inline cbtU32 GetCount() { return m_Array.size(); }

    /**
        \brief Get the nth element of the array specified by _index.

        \return The nth element of the array specified by _index.

        \sa operator=(const CBTFixedArray& _other)
    */
    inline const T& operator[](cbtS32 _index) const { return m_Array[_index]; }
    /**
        \brief Get the nth element of the array specified by _index.

        \return The nth element of the array specified by _index.

        \sa operator=(const CBTFixedArray& _other)
    */
    inline T& operator[](cbtS32 _index) { return m_Array[_index]; } 
    /**
        \brief Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

        \return The current CBTFixedArray after copying another CBTFixedArray _other.

        \sa operator=(const CBTFixedArray& _other), operator[](cbtS32 _index)
    */
    inline T& operator=(const CBTDynamicArray& _other)
    {
        m_Array = _other.m_Array;
        return {*this};
    }

    /**
        \brief Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.

        \param _value The element to add.
    */
    void PushBack(const T& _value) { m_Array.push_back(_value); }
    /**
        \brief Removes the last element in the vector, effectively reducing the container size by one. This destroys the removed element.
    */
    void PopBack() { m_Array.pop_back(); }
    /**
        \brief The vector is extended by inserting a new element before the element at the specified position.

        \param _index The postition to insert the element.
        \param _value The element to add.
    */
    void Insert(cbtU32 _index, const T& _value) { m_Array.insert(m_Array.begin() + _index, _value); }
    /**
        \brief Removes from the vector the element at position _index.

        \param _index The postition to remove the element.
    */
    void Remove(cbtU32 _index) { m_Array.erase(m_Array.begin() + _index); }

    /**
        \brief Make a copy of a CBTFixedArray as a CBTDynamicArray.

        \param _fixedArray The CBTFixedArray to copy.

        \return A CBTDynamicArray copy of CBTFixedArray _fixedArray.
    */
    friend CBTDynamicArray<T> GetDynamicArray(CBTFixedArray<T>& _fixedArray)
    {
        CBTDynamicArray<T> dynamicArray;
        for (cbtU32 i = 0; i < _fixedArray.GetCount(); ++i) { dynamicArray.PushBack(_fixedArray[i]); }
        return dynamicArray;
    }
    /**
        \brief Make a copy of a CBTDynamicArray as a CBTFixedArray.

        \param _dynamicArray The CBTDynamicArray to copy.

        \return A CBTFixedArray copy of CBTDynamicArray _dynamicArray.
    */
    friend CBTFixedArray<T> GetFixedArray(CBTDynamicArray<T>& _dynamicArray)
    {
        CBTFixedArray<T> fixedArray(_dynamicArray.GetCount());
        for (cbtU32 i = 0; i < fixedArray.GetCount(); ++i) { fixedArray[i] = _dynamicArray[i]; }
        return fixedArray;
    }
};

NS_CBT_END