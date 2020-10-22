#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Debug/cbtDebug.h"

// Include STD
#include <vector>

NS_CBT_BEGIN

    enum cbtBufferUsage
    {
        CBT_STREAM_DRAW,
        CBT_STREAM_READ,
        CBT_STREAM_COPY,
        CBT_STATIC_DRAW,
        CBT_STATIC_READ,
        CBT_STATIC_COPY,
        CBT_DYNAMIC_DRAW,
        CBT_DYNAMIC_READ,
        CBT_DYNAMIC_COPY,
    };

    enum cbtBufferDataType
    {
        // 1 BYTE
        CBT_S8,
        CBT_U8,

        // 2 BYTES
        CBT_S16,
        CBT_U16,
        CBT_F16,

        // 4 BYTES
        CBT_S32,
        CBT_U32,
        CBT_F32,

        // 8 BYTES
        CBT_F64,
    };

    cbtU32 GetByteSize(cbtBufferDataType _dataType);

    class cbtBufferLayout;

    class cbtBufferElement
    {
        friend class cbtBufferLayout;

    private:
        const cbtBufferDataType m_DataType;
        const cbtU32 m_ComponentCount;
        const cbtBool m_Normalized;
        const cbtU32 m_ByteSize;
        cbtU32 m_Offset;

    public:
        inline cbtBufferDataType GetDataType() const
        {
            return m_DataType;
        }

        inline cbtU32 GetComponentCount() const
        {
            return m_ComponentCount;
        }

        inline cbtBool IsNormalized() const
        {
            return m_Normalized;
        }

        inline cbtU32 GetByteSize() const
        {
            return m_ByteSize;
        }

        inline cbtU32 GetOffset() const
        {
            return m_Offset;
        }

        cbtBufferElement(cbtBufferDataType _dataType, cbtU32 _componentCount, cbtBool _normalized)
                :m_DataType(_dataType), m_ComponentCount(_componentCount), m_Normalized(_normalized), m_Offset(0),
                 m_ByteSize(m_ComponentCount * NS_CBT::GetByteSize(_dataType))
        {
        }

        ~cbtBufferElement()
        {
        }
    };

    class cbtBufferLayout
    {
    private:
        cbtU32 m_ByteSize;
        std::vector<cbtBufferElement> m_Elements;

    public:
        cbtBufferLayout(const std::initializer_list<cbtBufferElement>& _elements)
                :m_ByteSize(0), m_Elements(_elements)
        {
            for (cbtS32 i = 0; i < m_Elements.size(); ++i)
            {
                m_Elements[i].m_Offset = m_ByteSize;
                m_ByteSize += m_Elements[i].m_ByteSize;
            }
        }

        ~cbtBufferLayout()
        {
        }

        inline cbtU32 GetElementCount() const
        {
            return static_cast<cbtU32>(m_Elements.size());
        }

        inline cbtU32 GetByteSize() const
        {
            return m_ByteSize;
        }

        inline const cbtBufferElement* GetElements() const
        {
            return m_Elements.empty() ? nullptr : &m_Elements[0];
        }
    };

NS_CBT_END