#pragma once

// Include CBT
#include "cbtShaderProgram.h"
#include "Core/General/cbtLibrary.h"
#include "Core/FileUtil/cbtFileUtil.h"

// Include STD
#include <unordered_map>

NS_CBT_BEGIN

    class cbtShaderBuilder
    {
    private:
        cbtShaderBuilder()
        {
        }

        ~cbtShaderBuilder()
        {
        }

    public:
        // Shader Creation
        static cbtShaderProgram* CreateShaderProgram(const cbtStr& _name, std::vector<cbtStr> _vertexShaderFiles,
                std::vector<cbtStr> _fragmentShaderFiles)
        {
            std::vector<cbtStr> vertexShaderSources, fragmentShaderSources;
            for (cbtU32 i = 0; i < _vertexShaderFiles.size(); ++i)
            {
                vertexShaderSources.push_back(cbtFileUtil::FileToString(_vertexShaderFiles[i]));
            }
            for (cbtU32 i = 0; i < _fragmentShaderFiles.size(); ++i)
            {
                fragmentShaderSources.push_back(cbtFileUtil::FileToString(_fragmentShaderFiles[i]));
            }
            return cbtShaderProgram::CreateShaderProgram(_name, vertexShaderSources, fragmentShaderSources);
        }
    };

NS_CBT_END 