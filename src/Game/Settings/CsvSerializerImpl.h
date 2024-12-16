#pragma once
#include "CsvSerializer.h"
#include "ICsvSerializer.h"

template <typename SerializeType>
class CsvSerializerImpl : public ICsvSerializer<SerializeType> {
public:
    SerializeType load(const std::string& configPath) override
    {
        return CsvSerializer::load<SerializeType>(configPath);
    }

    SerializeType loadAsync(const std::string& configPath) override
    {
        return CsvSerializer::loadAsync<SerializeType>(configPath);
    }

    void update(const SerializeType& serialize, const std::string& configPath) override
    {
        CsvSerializer::update<SerializeType>(serialize, configPath);
    }

    void updateAsync(const SerializeType& serialize, const std::string& configPath) override
    {
        CsvSerializer::updateAsync<SerializeType>(serialize, configPath);
    }
};
