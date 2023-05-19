#pragma once

#include <string>

namespace ModernChess
{
    class UCICommunication
    {
    public:
        void startCommunication();

    private:
        static void registerToUI();
        static void sendAcknowledgeToUI();

        static void getInput(std::string &uiCommand);
    };
}