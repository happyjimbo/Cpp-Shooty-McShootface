#pragma once

#include "CsvSerializerImpl.h"
#include "GameSettingsData.h"

class MockCsvSerializer : public CsvSerializerImpl<GameSettingsData>
{
public:
    MOCK_METHOD(GameSettingsData, load, (const std::string& configPath), (override));
    MOCK_METHOD(GameSettingsData, loadAsync, (const std::string& configPath), (override));
    MOCK_METHOD(void, update, (const GameSettingsData& serialize, const std::string& configPath), (override));
    MOCK_METHOD(void, updateAsync, (const GameSettingsData& serialize, const std::string& configPath), (override));
};
