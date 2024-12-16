#pragma once
#include "ICsvSerializer.h"

template <typename SerializeType>
class CsvSerializer : public ICsvSerializer<SerializeType> {
public:
    SerializeType load(const std::string& configPath) override;
    SerializeType loadAsync(const std::string& configPath) override;
    void update(const SerializeType& serialize, const std::string& configPath) override;
    void updateAsync(const SerializeType& serialize, const std::string& configPath) override;
};

#include "CsvSerializer.inl"