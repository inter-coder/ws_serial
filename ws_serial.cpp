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
#include "ws_serial.h"

ws_serial::ws_serial(){
}

void ws_serial::_wd(){
	_webSocket->loop();
	delay(1000);
	_server->handleClient();
}
void ws_serial::_handleHtml(){
	String info="<!DOCTYPE HTML><HTML>\n";
	info+="<META name='viewport' content='width=device-width, initial-scale=1'>\n";	
	info+="<script>\n";
	info+="function InitWebSocket(){\n";
	info+="   websock=new WebSocket('ws://'+window.location.hostname+':"+(String)_port+"/');\n";
	info+="   document.getElementById('wd').innerHTML='';\n";
	info+="   websock.onmessage=function(evt){\n";
	info+="     JSONobj=JSON.parse(evt.data);\n";
	info+="     var p=document.createElement('p');\n";
	info+="     p.innerHTML=JSONobj.ws_serial;\n";
	info+="     document.getElementById('wd').appendChild(p);\n";
	info+="   }\n";
	info+="}\n";
	info+="   ";
	info+="\n";
	info+="</script>\n";
	info+="<body onload='InitWebSocket();'>\n";
	info+="<h1>Info debug</h1>";
	info+="<div id='wd' style='width:100%;float:left;border:solid 1px blue;height:350px;margin-bottom:25px;overflow-y: scroll;'>Loading...</div>";
	info+="</BODY>\n";
	info+="</HTML>\n";  
  _server->send(200, "text/html", info);
}

static void temp_wd(ws_serial * pom){
	pom->_wd();
}

void ws_serial::init(int port){
	_port=port+1;		
	_secondTick->attach(1,temp_wd,this);
	WebSocketsServer _webSocket=WebSocketsServer(_port);
	ESP8266WebServer _server(port);
	Serial.println(port);
}

void ws_serial::begin(){
	_webSocket->begin();
	_server->on("/", [this](){_handleHtml();});
	_server->begin();
}

bool ws_serial::println(String text){
	Serial.println(text);
	String JSONtxt="{\"ws_serial\":\""+text+"\"}";	
	_webSocket->broadcastTXT(JSONtxt);
	return true; 
}

bool ws_serial::print(String text){
	Serial.print(text);
	String JSONtxt="{\"ws_serial_\":\""+text+"\"}";
	_webSocket->broadcastTXT(JSONtxt);
	return true; 
}

