/*
** Copyright 2011-2012 Merethis
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

#include <exception>
#include <QCoreApplication>
#include <QDebug>
#include "com/centreon/engine/error.hh"
#include "com/centreon/engine/external_commands/commands.hh"
#include "com/centreon/engine/globals.hh"
#include "com/centreon/engine/logging/engine.hh"
#include "test/unittest.hh"

using namespace com::centreon::engine;

/**
 *  Run del_downtime_by_host_name test.
 */
static int check_del_downtime_by_host_name() {
  init_object_skiplists();

  host* hst = add_host("name", NULL, NULL, "localhost", NULL, 0, 0.0, 0.0, 42,
                       0, 0, 0, 0, 0, 0.0, 0.0, NULL, 0, NULL, 0, 0, NULL, 0,
                       0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL,
                       NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0.0, 0.0,
                       0.0, 0, 0, 0, 0, 0);
  if (!hst)
    throw (engine_error() << "create host failed.");

  next_downtime_id = 1;
  unsigned long downtime_id;
  scheduled_downtime_list = NULL;
  if (add_new_host_downtime("name",
                            time(NULL),
                            NULL,
                            NULL,
                            time(NULL),
                            time(NULL),
                            0,
                            0,
                            0,
                            &downtime_id) != OK)
    throw (engine_error() << "create downtime failed.");

  char const* cmd("[1317196300] DEL_DOWNTIME_BY_HOST_NAME;name");
  process_external_command(cmd);

  if (scheduled_downtime_list)
    throw (engine_error() << "del_downtime_by_host_name failed.");

  delete[] hst->name;
  delete[] hst->display_name;
  delete[] hst->alias;
  delete[] hst->address;
  delete hst;

  free_object_skiplists();

  return (0);
}

/**
 *  Init unit test.
 */
int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  unittest utest(&check_del_downtime_by_host_name);
  QObject::connect(&utest, SIGNAL(finished()), &app, SLOT(quit()));
  utest.start();
  app.exec();
  return (utest.ret());
}