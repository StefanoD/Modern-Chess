#pragma once

#include "GameState.h"
#include "Timer.h"
#include "PeriodicTask.h"

#include <string>
#include <istream>
#include <ostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

namespace ModernChess
{
    class UCIParser;

    class UCICommunication final
    {
        struct SearchRequest {
            GameState gameState{};
            std::atomic_int32_t depth{};
            std::chrono::milliseconds timeToSearch{};
            Timer<> timer{};
        };
    public:
        explicit UCICommunication(std::istream &inputStream, std::ostream &outputStream, std::ostream &errorStream);

        UCICommunication(const UCICommunication&) = delete;
        UCICommunication(UCICommunication&&) = delete;
        UCICommunication&operator=(const UCICommunication&) = delete;
        UCICommunication&operator=(UCICommunication&&) = delete;

        ~UCICommunication();

        void startCommunication();

        [[nodiscard]] GameState getGameState() const
        {
            const std::lock_guard lock(m_mutex);
            return m_searchRequest.gameState;
        }

    private:
        std::istream &m_inputStream;
        std::ostream &m_outputStream;
        std::ostream &m_errorStream;

        mutable std::mutex m_mutex;
        bool m_stopped = true;
        bool m_quit = false;
        Timer<> m_timeSinceSearchStarted{};
        WaitCondition m_waitForSearchRequest;
        SearchRequest m_searchRequest{};
        std::thread m_searchThread;

        void registerToUI();

        void sendAcknowledgeToUI();

        void getInput(std::string &uiCommand);

        void parsePosition(UCIParser &parser);

        Move executeMoves(UCIParser &parser);

        void executeGoCommand(UCIParser &parser);

        void createNewGame();

        void searchBestMove();

        void setGameState(GameState getGameState);

        void stopSearch();

        void quitGame();

        [[nodiscard]] bool searchHasBeenStopped() const;

        [[nodiscard]] bool gameHasBeenQuit() const;
    };
}