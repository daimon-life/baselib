class CaptionTimer {
 public:
  CaptionTimer(const char *prefix) {
    prefix_.assign(prefix);
    start_ = std::chrono::system_clock::now();
  }
  ~CaptionTimer() {
    end_ = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end_ - start_;
    std::string szDuration("");
    for (auto &it : duration_vector_) {
      if (szDuration.empty()) {
        szDuration =
            std::to_string((int)(it.count())) + std::string(".") + std::to_string((int)(it.count() * 100) % 100);
      } else {
        szDuration += std::string(",") + std::to_string((int)(it.count())) + std::string(".") +
                      std::to_string((int)(it.count() * 100) % 100);
      }
    }
    WESLog("performance", kLogLevelDebug, "module[%s]  cost[%.2f(%s)]ms", prefix_.c_str(), elapsed.count(),
           szDuration.c_str());
    duration_vector_.clear();
  }
  int Set() {
    std::chrono::time_point<std::chrono::system_clock> tmp_;
    tmp_ = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> elapsed = tmp_ - start_;
    for (auto &it : duration_vector_) {
      elapsed -= it;
    }
    duration_vector_.push_back(elapsed);
    return (int)duration_vector_.size();
  }

 private:
  std::string prefix_;
  std::chrono::time_point<std::chrono::system_clock> start_;
  std::chrono::time_point<std::chrono::system_clock> end_;
  std::vector<std::chrono::duration<double, std::milli>> duration_vector_;
};
