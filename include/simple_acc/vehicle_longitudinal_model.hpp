/** @file vehicle_longitudinal_model.hpp
 *  @brief Header file for simple longitudinal vehicle motion model
 */

#ifndef SIMPLE_ACC__VEHICLE_LONGITUDINAL_MODEL_HPP_
#define SIMPLE_ACC__VEHICLE_LONGITUDINAL_MODEL_HPP_

/**
 * @brief Class for simple longitudinal vehicle motion model
 *
 */
class VehicleLongitudinalModel {
 public:
  /**
   * @brief Constructs a new Longitudinal Vehicle Model object and initializes
   * motion state member variables
   *
   * @param[in] initial_travel_distance  (m)     Initial travel distance of
   * vehicle
   * @param[in] initial_velocity         (m/s)   Initial velocity of vehicle
   * @param[in] initial_acceleration     (m/s^2) Initial acceleration of vehicle
   */
  VehicleLongitudinalModel(const float initial_travel_distance,
                           const float initial_velocity,
                           const float initial_acceleration);
  /**
   * @brief Updates the vehicle motion state member variables
   * @details Calculates the travel distance, velocity and acceleration of the
   * vehicle after applying an acceleration_setpoint for one time step (100 ms).
   * @param[in] acceleration_setpoint (m/s^2) Acceleration setpoint for
   * first-order acceleration response model
   */
  void UpdateMotion(const float acceleration_setpoint);

  /// Accessor for member variable
  inline float travel_distance() const { return travel_distance_; }
  /// Accessor for member variable
  inline float velocity() const { return velocity_; }
  /// Accessor for member variable
  inline float acceleration() const { return acceleration_; }

 private:
  /// (m) Travel distance of vehicle
  float travel_distance_;
  /// (m/s) Velocity of vehicle
  float velocity_;
  /// (m/s^2) Acceleration of vehicle
  float acceleration_;
};

#endif  // SIMPLE_ACC__VEHICLE_LONGITUDINAL_MODEL_HPP_