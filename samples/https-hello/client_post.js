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

var http = require('https');

var message = JSON.stringify({
  greeting: 'Hello, IoT.JS!',
  answer: '',
});

var options = {
  hostname: 'httpbin.org',
  port: 443,
  path: '/post',
  method: 'POST',
  headers: {
    'Content-Length': message.length
  }
};

http.request(options, function (res) {
  receive(res, function (data) {
    console.log("log: received:");
    console.log(data);
  });
}).end(message);

function receive(incoming, callback) {
  var data = '';

  incoming.on('data', function (chunk) {
    data += chunk;
  });

  incoming.on('end', function () {
    callback ? callback(data) : '';
  });
}
