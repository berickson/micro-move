#include <array>

template <std::size_t joint_count>
class  MicroMove {
private:
    std::array<float, joint_count> from_;
    std::array<float, joint_count> delta_;
    bool done_ = false;

    uint32_t start_ms_;
    float duration_;

public:
    MicroMove() {}

    // returns true when movement is done
    inline bool done() {
        return done_;
    }

    // configure planned movement
    void plan(std::array<float, joint_count> from, std::array<float, joint_count> to, uint32_t start_ms, uint32_t duration) {
        from_ = from;
        for (size_t i = 0; i < joint_count; ++i) {
            delta_[i] = to[i]-from[i];
        }
        start_ms_ = start_ms;
        duration_ = (float) duration;
        done_ = false;
    }

    // returns joint positions based on time
    std::array<float, joint_count> update(uint32_t ms) {
        std::array<float, joint_count> out;
        uint32_t elapsed = ms - start_ms_;
        float p = elapsed / duration_;
        if (p < 0) p = 0;
        if (p >= 1) {
            p = 1;
            done_ = true;
        }

        for(uint32_t i=0; i < joint_count; ++i) {
            out[i]=from_[i] + p * delta_[i];
        }
        return out;
    }
};