#ifndef TRACKER_H
#define TRACKER_H

#include "global.h"
#include "object.h"
#include "utils.h"

const float ts = 0.05;
const float max_acc = 2;
const float range_accuracy_rate = 0.05;
const float range_accuracy = 1;
const float theta_accuracy_rate = 0;
const float theta_accuracy = 1 * pi / 180;
const float velocity_accuracy_rate = 0;
const float velocity_accuracy = 2;
const float velocity_lateral_xinit = 0;
const float velocity_lateral_pinit = 30;

const int max_loss_cnt = 3;
const int min_exist_cnt = 5;

struct TrackCount
{
    int loss_cnt;
    int exist_cnt;
};

class Tracker
{
public:
    Tracker();

    void InitTrack(const RadarObject &obj);
    void RemoveTrack(int index);
    void Predict();
    void Update(std::vector<RadarObject> &src);
    void MatchNN(std::vector<RadarObject> &src);
    void EKF(std::vector<RadarObject> &src,
             std::vector<BoxObject> &dst);
    void PrintMeasurements(std::vector<RadarObject> &src);
    void PrintOutputTracks(std::vector<BoxObject> &dst);
    bool IsConverged(int track_index);

private:
    std::vector<Eigen::VectorXf> X;  // rx ry vx vy
    std::vector<Eigen::MatrixXf> P;
    std::vector<std::pair<uint64_t, TrackCount>> track_info;

    uint64_t id_cnt;

    std::vector<std::pair<int, int>> matched_pair;
    std::vector<bool> prev_matched;
    std::vector<bool> src_matched;
};

#endif // TRACKER_H
