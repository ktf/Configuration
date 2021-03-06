/// \file JsonBackend.cxx
/// \brief Implementation of configuration interface for JSON files
///
/// \author Pascal Boeschoten, CERN

#include "JsonBackend.h"
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include "JsonHandler.h"

namespace AliceO2
{
namespace Configuration
{
namespace Backends
{
namespace
{

auto jsonToTree(const std::string& json) -> Tree::Node
{
  rapidjson::Reader reader;
  rapidjson::StringStream ss(json.c_str());
  JsonHandler handler;
  reader.Parse(ss, handler);
  return Tree::keyValuesToTree(handler.keyValues);
}
} // Anonymous namespace

JsonBackend::~JsonBackend()
{
}

JsonBackend::JsonBackend(const std::string& filePath)
    : mFilePath(filePath)
{
  std::ifstream stream(filePath);
  std::string json((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  mRootNode = jsonToTree(json);
  mCurrentNode = mRootNode;
}

void JsonBackend::putString(const std::string&, const std::string&)
{
  throw std::runtime_error("JsonBackend does not support putting values");
}

auto JsonBackend::getString(const std::string& path) -> Optional<std::string>
{
  const Tree::Node& node = Tree::getSubtree(mRootNode, path);
  return Tree::get<std::string>(node);
}

auto JsonBackend::getRecursive(const std::string& path) -> Tree::Node
{
  const Tree::Node& node = Tree::getSubtree(mCurrentNode, path);
  return node;
}

void JsonBackend::setPrefix(const std::string& path)
{
  const Tree::Node& node = Tree::getSubtree(mRootNode, path);
  mCurrentNode = node;
}

} // namespace Backends
} // namespace Configuration
} // namespace AliceO2
