/* Copyright 2017-present Samsung Electronics Co., Ltd. and other contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var websocketBuiltin = process.binding(process.binding.websocket);
var util = require('util');

function Websocket()
{
}

Websocket.prototype.w3cwebsocket = function(url)
{
    var instance = new websocketBuiltin(this, url);

    var interval = setInterval(function() {
        instance.idle_(); }, 8);
    return instance;
}

Websocket.prototype.w3cwebsocket.close = function() {
    return websocketBuiltin.close();
}

Websocket.prototype.w3cwebsocket.send = function send(data)
{
    return websocketBuiltin.send(util.format.apply(this, arguments) + '\n');
}

Websocket.prototype.w3cwebsocket.idle_ = function() {
    console.log("############");
    
    return websocketBuiltin.idle_();
}

module.exports = new Websocket()
