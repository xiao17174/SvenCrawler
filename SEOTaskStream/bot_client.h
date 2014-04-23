﻿/**
 * @Copyright 2014 GanJi Inc.
 * @file    ganji/crawler/octopus_crawler/GJOctClient/libs/base/src/net/bot_client.h
 * @namespace ganji::crawler::octopus_crawler::net
 * @version 1.0
 * @author  lisizhong (transport by zhangdanian)
 * @date    2014-04-02
 *
 * �Ķ��������� ��ʹ��tools/cpplint/cpplint.py ���������Ƿ����ϱ����淶!
 * ��ѭ�ı����淶���ο�: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#ifndef _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLIENT_H_
#define _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLINET_H_


#include "long_short_conn.h"
#include "gen-cpp/octopus_crawler_types.h"
#include "gen-cpp/OctopusProxyService.h"

#ifndef _WIN32
#include "ganji/ganji_global.h"
#include "ganji/util/thread/thread.h"
#include "ganji/util/thread/mutex.h"
#include "ganji/util/thread/condition.h"
#else
//#include "utils/Threading.h"
#endif

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <deque>

//using namespace ganji::crawler::octopus_crawler::downloader;
namespace net
{

using std::string;
using std::vector;
using std::queue;
using std::deque;
using boost::shared_ptr;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

//class LongShortConn<OctopusProxyServiceClient>;
template class LongShortConn<OctopusProxyServiceClient>;

class BotMessageHeader
{
public:
    int    node_id_;
    string token_;          // token
};

class BotMessageHandler
{
public:
  int  Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval);

  //bool GetBotTask(const BotTasktypes::type bot_task_type, const std::vector<BotMessage> &requests);
  /*
  bool GetBotTask(
              std::vector<BotMessage> &requests,
              const BotTasktypes::type bot_task_type,
              const NodeState& node_state
              );
  */
  bool GetBotTask(const BotTasktypes::type bot_task_type,
                  std::vector<BotMessage> &requests,
                  const NodeState& node_state);

  //bool UploadBotTask(const std::vector<BotMessage> &responses);
  bool UploadBotTask(
              const std::vector<BotMessage> &responses,
              const NodeState& node_state
              );

  OctopusProxyServiceClient * Client() {return proxy_conn_.Client();}
  bool Reset();
  void IncrTimes();
  void Lock();
  void Unlock();
  bool NeedReset();
protected:
  //LongShortConn<OctopusProxyServiceClient> proxy_conn_;
  LongShortConn<OctopusProxyServiceClient> proxy_conn_;
  string  proxy_ip_;
  int     proxy_port_;
  int     connection_timeout_;
  int     check_interval_;
};

} ///<
#endif  ///< _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLIENT_H_
