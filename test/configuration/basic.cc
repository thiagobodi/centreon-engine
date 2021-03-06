/*
** Copyright 2011-2015 Merethis
**
** This file is part of Centreon Engine.
**
** Centreon Engine is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Engine is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Engine. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <map>
#include "com/centreon/engine/error.hh"
#include "com/centreon/engine/globals.hh"
#include "com/centreon/engine/macros.hh"
#include "test/unittest.hh"

using namespace com::centreon::engine;

/**
 *  Create a random integer between min and max.
 *
 *  @param[in] min The minimum.
 *  @param[in] max The maximum.
 */
static int my_rand(int min = INT_MIN + 1, int max = INT_MAX - 1) throw() {
  return ((random() % (max - min + 1)) + min);
}

/**
 *  Create a random float between min and max.
 *
 *  @param[in] min The minimum.
 *  @param[in] max The maximum.
 */
static float my_rand(float min, float max) throw() {
  return ((max - min) * ((float)random() / (float)RAND_MAX) + min);
}

/**
 *  Get value into string.
 *
 *  @param[in] value The value to translate on string.
 *
 *  @return The value into string.
 */
template<class T> static std::string obj2str(T const& value) {
  std::ostringstream oss;
  oss << value;
  return (oss.str());
}

/**
 *  Build the resource file.
 *
 *  @param[in] resource The resource file name.
 */
static void build_resource(std::string const& resource) {
  std::ofstream ofs(resource.c_str());
  for (unsigned int i = 0; i < MAX_USER_MACROS; ++i) {
    if (my_rand(1, 5) == 5) {
      ofs << "# comment !" << std::endl;
    }

    ofs << std::string(my_rand(0, 10), ' ')
    	<< "$USER" + obj2str(i + 1) + "$"
    	<< std::string(my_rand(0, 10), ' ')
    	<< "="
    	<< std::string(my_rand(0, 10), ' ')
    	<< "USER" + obj2str(i + 1)
    	<< std::string(my_rand(0, 10), ' ')
    	<< std::endl;
  }
  ofs.close();
}

/**
 *  Build the main configuration file.
 *
 *  @param[in] mainconf The main configuration file name.
 *  @param[in] resource The resource file name.
 *
 *  @return The configuration value.
 */
static std::map<std::string, std::string> build_configuration(
                                            std::string const& mainconf,
                                            std::string const& resource) {
  std::map<std::string, std::string> var;

  std::string check_delay[] = { "n", "d", "s", "" };

  int cmd_check_interval = my_rand(-1, 10000);
  cmd_check_interval = (cmd_check_interval == 0 ? -1 : cmd_check_interval);

  std::string scd = check_delay[my_rand(0, 3)];
  if (scd == "")
    scd = obj2str(my_rand(0.1f, 10000.0f));

  std::string hcd = check_delay[my_rand(0, 3)];
  if (hcd == "")
    hcd = obj2str(my_rand(0.1f, 10000.0f));

  var["command_check_interval"] = obj2str(cmd_check_interval) + (my_rand(0, 1) ? "s" : "");
  var["resource_file"] = resource;
  var["log_file"] = "log_file.tmp";
  var["debug_level"] = obj2str(my_rand(0));
  var["debug_verbosity"] = obj2str(my_rand(0, 2));
  var["debug_file"] = "debug_file.tmp";
  var["max_debug_file_size"] = obj2str(my_rand(0));
  var["max_log_file_size"] = obj2str(my_rand(0));
  var["command_file"] = "command_file.tmp";
  var["global_host_event_handler"] = "host-event-handler";
  var["global_service_event_handler"] = "service-event-handler";
  var["ocsp_command"] = "ocsp-command";
  var["ochp_command"] = "ochp-command";
  var["use_syslog"] = obj2str(my_rand(0, 1));
  var["log_notifications"] = obj2str(my_rand(0, 1));
  var["log_service_retries"] = obj2str(my_rand(0, 1));
  var["log_host_retries"] = obj2str(my_rand(0, 1));
  var["log_event_handlers"] = obj2str(my_rand(0, 1));
  var["log_external_commands"] = obj2str(my_rand(0, 1));
  var["log_passive_checks"] = obj2str(my_rand(0, 1));
  var["log_initial_states"] = obj2str(my_rand(0, 1));
  var["retention_update_interval"] = obj2str(my_rand(0));
  var["additional_freshness_latency"] = obj2str(my_rand());
  var["obsess_over_services"] = obj2str(my_rand(0, 1));
  var["obsess_over_hosts"] = obj2str(my_rand(0, 1));
  var["service_check_timeout"] = obj2str(my_rand(1));
  var["host_check_timeout"] = obj2str(my_rand(1));
  var["event_handler_timeout"] = obj2str(my_rand(1));
  var["notification_timeout"] = obj2str(my_rand(1));
  var["ocsp_timeout"] = obj2str(my_rand(1));
  var["ochp_timeout"] = obj2str(my_rand(1));
  var["cached_host_check_horizon"] = obj2str(my_rand(0));
  var["enable_predictive_host_dependency_checks"] = obj2str(my_rand(0, 1));
  var["cached_service_check_horizon"] = obj2str(my_rand(0));
  var["enable_predictive_service_dependency_checks"] = obj2str(my_rand(0, 1));
  var["soft_state_dependencies"] = obj2str(my_rand(0, 1));
  var["enable_event_handlers"] = obj2str(my_rand(0, 1));
  var["enable_notifications"] = obj2str(my_rand(0, 1));
  var["max_concurrent_checks"] = obj2str(my_rand(0));
  var["check_result_reaper_frequency"] = obj2str(my_rand(1));
  var["service_reaper_frequency"] = var["check_result_reaper_frequency"];
  var["sleep_time"] = obj2str(my_rand(0.1f, 10000.0f));
  var["interval_length"] = obj2str(my_rand(1, 10000));
  var["check_service_freshness"] = obj2str(my_rand(0, 1));
  var["check_host_freshness"] = obj2str(my_rand(0, 1));
  var["service_freshness_check_interval"] = obj2str(my_rand(1));
  var["host_freshness_check_interval"] = obj2str(my_rand(1));
  var["time_change_threshold"] = obj2str(my_rand(6));
  var["enable_flap_detection"] = obj2str(my_rand(0, 1));
  var["low_service_flap_threshold"] = obj2str(my_rand(0.1f, 99.0f));
  var["high_service_flap_threshold"] = obj2str(my_rand(0.1f, 99.0f));
  var["low_host_flap_threshold"] = obj2str(my_rand(0.1f, 99.0f));
  var["high_host_flap_threshold"] = obj2str(my_rand(0.1f, 99.0f));
  var["use_timezone"] = "US/Mountain";
  var["event_broker_options"] = obj2str(my_rand(1));
  var["illegal_object_name_chars"] = "`~!$%^&*|'\"<>?,()";
  var["illegal_macro_output_chars"] = "`~$&|'\"<>";
  var["broker_module"] = "module argument";
  var["external_command_buffer_slots"] = obj2str(my_rand());

  std::ofstream ofs(mainconf.c_str());
  for (std::map<std::string, std::string>::const_iterator
         it(var.begin()),
         end(var.end());
       it != end; ++it) {
    if (my_rand(1, 5) == 5) {
      ofs << "# comment !" << std::endl;
    }
    ofs << std::string(my_rand(0, 10), ' ')
	<< it->first
	<< std::string(my_rand(0, 10), ' ')
	<< "="
	<< std::string(my_rand(0, 10), ' ')
	<< it->second
	<< std::string(my_rand(0, 10), ' ')
	<< std::endl;
  }
  ofs.close();

  build_resource(resource);

  return (var);
}

/**
 *  Test the configuration file.
 *
 *  @param[in] filename The configuration file name.
 *  @param[in] my_conf  The configuration value.
 */
void test_configuration(
       std::string const& filename,
       std::map<std::string, std::string>& my_conf) {
  config->parse(filename);

  std::string check_delay[] = { "n", "d", "s", "" };

  if (my_conf["debug_level"] != obj2str(config->debug_level())) {
    throw (engine_error() << "debug_level: init with '" << my_conf["debug_level"] << "'");
  }
  if (my_conf["debug_verbosity"] != obj2str(config->debug_verbosity())) {
    throw (engine_error() << "debug_verbosity: init with '" << my_conf["debug_verbosity"] << "'");
  }
  if (my_conf["max_debug_file_size"] != obj2str(config->max_debug_file_size())) {
    throw (engine_error() << "max_debug_file_size: init with '" << my_conf["max_debug_file_size"] << "'");
  }
  if (my_conf["max_log_file_size"] != obj2str(config->max_log_file_size())) {
    throw (engine_error() << "max_log_file_size: init with '" << my_conf["max_log_file_size"] << "'");
  }
  if (my_conf["use_syslog"] != obj2str(config->use_syslog())) {
    throw (engine_error() << "use_syslog: init with '" << my_conf["use_syslog"] << "'");
  }
  if (my_conf["log_notifications"] != obj2str(config->log_notifications())) {
    throw (engine_error() << "log_notifications: init with '" << my_conf["log_notifications"] << "'");
  }
  if (my_conf["log_service_retries"] != obj2str(config->log_service_retries())) {
    throw (engine_error() << "log_service_retries: init with '" << my_conf["log_service_retries"] << "'");
  }
  if (my_conf["log_host_retries"] != obj2str(config->log_host_retries())) {
    throw (engine_error() << "log_host_retries: init with '" << my_conf["log_host_retries"] << "'");
  }
  if (my_conf["log_event_handlers"] != obj2str(config->log_event_handlers())) {
    throw (engine_error() << "log_event_handlers: init with '" << my_conf["log_event_handlers"] << "'");
  }
  if (my_conf["log_external_commands"] != obj2str(config->log_external_commands())) {
    throw (engine_error() << "log_external_commands: init with '" << my_conf["log_external_commands"] << "'");
  }
  if (my_conf["log_passive_checks"] != obj2str(config->log_passive_checks())) {
    throw (engine_error() << "log_passive_checks: init with '" << my_conf["log_passive_checks"] << "'");
  }
  if (my_conf["log_initial_states"] != obj2str(config->log_initial_states())) {
    throw (engine_error() << "log_initial_states: init with '" << my_conf["log_initial_states"] << "'");
  }
  if (my_conf["retention_update_interval"] != obj2str(config->retention_update_interval())) {
    throw (engine_error() << "retention_update_interval: init with '" << my_conf["retention_update_interval"] << "'");
  }
  if (my_conf["additional_freshness_latency"] != obj2str(config->additional_freshness_latency())) {
    throw (engine_error() << "additional_freshness_latency: init with '" << my_conf["additional_freshness_latency"] << "'");
  }
  if (my_conf["obsess_over_services"] != obj2str(config->obsess_over_services())) {
    throw (engine_error() << "obsess_over_services: init with '" << my_conf["obsess_over_services"] << "'");
  }
  if (my_conf["obsess_over_hosts"] != obj2str(config->obsess_over_hosts())) {
    throw (engine_error() << "obsess_over_hosts: init with '" << my_conf["obsess_over_hosts"] << "'");
  }
  if (my_conf["service_check_timeout"] != obj2str(config->service_check_timeout())) {
    throw (engine_error() << "service_check_timeout: init with '" << my_conf["service_check_timeout"] << "'");
  }
  if (my_conf["host_check_timeout"] != obj2str(config->host_check_timeout())) {
    throw (engine_error() << "host_check_timeout: init with '" << my_conf["host_check_timeout"] << "'");
  }
  if (my_conf["event_handler_timeout"] != obj2str(config->event_handler_timeout())) {
    throw (engine_error() << "event_handler_timeout: init with '" << my_conf["event_handler_timeout"] << "'");
  }
  if (my_conf["notification_timeout"] != obj2str(config->notification_timeout())) {
    throw (engine_error() << "notification_timeout: init with '" << my_conf["notification_timeout"] << "'");
  }
  if (my_conf["ocsp_timeout"] != obj2str(config->ocsp_timeout())) {
    throw (engine_error() << "ocsp_timeout: init with '" << my_conf["ocsp_timeout"] << "'");
  }
  if (my_conf["ochp_timeout"] != obj2str(config->ochp_timeout())) {
    throw (engine_error() << "ochp_timeout: init with '" << my_conf["ochp_timeout"] << "'");
  }
  if (my_conf["cached_host_check_horizon"] != obj2str(config->cached_host_check_horizon())) {
    throw (engine_error() << "cached_host_check_horizon: init with '" << my_conf["cached_host_check_horizon"] << "'");
  }
  if (my_conf["enable_predictive_host_dependency_checks"] != obj2str(config->enable_predictive_host_dependency_checks())) {
    throw (engine_error() << "enable_predictive_host_dependency_checks: init with '" << my_conf["enable_predictive_host_dependency_checks"] << "'");
  }
  if (my_conf["cached_service_check_horizon"] != obj2str(config->cached_service_check_horizon())) {
    throw (engine_error() << "cached_service_check_horizon: init with '" << my_conf["cached_service_check_horizon"] << "'");
  }
  if (my_conf["enable_predictive_service_dependency_checks"] != obj2str(config->enable_predictive_service_dependency_checks())) {
    throw (engine_error() << "enable_predictive_service_dependency_checks: init with '" << my_conf["enable_predictive_service_dependency_checks"] << "'");
  }
  if (my_conf["soft_state_dependencies"] != obj2str(config->soft_state_dependencies())) {
    throw (engine_error() << "soft_state_dependencies: init with '" << my_conf["soft_state_dependencies"] << "'");
  }
  if (my_conf["enable_event_handlers"] != obj2str(config->enable_event_handlers())) {
    throw (engine_error() << "enable_event_handlers: init with '" << my_conf["enable_event_handlers"] << "'");
  }
  if (my_conf["enable_notifications"] != obj2str(config->enable_notifications())) {
    throw (engine_error() << "enable_notifications: init with '" << my_conf["enable_notifications"] << "'");
  }
  if (my_conf["max_concurrent_checks"] != obj2str(config->max_parallel_service_checks())) {
    throw (engine_error() << "max_concurrent_checks: init with '" << my_conf["max_concurrent_checks"] << "'");
  }
  if (my_conf["check_result_reaper_frequency"] != obj2str(config->check_reaper_interval())) {
    throw (engine_error() << "check_result_reaper_frequency: init with '" << my_conf["check_result_reaper_frequency"] << "'");
  }
  if (my_conf["service_reaper_frequency"] != obj2str(config->check_reaper_interval())) {
    throw (engine_error() << "service_reaper_frequency: init with '" << my_conf["service_reaper_frequency"] << "'");
  }
  if (my_conf["sleep_time"] != obj2str(config->sleep_time())) {
    throw (engine_error() << "sleep_time: init with '" << my_conf["sleep_time"] << "'");
  }
  if (my_conf["interval_length"] != obj2str(config->interval_length())) {
    throw (engine_error() << "interval_length: init with '" << my_conf["interval_length"] << "'");
  }
  if (my_conf["check_service_freshness"] != obj2str(config->check_service_freshness())) {
    throw (engine_error() << "check_service_freshness: init with '" << my_conf["check_service_freshness"] << "'");
  }
  if (my_conf["check_host_freshness"] != obj2str(config->check_host_freshness())) {
    throw (engine_error() << "check_host_freshness: init with '" << my_conf["check_host_freshness"] << "'");
  }
  if (my_conf["service_freshness_check_interval"] != obj2str(config->service_freshness_check_interval())) {
    throw (engine_error() << "service_freshness_check_interval: init with '" << my_conf["service_freshness_check_interval"] << "'");
  }
  if (my_conf["host_freshness_check_interval"] != obj2str(config->host_freshness_check_interval())) {
    throw (engine_error() << "host_freshness_check_interval: init with '" << my_conf["host_freshness_check_interval"] << "'");
  }
  if (my_conf["time_change_threshold"] != obj2str(config->time_change_threshold())) {
    throw (engine_error() << "time_change_threshold: init with '" << my_conf["time_change_threshold"] << "'");
  }
  if (my_conf["enable_flap_detection"] != obj2str(config->enable_flap_detection())) {
    throw (engine_error() << "enable_flap_detection: init with '" << my_conf["enable_flap_detection"] << "'");
  }
  if (my_conf["low_service_flap_threshold"] != obj2str(config->low_service_flap_threshold())) {
    throw (engine_error() << "low_service_flap_threshold: init with '" << my_conf["low_service_flap_threshold"] << "'");
  }
  if (my_conf["high_service_flap_threshold"] != obj2str(config->high_service_flap_threshold())) {
    throw (engine_error() << "high_service_flap_threshold: init with '" << my_conf["high_service_flap_threshold"] << "'");
  }
  if (my_conf["low_host_flap_threshold"] != obj2str(config->low_host_flap_threshold())) {
    throw (engine_error() << "low_host_flap_threshold: init with '" << my_conf["low_host_flap_threshold"] << "'");
  }
  if (my_conf["high_host_flap_threshold"] != obj2str(config->high_host_flap_threshold())) {
    throw (engine_error() << "high_host_flap_threshold: init with '" << my_conf["high_host_flap_threshold"] << "'");
  }
  if (my_conf["event_broker_options"] != obj2str(config->event_broker_options())) {
    throw (engine_error() << "event_broker_options: init with '" << my_conf["event_broker_options"] << "'");
  }
  if (my_conf["external_command_buffer_slots"] != obj2str(config->external_command_buffer_slots())) {
    throw (engine_error() << "external_command_buffer_slots: init with '" << my_conf["external_command_buffer_slots"] << "'");
  }
  if (my_conf["debug_file"] != config->debug_file()) {
    throw (engine_error() << "debug_file: init with '" << my_conf["debug_file"] << "'");
  }
  if (my_conf["command_file"] != config->command_file()) {
    throw (engine_error() << "command_file: init with '" << my_conf["command_file"] << "'");
  }
  if (my_conf["global_host_event_handler"] != config->global_host_event_handler()) {
    throw (engine_error() << "global_host_event_handler: init with '" << my_conf["global_host_event_handler"] << "'");
  }
  if (my_conf["global_service_event_handler"] != config->global_service_event_handler()) {
    throw (engine_error() << "global_service_event_handler: init with '" << my_conf["global_service_event_handler"] << "'");
  }
  if (my_conf["ocsp_command"] != config->ocsp_command()) {
    throw (engine_error() << "ocsp_command: init with '" << my_conf["ocsp_command"] << "'");
  }
  if (my_conf["ochp_command"] != config->ochp_command()) {
    throw (engine_error() << "ochp_command: init with '" << my_conf["ochp_command"] << "'");
  }
  if (my_conf["log_file"] != config->log_file()) {
    throw (engine_error() << "log_file: init with '" << my_conf["log_file"] << "'");
  }
  if (my_conf["illegal_object_name_chars"] != config->illegal_object_chars()) {
    throw (engine_error() << "illegal_object_name_chars: init with '" << my_conf["illegal_object_name_chars"] << "'");
  }
  if (my_conf["illegal_macro_output_chars"] != config->illegal_output_chars()) {
    throw (engine_error() << "illegal_macro_output_chars: init with '" << my_conf["illegal_macro_output_chars"] << "'");
  }
  if (my_conf["command_check_interval"] != obj2str(config->command_check_interval() / config->interval_length()) &&
      my_conf["command_check_interval"] != obj2str(config->command_check_interval()) + "s") {
    throw (engine_error() << "command_check_interval: init with '" << my_conf["command_check_interval"] << "'");
  }

  nagios_macros* mac = get_global_macros();

  for (unsigned int i = 0; i < MAX_USER_MACROS; ++i) {
    if (macro_user[i] != "USER" + obj2str(i + 1)) {
      throw (engine_error() << "resource_file: init with '" << macro_user[i] << "'");
    }
  }
}

/**
 *  Check the configuration working.
 */
int main_test(int argc, char** argv) {
  (void)argc;
  (void)argv;

  // Initialize random number generation.
  srandom(time(NULL));

  // Generate temporary file names.
  char const* mainconf_path_ptr(tmpnam(NULL));
  if (!mainconf_path_ptr)
    throw (engine_error() << "generate temporary file failed");
  std::string mainconf_path(mainconf_path_ptr);

  char const* resource_path_ptr(tmpnam(NULL));
  if (!resource_path_ptr)
    throw (engine_error() << "generate temporary file failed");
  std::string resource_path(resource_path_ptr);

  // Test.
  try {
    std::map<std::string, std::string>
      my_conf(build_configuration(mainconf_path, resource_path));
    test_configuration(mainconf_path, my_conf);
  }

  // Remove temporary files.
  catch (...) {
    remove(mainconf_path.c_str());
    remove(resource_path.c_str());
    throw ;
  }
  remove(mainconf_path.c_str());
  remove(resource_path.c_str());

  return (0);
}

/**
 *  Init unit test.
 */
int main(int argc, char** argv) {
  unittest utest(argc, argv, &main_test);
  return (utest.run());
}
