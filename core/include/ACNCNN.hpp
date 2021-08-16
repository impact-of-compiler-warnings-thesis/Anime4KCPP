#pragma once

#ifdef ENABLE_NCNN

#include"NCNNACNet.hpp"
#include"ACManager.hpp"

namespace Anime4KCPP
{
    namespace NCNN
    {
        class AC_EXPORT Manager;

        struct AC_EXPORT GPUList;

        //return platforms, devices of each platform, all devices information
        AC_EXPORT GPUList listGPUs() noexcept;
    }

    namespace Processor
    {
        template<>
        struct GetManager<NCNN::ACNet> {
            using Manager = NCNN::Manager;
        };
    }
}

class Anime4KCPP::NCNN::Manager : public Anime4KCPP::Processor::Manager
{
public:
    Manager(std::string modelPath, std::string paramPath, int dID = -1, CNNType type = CNNType::Default, int threads = std::thread::hardware_concurrency());
    Manager(int dID = -1, CNNType type = CNNType::Default, int threads = std::thread::hardware_concurrency()) noexcept;
    void init() override;
    void release() noexcept override;
    bool isInitialized() noexcept override;
    bool isSupport() noexcept override;
    const char* name() noexcept override { return "NCNN Processor Manager"; };

private:
    bool testFlag;
    int dID, threads;
    int currACNetType;
    std::string modelPath, paramPath;
};

struct Anime4KCPP::NCNN::GPUList
{
    int devices;
    std::string message;

    GPUList(int devices, std::string message);
    std::string& operator()() noexcept;
};

#endif
