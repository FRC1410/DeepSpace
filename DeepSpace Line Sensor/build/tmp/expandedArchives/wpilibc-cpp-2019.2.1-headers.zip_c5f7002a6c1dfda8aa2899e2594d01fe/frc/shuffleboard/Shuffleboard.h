/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <wpi/StringRef.h>

#include "frc/shuffleboard/RecordingController.h"
#include "frc/shuffleboard/ShuffleboardEventImportance.h"
#include "frc/shuffleboard/ShuffleboardInstance.h"

namespace frc {

class ShuffleboardTab;

/**
 * The Shuffleboard class provides a mechanism with which data can be added and
 * laid out in the Shuffleboard dashboard application from a robot program. Tabs
 * and layouts can be specified, as well as choosing which widgets to display
 * with and setting properties of these widgets; for example, programmers can
 * specify a specific {@code boolean} value to be displayed with a toggle button
 * instead of the default colored box, or set custom colors for that box.
 *
 * For example, displaying a boolean entry with a toggle button:
 * <pre>{@code
 * NetworkTableEntry myBoolean = Shuffleboard.getTab("Example Tab")
 *   .add("My Boolean", false)
 *   .withWidget("Toggle Button")
 *   .getEntry();
 * }</pre>
 *
 * Changing the colors of the boolean box:
 * <pre>{@code
 * NetworkTableEntry myBoolean = Shuffleboard.getTab("Example Tab")
 *   .add("My Boolean", false)
 *   .withWidget("Boolean Box")
 *   .withProperties(Map.of("colorWhenTrue", "green", "colorWhenFalse",
 * "maroon")) .getEntry();
 * }</pre>
 *
 * Specifying a parent layout. Note that the layout type must <i>always</i> be
 * specified, even if the layout has already been generated by a previously
 * defined entry.
 * <pre>{@code
 * NetworkTableEntry myBoolean = Shuffleboard.getTab("Example Tab")
 *   .getLayout("List", "Example List")
 *   .add("My Boolean", false)
 *   .withWidget("Toggle Button")
 *   .getEntry();
 * }</pre>
 * </p>
 *
 * Teams are encouraged to set up shuffleboard layouts at the start of the robot
 * program.
 */
class Shuffleboard final {
 public:
  /**
   * The name of the base NetworkTable into which all Shuffleboard data will be
   * added.
   */
  static constexpr const char* kBaseTableName = "/Shuffleboard";

  /**
   * Updates all the values in Shuffleboard. Iterative and timed robots are
   * pre-configured to call this method in the main robot loop; teams using
   * custom robot base classes, or subclass SampleRobot, should make sure to
   * call this repeatedly to keep data on the dashboard up to date.
   */
  static void Update();

  /**
   * Gets the Shuffleboard tab with the given title, creating it if it does not
   * already exist.
   *
   * @param title the title of the tab
   * @return the tab with the given title
   */
  static ShuffleboardTab& GetTab(wpi::StringRef title);

  /**
   * Selects the tab in the dashboard with the given index in the range
   * [0..n-1], where <i>n</i> is the number of tabs in the dashboard at the time
   * this method is called.
   *
   * @param index the index of the tab to select
   */
  static void SelectTab(int index);

  /**
   * Selects the tab in the dashboard with the given title.
   *
   * @param title the title of the tab to select
   */
  static void SelectTab(wpi::StringRef title);

  /**
   * Enables user control of widgets containing actuators: speed controllers,
   * relays, etc. This should only be used when the robot is in test mode.
   * IterativeRobotBase and SampleRobot are both configured to call this method
   * when entering test mode; most users should not need to use this method
   * directly.
   */
  static void EnableActuatorWidgets();

  /**
   * Disables user control of widgets containing actuators. For safety reasons,
   * actuators should only be controlled while in test mode. IterativeRobotBase
   * and SampleRobot are both configured to call this method when exiting in
   * test mode; most users should not need to use this method directly.
   */
  static void DisableActuatorWidgets();

  /**
   * Starts data recording on the dashboard. Has no effect if recording is
   * already in progress.
   */
  static void StartRecording();

  /**
   * Stops data recording on the dashboard. Has no effect if no recording is in
   * progress.
   */
  static void StopRecording();

  /**
   * Sets the file name format for new recording files to use. If recording is
   * in progress when this method is called, it will continue to use the same
   * file. New recordings will use the format.
   *
   * <p>To avoid recording files overwriting each other, make sure to use unique
   * recording file names. File name formats accept templates for inserting the
   * date and time when the recording started with the {@code ${date}} and
   * {@code ${time}} templates, respectively. For example, the default format is
   * {@code "recording-${time}"} and recording files created with it will have
   * names like {@code "recording-2018.01.15.sbr"}. Users are
   * <strong>strongly</strong> recommended to use the {@code ${time}} template
   * to ensure unique file names.
   * </p>
   *
   * @param format the format for the
   */
  static void SetRecordingFileNameFormat(wpi::StringRef format);

  /**
   * Clears the custom name format for recording files. New recordings will use
   * the default format.
   *
   * @see #setRecordingFileNameFormat(String)
   */
  static void ClearRecordingFileNameFormat();

  /**
   * Notifies Shuffleboard of an event. Events can range from as trivial as a
   * change in a command state to as critical as a total power loss or component
   * failure. If Shuffleboard is recording, the event will also be recorded.
   *
   * <p>If {@code name} is {@code null} or empty, no event will be sent and an
   * error will be printed to the driver station.
   *
   * @param name        the name of the event
   * @param description a description of the event
   * @param importance  the importance of the event
   */
  static void AddEventMarker(wpi::StringRef name, wpi::StringRef description,
                             ShuffleboardEventImportance importance);

  /**
   * Notifies Shuffleboard of an event. Events can range from as trivial as a
   * change in a command state to as critical as a total power loss or component
   * failure. If Shuffleboard is recording, the event will also be recorded.
   *
   * <p>If {@code name} is {@code null} or empty, no event will be sent and an
   * error will be printed to the driver station.
   *
   * @param name        the name of the event
   * @param importance  the importance of the event
   */
  static void AddEventMarker(wpi::StringRef name,
                             ShuffleboardEventImportance importance);

 private:
  static detail::ShuffleboardInstance& GetInstance();
  static detail::RecordingController& GetRecordingController();

  // TODO usage reporting

  Shuffleboard() = default;
};

}  // namespace frc

// Make use of references returned by member functions usable
#include "frc/shuffleboard/ShuffleboardTab.h"
