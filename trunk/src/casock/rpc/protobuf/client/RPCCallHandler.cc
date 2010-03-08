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
 * \file casock/rpc/protobuf/client/RPCCallHandler.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/client/RPCCallHandler.h"

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/api/rpc.pb.h"
#include "casock/rpc/protobuf/client/RPCCall.h"
#include "casock/rpc/protobuf/client/RPCCallQueue.h"
#include "casock/rpc/protobuf/client/RPCReaderHandler.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace client {
        using casock::rpc::protobuf::api::RpcRequest;
        using casock::rpc::protobuf::api::RpcResponse;

        RPCCallHandler::RPCCallHandler (RPCCallQueue& rCallQueue) : mrCallQueue (rCallQueue)
        {
        }

        void RPCCallHandler::run ()
        {
          while (true)
          {
            RPCCall* pCall = mrCallQueue.get ();

            RpcResponse* pRpcResponse = static_cast<RpcResponse*>(pCall->rpcResponse ());
            google::protobuf::RpcController* controller = pCall->controller ();
            google::protobuf::Closure* closure = pCall->closure ();

            LOGMSG (LOW_LEVEL, "RPCCallHandler::%s () - id [%u]\n", __FUNCTION__, pRpcResponse->id ());
            LOGMSG (LOW_LEVEL, "RPCCallHandler::%s () - type [%u]\n", __FUNCTION__, pRpcResponse->type ());

            pCall->response ()->ParseFromString (pRpcResponse->response ());

            closure->Run ();

            //pCall->lock ();
            //if (pCall->handler ())
            //  pCall->handler ()->communicator ().write (response);
            //pCall->unlock ();

            //delete response;
            //delete pCall;
          }
        }
      }
    }
  }
}
