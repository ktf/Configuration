/// \file Get.cxx
/// \brief Command-line utility for getting values from a configuration backend
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include "Configuration/ConfigurationFactory.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
  bool help;
  std::string serverUri;
  std::string key;
  bool recursive;

  {
    auto optionsDescription = po::options_description("Options");
    optionsDescription.add_options()
        ("help", po::bool_switch(&help), "Print help")
        ("uri", po::value<std::string>(&serverUri)->required(), "Server URI")
        ("key,k", po::value<std::string>(&key)->required(), "Key to get value with")
        ("recursive,r", po::bool_switch(&recursive), "Recursive get");

    try {
      auto map = po::variables_map();
      po::store(po::parse_command_line(argc, argv, optionsDescription), map);
      po::notify(map);
      if (help) {
        std::cout << optionsDescription << '\n';
        return 0;
      }
    }
    catch (const po::error& e) {
      std::cout << "Error: " << e.what() << '\n' << optionsDescription << '\n';
      return 0;
    }
  }

  auto configuration = AliceO2::Configuration::ConfigurationFactory::getConfiguration(serverUri);
  if (recursive) {
    AliceO2::Configuration::Tree::printTree(configuration->getRecursive(key), std::cout);
  } else {
    std::cout << configuration->getString(key).value_or("Key did not exist") << '\n';
  }
  return 0;
}

