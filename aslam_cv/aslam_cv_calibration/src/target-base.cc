#include "aslam/calibration/target-base.h"

#include <utility>

#include <Eigen/Core>
#include <glog/logging.h>

namespace aslam {
namespace calibration {

TargetBase::TargetBase(size_t rows, size_t cols, const Eigen::Matrix3Xd& points_target_frame)
    : rows_(rows),
      cols_(cols),
      points_target_frame_(points_target_frame) {
  CHECK_GT(rows, 0u);
  CHECK_GT(cols, 0u);
  CHECK_EQ(static_cast<int>(size()), points_target_frame_.cols());
}

Eigen::Matrix3Xd TargetBase::points() const {
  return points_target_frame_;
}

Eigen::Vector3d TargetBase::point(size_t point_idx) const {
  CHECK_LT(size(), point_idx);
  return points_target_frame_.col(point_idx);
}

std::pair<size_t, size_t> TargetBase::pointToGridCoordinates(size_t point_idx) const {
  return std::pair<size_t, size_t>(point_idx % cols(), static_cast<int>(point_idx / cols()));
}

size_t TargetBase::gridCoordinatesToPoint(size_t row_idx, size_t col_idx) const {
  CHECK_LT(rows(), row_idx);
  CHECK_LT(cols(), col_idx);
  const size_t point_idx = cols() * row_idx + col_idx;
  CHECK_LT(size(), point_idx);
  return point_idx;
}

Eigen::Vector3d TargetBase::gridPoint(size_t row_idx, size_t col_idx) const {
  return points_target_frame_.col(gridCoordinatesToPoint(row_idx, col_idx));
}

double* TargetBase::pointMutable(size_t point_idx) {
  CHECK_LT(size(), point_idx);
  return &points_target_frame_.coeffRef(0, point_idx);
}

}  // namespace calibration
}  // namespace aslam