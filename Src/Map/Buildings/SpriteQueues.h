#pragma once

#include <cstdint>
#include <memory>
#include <deque>
#include <mutex>
#include <string>
#include <utility>

namespace MiniMapBuildingCache { struct Sprite; }

namespace MiniMapSpriteQueues
{
    struct Feedback
    {
        std::string BlueprintPath;
        bool Success = false;
        uint64_t Session = 0;
        // Optional owned immutable CPU pixels, never a native/readback pointer.
        // Kept in this existing completion queue and the bounded draw handoff.
        std::shared_ptr<const MiniMapBuildingCache::Sprite> Payload;
    };

    class SpriteFifo
    {
    public:
        void Add(std::string blueprintPath)
        {
            std::lock_guard<std::mutex> lock(Mutex);
            Items.push_back(std::move(blueprintPath));
        }

        bool HasPending()
        {
            std::lock_guard<std::mutex> lock(Mutex);
            return !Items.empty();
        }

        bool Remove(std::string& blueprintPath)
        {
            std::lock_guard<std::mutex> lock(Mutex);
            if (Items.empty()) return false;
            blueprintPath = std::move(Items.front());
            Items.pop_front();
            return true;
        }

        // Removes the lowest-ranked entry; ties keep queue order. Rank runs
        // under the queue mutex and must not call back into this queue.
        template<class Rank> bool RemoveLowest(std::string& blueprintPath, const Rank& rank)
        {
            std::lock_guard<std::mutex> lock(Mutex);
            if (Items.empty()) return false;
            auto best = Items.begin();
            auto bestRank = rank(*best);
            for (auto it = best + 1; it != Items.end(); ++it)
                if (const auto itemRank = rank(*it); itemRank < bestRank) { best = it; bestRank = itemRank; }
            blueprintPath = std::move(*best);
            Items.erase(best);
            return true;
        }

    private:
        std::mutex Mutex;
        std::deque<std::string> Items;
    };

    class SpriteFeedbackQueue
    {
    public:
        void Add(Feedback feedback)
        {
            std::lock_guard<std::mutex> lock(Mutex);
            Items.push_back(std::move(feedback));
        }

        bool Remove(Feedback& feedback)
        {
            std::lock_guard<std::mutex> lock(Mutex);
            if (Items.empty()) return false;
            feedback = std::move(Items.front());
            Items.pop_front();
            return true;
        }

    private:
        std::mutex Mutex;
        std::deque<Feedback> Items;
    };
}
