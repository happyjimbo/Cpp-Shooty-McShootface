#pragma once

// ICsvSerializer exists so that we can use gmock on the CsvSerializer in our tests
template<typename SerializeType>
class ICsvSerializer {
public:
    virtual ~ICsvSerializer() = default;
    virtual SerializeType load(const std::string& configPath) = 0;
    virtual SerializeType loadAsync(const std::string& configPath) = 0;
    virtual void update(const SerializeType& serialize, const std::string& configPath) = 0;
    virtual void updateAsync(const SerializeType& serialize, const std::string& configPath) = 0;
};

template <typename SerializeType>
class CsvSerializer : public ICsvSerializer<SerializeType> {
public:
    SerializeType load(const std::string& configPath) override;
    SerializeType loadAsync(const std::string& configPath) override;
    void update(const SerializeType& serialize, const std::string& configPath) override;
    void updateAsync(const SerializeType& serialize, const std::string& configPath) override;
};


#include "CsvSerializer.inl"