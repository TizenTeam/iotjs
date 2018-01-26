var https = require("https");

var options = {
  hostname: 'api.openweathermap.org',
  port: 443,
  path: '/data/2.5/weather?q=London,uk%20forecast?id=524901&APPID=c96d8df876bd744bed69e40c4fc891f7', //TODO remove key
  method: 'GET',
};

https.request(options, function (res) {
  receive(res, function (data) {
    console.log("log: received:");
    console.log(data);
  });
}).end();

function receive(incoming, callback) {
  var data = '';

  incoming.on('data', function (chunk) {
    data += chunk;
  });

  incoming.on('end', function () {
    callback ? callback(data) : '';
  });
}
