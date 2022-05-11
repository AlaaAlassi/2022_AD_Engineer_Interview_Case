/** @file vehicle_longitudinal.cpp
 *  @brief Source file for simple longitudinal vehicle model
 */

#include "simple_acc/vehicle_longitudinal_model.hpp"

#include <cmath>

VehicleLongitudinalModel::VehicleLongitudinalModel(
    const float initial_distance, const float initial_velocity,
    const float initial_acceleration)
    : travel_distance_(initial_distance),
      velocity_(initial_velocity),
      acceleration_(initial_acceleration) {}

void VehicleLongitudinalModel::UpdateMotion(const float acceleration_setpoint) {
  // Update vehicle state using first-order acceleration response with time
  // constant of 0.5 sec and time step length of 0.1 sec.
  float travel_distance = 1.000000000000000 * travel_distance_ +
                          0.100000000000000 * velocity_ +
                          0.004682688269495 * acceleration_ +
                          0.000317311730505 * acceleration_setpoint;
  float velocity = 1.000000000000000 * velocity_ +
                   0.090634623461009 * acceleration_ +
                   0.009365376538991 * acceleration_setpoint;
  float acceleration = 0.818730753077982 * acceleration_ +
                       0.181269246922018 * acceleration_setpoint;
  travel_distance_ = travel_distance;
  velocity_ = std::fmax(velocity, 0);  // No reverse driving
  acceleration_ = acceleration;
}
