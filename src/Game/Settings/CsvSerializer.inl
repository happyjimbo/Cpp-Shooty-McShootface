#include "CsvSerializer.h"

#include <iostream>
#include <future>
#include "rapidcsv.h"

#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <tracy/Tracy.hpp>

template<typename SerializeType>
SerializeType CsvSerializer::loadAsync(const std::string& configPath)
{
    ZoneScopedN("CvsSerializer::loadAsync");

    std::future<SerializeType> futureLoad = std::async(std::launch::async, &load<SerializeType>, configPath);
    SerializeType result = futureLoad.get();
    return result;
}

template<typename SerializeType>
SerializeType CsvSerializer::load(const std::string& configPath)
{
    ZoneScopedN("CvsSerializer::load");

    SerializeType serialize;
    try
    {
        std::cout << "CvsSerializer::load" << std::endl;

        const rapidcsv::Document doc(configPath);
        constexpr auto names = boost::pfr::names_as_array<SerializeType>();

        std::size_t idx = 0;
        boost::pfr::for_each_field(serialize, [&idx, &names, &doc]<typename T>(T& field)
        {
            const auto fieldName = std::string(names[idx]);

            if constexpr (std::is_same_v<T, bool>)
            {
                field = doc.GetCell<std::string>(fieldName, 0) == "true";
            }
            else
            {
                field = doc.GetCell<T>(fieldName, 0);
            }

            std::cout << idx
            << " : "
            << fieldName
            << " - "
            << typeid(T).name()
            << " = "
            << field << std::endl;

            ++idx;
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error while deserialising " << e.what() << std::endl;
    }
    return serialize;
}

template<typename SerializeType>
void CsvSerializer::updateAsync(const SerializeType& serialize, const std::string& configPath)
{
    ZoneScopedN("CvsSerializer::updateAsync");
    const std::future<void> future = std::async(std::launch::async, &update<SerializeType>, serialize, configPath);
    future.wait();
}

template<typename SerializeType>
void CsvSerializer::update(const SerializeType& serialize, const std::string& configPath)
{
    ZoneScopedN("CvsSerializer::update");
    try
    {
        std::cout << "CvsSerializer::update" << std::endl;

        if (rapidcsv::Document doc(configPath); doc.GetRowCount() > 0)
        {
            constexpr auto names = boost::pfr::names_as_array<SerializeType>();

            std::size_t idx = 0;
            boost::pfr::for_each_field(serialize, [&idx, &names, &doc]<typename T>(T field)
            {
                const auto fieldName = std::string(names[idx]);

                std::cout << idx
                << " : "
                << fieldName
                << " - "
                << typeid(T).name()
                << " = "
                << field << std::endl;

                if constexpr (std::is_same_v<T, bool>)
                {
                    doc.SetCell<std::string>(doc.GetColumnIdx(fieldName), 0, field ? "true" : "false");
                }
                else
                {
                    doc.SetCell<T>(doc.GetColumnIdx(fieldName), 0, field);
                }

                ++idx;
            });

            doc.Save();
            std::cout << "Settings saved successfully!" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error whilst saving settings: " << e.what() << std::endl;
    }
}