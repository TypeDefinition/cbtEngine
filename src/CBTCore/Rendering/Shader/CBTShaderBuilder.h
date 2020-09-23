#pragma once

// Include CBT
#include "CBTShaderProgram.h"
#include "Core/General/CBTLibrary.h"
#include "Core/FileUtil/CBTFileUtil.h"

// Include STD
#include <unordered_map>

NS_CBT_BEGIN

class CBTShaderBuilder
{
private:
    CBTShaderBuilder() {}
    ~CBTShaderBuilder() {}

public:
    // Shader Creation
    static CBTShaderProgram* CreateShaderProgram(const cbtStr& _name, std::vector<cbtStr> _vertexShaderFiles, std::vector<cbtStr> _fragmentShaderFiles)
    {
        std::vector<cbtStr> vertexShaderSources, fragmentShaderSources;
        for (cbtU32 i = 0; i < _vertexShaderFiles.size(); ++i) { vertexShaderSources.push_back(CBTFileUtil::FileToString(_vertexShaderFiles[i])); }
        for (cbtU32 i = 0; i < _fragmentShaderFiles.size(); ++i) { fragmentShaderSources.push_back(CBTFileUtil::FileToString(_fragmentShaderFiles[i])); }
        return CBTShaderProgram::CreateShaderProgram(_name, vertexShaderSources, fragmentShaderSources);
    }
};

NS_CBT_END 