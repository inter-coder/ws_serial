/**
 * @file ws_serial.cpp
 * @date 04.07.2017
 * @author Dusan Krstic, admin@inter-coder.com
 *
 * Copyright (c) 2017 Dusan Krstic. All rights reserved.
 * This file is part of the ws_serial for ESP8266.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#ifndef ws_serial_h
#define ws_serial_h
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>

class ws_serial{
  public:
    ws_serial();
    void init(int port);
    bool println(String text);
    bool print(String text);
    void begin();
    void _wd();
  private:
    int _port;
    void _handleHtml();      
    Ticker * _secondTick;
    WebSocketsServer * _webSocket;
    ESP8266WebServer * _server;    
};
#endif
