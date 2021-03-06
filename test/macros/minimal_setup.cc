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

#include "com/centreon/engine/error.hh"
#include "com/centreon/engine/globals.hh"
#include "test/macros/minimal_setup.hh"

using namespace com::centreon::engine;

/**
 *  Setup a minimal Centreon Engine setup.
 */
void com::centreon::engine::test::minimal_setup() {
  // Add host.
  host* hst(add_host(
    1,                              // Host ID
    const_cast<char*>("myhost"),    // Name
    const_cast<char*>("MyAlias"),   // Alias
    const_cast<char*>("127.0.0.1"), // Address
    NULL,                           // Check period
    0,                              // Initial state
    1.0,                            // Check interval
    1.0,                            // Retry interval
    1,                              // Max attempts
    0,                              // Host check timeout
    const_cast<char*>("mycommand"), // Check command
    1,                              // Checks enabled
    NULL,                           // Event handler
    0,                              // Event handler enabled
    0,                              // Flap detection enabled
    0.0,                            // Low flap threshold
    0.0,                            // High flap threshold
    0,                              // Flap detection on up
    0,                              // Flap detection on down
    0,                              // Flap detection on unreachable
    0,                              // Check freshness
    0,                              // Freshness threshold
    0,                              // Should be drawn
    0,                              // Obsess over
    NULL));                         // System timezone
  if (!hst)
    throw (error() << "default host creation failed");
  host_list->has_been_checked = 1;
  host_list->last_check = time(NULL);
  config->cached_host_check_horizon(24 * 60 * 60);

  // Add service.
  service* svc(add_service(
    1,                              // Host ID
    const_cast<char*>("myhost"),    // Host name
    1,                              // Service ID
    const_cast<char*>("myservice"), // Service description
    NULL,                           // Check period
    0,                              // Initial state
    1,                              // Max attempts
    0,                              // Service check timeout
    1.0,                            // Check interval
    1.0,                            // Retry interval
    0,                              // Volatile
    NULL,                           // Event handler
    0,                              // Event handler enabled
    const_cast<char*>("mycommand"), // Check command
    1,                              // Checks enabled
    0,                              // Flap detection enabled
    0.0,                            // Low flap threshold
    0.0,                            // High flap threshold
    0,                              // Flap detection on ok
    0,                              // Flap detection on warning
    0,                              // Flap detection on unknown
    0,                              // Flap detection on critical
    0,                              // Check freshness
    0,                              // Freshness threshold
    0,                              // Obsess over service
    NULL));                         // System timezone
  if (!svc)
    throw (error() << "default service creation failed");
  service_list->host_ptr = host_list;
  if (!add_service_link_to_host(hst, svc))
    throw (error() << "could not link default service with default host");

  // Add command.
  command* cmd(add_command(
    const_cast<char*>("mycommand"),
    const_cast<char*>("true")));
  if (!cmd)
    throw (error() << "default command creation failed");

  return ;
}
