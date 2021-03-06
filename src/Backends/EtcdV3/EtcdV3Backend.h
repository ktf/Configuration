/// \file EtcdBackend.h
/// \brief Definition of configuration interface to the etcd distributed key-value store using the v3 API
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#ifndef ALICEO2_CONFIGURATION_SRC_BACKENDS_ETCDV3_ETCDV3BACKEND_H_
#define ALICEO2_CONFIGURATION_SRC_BACKENDS_ETCDV3_ETCDV3BACKEND_H_

#include <iostream>
#include <memory>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include "../BackendBase.h"
#include "proto/rpc.grpc.pb.h"
//#include "InfoLogger/InfoLogger.hxx"

namespace AliceO2
{
namespace Configuration
{
namespace Backends
{

/// Backend for etcd with the v3 API.
class EtcdV3Backend final : public BackendBase
{
  public:
    EtcdV3Backend(const std::string& host, int port);
    virtual void putString(const std::string& path, const std::string& value) override;
    virtual Optional<std::string> getString(const std::string& path) override;
    virtual void setPrefix(const std::string& path) override;
    virtual auto getRecursive(const std::string& path) -> Tree::Node override;

  private:
    auto replaceSeparator(const std::string& path) -> std::string;
    auto addPrefix(const std::string& path) -> std::string;
    auto makeChannelString(const std::string& host, int port) -> std::string;

    std::string mPrefix;
    std::shared_ptr<grpc::Channel> mChannel;
    std::unique_ptr<etcdserverpb::KV::Stub> mStub;
    //InfoLogger::InfoLogger mLogger;
};

} // namespace Backends
} // namespace Configuration
} // namespace AliceO2

#endif // ALICEO2_CONFIGURATION_SRC_BACKENDS_ETCDV3_ETCDV3BACKEND_H_
