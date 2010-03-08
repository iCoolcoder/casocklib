/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/client/ClientSocket.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "ClientSocket.h"

#include <errno.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>

#include "casock/util/Logger.h"
#include "casock/client/CASClientException.h"

namespace casock {
  namespace client {
    ClientSocket::ClientSocket (const string& host, const unsigned int& port) : Socket (port), m_host (host)
    {
      struct hostent* p_hostent = gethostbyname (m_host.c_str ());

      if (p_hostent)
      {
        m_addr.sin_addr = *((struct in_addr *) p_hostent->h_addr);
        m_connected     = false;
      }
      else
        throw (casock::client::CASClientException (strerror (errno)));
    }

    ClientSocket::~ClientSocket ()
    {
      if (m_connected)
      {
        FileDescriptor::close ();
        m_connected = false;
      }
    }

    void ClientSocket::connect ()
    {
      LOGMSG (HIGH_LEVEL, "ClientSocket::%s () - begin\n", __FUNCTION__);

      if (m_fd > 0)
      {
        if (::connect (m_fd, (struct sockaddr *) &m_addr, sizeof (struct sockaddr_in)) == 0) 
          m_connected = true;
        else
          throw (casock::client::CASClientException (strerror (errno)));
      }

      LOGMSG (HIGH_LEVEL, "ClientSocket::%s () - end\n", __FUNCTION__);
    }

    void ClientSocket::close ()
    {
      if (m_connected)
      {
        FileDescriptor::close ();
        m_connected = false;
      }
    }
  }
}
