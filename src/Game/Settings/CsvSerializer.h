#pragma once

class CsvSerializer final {
public:
    template<typename SerializeType>
    static SerializeType load(const std::string& configPath);

    template<typename SerializeType>
    static SerializeType loadAsync(const std::string& configPath);

    template<typename SerializeType>
    static void update(const SerializeType& serialize, const std::string& configPath);

    template<typename SerializeType>
    static void updateAsync(const SerializeType& serialize, const std::string& configPath);
};

#include "CsvSerializer.inl"
