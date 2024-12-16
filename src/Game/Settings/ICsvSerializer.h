#pragma once

template<typename SerializeType>
class
ICsvSerializer {
public:
    virtual ~ICsvSerializer() = default;
    virtual SerializeType load(const std::string& configPath) = 0;
    virtual SerializeType loadAsync(const std::string& configPath) = 0;
    virtual void update(const SerializeType& serialize, const std::string& configPath) = 0;
    virtual void updateAsync(const SerializeType& serialize, const std::string& configPath) = 0;
};
