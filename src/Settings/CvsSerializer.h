#pragma once

#include <string>
#include <iostream>
#include "rapidcsv.h"

#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>

class CvsSerializer final {
    public:
    template<typename SerializeType>
    static SerializeType load(const std::string& configPath)
    {
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
    static void update(const SerializeType& serialize, const std::string& configPath)
    {
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

};