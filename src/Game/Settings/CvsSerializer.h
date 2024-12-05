#pragma once

#include <string>

class CvsSerializer final {
public:
    template<typename SerializeType>
    static SerializeType load(const std::string& configPath);

    template<typename SerializeType>
    static void update(const SerializeType& serialize, const std::string& configPath);
};

#include "CvsSerializer.inl"