#include "casock/util/Logger.h"
#include "casock/proactor/asio/base/AsyncProcessor.h"
#include "tests/proactor/asio/SocketClient1.h"

using casock::proactor::asio::base::AsyncProcessor;

int main ()
{
  LOGGER->setDebugLevel (LOW_LEVEL);
  LOGMSG (LOW_LEVEL, "%s () - start\n", __FUNCTION__);

  AsyncProcessor::initialize ();
  AsyncProcessor* pAsyncProcessor = AsyncProcessor::getInstance ();

  try
  {
    LOGMSG (LOW_LEVEL, "%s () - creating client...\n", __FUNCTION__);
    tests::proactor::asio::SocketClient1 client (pAsyncProcessor, "localhost", "2000");

    LOGMSG (LOW_LEVEL, "%s () - asynchronously connecting...\n", __FUNCTION__);
    client.asyncConnect ();

    LOGMSG (LOW_LEVEL, "%s () - running async processor...\n", __FUNCTION__);
    pAsyncProcessor->run ();
  }
  catch (std::exception& e)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (std::exception&) - e [%s]\n", __FUNCTION__, e.what ());
  }
  catch (...)
  {
    LOGMSG (NO_DEBUG, "%s () - catch (...)\n", __FUNCTION__);
  }

  AsyncProcessor::destroy ();
}
