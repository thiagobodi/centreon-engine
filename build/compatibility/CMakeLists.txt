##
## Copyright 2011-2015 Merethis
##
## This file is part of Centreon Engine.
##
## Centreon Engine is free software: you can redistribute it and/or
## modify it under the terms of the GNU General Public License version 2
## as published by the Free Software Foundation.
##
## Centreon Engine is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Centreon Engine. If not, see
## <http://www.gnu.org/licenses/>.
##

# Set directories.
set(SRC_DIR "${SRC_DIR}/compatibility")
set(INC_DIR "${INC_DIR}/compatibility")

# Configure files.
configure_file("${INC_DIR}/locations.h.in"
  "${INC_DIR}/locations.h")

# Set files.
set(
  FILES
  ${FILES}

  # Sources.
  "${SRC_DIR}/find.cc"
  "${SRC_DIR}/logging.cc"
  "${SRC_DIR}/mmap.cc"

  # Headers.
  "${INC_DIR}/broker.h"
  "${INC_DIR}/config.h"
  "${INC_DIR}/find.hh"
  "${INC_DIR}/locations.h"
  "${INC_DIR}/logging.h"
  "${INC_DIR}/macros.h"
  "${INC_DIR}/mmap.h"
  "${INC_DIR}/nagios.h"
  "${INC_DIR}/nebcallbacks.h"
  "${INC_DIR}/neberrors.h"
  "${INC_DIR}/nebmods.h"
  "${INC_DIR}/nebmodules.h"
  "${INC_DIR}/nebstructs.h"
  "${INC_DIR}/netutils.h"
  "${INC_DIR}/objects.h"
  "${INC_DIR}/shared.h"
  "${INC_DIR}/sretention.h"
  "${INC_DIR}/statusdata.h"
  "${INC_DIR}/xcddefault.h"
  "${INC_DIR}/xdddefault.h"
  "${INC_DIR}/xodtemplate.h"
  "${INC_DIR}/xrddefault.h"
  "${INC_DIR}/xsddefault.h"

  PARENT_SCOPE
)

# Install header files for development.
install(DIRECTORY "${INC_DIR}"
  DESTINATION "${PREFIX_INC}"
  COMPONENT "development"
  FILES_MATCHING PATTERN "*.h")
