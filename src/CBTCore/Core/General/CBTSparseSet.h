#pragma once

// Include CBT
#include "Debug/cbtDebug.h"

// Include STD
#include <vector>
#include <utility>

NS_CBT_BEGIN

/**
    \brief
        A paged sparse set of template type T. The maximum number of items it can hold is PAGE_COUNT * PARAGRAPH_COUNT.

        The sparse set contains 3 arrays.

        1. Sparse Array - A large which size is the maximum number of items the sparse set can hold. It is referred to as the "sparse" array.
           The elements of the sparse array is the index of the items in the dense array. For example, when store an item
           into the sparse set at index 5, it may be stored in the dense array at somewhere like index 8, so we will store
           the the value 8 in element 5 of the sparse array. We will also store the value 5 in element 8 of the dense array.

        2. Dense Index Array - A dense array, which size is that of the number of items in the sparse set.
           The elements of the sparse array is the index of the items in the sparse array. For example, when store an item
           into the sparse set at index 5, it may be stored in the dense array at somewhere like index 8, so we will store
           the the value 8 in element 5 of the sparse array. We will also store the value 5 in element 8 of the dense array.

        3. Dense Item Array - A dense array, which size is that of the number of items in the sparse set.
           The elements of the sparse array is the items in the sparse array. It must be in the same order as the Dense Index Array
           so that the item can be retrieved correctly.

        Since the sparse array may be quite large, we page it instead. This means that instead of a large 1D array, we have a 2D array of size PAGE_COUNT by PARAGRAPH_COUNT.
        If a page does not need to store any indices, we can delete it to save memory. Each element of a "page" is referred to as a "paragraph".
*/
template <class T, cbtU32 PAGE_COUNT, cbtU32 PARAGRAPH_COUNT>
class cbtSparseSet
{
    /// Dense Item Array
    std::vector<T> m_Items;
    /// Dense Index Array
    std::vector<cbtS32> m_Dense ;
    /// Sparse Array
    cbtS32* m_Sparse[PAGE_COUNT] = { 0 };
    /// An array containing the number of paragraphs in each page. Helps us keep track of when a page is empty so we can delete it to save memory.
    cbtS32 m_ParagraphCounter[PAGE_COUNT] = { 0 };

    /**
        \brief Given an index, find out which page (row) it is in.

        \param _index The index to check.

        \return The page the given index is in.
    */
    inline cbtS32 GetPage(cbtS32 _index) const { return _index / PARAGRAPH_COUNT; }
    /**
        \brief Given an index, find out which paragraph (column) it is in.

        \param _index The index to check.

        \return The paragraph the given index is in.
    */
    inline cbtS32 GetParagraph(cbtS32 _index) const { return _index % PARAGRAPH_COUNT; }

public:
    /// The maximum number of items the sparse set can contain.
    static constexpr cbtU32 MAX_COUNT = PAGE_COUNT * PARAGRAPH_COUNT;

    /**
        \brief Constructor

        \return A cbtSparseSet
    */
    cbtSparseSet() {}
    /**
        \brief Destructor. All items are destroyed.
    */
    ~cbtSparseSet() { Clear(); }

    /**
        \brief Clear the sparse set. All items are destroyed.
    */
    void Clear()
    {
        m_Items.clear();
        m_Dense.clear();
        for (cbtU32 i = 0; i < PAGE_COUNT; ++i)
        {
            if (m_Sparse[i]) { delete[] m_Sparse[i]; }
            m_Sparse[i] = nullptr;
        }

        std::memset(m_ParagraphCounter, 0, sizeof(m_ParagraphCounter));
    }

    /**
        \brief Checks if a index is valid.

        \param _index The index to check.

        \return Returns true if the index is between 0 (inclusive) and PARAGRAPH_COUNT * PAGE_COUNT (exclusive). Otherwise, return false.
    */
    cbtBool IsValid(cbtS32 _index) const
    {
        return (_index >= 0) && (_index < PARAGRAPH_COUNT * PAGE_COUNT);
    }

    /**
        \brief Checks if there is an item at a given index.

        \param _index The index to check.

        \return Returns true if an item exists at the given index. Otherwise, return false.
    */
    cbtBool Has(cbtS32 _index) const
    {
        if (!IsValid(_index)) { return false; }

        cbtS32 page = GetPage(_index);
        cbtS32 paragraph = GetParagraph(_index);
        return m_Sparse[page] ? (m_Sparse[page][paragraph] != -1) : false;
    }

    /**
        \brief Insert an item at the given index.

        \param _index The index to insert the item.
        \param _item The item to insert.
    */
    void Insert(cbtS32 _index, T& _item)
    {
        CBT_ASSERT(IsValid(_index));
        CBT_ASSERT(!Has(_index));

        cbtS32 page = GetPage(_index);
        cbtS32 paragraph = GetParagraph(_index);

        // Create the page if it does not exist.
        if (!m_Sparse[page])
        {
            m_Sparse[page] = cbtNew cbtS32[PARAGRAPH_COUNT];
            std::memset(m_Sparse[page], -1, sizeof(cbtS32) * PARAGRAPH_COUNT);
        }

        // Add the item to m_Items. Ensure that m_Dense is kept in sync.
        m_Items.push_back(_item);
        m_Dense.push_back(_index);
        m_Sparse[page][paragraph] = static_cast<cbtS32>(m_Dense.size() - 1);
        ++m_ParagraphCounter[page];
    }

    /**
        \brief Remove an item at the given index.

        \param _index The index to remove the item.
    */
    void Remove(cbtS32 _index)
    {
        CBT_ASSERT(Has(_index));

        // Get the denseIndex of the item we are removing.
        cbtS32 removePage = GetPage(_index);
        cbtS32 removeParagraph = GetParagraph(_index);
        cbtS32 denseIndex = m_Sparse[removePage][removeParagraph];
        m_Sparse[removePage][removeParagraph] = -1;

        // Overwrite the item we are removing with the last item in the dense array.
        m_Items[denseIndex] = m_Items.back();
        m_Dense[denseIndex] = m_Dense.back();
        // Delete the last item since we've already moved it.
        m_Items.pop_back();
        m_Dense.pop_back();

        // Since we've moved the last item, we need to update it's dense index in m_Sparse.
        cbtS32 sparseIndex = m_Dense[denseIndex];
        cbtS32 lastPage = GetPage(sparseIndex);
        cbtS32 lastParagraph = GetParagraph(sparseIndex);
        m_Sparse[lastPage][lastParagraph] = denseIndex;

        // If a page of m_Sparse is empty, delete it.
        --m_ParagraphCounter[removePage];
        if (m_ParagraphCounter[removePage] == 0)
        {
            delete[] m_Sparse[removePage];
            m_Sparse[removePage] = nullptr;
        }
    }

    /**
        \brief Get the number of items currently in the sparse set.

        \return The number of items currently in the sparse set.
    */
    inline cbtU32 GetCount() const { return static_cast<cbtU32>(m_Items.size()); }

    /**
        \brief Get a pointer to the dense item array.

        \return A pointer to the dense item array.
    */
    const T* GetArray() const { return m_Items.empty() ? nullptr : &m_Items[0]; }
    /**
        \brief Get a pointer to the dense item array.

        \return A pointer to the dense item array.
    */
    T* GetArray() { return m_Items.empty() ? nullptr : &m_Items[0]; }

    /**
        \brief Get a reference to the item at the specified index.

        \return A reference to the item at the specified index.
    */
    const T& operator[](cbtS32 _index) const
    {
        CBT_ASSERT(Has(_index));
        return m_Items[m_Sparse[GetPage(_index)][GetParagraph(_index)]];
    }
    /**
        \brief Get a reference to the item at the specified index.

        \return A reference to the item at the specified index.
    */
    T& operator[](cbtS32 _index)
    {
        CBT_ASSERT(Has(_index));
        return m_Items[m_Sparse[GetPage(_index)][GetParagraph(_index)]];
    }
};

NS_CBT_END