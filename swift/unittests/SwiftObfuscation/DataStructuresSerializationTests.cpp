#include "swift/Obfuscation/DataStructures.h"
#include "gtest/gtest.h"

using namespace swift::json;
using namespace llvm;

TEST(DataStructuresSerialization, SerializeSymbol) {
  Symbol Object("sampleIdentifier", "sampleName", "sampleModule");
  
  auto Serialized = serialize(Object);
  
  std::string Expected =
  "{\n"
  "  \"name\": \"sampleName\",\n"
  "  \"identifier\": \"sampleIdentifier\",\n"
  "  \"module\": \"sampleModule\"\n"
  "}";
  
  EXPECT_EQ(Serialized, Expected);
}

TEST(DataStructuresSerialization, SerializeSymbolsJson) {
  Symbol Symbol0("sampleIdentifier0", "sampleName0", "sampleModule0");
  Symbol Symbol1("sampleIdentifier1", "sampleName1", "sampleModule1");
  
  auto Object = SymbolsJson();
  Object.Symbols.push_back(Symbol0);
  Object.Symbols.push_back(Symbol1);
  
  auto Serialized = serialize(Object);
  
  std::string Expected =
  "{\n"
  "  \"symbols\": [\n"
  "    {\n"
  "      \"name\": \"sampleName0\",\n"
  "      \"identifier\": \"sampleIdentifier0\",\n"
  "      \"module\": \"sampleModule0\"\n"
  "    },\n"
  "    {\n      \"name\": \"sampleName1\",\n"
  "      \"identifier\": \"sampleIdentifier1\",\n"
  "      \"module\": \"sampleModule1\"\n"
  "    }\n"
  "  ]\n"
  "}";
  
  EXPECT_EQ(Serialized, Expected);
}

TEST(DataStructuresSerialization, SerializeSymbolRenaming) {
  SymbolRenaming Object("sampleIdentifier", "sampleName", "sampleObfuscatedName", "sampleModule");
  
  auto Serialized = serialize(Object);
  
  std::string Expected =
  "{\n"
  "  \"identifier\": \"sampleIdentifier\",\n"
  "  \"originalName\": \"sampleName\",\n"
  "  \"obfuscatedName\": \"sampleObfuscatedName\",\n"
  "  \"module\": \"sampleModule\"\n"
  "}";
  
  EXPECT_EQ(Serialized, Expected);
}


TEST(DataStructuresSerialization, SerializeRenamesJson) {
  SymbolRenaming Symbol0("sampleIdentifier0", "sampleName0", "sampleObfuscatedName0", "sampleModule0");
  SymbolRenaming Symbol1("sampleIdentifier1", "sampleName1", "sampleObfuscatedName1", "sampleModule1");
  
  auto Object = RenamesJson();
  Object.Symbols.push_back(Symbol0);
  Object.Symbols.push_back(Symbol1);
  
  auto Serialized = serialize(Object);
  
  std::string Expected =
  "{\n"
  "  \"symbols\": [\n"
  "    {\n"
  "      \"identifier\": \"sampleIdentifier0\",\n"
  "      \"originalName\": \"sampleName0\",\n"
  "      \"obfuscatedName\": \"sampleObfuscatedName0\",\n"
  "      \"module\": \"sampleModule0\"\n"
  "    },\n"
  "    {\n"
  "      \"identifier\": \"sampleIdentifier1\",\n"
  "      \"originalName\": \"sampleName1\",\n"
  "      \"obfuscatedName\": \"sampleObfuscatedName1\",\n"
  "      \"module\": \"sampleModule1\"\n"
  "    }\n"
  "  ]\n"
  "}";
  
  EXPECT_EQ(Serialized, Expected);
}


