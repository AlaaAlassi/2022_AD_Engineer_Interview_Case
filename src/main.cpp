/** @file main.cpp
 *  @brief Main file for simple Adaptive Cruise Control (ACC) interview case
 */

#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

#include "simple_acc/vehicle_longitudinal_model.hpp"
#include "simple_acc/logger.hpp"

using namespace std;

int main() {
  // General parameters
  const float time_step_length = 0.1;            // (s)
  const float max_time = 80;                     // (s)
  const float set_velocity_driver = 70.0 / 3.6;  // (m/s)

  // Create longitudinal ego vehicle object
  const float initial_ego_travel_distance = 0.0;  // (m)
  const float initial_ego_velocity = 50.0 / 3.6;  // (m/s)
  const float initial_ego_acceleration = 0.0;     // (m/s^2)
  VehicleLongitudinalModel ego_vehicle(initial_ego_travel_distance,
                                       initial_ego_velocity,
                                       initial_ego_acceleration);

  // Load target vehicle data
  std::vector<float> target_vehicle_travel_distances;  // (m)
  std::vector<float> target_vehicle_velocities;        // (m/s)
  std::ifstream fin("data/target_vehicle_travel_dist_vel.dat");
  if (fin.fail()) {
    throw std::runtime_error("Could not open file.");
  }
  float travel_distance, velocity;
  while (fin >> travel_distance) {
    target_vehicle_travel_distances.push_back(travel_distance);
    fin >> velocity;
    target_vehicle_velocities.push_back(velocity);
  }

  // prepare the logger
  logger loggerObject("data/results.dat");

  //controller parameters
  float time_gap_limit = 2;
  float min_distance = 2;
  float kp=1;
  bool  cruise_control_enabled = true;
  float vel_command = 0;
  float kp_ac = 3;

  // controller input
  float acceleration_setpoint = 0;

  // Simulate driving scenario
  size_t number_of_steps = std::floor(max_time / time_step_length);
  for (int step = 0; step < number_of_steps; ++step) {
    // Update target vehicle data
    float target_vehicle_travel_distance =
        target_vehicle_travel_distances[step];
    float target_vehicle_distance =
        target_vehicle_travel_distance - ego_vehicle.travel_distance();
    float target_vehicle_velocity = target_vehicle_velocities[step];

    //================================================================
    // Acceleration setpoint calculation (insert your controller here)
    // Inputs:
    // - ego_vehicle.velocity()
    // - ego_vehicle.acceleration()
    // - target_vehicle_distance
    // - target_vehicle_velocity
    // - set_velocity_driver

    float time_gap = target_vehicle_distance / ego_vehicle.velocity();
    float safe_distance = min_distance + time_gap_limit * ego_vehicle.velocity();
    float distance_control_action = kp * (-target_vehicle_distance + safe_distance) / time_step_length;
    float vel_reference = target_vehicle_velocity - distance_control_action;

    if (target_vehicle_distance < safe_distance)
    {
      if (ego_vehicle.velocity() < set_velocity_driver)
      {
        cruise_control_enabled = false;
      }
      else
      {
        cruise_control_enabled = true;
      }
    }
    else
    {
      cruise_control_enabled = true;
    }

    if (cruise_control_enabled)
    {
      vel_command = set_velocity_driver;
    }
    else
    {
      vel_command = vel_reference;
    }

    acceleration_setpoint = kp_ac*(vel_command - ego_vehicle.velocity());

    if(acceleration_setpoint > 5){
      acceleration_setpoint = 5;
    }
    if(acceleration_setpoint < -5){
      acceleration_setpoint = -5;
    }


    // Print to console for debugging
    float time = step*time_step_length;
    /*cout << "time " << step*time_step_length;
    cout << "   ego_vel " << ego_vehicle.velocity();
    cout << "   ego_acc " << ego_vehicle.acceleration();
    cout << "   ego_acc_setpoint " << acceleration_setpoint;
    cout << "   cc " << cruise_control_enabled;
    cout << "   dist_to_target_veh " << target_vehicle_distance << endl;*/

    //call logger
    //loggerObject.log(time,ego_vehicle.velocity(),ego_vehicle.acceleration(),acceleration_setpoint,target_vehicle_distance);
    loggerObject.log("time", time);
    loggerObject.log("ego_vel", ego_vehicle.velocity());
    loggerObject.log("ego_acc", ego_vehicle.acceleration());
    loggerObject.log("ego_acc_setpoint", acceleration_setpoint);
    loggerObject.log("dist_to_target_veh", target_vehicle_distance);


    //================================================================

    // Update ego vehicle motion by one time step
    ego_vehicle.UpdateMotion(acceleration_setpoint);
  }

  loggerObject.saveLoggedData();

  return 0;
}